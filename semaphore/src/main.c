/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xBinarySemaphore;
typedef int TaskProfiler;
TaskProfiler RedLedController, BlueLedController , GreenLedController;

void RedLedTask(void *pvParameters)
{
    xSemaphoreGive(xBinarySemaphore);
    while(1)
    {
        xSemaphoreTake(xBinarySemaphore , portMAX_DELAY);
        RedLedController++;
        printf("red=%d\n",RedLedController);
        xSemaphoreGive(xBinarySemaphore);
        vTaskDelay(1);
    }
}
void BlueLedTask(void *pvParameters)
{
    while(1)
    {
        xSemaphoreTake(xBinarySemaphore , portMAX_DELAY);
        BlueLedController++;
        printf("Blue=%d\n",BlueLedController);
        xSemaphoreGive(xBinarySemaphore);
        vTaskDelay(1);
    }
}
void GreenLedTask(void *pvParameters)
{
  
    while(1)
    {
        xSemaphoreTake(xBinarySemaphore , portMAX_DELAY);
        GreenLedController++;
        printf("Green=%d\n",GreenLedController);
        xSemaphoreGive(xBinarySemaphore);
        vTaskDelay(1);
    }
}
int main()
{
    xBinarySemaphore = xSemaphoreCreateBinary();
    xTaskCreate(RedLedTask, "Red Led Task", 100, NULL , 1 ,NULL);
    xTaskCreate(BlueLedTask, "Blue Led Task", 100, NULL , 1 ,NULL);
    xTaskCreate(GreenLedTask, "Green Led Task", 100, NULL , 1 ,NULL);
	vTaskStartScheduler();
	return 0;
}
