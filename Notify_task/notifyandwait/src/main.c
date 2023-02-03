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
        xTaskNotify(task2,0,eNoAction);
        vTaskDelay(1000);
    }
}
void myTask2(void *pvParameters)
{   
    uint32_t ulnotificationvalue;
    while(1)
    {
        if(xTaskNotifyWait(0,0,&ulnotificationvalue ,portMAX_DELAY) == pdTRUE)
        {
            printf("Notification Received = %d\n",ulnotificationvalue);
 
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
