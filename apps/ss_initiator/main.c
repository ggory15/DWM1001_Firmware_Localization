#include <zephyr.h>
#include <sys/printk.h>

#include "ble_init.h"
#include "ss_init.h"

extern void ble_notify(double, double, double);
extern void dw_init(void);
#define NUM_ANCHOR 3

void ble_init(){
    int err;

	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	bt_ready();
	
	bt_conn_cb_register(&conn_callbacks);
	
	
}

void dwm_init(){
	dw_init();
}

double dist1;
int cnt = 0;
void main(){
	// DWM init	
	dwm_init();
	// Ble init and Advertisement	
	ble_init();

	double dist1_sum = 0.0, dist1_c;
	double dist2_sum = 0.0, dist2_c;
	double dist3_sum = 0.0, dist3_c;
	int cnt1 = 0;
	int cnt2 = 0;
	int cnt3 = 0;

	while (1)
	{	
		while (cnt < 3){
			dist1_c = dw_main(1);
			if (dist1_c > -1.){
				dist1_sum += dist1_c;
				cnt1++;
			}
			dist2_c = dw_main(2);
			if (dist2_c > -1.){
				dist2_sum += dist2_c;
				cnt2++;
			}
			dist3_c = dw_main(3);
			if (dist3_c > -1.){
				dist3_sum += dist3_c;
				cnt3++;
			}
			cnt++;
		}
		
		//printk("%f, %f, %f\n", dist1_sum/(double)cnt1, dist2_sum/(double)cnt2, dist3_sum/(double)cnt3);
		k_sleep(K_SECONDS(0.001));
		ble_notify(dist1_sum/(double)cnt1, dist2_sum/(double)cnt2, dist3_sum/(double)cnt3);

		cnt = 0;
		cnt1 = 0;
		cnt2 = 0;
		cnt3 = 0;
		dist1_sum = 0.0;
		dist2_sum = 0.0;
		dist3_sum = 0.0;
	}
	
    

}

