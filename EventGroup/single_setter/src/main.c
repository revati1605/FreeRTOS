/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

EventGroupHandle_t xEventGroup;
#define TASK1_BIT (1UL << 0UL)
#define TASK2_BIT (1UL << 1UL)

void vEventBitSettingTask(void *p)
{
    const TickType_t xDelay = pdMS_TO_TICKS(500UL);
    while(1)
    {
        printf("Bit Setting Task about to set bit 0\n");
        xEventGroupSetBits(xEventGroup ,TASK1_BIT);
        vTaskDelay(xDelay);

        printf("Bit Setting Task about to set bit 1\n");
        xEventGroupSetBits(xEventGroup ,TASK2_BIT);
        vTaskDelay(xDelay);
    }
}

void vEventBitReadingTask(void *p)
{
    EventBits_t xEventGroupBits ;
    const EventBits_t xBitsToWaitFor = (TASK1_BIT | TASK2_BIT);
    const TickType_t xDelay2 = pdMS_TO_TICKS(200UL);
    while(1)
    {
        xEventGroupBits = xEventGroupWaitBits (xEventGroup, xBitsToWaitFor ,pdTRUE, pdFALSE , portMAX_DELAY);
        if((xEventGroupBits & TASK1_BIT) !=  0)
        {
            printf("EVENT BIT READING TASK : EVENT BIT 0 SET -TASK1\n");
        } 
        if((xEventGroupBits & TASK2_BIT) !=  0)
        {
            printf("EVENT BIT READING TASK : EVENT BIT 1 SET -TASK2\n");
        } 
        vTaskDelay(xDelay2);
    }
}


   

int main()
{
    xEventGroup = xEventGroupCreate();
    xTaskCreate(vEventBitSettingTask , "Setting bit", 100, NULL, 1, NULL);
    xTaskCreate(vEventBitReadingTask , "Reading bit", 100, NULL, 1, NULL);
	
	vTaskStartScheduler();
	return 0;
}
