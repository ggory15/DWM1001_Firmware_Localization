#include "ble_init.h"
#include <math.h>

BT_GATT_SERVICE_DEFINE(dwm1001_svc,
        BT_GATT_PRIMARY_SERVICE(BT_UUID_DWM1001_SERVICE),
        BT_GATT_CHARACTERISTIC(BT_UUID_DWM1001_NOTIFY,
                    BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE | BT_GATT_CHRC_NOTIFY,
                    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                    read_vnd, write_vnd, vnd_value),
        BT_GATT_CCC(vnd_ccc_cfg_changed,
                BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
    );

void ble_notify(double dist1, double dist2, double dist3)
{   
    int intg;
    int decm;

    if (true){
        if (dist1 > 127.0){
            intg = 127;
            decm = 0;
        }
        else if (dist1 < 0.0){
            intg = 0;
            decm = 0;
        }
        else{
            intg = (int)dist1;
            decm = (dist1 - intg) * 100;
        }
	    vnd_value[0] = intg;
        vnd_value[1] = decm; 

        if (dist2 > 127.0){
            intg = 127;
            decm = 0;
        }
        else if (dist2 < 0.0){
            intg = 0;
            decm = 0;
        }
        else{
            intg = (int)dist2;
            decm = (dist2 - intg) * 100;
        }
	    vnd_value[2] = intg;
        vnd_value[3] = decm; 

        if (dist3 > 127.0){
            intg = 127;
            decm = 0;
        }
        else if (dist3 < 0.0){
            intg = 0;
            decm = 0;
        }
        else{
            intg = (int)dist3;
            decm = (dist3 - intg) * 100;
        }
	    vnd_value[4] = intg;
        vnd_value[5] = decm; 
        bt_gatt_notify(NULL, &dwm1001_svc.attrs[1], &vnd_value, sizeof(vnd_value));
    }
}