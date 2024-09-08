#ifndef FIREBASE_OPERATIONS_H
#define FIREBASE_OPERATIONS_H

#include <FirebaseClient.h>
#include "AsyncCallback.h"
#include "Callbacks.h"
#include "globalVars.h"

bool taskComplete = false;
unsigned long currentMillis;
unsigned long previousMillis = 0;
unsigned long interval = 2500;

void getSolenoid()
{
    currentMillis = millis();
    String dataPath = "/SolenoidData/Tenant" + String(tenantId) + "/solenoid";  // tenantId from globalVars.h
    String taskUID = "getTenant" + String(tenantId);
    if(app.ready() && !taskComplete)
    {
        //run once
        taskComplete = true;
        Database.get(aClient, dataPath, solenoidCallback, false, "getTenant" + String(tenantId)); // solenoideCallback from Callbacks.h
    }
    // current and previous millis are declared in pinouts.h
    if (currentMillis - previousMillis >= interval && app.ready()) {
       
        Serial.println(currentMillis);
        previousMillis = currentMillis;
        Database.get(aClient, dataPath, solenoidCallback, false, taskUID); // solenoideCallback from Callbacks.h
    }  
  
}

void handleFirebase()
{
    // Run Firebase async tasks
    app.loop();
    Database.loop();
}

#endif // FIREBASE_OPERATIONS_H
