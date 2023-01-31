/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
int is_killed = 0;
uint32_t execution_monitor=0;
uint32_t resume_monitor=0;
TaskHandle_t mytask1handler = NULL;
TaskHandle_t mytask2handler = NULL;
 void mytask1(void * p)
{
	
	while(1)
	{   
        execution_monitor++;
        printf("%d\n",execution_monitor);
        if(execution_monitor >= 50)
        {
            execution_monitor = 0;
            is_killed = 1;
            vTaskDelete(NULL);

    	}
    }
}   

void mytask2(void * p)
{
	while(1)
	{
		if(is_killed =1)
        {
            resume_monitor++;
            if(resume_monitor >=30)
            {
                vTaskResume(mytask1handler);
                 printf("task 1 resume\n");
                resume_monitor=0;
                is_killed = 0;
            }
    }
}
}
int main()
{
	xTaskCreate(mytask1,"task1",200,(void*) 0,tskIDLE_PRIORITY,&mytask1handler);
	xTaskCreate(mytask2,"task2",200,(void*) 0,tskIDLE_PRIORITY,&mytask2handler);
	vTaskStartScheduler();
	while(1);
}
