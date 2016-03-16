#ifndef VSLTHREAD_H
#define VSLTHREAD_H

#include <Arduino.h>
#include <inttypes.h>

#define MAX_THREAD_IN_CONTROLLER 15

class Thread;
class ThreadControl;

struct ThreadList{
    Thread *pointer;
    struct ThreadList *next;
};

class Thread{
    private:
        int id;
        long int time,
            lastTime;
        bool activated;
        void (*function)(void);
    public:
        // Constructor
        Thread();
        
        // Define the time (milliseconds) of interval the thread
        void setTime(long int newTime);
        
        // Updates the last time run
        void setLastTime(long int newLastTime);
        
        // Define the functions to be run
        void setFunction(void (*newFunction)(void));
        
        // Get the number of identification
        int getId();
        
        // Get the time of run configured
        long int getTime();
        
        // Check if should run
        bool needRun();
        
        // Run the function set
        void run();
        
        // Enables or disables the execution of the thread
        void active(bool newActive);
        
};

class ThreadControl{
    private:
        int id;
        struct ThreadList *controller;
        
        // Creates new node
        struct ThreadList *newController(Thread *newThread);
    public:
        // Constructor
        ThreadControl();
        
        // Get the number of identification
        int getId();
        
        // Adds threads to controller
        bool addThread(Thread *newThread);
        
        // Lists the elements of controller
        char *list();
        
        // Checks and run all threads controller
        int run();
        
        // Remove all threads of controller
        void removeAll();
        
        // Remove the thread desired by id or name
        bool remove(int rId);
        bool remove(Thread *rThread);
        
        // Show the quantity of thread
        int size();
};

#endif