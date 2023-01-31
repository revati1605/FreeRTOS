/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t mytask1handler = NULL;
TaskHandle_t mytask2handler = NULL;
 void mytask1(void * p)
{
	int count = 0;
	while(1)
	{
		printf("hello world:%d\n",count++);
		vTaskDelay(1000 * configTICK_RATE_HZ/1000);
	}
}

void mytask2(void * p)
{
	while(1)
	{
		vTaskSuspend(mytask1handler);
		vTaskDelay(5000 * configTICK_RATE_HZ/1000);
		vTaskResume(mytask1handler);
		vTaskDelay(5000 * configTICK_RATE_HZ/1000);
	}
}
int main()
{
	xTaskCreate(mytask1,"task1",200,(void*) 0,tskIDLE_PRIORITY,&mytask1handler);
	xTaskCreate(mytask2,"task2",200,(void*) 0,tskIDLE_PRIORITY,&mytask2handler);
	vTaskStartScheduler();
	while(1);
}
