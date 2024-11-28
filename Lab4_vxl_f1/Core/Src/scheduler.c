/*
 * scheduler.c
 *
 *  Created on: Nov 28, 2024
 *      Author: Admin
 */
#include "scheduler.h"



Container* container = NULL;

STask* addNode(void(*pFunction)(), int delay, int period){
	STask* newNode = (struct STask*)malloc(sizeof(struct STask));
	newNode->Delay = delay;
	newNode->Period = period;
	newNode->pTask = pFunction;
	newNode->next = NULL;
	return newNode;
}

void SCH_init(void){
	timer_init();
	///
	container = (struct Container*)malloc(sizeof(struct Container));
	container->tail = NULL;
	container->numTask = 0;
	container->emptySlot = 0;
}

void SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
    STask* newNode;

    if(container->tail == NULL){
        // add first node
        newNode = addNode(pFunction, DELAY, PERIOD);
        container->tail = newNode;
        container->tail->next =  newNode;
        container->numTask++;
    }
    else{
        STask* prevTail = container->tail->next;
        STask* temp = container->tail->next;
        int Total = 0;

        for(int i = 0; i < container->numTask; i++){
            Total += temp->Delay;
            if((Total + temp->next->Delay > DELAY) && temp != container->tail){
                // add head
                if(Total > DELAY){
                    if(container->emptySlot == 0){
                        newNode = addNode(pFunction, DELAY, PERIOD);
                        // update next node DELAY
                        temp->Delay -= DELAY;
                        // update newNode position
                        newNode->next = temp;
                        container->tail->next = newNode;
                        //update numTask
                        container->numTask++;
                        return;
                    }
                    else{
                        // update new head
                        container->tail->Delay = PERIOD;
                        container->tail->Period = PERIOD;
                        container->tail->pTask = pFunction;
                        //update next to node DELAY
                        temp->Delay -= PERIOD;
                        // update tail
                        while(prevTail->next != container->tail){
                            prevTail = prevTail->next;
                        }
                        container->tail = prevTail;
                        // update emptySlot
                        container->emptySlot--;
                        return;
                    }
                }



                // add middle
                if(container->emptySlot == 0){
                    // update newNode DELAY
                    newNode = addNode(pFunction, DELAY - Total, PERIOD);
                    // update position
                    newNode->next = temp->next;
                    temp->next = newNode;
                    // update next to DELAY
                    newNode->next->Delay -=  newNode->Delay;

                    container->numTask++;
                    return;
                }
                else{
                    // update newNode DELAY
                    newNode = container->tail;
                    newNode->Delay = PERIOD - Total;
                    newNode->Period = PERIOD;
                    newNode->pTask = pFunction;
                    // update new tail
                    while(prevTail->next != container->tail){
                        prevTail = prevTail->next;
                    }
                    prevTail->next = newNode->next;
                    container->tail = prevTail;
                    // update new node position
                    newNode->next = temp->next;
                    temp->next = newNode;
                    // update next to DELAY
                    newNode->next->Delay -= newNode->Delay;

                    container->emptySlot--;
                    return;
                }
            }

            // add tail
            if(temp == container->tail){
                if(container->emptySlot == 0){
                    // update DELAY
                    newNode = addNode(pFunction, DELAY - Total, PERIOD);
                    // update position
                    newNode->next = temp->next;
                    temp->next = newNode;
                    container->tail = newNode;
                    // update num Task
                    container->numTask++;
                    return;
                }
                else{
                    // update DELAY
                    container->tail->Delay = PERIOD - Total;
                    container->tail->Period = PERIOD;
                    container->tail->pTask = pFunction;
                    // update empty slot
                    container->emptySlot--;
                    return;
                }
            }
            temp = temp->next;
        }
    }
}

void SCH_Delete_Task(void){
	container->tail->next->Delay = 0;
	container->tail->next->Period = 0;
	container->tail->next->pTask = NULL;
	container->tail = container->tail->next;
	container->emptySlot++;
}

void SCH_Update_Task(void){
	if(container != NULL && container->tail != NULL){
		if(container->tail->next->Delay > 0){
			container->tail->next->Delay--;
		}
	}

}

//void SCH_Dispatch_Task(void){
//	if(container->tail->next->Delay == 0){
//		(*(container -> tail -> next -> pTask))();
//		struct STask temp = *(container -> tail -> next);
//		SCH_Delete_Task();
//		if(temp.Period != 0){
//			SCH_Add_Task(temp.pTask, temp.Period, temp.Period);
//		}
//	}
//}


void SCH_Dispatch_Task(void) {
    if (container != NULL && container->tail != NULL) {
        STask* currentTask = container->tail->next; // Lấy nhiệm vụ đầu tiên (sau tail)

        if (currentTask->Delay == 0) {
            // Thực thi nhiệm vụ
            (*(currentTask->pTask))();

            // Lưu thông tin nhiệm vụ hiện tại
            int taskPeriod = currentTask->Period;
            void (*taskFunction)() = currentTask->pTask;

            // Xóa nhiệm vụ khỏi danh sách
            SCH_Delete_Task();

            // Nếu nhiệm vụ cần lặp lại, thêm lại vào danh sách
            if (taskPeriod != 0) {
                SCH_Add_Task(taskFunction, taskPeriod, taskPeriod);
            }
        }
    }
}
