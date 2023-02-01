/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
TaskHandle_t sender_handle , receiver_handle;
QueueHandle_t  Queue;
void Sender_Task(void *pvParameters)
{
    int32_t value_to_send = 1;
    BaseType_t qStatus;
    while(1)
    {
         qStatus = xQueueSend(Queue,&value_to_send,0);
       /* if(qStatus != pdPASS)
        {
            printf("error data not send....\r\n");
        }*/
        for(int i=0;i<10000;i++) { }

    }
    
}
void Receiver_Task(void *pvParameters)
{
    int32_t value_received;
    const TickType_t wait_time = pdMS_TO_TICKS(50);
    BaseType_t qStatus;
    while(1)
    {
        qStatus = xQueueReceive(Queue,&value_received,wait_time);
        if(qStatus == pdPASS)
        {
            printf("data received is %d\n",value_received);
        }
        else
        {
            printf("error data does not receive\n");
        }
    }
}



int main()
{
	Queue = xQueueCreate(10,sizeof(int32_t));
	xTaskCreate(Sender_Task,"sender task",200,NULL,1,&receiver_handle);
	xTaskCreate(Receiver_Task,"receiver task",200,NULL,1,&sender_handle);
	vTaskStartScheduler();
	return 0;
}
