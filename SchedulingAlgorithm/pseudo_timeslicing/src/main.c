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
TaskHandle_t task3 = NULL;

TickType_t delay = pdMS_TO_TICKS(50);

void myTask1(void *pvParameters)
{
    while(1)
    {
   //     printf("task1 \r\n");
        int count =0;
        count++;

        printf("count in task 1= %d\n",count);
        vTaskDelay(delay);
    }
}
void myTask2(void *pvParameters)
{   
    while(1)
    {
     //   printf("Task2 \r\n");
        int count = 0;
        count++;
 
        printf("count in task 2 = %d\n",count);
        vTaskDelay(delay);
    }
}
void myTask3(void *pvParameters)
{   
    while(1)
    {
       // printf("Task3 \r\n");
        int count = 0;
        count++;
     
        printf("count in task3 = %d\n",count);
        vTaskDelay(delay);

    }
}
int main()
{

	xTaskCreate(myTask1,"task1",200,NULL,2,&task1);
    xTaskCreate(myTask2,"task2",200,NULL,2,&task2);
    xTaskCreate(myTask3 , "task3" ,200 ,NULL ,1,&task3);

	//xTaskCreate(mytask1,"task1",200,(void*)0,tskIDLE_PRIORITY,&mytaskhandler);
	vTaskStartScheduler();
	return 0;
}
