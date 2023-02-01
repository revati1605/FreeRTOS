/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

static QueueHandle_t Q1 = NULL , Q2 = NULL;
static QueueSetHandle_t Qset = NULL;

void senderTask1(void *pvParameters)
{
    const TickType_t xBlockTime = pdMS_TO_TICKS(100);
     char *msg = "message from sendertask1\n";
    while(1)
    {
        vTaskDelay(xBlockTime);
        xQueueSend(Q1 , &msg ,0);
        
    }
}
void senderTask2(void *pvParameters)
{
    const TickType_t xBlockTime = pdMS_TO_TICKS(200);
     char *msg = "message from sendertask2\n";
    while(1)
    {
        vTaskDelay(xBlockTime);
        xQueueSend(Q2 , &msg ,0);
        
    }
}

void receiverTask(void*pvParameters)
{
    QueueHandle_t xQueueContainsData;
    char *pcReceivedData;
    while(1)
    {
        xQueueContainsData = (QueueHandle_t) xQueueSelectFromSet(Qset ,portMAX_DELAY);
        xQueueReceive(xQueueContainsData,&pcReceivedData , 0);
        printf("%s\n",pcReceivedData);
    }
}

int main()
{
//create a queue
Q1 = xQueueCreate(1,sizeof(char*));
Q2 = xQueueCreate(1,sizeof(char*));

//create Qset
Qset = xQueueCreateSet(1*2);

//Add Queue to Queue set
xQueueAddToSet(Q1 ,Qset);
xQueueAddToSet(Q2,Qset);

//sender task
xTaskCreate(senderTask1 , "sender task 1", 100 , NULL , 1 , NULL);
xTaskCreate(senderTask2 , "sender task 2", 100, NULL , 1 ,NULL);
xTaskCreate(receiverTask , " receiver task", 100 , NULL , 2, NULL);

vTaskStartScheduler();
}

