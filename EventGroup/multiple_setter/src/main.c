/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

// const TickType_t xDelay2 = pdMS_TO_TICKS(200UL);

EventGroupHandle_t xEventGroup;

#define TASK1_BIT (1UL << 0UL)
#define TASK2_BIT (1UL << 1UL)
#define TASK3_BIT (1UL << 2UL)

void vInputTask1 (void *p)
{   
    while(1)
    {
        xEventGroupSetBits(xEventGroup ,TASK1_BIT);
    }
}

void vInputTask2 (void *p)
{   
    while(1)
    {
        xEventGroupSetBits(xEventGroup ,TASK2_BIT);
    }
}
void vInputTask3 (void *p)
{   
    while(1)
    {
        xEventGroupSetBits(xEventGroup ,TASK3_BIT);
    }
}
void vOutputTask(void *p)
{
    EventBits_t xEventGroupBits ;
    const EventBits_t xBitsToWaitFor = (TASK1_BIT | TASK2_BIT |TASK3_BIT);
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
        if((xEventGroupBits & TASK3_BIT) !=  0)
        {
            printf("EVENT BIT READING TASK : EVENT BIT 2 SET -TASK3\n");
        } 
    }
}


   

int main()
{
    xEventGroup = xEventGroupCreate();
    xTaskCreate(vInputTask1 , "Input Task 1", 100, NULL, 1, NULL);
    xTaskCreate(vInputTask2 , "Input Task 2", 100, NULL, 1, NULL);
    xTaskCreate(vInputTask3 , "Input Task 3", 100, NULL, 1, NULL);
    xTaskCreate(vOutputTask , "Output Task", 100, NULL, 1, NULL);
    
//   vTaskDelay(xDelay2);

	vTaskStartScheduler();
	return 0;
}
