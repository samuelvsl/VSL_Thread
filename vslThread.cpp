#include <string.h>
#include "vslThread.h"

int ThreadId = 1;
int ThreadControlId = 1;

Thread::Thread(){
    time = 0;
    lastTime = 0;
    activated = true;
    id = ThreadId;
    ThreadId++;
}

void Thread::setTime(long int newTime){
    time = newTime;
}

void Thread::setLastTime(long int newLastTime){
    lastTime = newLastTime;
}

void Thread::setFunction(void (*newFunction)(void)){
    function = newFunction;
}

int Thread::getId(){
    return id;
}

long int Thread::getTime(){
    return time;
}

bool Thread::needRun(){
    if(((lastTime + time) <= millis()) && activated){
        setLastTime(millis());
        return true;
    }
    else
        return false;
}

void Thread::run(){
    if(function != NULL)
        function();
}

void Thread::active(bool newActive){
    activated = newActive;
}

ThreadControl::ThreadControl(){
    controller = NULL;
    id = ThreadControlId;
    ThreadControlId++;
}

int ThreadControl::getId(){
    return id;
}

bool ThreadControl::addThread(Thread *newThread){
    int cont = 1;
    struct ThreadList *auxiliary;
    if(controller == NULL){
        controller = newController(newThread);
    }
    else{
        auxiliary = controller;
        while(true){
            if(newThread == auxiliary->pointer || cont >= MAX_THREAD_IN_CONTROLLER)
                return false;
            if(auxiliary->next == NULL)
                break;
            auxiliary = auxiliary->next;
            cont++;
        }
        auxiliary->next = newController(newThread);
    }
    return true;
}

struct ThreadList *ThreadControl::newController(Thread *newThread){
    struct ThreadList *auxiliary;
    auxiliary = (struct ThreadList *) malloc(sizeof(struct ThreadList));
    auxiliary->pointer = newThread;
    auxiliary->next = NULL;
    return auxiliary;
}

char *ThreadControl::list(){
    char buffer[MAX_THREAD_IN_CONTROLLER*16]={};
    struct ThreadList *auxiliary;
    if(controller == NULL)
        return '\0';
    else{
        auxiliary = controller;
        while(auxiliary != NULL){
            sprintf(buffer, "%sID = %0.3d -- TIME = %0.6d\n", buffer, auxiliary->pointer->getId(), auxiliary->pointer->getTime());
            auxiliary = auxiliary->next;
        }
    }
    return buffer;
}

int ThreadControl::run(){
    int run = 0;
    struct ThreadList *auxiliary;
    auxiliary = controller;
    while(auxiliary != NULL){
        if(auxiliary->pointer->needRun()){
            auxiliary->pointer->run();
            run++;
        }
        auxiliary = auxiliary->next;
    }
    return run;
}

void ThreadControl::removeAll(){
    struct ThreadList *auxiliary;
    while(controller != NULL){
        auxiliary = controller;
        controller = controller->next;
        free(auxiliary);
    }
}

bool ThreadControl::remove(int rId){
    bool flag = true;
    struct ThreadList *auxiliary;
    struct ThreadList *auxiliary2;
    auxiliary = auxiliary2 = controller;
    while(auxiliary != NULL){
        if(auxiliary->pointer->getId() == rId){
            if(flag)
                auxiliary2 = auxiliary->next;
            else
                auxiliary2->next = auxiliary->next;
            free(auxiliary);
            return true;
        }
        flag = false;
        auxiliary2 = auxiliary;
        auxiliary = auxiliary->next;
    }
    return false;
}

bool ThreadControl::remove(Thread *rThread){
    bool flag = true;
    struct ThreadList *auxiliary;
    struct ThreadList *auxiliary2;
    auxiliary = auxiliary2 = controller;
    while(auxiliary != NULL){
        if(auxiliary->pointer == rThread){
            if(flag)
                auxiliary2 = auxiliary->next;
            else
                auxiliary2->next = auxiliary->next;
            free(auxiliary);
            return true;
        }
        flag = false;
        auxiliary2 = auxiliary;
        auxiliary = auxiliary->next;
    }
    return false;
}

int ThreadControl::size(){
    struct ThreadList *auxiliary;
    int quantity = 0;
    auxiliary = controller;
    while(auxiliary != NULL){
        auxiliary = auxiliary->next;
        quantity++;
    }
    return quantity;
}