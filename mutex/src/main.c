/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xMutex;

char mySharedResource[50];
void task1(void *pvParameters)
{
char msg[] ="message received from task1";
while(1)
{
    if(xSemaphoreTake(xMutex ,(TickType_t) 0xFFFFFFF) == 1)
        {
            int i;
            for(i=0;msg[i] ;i++)
            {
                mySharedResource[i] = msg[i];
                  vTaskDelay(50);
            }
        
            mySharedResource[i] ='\n';
            printf("T1=%s\n",mySharedResource);
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(100);
}
}
void task2(void *pvParameters)
{
char msg[] ="message received from task2";
while(1)
{
    if(xSemaphoreTake(xMutex ,(TickType_t) 0xFFFFFFF) == 1)
        {
            int i;
            for(i=0;msg[i] ;i++)
            {
                mySharedResource[i] = msg[i];
                  vTaskDelay(50);
            }
        
            mySharedResource[i] ='\n';
            printf("T2=%s\n",mySharedResource);
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(100);
}
}
int main()
{
    xMutex = xSemaphoreCreateMutex();
    xTaskCreate(task1, "Task1", 100, NULL , 1 ,NULL);
    xTaskCreate(task2, "Task 2", 100, NULL , 1 ,NULL);
	vTaskStartScheduler();
	return 0;
}
