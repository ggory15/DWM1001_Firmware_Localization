#ifndef __BLE_INIT_H__
#define __BLE_INIT_H__

    #include <bluetooth/bluetooth.h>
    #include <bluetooth/hci.h>
    #include <bluetooth/conn.h>
    #include <bluetooth/uuid.h>
    #include <bluetooth/gatt.h>
    #include <bluetooth/services/bas.h>
    #include <bluetooth/services/hrs.h>

    #include <zephyr/types.h>
    #include <stddef.h>
    #include <string.h>
    #include <errno.h>
    #include <sys/printk.h>
    #include <sys/byteorder.h>
    #include <zephyr.h>

    #include <settings/settings.h>
    #include "ble_uuids.h"
    static uint8_t vnd_value[] = { 'V', 'a', 'c', 'd', 'f', 'c'};
    static bool connect_state = false;

    static ssize_t read_vnd(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                void *buf, uint16_t len, uint16_t offset)
    {
        const char *value = attr->user_data;

        return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
                    strlen(vnd_value));
    }

    static ssize_t write_vnd(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                const void *buf, uint16_t len, uint16_t offset,
                uint8_t flags)
    {
        uint8_t *value = attr->user_data;

        if (offset + len > sizeof(vnd_value)) {
            return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
        }

        memcpy(value + offset, buf, len);

        return len;
    }

    static struct bt_gatt_indicate_params ind_params;

    static uint8_t simulate_vnd;
    static void vnd_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
    {
        simulate_vnd = (value == BT_GATT_CCC_INDICATE) ? 1 : 0;
    }

    
    static void connected(struct bt_conn *conn, uint8_t err)
    {
        if (err) {
            printk("Connection failed (err 0x%02x)\n", err);
        } else {
            printk("Connected\n");
            connect_state = true;
        }
    }

    static void disconnected(struct bt_conn *conn, uint8_t reason)
    {
        printk("Disconnected (reason 0x%02x)\n", reason);
        connect_state = false;
    }

    static struct bt_conn_cb conn_callbacks = {
        .connected = connected,
        .disconnected = disconnected,
    };

    static bool is_connected_ble(void)
    {
        return connect_state;
    }

    static const struct bt_data ad[] = {
        BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
        BT_DATA_BYTES(BT_DATA_UUID16_ALL,
                BT_UUID_16_ENCODE(BT_UUID_HRS_VAL),
                BT_UUID_16_ENCODE(BT_UUID_BAS_VAL),
                BT_UUID_16_ENCODE(BT_UUID_CTS_VAL)),
        BT_DATA_BYTES(BT_DATA_UUID128_ALL,
                0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
                0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12),
    };


    static void bt_ready(void)
    {
        int err;

        printk("Bluetooth initialized\n");

        if (IS_ENABLED(CONFIG_SETTINGS)) {
            settings_load();
        }

        err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
        if (err) {
            printk("Advertising failed to start (err %d)\n", err);
            return;
        }

        printk("Advertising successfully started\n");
    }

    void ble_notify(double, double, double);

#endif