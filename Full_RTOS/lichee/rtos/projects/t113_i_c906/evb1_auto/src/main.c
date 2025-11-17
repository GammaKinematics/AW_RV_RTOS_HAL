/*
* Copyright (C) 2013 Guangzhou Tronlong Electronic Technology Co., Ltd. - www.tronlong.com
*
* @file     main.c
*
* @brief    This application will toggle the level state of the led.
*
* @author Tronlong <support@tronlong.com>
*
* @version V1.0
*
* @date 2024-01-16
**/
#include "FreeRTOS.h"
#include "task.h"
#include <console.h>
#include <hal_gpio.h>
#include <hal_timer.h>

#define GPIO_LED        GPIO_PG11

void led_flash_thread(void *param)
{
        /* Set gpio direction */
        hal_gpio_set_direction(GPIO_LED, GPIO_DIRECTION_OUTPUT);

        /* LED flash control */
        while(1) {
                /* Set gpio output high level */
                hal_gpio_set_data(GPIO_LED, GPIO_DATA_HIGH);
                /* Delay 500ms */
                hal_msleep(500);
                /* Set gpio output low level */
                hal_gpio_set_data(GPIO_LED, GPIO_DATA_LOW);
                /* Delay 500ms */
                hal_msleep(500);
        }

        hal_thread_stop(NULL);
}

void cpu0_app_entry(void *param)
{
        void *thread;

        printf("led flash demo!\n");

        /* Create thread */
        thread = hal_thread_create(
                        led_flash_thread,       /* Pointer to the function that implements the task. */
                        NULL,                   /* We are not using the task parameter. */
                        "led_flash_thread",     /* Text name for the task, provided to assist debugging only. */
                        configMINIMAL_STACK_SIZE, /* The stack allocated to the task.  configMINIMAL_STACK_SIZE = 1024 */
                        HAL_THREAD_PRIORITY_SYS); /* Task priority, 0 is lowest, configMAX_PRIORITIES-1 is highest, HAL_THREAD_PRIORITY_SYS = 13 */

        /* Start thread */
        if (thread != NULL)
                hal_thread_start(thread);

        /* Delete own task */
        vTaskDelete(NULL);
}