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

    const EventBits_t uxAllsyncBits = (TASK1_BIT | TASK2_BIT |TASK3_BIT);
void vInputTask1 (void *p)
{
    EventBits_t uxReturn;   
    while(1)
    {
        uxReturn = xEventGroupSync(xEventGroup , TASK1_BIT , uxAllsyncBits , portMAX_DELAY);
    
        if((uxReturn & uxAllsyncBits ) == uxAllsyncBits)
        {
        }
    }
}
void vInputTask2 (void *p)
{    
    EventBits_t uxReturn;
    while(1)
    {
       
        uxReturn = xEventGroupSync(xEventGroup , TASK2_BIT , uxAllsyncBits , portMAX_DELAY);
    
        if((uxReturn & uxAllsyncBits ) == uxAllsyncBits)
        {
        }
    }
}
void vInputTask3 (void *p)
{   
    EventBits_t uxReturn;
    while(1)
    {
        
        uxReturn = xEventGroupSync(xEventGroup , TASK3_BIT , uxAllsyncBits , portMAX_DELAY);

        
   
        if((uxReturn & uxAllsyncBits ) == uxAllsyncBits)
        {
            printf("All task set\n");
        }
    }
}
int main()
{
    xEventGroup = xEventGroupCreate();

    xTaskCreate(vInputTask1 , "Input Task 1", 100, NULL, 1, NULL);
    xTaskCreate(vInputTask2 , "Input Task 2", 100, NULL, 1, NULL);
    xTaskCreate(vInputTask3 , "Input Task 3", 100, NULL, 1, NULL);

	vTaskStartScheduler();
	return 0;
}
