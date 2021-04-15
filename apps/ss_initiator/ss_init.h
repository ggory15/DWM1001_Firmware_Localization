#ifndef __SS_INIT_H__
#define __SS_INIT_H__

    #include <stdio.h>
    #include <string.h>

    #include "deca_device_api.h"
    #include "deca_regs.h"
    #include "port.h"

    // zephyr includes
    #include <zephyr.h>
    #include <sys/printk.h>

    #define LOG_LEVEL 3
    #include <logging/log.h>

    void dw_init(void);
    double dw_main(int);
    

#endif  
