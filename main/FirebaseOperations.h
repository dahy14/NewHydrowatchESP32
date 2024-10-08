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

unsigned long INTERVAL = 10000; // for both get and set operations
unsigned long intervalSolenoid = 2500;

unsigned long prevUsersDataMillis = 0;
unsigned long intervalUsersData = 15000;

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
    if ((app.ready()) && (currentMillis - prevSolenoidMillis >= intervalSolenoid)) {
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
    float lastSentVol;
    float vol = volume(pulse); // volume from volume.h
    String timestamp = getTime(); // getTime from NTPtime.h

    if(app.ready() && !setFirstRun) {
      // first run supposed to get data from firebase then update self of the current then increment... for now pass 
      setFirstRun = true;
      Database.set<float>(aClient, consPath, vol, setCallback, consUID);
      Database.set<String>(aClient, timestampPath, timestamp, setCallback, timeUID);
      lastSentVol = vol; 
    }
    // sends only when tolerance is greater than set limit 
    const float EPSILON = 0.01; 
    if ((app.ready()) && (currentMillis - prevUsersDataMillis >= intervalUsersData)) {
      prevUsersDataMillis = currentMillis;
      if (fabs(vol - lastSentVol) > EPSILON || fabs(vol - lastSentVol) != 0.00 ) {
        Database.set<float>(aClient, consPath, vol, setCallback, consUID);
        Database.set<String>(aClient, timestampPath, timestamp, setCallback, timeUID);
        lastSentVol = vol; 
      }
        Serial.print("vol: "); Serial.println(vol);
        Serial.print("lastSentVol: "); Serial.println(lastSentVol);
        Serial.print("Difference: "); Serial.println(fabs(vol - lastSentVol));
        Serial.print("Sending data? "); Serial.println(fabs(vol - lastSentVol) > EPSILON);
    }
}

void handleFirebase()
{
    // Run Firebase async tasks
    app.loop();
    Database.loop();
}

#endif // FIREBASE_OPERATIONS_H
