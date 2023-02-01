/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

typedef enum
{
    humidity_sensor,
    pressure_sensor
}DataSource_t;

typedef struct
{
    uint8_t ucValue;
    DataSource_t eDataSource;
}Data_t;

static const Data_t xStructsToSend [2] = 
{
    {77, humidity_sensor},
    {63, pressure_sensor}
};

TaskHandle_t pre_sen_handle , hum_sen_handle , receiver_handle;
QueueHandle_t Queue ;

void Sender_Task(void *pvParameters)
{
    BaseType_t qStatus;
    const TickType_t wait_time = pdMS_TO_TICKS(200);
    while(1)
    {
         qStatus = xQueueSend(Queue,pvParameters,wait_time);
        if(qStatus != pdPASS)
        {
          //printf("error data not send..\n");
        }
        for(int i=0;i<10000;i++) { }

    }
    
}
void Receiver_Task(void *pvParameters)
{
    Data_t xDataReceived;
    BaseType_t qStatus;
    while(1)
    {
        qStatus = xQueueReceive(Queue,pvParameters,0);
        if(qStatus == pdPASS)
        {
            if(xDataReceived.eDataSource == humidity_sensor)
            {
                printf("humidity sensor value = %d\n",xDataReceived.ucValue);     
            }
            else
            {
                printf("pressure sensor value =%d\n",xDataReceived.ucValue);
            }
        }
        else
            {
                //printf("error\n");
            }
    }
}



int main()
{
	Queue = xQueueCreate(3,sizeof(Data_t));
	xTaskCreate(Sender_Task,
                 "humidity sensor task",
                  200,
                  (void*)&xStructsToSend[0],
                    1,
                  &hum_sen_handle);
	xTaskCreate(Sender_Task,
                "pressure sensor task",
                 200,
                 (void*)&xStructsToSend[1],
                  2,
                &pre_sen_handle);
	xTaskCreate(Receiver_Task,
                "receiver task",
                200,
                NULL,
                2,
                &receiver_handle);
	vTaskStartScheduler();
	return 0;

}
