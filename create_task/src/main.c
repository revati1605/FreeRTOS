/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t mytaskhandler = NULL;

void mytask1(void *p)
{
	//int count =0;
	int count = (int*)p;
	TickType_t mylastunblock;
	mylastunblock = xTaskGetTickCount();
	while(1)
	{
		printf("hello world:%d\n",count++);
	//	vTaskDelay(1000);
	vTaskDelayUntil(&mylastunblock , 1000*configTICK_RATE_HZ/1000);
	/*	if(count == 30)
		{
			vTaskDelete(mytaskhandler);
		}*/
	}
}

int main()
{
	int p=25;
	xTaskCreate(mytask1,"task1",200,(void*)p,tskIDLE_PRIORITY,&mytaskhandler);
	//xTaskCreate(mytask1,"task1",200,(void*)0,tskIDLE_PRIORITY,&mytaskhandler);
	vTaskStartScheduler();
	return 0;
}
