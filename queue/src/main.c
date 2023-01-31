/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include"queue.h"

TaskHandle_t task1 = NULL;
TaskHandle_t task2 = NULL;
QueueHandle_t myqueue;
void mytask1(void *p)
{	
	char txbuff[300];
	myqueue = xQueueCreate(5,sizeof(txbuff));
	sprintf(txbuff,"message1");
	xQueueSend(myqueue ,(void*)txbuff,(TickType_t) 0);
	while(1)
	{


	}
	
	
}
void mytask2(void *p)
{
	char rxbuff[300];
	while(1)
	{
		if(myqueue != 0)
		{
			if(xQueueRecieve(myqueue , (void*)rxbuff ,(TickType_t) 5))

int main()
{

//	xTaskCreate(mytask1,"task1",200,(void*)p,tskIDLE_PRIORITY,&mytaskhandler);
	xTaskCreate(mytask1,"task1",200,(void*)0,tskIDLE_PRIORITY,&mytaskhandler);
	vTaskStartScheduler();
	return 0;
}
