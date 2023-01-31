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
void myTask1(void *pvParameters)
{
    while(1)
    {
        printf("task1 \r\n");
        int count =0;
        count++;
       
    }
}
void myTask2(void *pvParameters)
{   
    while(1)
    {
        printf("Task2 \r\n");
        int count = 0;
        count++;
        vTaskPrioritySet(task3 , 3); 
    }
}
void myTask3(void *pvParameters)
{   
    while(1)
    {
        printf("Task3 \r\n");
        int count = 0;
        count++;
     
    }
}
int main()
{

	xTaskCreate(myTask1,"task1",200,NULL,2,&task1);
    xTaskCreate(myTask2,"task2",200,NULL,1,&task2);
    xTaskCreate(myTask3 , "task3" ,200 ,NULL ,1,&task3);

	//xTaskCreate(mytask1,"task1",200,(void*)0,tskIDLE_PRIORITY,&mytaskhandler);
	vTaskStartScheduler();
	return 0;
}
