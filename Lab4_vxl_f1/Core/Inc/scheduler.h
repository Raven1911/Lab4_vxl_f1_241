/*
 * scheduler.h
 *
 *  Created on: Nov 28, 2024
 *      Author: Admin
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdlib.h>
#include "software_timer.h"


typedef struct STask{

	void (*pTask)();
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;

	struct STask* next;
}STask;




typedef struct Container{
	unsigned char empty_Slot;
	unsigned char num_Task;
	struct STask* tail;
} Container;



STask* add_Node(void(*pFunction)(), uint32_t Delay, uint32_t Period);


void SCH_init(void);
void SCH_Update_Task(void);
void SCH_Add_Task(void(*pFunction)(), uint32_t Delay, uint32_t Period);
void SCH_Delete_Task(void);
void SCH_Dispatch_Task(void);


#endif /* INC_SCHEDULER_H_ */
