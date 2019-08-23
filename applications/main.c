/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-08     obito0   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <fal.h>
#include <dfs_posix.h>

/* defined the LED0 pin: PC13 */
#define LED0_PIN    GET_PIN(C, 13)

#define FS_PARTITION_NAME  "flash0"

int main(void)
{
    int count = 1;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    fal_init();

#ifdef RT_USB_DEVICE_MSTORAGE
    struct rt_device *flash_dev = fal_blk_device_create(FS_PARTITION_NAME);
#else
    struct rt_device *flash_dev = fal_mtd_nor_device_create(FS_PARTITION_NAME);
#endif

    if (flash_dev == NULL)
    {
        rt_kprintf("Can't create a block device on '%s' partition.\n", FS_PARTITION_NAME);
    }
    else
    {
        rt_kprintf("Create a block device on the %s partition of flash successful.\n", FS_PARTITION_NAME);
    }
    
    while (count++)
    {
#ifndef RT_USB_DEVICE_MSTORAGE
        if(rt_device_find(FS_PARTITION_NAME) != RT_NULL)
        {
            dfs_mkfs("lfs", FS_PARTITION_NAME);

            if (dfs_mount(FS_PARTITION_NAME, "/", "lfs", 0, 0) == RT_EOK)
            {
                rt_kprintf("sd card mount to '/'\n");
                break;
            }
            else
            {
                rt_kprintf("sd card mount to '/' failed!\n");
            }
        }
#endif
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
