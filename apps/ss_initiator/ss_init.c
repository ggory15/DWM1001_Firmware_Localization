
#include "ss_init.h"
#define APP_NAME "SS TWR INIT v1.4\n"

/* Inter-ranging delay period, in milliseconds. */
#define RNG_DELAY_MS 2

/* Default communication configuration. */
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
#define TX_ANT_DLY 16300
#define RX_ANT_DLY 16456	

int my_id = 0;
// int resp_id = 1;
#define NUM_ANCHORS 3
static uint8 tx_poll_msg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'W', 'A', 'V', 'E', 0xE0, 0, 0};
static uint8 rx_resp_msg[] = {0x41, 0x88, 0, 0xCA, 0xDE, 'V', 'E', 'W', 'A', 0xE1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#define SOURCE_IDX 8
#define DEST_IDX 6

/* Length of the common part of the message (up to and including the function code, 
 * see NOTE 3 below. 
 */
#define ALL_MSG_COMMON_LEN 10

/* Indexes to access some of the fields in the frames defined above. */
#define ALL_MSG_SN_IDX 2
#define RESP_MSG_POLL_RX_TS_IDX 10
#define RESP_MSG_RESP_TX_TS_IDX 14
#define RESP_MSG_TS_LEN 4

/* Frame sequence number, incremented after each transmission. */
static uint8 frame_seq_nb = 0;

/* Buffer to store received response message.
 * Its size is adjusted to longest frame that this example code is 
 * supposed to handle.
 */
#define RX_BUF_LEN 20
static uint8 rx_buffer[RX_BUF_LEN];

/* Hold copy of status register state here for reference so that it 
 * can be examined at a debug breakpoint.
 */
static uint32 status_reg = 0;

/* UWB microsecond (uus) to device time unit (dtu, around 15.65 psec) 
 * conversion factor.
 * 1 uus = 512 / 499.2 usec and 1 usec = 499.2 * 128 dtu.
 */
#define UUS_TO_DWT_TIME 65536

/* Delay between frames, in UWB microseconds. See NOTE 1 below. */
#define POLL_TX_TO_RESP_RX_DLY_UUS 100
/* Receive response timeout. See NOTE 5 below. */
#define RESP_RX_TIMEOUT_UUS 510

/* Speed of light in air, in metres per second. */
#define SPEED_OF_LIGHT 299702547

/* Hold copies of computed time of flight and distance here for reference 
 * so that it can be examined at a debug breakpoint.
 */
static double tof;
static double distance;

/* Declaration of static functions. */
static void resp_msg_get_ts(uint8 *ts_field, uint32 *ts);
static volatile int tx_count = 0 ; // Successful transmit counter
static volatile int rx_count = 0 ; // Successful receive counter 

void dw_init(void){
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

    /* Configure DW1000. See NOTE 6 below. */
    dwt_configure(&config);

    /* Configure DW1000 LEDs */
    dwt_setleds(1);

    /* Apply default antenna delay value. See NOTE 2 below. */
    dwt_setrxantennadelay(RX_ANT_DLY);
    dwt_settxantennadelay(TX_ANT_DLY);

    /* Set expected response's delay and timeout. See NOTE 1 and 5 below.
     * As this example only handles one incoming frame with always the same 
      * delay and timeout, those values can be set here once for all.
      */
    dwt_setrxaftertxdelay(POLL_TX_TO_RESP_RX_DLY_UUS);
    dwt_setrxtimeout(65000);
}

double dw_main(int resp_id) {  
    tx_poll_msg[SOURCE_IDX] = my_id;
    tx_poll_msg[DEST_IDX] = resp_id;

    tx_poll_msg[ALL_MSG_SN_IDX] = frame_seq_nb;
    dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_TXFRS);

    /* Zero offset in TX buffer. */
    dwt_writetxdata(sizeof(tx_poll_msg), tx_poll_msg, 0);

    /* Zero offset in TX buffer, ranging. */
    dwt_writetxfctrl(sizeof(tx_poll_msg), 0, 1); 

    /* Start transmission, indicating that a response is expected so that
        * reception is enabled automatically after the frame is sent and the delay
        * set by dwt_setrxaftertxdelay() has elapsed.
        */
    dwt_starttx(DWT_START_TX_IMMEDIATE | DWT_RESPONSE_EXPECTED);
    tx_count++;
    // printk("tx: %d\n", tx_count);

    /* We assume that the transmission is achieved correctly, 
        * poll for reception of a frame or error/timeout. See NOTE 8 below. 
        */
    while (!((status_reg = dwt_read32bitreg(SYS_STATUS_ID)) & (SYS_STATUS_RXFCG | SYS_STATUS_ALL_RX_TO | SYS_STATUS_ALL_RX_ERR)))
    {};

    /* Increment frame sequence number after transmission of 
        * the poll message (modulo 256).
        */
    frame_seq_nb++;

    if (status_reg & SYS_STATUS_RXFCG) {

        uint32 frame_len;

        /* Clear good RX frame event in the DW1000 status register. */
        dwt_write32bitreg(SYS_STATUS_ID, SYS_STATUS_RXFCG);

        /* A frame has been received, read it into the local buffer. */
        frame_len = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFLEN_MASK;
        if (frame_len <= RX_BUF_LEN)
        {
            dwt_readrxdata(rx_buffer, frame_len, 0);
        }

        /* Check that the frame is the expected response from the companion 
            * "SS TWR responder" example.
            * As the sequence number field of the frame is not relevant, 
            * it is cleared to simplify the validation of the frame.
            */
        rx_buffer[ALL_MSG_SN_IDX] = 0;
        
        // if (memcmp(rx_buffer, rx_resp_msg, ALL_MSG_COMMON_LEN) == 0) {
        if((rx_buffer[SOURCE_IDX]==resp_id) && (rx_buffer[DEST_IDX] == my_id) && (rx_buffer[DEST_IDX - 1] == 'V')) {
            rx_count++;
            //   printk("\t rx: %d\n", rx_count);
            uint32 poll_tx_ts, resp_rx_ts, poll_rx_ts, resp_tx_ts;
            int32 rtd_init, rtd_resp;
            float clockOffsetRatio ;

            /* Retrieve poll transmission and response reception timestamps. 
                * See NOTE 9 below.
                */
            poll_tx_ts = dwt_readtxtimestamplo32();
            resp_rx_ts = dwt_readrxtimestamplo32();

            /* Read carrier integrator value and calculate clock offset ratio.
                * See NOTE 11 below.
                */
            clockOffsetRatio = dwt_readcarrierintegrator() * 
                (FREQ_OFFSET_MULTIPLIER * HERTZ_TO_PPM_MULTIPLIER_CHAN_2 / 1.0e6) ;

            /* Get timestamps embedded in response message. */
            resp_msg_get_ts(&rx_buffer[RESP_MSG_POLL_RX_TS_IDX], &poll_rx_ts);
            resp_msg_get_ts(&rx_buffer[RESP_MSG_RESP_TX_TS_IDX], &resp_tx_ts);

            /* Compute time of flight and distance, using clock offset ratio 
                * to correct for differing local and remote clock rates
                */
            rtd_init = resp_rx_ts - poll_tx_ts;
            rtd_resp = resp_tx_ts - poll_rx_ts;

            tof = ((rtd_init - rtd_resp * 
                    (1.0f - clockOffsetRatio)) / 2.0f) * DWT_TIME_UNITS;

            distance = tof * SPEED_OF_LIGHT;

            /* Display computed distance on console. */
            //printk("%d : %f\r\n",resp_id, distance);
            // resp_id++;
            // if (resp_id > NUM_ANCHORS)
            //     resp_id = 1;
            return distance;
        }
    }
    else {

        // if (status_reg & SYS_STATUS_ALL_RX_TO) {
        //     printk("timeout: %08lx\n", status_reg);
        // }
        // else {
        //     printk("error: %08lx\n", status_reg);      
        // }

        /* Clear RX error/timeout events in the DW1000 status register. */
        dwt_write32bitreg(SYS_STATUS_ID, (SYS_STATUS_ALL_RX_TO |
                                            SYS_STATUS_ALL_RX_ERR));

        /* Reset RX to properly reinitialise LDE operation. */
        dwt_rxreset();
    }

    /* Execute a delay between ranging exchanges. */
    Sleep(RNG_DELAY_MS);
    return -10.0;
}

/*! ---------------------------------------------------------------------------
 * @fn resp_msg_get_ts()
 *
 * @brief Read a given timestamp value from the response message. 
 *        In the timestamp fields of the response message, the
 *        least significant byte is at the lower address.
 *
 * @param  ts_field  pointer on the first byte of the timestamp field to get
 *         ts  timestamp value
 *
 * @return none
 */
static void resp_msg_get_ts(uint8 *ts_field, uint32 *ts)
{
    *ts = 0;
    for (int i = 0; i < RESP_MSG_TS_LEN; i++) {
        *ts += ts_field[i] << (i * 8);
    }
}


