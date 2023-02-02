/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#define main_ONE_SHOT_TIMER_PERIOD (pdMS_TO_TICKS(4000UL))
#define main_AUTO_RELOAD_TIMER_PERIOD (pdMS_TO_TICKS(500UL))


TimerHandle_t xAutoReloadTimer , xOneShotTimer;
BaseType_t xTimer1Started, xTimer2Started;


void prvOneShotTimerCallback(TimerHandle_t xTimer)
{
    TickType_t xTimeNow;
    xTimeNow = xTaskGetTickCount();
    printf("One Shot  timer callback executing = %d\n",(int)xTimeNow);
}

void  prvAutoRelaodTimerCallback(TimerHandle_t xTimer)
{
    TickType_t xTimeNow;
    xTimeNow = xTaskGetTickCount();
    printf("auto Reload timer callback executing = %d\n",(int)xTimeNow);
}
int main()
{
    xOneShotTimer = xTimerCreate("One shot", main_ONE_SHOT_TIMER_PERIOD, pdFALSE , 0 , prvOneShotTimerCallback);
    
    xAutoReloadTimer = xTimerCreate("Auto reload", main_AUTO_RELOAD_TIMER_PERIOD, pdTRUE , 0 ,  prvAutoRelaodTimerCallback);
    
    xTimer1Started = xTimerStart(xOneShotTimer , 0);
    
    xTimer2Started = xTimerStart(xAutoReloadTimer , 0);
	
	vTaskStartScheduler();
	return 0;
}
