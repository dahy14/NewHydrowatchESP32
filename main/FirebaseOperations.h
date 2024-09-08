#ifndef FIREBASE_OPERATIONS_H
#define FIREBASE_OPERATIONS_H

#include <FirebaseClient.h>

bool taskComplete = false;

void startFirebaseOperations()
{
    if (app.ready() && !taskComplete)
    {
        taskComplete = true;

        // Perform GET operations
        Database.get(aClient, "/test/int", asyncCB, false, "getTask1");
        Database.get(aClient, "/test/string", asyncCB, false, "getTask2");

        // You can add SET operations here too
    }
}

void handleFirebase()
{
    // Run Firebase async tasks
    app.loop();
    Database.loop();
}

#endif // FIREBASE_OPERATIONS_H
