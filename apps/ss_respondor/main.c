/*! ---------------------------------------------------------------------------
 *  @file    main.c
 *  @brief   Single-sided two-way ranging (SS TWR) responder example code
 *
 *           This is a simple code example which acts as the responder in a 
 *           SS TWR distance measurement exchange. This application waits for 
 *           a "poll" message (recording the RX time-stamp of the poll) 
 *           expected from the "SS TWR initiator" example code (companion to
 *           this application), and then sends a "response" message to complete
 *           the exchange. The response message contains all the time-stamps
 *           recorded by this application, including the calculated/predicted 
 *           TX time-stamp for the response message itself. The companion 
 *           "SS TWR initiator" example application works out the time-of-flight
 *           over-the-air and, thus, the estimated distance between the two 
 *           devices.
 *
 * @attention
 *
 * Copyright 2015 (c) Decawave Ltd, Dublin, Ireland.
 * Copyright 2019 (c) Frederic Mes, RTLOC.
 *
 * All rights reserved.
 *
 * @author Decawave
 */
#include <string.h>

#include "deca_device_api.h"
#include "deca_regs.h"
#include "deca_spi.h"
#include "port.h"

// zephyr includes
#include <zephyr.h>
#include <sys/printk.h>

/* Example application name and version to display on console. */
#define APP_NAME "SS TWR RESP v1.3\n"

static dwt_config_t config = {
  5,                /* Channel number. */
  DWT_PRF_64M,      /* Pulse repetition frequency. */
  DWT_PLEN_128,     /* Preamble length. Used in TX only. */
  DWT_PAC8,         /* Preamble acquisition chunk size. Used in RX only. */
  10,               /* TX preamble code. Used in TX only. */
  10,               /* RX preamble code. Used in RX only. */
  0,                /* 0 to use standard SFD, 1 to use non-standard SFD. */
  DWT_BR_6M8,       /* Data rate. */
  DWT_PHRMODE_STD,  /* PHY header mode. */
  (129 + 8 - 8)     /* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only. */
};

/* Default antenna delay values for 64 MHz PRF. See NOTE 2 below. */
#define TX_ANT_DLY 16456
#define RX_ANT_DLY 16456

#define RNG_DELAY_MS 2
int my_id = 3; //1, 2, 3, 4
#define SOURCE_IDX 8
#define DEST_IDX 6
/* Frames used in the ranging process. See NOTE 3 below. */
static uint8 rx_poll_msg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'W', 'A', 'V', 'E', 0xE0, 0, 0};
static uint8 tx_resp_msg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'V', 'E', 'W', 'A', 0xE1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* Length of the common part of the message (up to and including the function code, 
 * see NOTE 3 below. 
 */
#define ALL_MSG_COMMON_LEN 10

/* Index to access some of the fields in the frames involved in the process. */
#define ALL_MSG_SN_IDX 2
#define RESP_MSG_POLL_RX_TS_IDX 10
#define RESP_MSG_RESP_TX_TS_IDX 14
#define RESP_MSG_TS_LEN 4

/* Frame sequence number, incremented after each transmission. */
static uint8 frame_seq_nb = 0;

/* Buffer to store received messages.
 * Its size is adjusted to longest frame that this example code is 
 * supposed to handle.
 */
#define RX_BUF_LEN 24
static uint8 rx_buffer[RX_BUF_LEN];

/* Hold copy of status register state here for reference so that it can 
* be examined at a debug breakpoint.
*/
static uint32 status_reg = 0;

/* UWB microsecond (uus) to device time unit (dtu, around 15.65 ps) c
 * onversion factor.
 * 1 uus = 512 / 499.2 usec and 1 usec = 499.2 * 128 dtu.
 */
#define UUS_TO_DWT_TIME 65536

/* Delay between frames, in UWB microseconds. See NOTE 1 below. */
#define POLL_RX_TO_RESP_TX_DLY_UUS 1100
#define RESP_TX_TO_FINAL_RX_DLY_UUS 500

/* Timestamps of frames transmission/reception.
 * As they are 40-bit wide, we need to define a 64-bit int type to handle them.
 */
typedef signed long long int64;
typedef unsigned long long uint64;
static uint64 poll_rx_ts;
static uint64 resp_tx_ts;

/* Declaration of static functions. */
static uint64 get_rx_timestamp_u64(void);
static void resp_msg_set_ts(uint8 *ts_field, const uint64 ts);


int main(void)
{
    /* Display application name on console. */
    printk(APP_NAME);

    /* Configure DW1000 SPI */
    openspi();

    /* Reset and initialise DW1000.
     * For initialisation, DW1000 clocks must be temporarily set to crystal speed.
     * After initialisation SPI rate can be increased for optimum performance.
     */
    
    /* Target specific drive of RSTn line into DW1000 low for a period. */
    reset_DW1000();

    port_set_dw1000_slowrate();
    if (dwt_initialise(DWT_LOADUCODE) == DWT_ERROR) {
        printk("INIT FAILED");
        k_sleep(K_MSEC(500)); // allow logging to run.
        while (1) { };
    }

    port_set_dw1000_fastrate();

    /* Configure DW1000. See NOTE 5 below. */
    dwt_configure(&config);

    /* Configure DW1000 LEDs */
    dwt_setleds(1);
    
    /* Apply default antenna delay value. See NOTE 2 below. */
    dwt_setrxantennadelay(RX_ANT_DLY);
    dwt_settxantennadelay(TX_ANT_DLY);

    dwt_setrxtimeout(0);
    //k_yield();

    /* Loop forever responding to ranging requests. */
    while (1) {
        tx_resp_msg[SOURCE_IDX] = my_id;
        /* Activate reception immediately. */
        dwt_rxenable(DWT_START_RX_IMMEDIATE);

        /* Poll for reception of a frame or error/timeout. See NOTE 6 below. */
        while (!((status_reg = dwt_read32bitreg(SYS_STATUS_ID)) & 
               (SYS_STATUS_RXFCG | SYS_STATUS_ALL_RX_ERR)))
        { };

        if (status_reg & SYS_STATUS_RXFCG) {

            uint32 frame_len;

            // printk("received frame\n");

            /* Clear good RX frame event in the DW1000 status register. */
            dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_RXFCG);

            /* A frame has been received, read it into the local buffer. */
            frame_len = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFL_MASK_1023;
            if (frame_len <= RX_BUFFER_LEN) {
                dwt_readrxdata(rx_buffer, frame_len, 0);
            }

            /* Check that the frame is a poll sent by "SS TWR initiator" example.
             * As the sequence number field of the frame is not relevant, 
             * it is cleared to simplify the validation of the frame.
             */
            rx_buffer[ALL_MSG_SN_IDX] = 0;
            
            // if (memcmp(rx_buffer, rx_poll_msg, ALL_MSG_COMMON_LEN) == 0) {
            if((rx_buffer[DEST_IDX-1]=='W') && ( rx_buffer[DEST_IDX] == my_id)) {
                uint32 resp_tx_time;
                int ret;

                /* Retrieve poll reception timestamp. */
                poll_rx_ts = get_rx_timestamp_u64();

                /* Compute final message transmission time. See NOTE 7 below. */
                resp_tx_time = (poll_rx_ts + 
                    (POLL_RX_TO_RESP_TX_DLY_UUS * UUS_TO_DWT_TIME)) >> 8;

                dwt_setdelayedtrxtime(resp_tx_time);

                /* Response TX timestamp is the transmission time we 
                 * programmed plus the antenna delay.
                 */
                resp_tx_ts = (((uint64)(resp_tx_time & 0xFFFFFFFEUL)) << 8) + TX_ANT_DLY;

                /* Write all timestamps in the final message. See NOTE 8 below. */
                resp_msg_set_ts(&tx_resp_msg[RESP_MSG_POLL_RX_TS_IDX], poll_rx_ts);
                resp_msg_set_ts(&tx_resp_msg[RESP_MSG_RESP_TX_TS_IDX], resp_tx_ts);

                /* Write and send the response message. See NOTE 9 below. */
                tx_resp_msg[ALL_MSG_SN_IDX] = frame_seq_nb;
                tx_resp_msg[DEST_IDX] = rx_buffer[SOURCE_IDX];

                 /* Zero offset in TX buffer. */
                dwt_writetxdata(sizeof(tx_resp_msg), tx_resp_msg, 0);

                /* Zero offset in TX buffer, ranging. */
                dwt_writetxfctrl(sizeof(tx_resp_msg), 0, 1); 
                ret = dwt_starttx(DWT_START_TX_DELAYED);

                /* If dwt_starttx() returns an error, abandon this ranging 
                 * exchange and proceed to the next one. See NOTE 10 below. 
                 */
                if (ret == DWT_SUCCESS) {

                    /* Poll DW1000 until TX frame sent event set. 
                     * See NOTE 6 below.
                     */
                    while (!(dwt_read32bitreg(SYS_STATUS_ID) & SYS_STATUS_TXFRS))
                    { };

                    /* Clear TXFRS event. */
                    dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_TXFRS);

                    /* Increment frame sequence number after transmission of 
                     * the poll message (modulo 256).
                     */
                    frame_seq_nb++;
                }
                else{
                    dwt_rxreset();
                }
            }
        }
        else {
            /* Clear RX error events in the DW1000 status register. */
            dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_ALL_RX_ERR);

            /* Reset RX to properly reinitialise LDE operation. */
            dwt_rxreset();
        }
        Sleep(RNG_DELAY_MS);
    }

    return 1;
}

/*! --------------------------------------------------------------------------
 * @fn get_rx_timestamp_u64()
 *
 * @brief Get the RX time-stamp in a 64-bit variable.
 *        /!\ This function assumes that length of time-stamps is 40 bits, 
 *        for both TX and RX!
 *
 * @param  none
 *
 * @return  64-bit value of the read time-stamp.
 */
static uint64 get_rx_timestamp_u64(void)
{
    uint8 ts_tab[5];
    uint64 ts = 0;
    int i;
    dwt_readrxtimestamp(ts_tab);
    for (i = 4; i >= 0; i--)
    {
        ts <<= 8;
        ts |= ts_tab[i];
    }
    return ts;
}

/*! --------------------------------------------------------------------------
 * @fn final_msg_set_ts()
 *
 * @brief Fill a given timestamp field in the response message with the 
 *        given value. In the timestamp fields of the response message, 
 *        the least significant byte is at the lower address.
 *
 * @param  ts_field  pointer on the first byte of the timestamp field to fill
 *         ts  timestamp value
 *
 * @return none
 */
static void resp_msg_set_ts(uint8 *ts_field, const uint64 ts)
{
    for (int i = 0; i < RESP_MSG_TS_LEN; i++) {
        ts_field[i] = (ts >> (i * 8)) & 0xFF;
    }
}

