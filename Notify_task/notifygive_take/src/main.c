/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"


TaskHandle_t task1 = NULL;
TaskHandle_t task2 = NULL;

void myTask1(void *pvParameters)
{
    while(1)
    {
        xTaskNotifyGive(task2);
        vTaskDelay(1000);
    }
}
void myTask2(void *pvParameters)
{   
    int notificationvalue;
    while(1)
    {
        notificationvalue = ulTaskNotifyTake(pdTRUE ,(TickType_t)portMAX_DELAY);
        if(notificationvalue > 0 )
        {
            printf("Notification Received = %d\n",notificationvalue);
 
        }
    }
}

int main()
{

	xTaskCreate(myTask1,"task1",200,NULL,2,&task1);
    xTaskCreate(myTask2,"task2",200,NULL,1,&task2);
   
	vTaskStartScheduler();
	return 0;
}
