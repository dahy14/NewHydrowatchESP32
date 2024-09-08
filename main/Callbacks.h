#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <FirebaseClient.h>
#include "globalVars.h"

void doSolenoidCB(AsyncResult &aResult) {
    if (aResult.isError())
    {
        Firebase.printf("Error task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.error().message().c_str(), aResult.error().code());
    }
    if (aResult.available())
    {
        String data = aResult.c_str();

        Firebase.printf("task: %s, payload: %s\n", aResult.uid().c_str(), aResult.c_str());
        if (data == "true")
        {
            Serial.println("Solenoid is open" );
            digitalWrite(solenoidPin, LOW); // solenoidPin From globalVars.h

        }
        else if (data == "false")
        {
            Serial.println("Solenoid is closed");
            digitalWrite(solenoidPin, HIGH); // solenoidPin From globalVars.h
        }
    }
}

void solenoidCallback(AsyncResult &aResult)
{
   doSolenoidCB(aResult);
}
#endif 
