/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
int c =0;
TaskHandle_t mytaskhandler = NULL;
const TickType_t delay = pdMS_TO_TICKS(250);
void mytask1(void *p)
{
    int count = 0;
	while(1)
	{
		count++;
        printf("%d\n",count);
//        vTaskDelay(delay);
	}
}
void vApplicationIdleHook( void )
{
    c++;
    printf("c=%d\n",c);
}
    

int main()
{

	xTaskCreate(mytask1,"task1",200,NULL,1,&mytaskhandler);
	vTaskStartScheduler();
	return 0;
}
