#ifndef FIREBASE_OPERATIONS_H
#define FIREBASE_OPERATIONS_H

#include <FirebaseClient.h>

#include "AsyncCallback.h"
#include "Callbacks.h"
#include "globalVars.h"
#include "volume.h"
#include "NTPtime.h"
#include "LCDOperations.h"

bool setFirstRun = false; 
bool taskComplete = false;
unsigned long currentMillis;
unsigned long prevSolenoidMillis = 0;

unsigned long INTERVAL = 2500; // for both get and set operations
unsigned long intervalSolenoid = INTERVAL;

unsigned long prevUsersDataMillis = 0;
unsigned long intervalUsersData = INTERVAL;

void getSolenoid()
{
    getOpLCD(); 
    currentMillis = millis();
    // string paths and UIDS /////////////////////////////////////////
    String dataPath = "/SolenoidData/Tenant" + String(tenantId) + "/solenoid";  // tenantId from globalVars.h
    String taskUID = "getTenant" + String(tenantId);
        // run once
    if(app.ready() && !taskComplete)
    {   //run once
        taskComplete = true;
        Database.get(aClient, dataPath, solenoidCallback,  false, "getTenant" + String(tenantId)); // solenoideCallback from Callbacks.h // no explicit calls for aClient but it is declared in FirebaseSetup.h
    }
    if (currentMillis - prevSolenoidMillis >= intervalSolenoid && app.ready()) {
        prevSolenoidMillis = currentMillis;
        Database.get(aClient, dataPath, solenoidCallback, false, taskUID); // solenoideCallback from Callbacks.h
    }  
}

void setVolume() {
    setOpLCD();
    currentMillis = millis();
    // string paths and UIDS /////////////////////////////////////////
    String consPath = "/UsersData/Tenant" + String(tenantId) + "/consumption";  // tenantId from globalVars.h
    String consUID = "setTenant" + String(tenantId) + "'s Consumption";

    String timestampPath = "/UsersData/Tenant" + String(tenantId) + "/timestamp";  // tenantId from globalVars.h
    String timeUID = "setTenant" + String(tenantId) + "'s Timestamp";
    // values to send  /////////////////////////////////////////////
    float vol = volume(pulse); // volume from volume.h
    String timestamp = getTime(); // getTime from NTPtime.h

    if(app.ready() && !setFirstRun) {
        // first run supposed to get data from firebase then update self of the current then increment... for now pass 
        setFirstRun = true;
    }

    if (currentMillis - prevUsersDataMillis >= intervalUsersData && app.ready()) {
    prevUsersDataMillis = currentMillis;
    Database.set<float>(aClient, consPath, vol, setCallback, consUID);
    Database.set<String>(aClient, timestampPath, timestamp, setCallback, timeUID);
    }
}

void handleFirebase()
{
    // Run Firebase async tasks
    app.loop();
    Database.loop();
}

#endif // FIREBASE_OPERATIONS_H
