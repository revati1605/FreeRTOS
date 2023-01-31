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

void mytask1(void *p)
{
	int count =0;
	//int count = (int*)p;
	//TickType_t mylastunblock;
	//mylastunblock = xTaskGetTickCount();
	while(1)
	{	
		count++;
//		printf("hello world:%d\n",count++);
	//	vTaskDelay(1000);
//	vTaskDelay( 1000*configTICK_RATE_HZ/1000);
//	printf("task 2 name is :%s\n",pcTaskGetName(task2));
/*	TaskHandle_t taskHand;
	taskHand = xTaskGetCurrentTaskHandle();
		if(count == 3)
		{
			vTaskDelete(xTaskGetHandle("task2"));
		}*/
	}
}

void mytask2(void *p)
{
	while(1)
	{
		eTaskState mystate;
		mystate = eTaskGetState(task1);
//		printf("hey there\n");
		printf("task1 state is :%d\n",mystate);
		
		mystate = eTaskGetState(task2);
		printf("task2 state is:%d\n",mystate);
		vTaskDelay(1000*configTICK_RATE_HZ/1000);
	}
}
int main()
{
	//int p=25;
	//xTaskCreate(mytask1,"task1",200,(void*)p,tskIDLE_PRIORITY,&mytaskhandler);
	xTaskCreate(mytask1,"task1",200,(void*)0,tskIDLE_PRIORITY,&task1);
	xTaskCreate(mytask2, "task2",200,(void*)0,tskIDLE_PRIORITY,&task2);
	vTaskStartScheduler();
	return 0;
}
