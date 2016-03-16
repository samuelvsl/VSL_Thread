#include <vslThread.h>

// Falta incluir comentarios

Thread myThread;

void setup(){
    pinMode(13, OUTPUT);
    myThread.setTime(1000);
    myThread.functionRun(blink);
}

void loop(){
    if(myThread.needRun())
        myThread.run();
}

void blink(){
    digitalWrite(13, !digitalRead(13));
}