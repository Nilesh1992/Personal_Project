#include<iostream>
#include"../../HandlerThread/inc/MsgTask.h"
#include<string.h>
class DriverClass {
    MsgTask* mMsgTaskPtr;
    public:
    DriverClass(string name = "Custome Thread")
    {
        mMsgTaskPtr = new MsgTask(name);
    }

    ~DriverClass()
    {
        delete mMsgTaskPtr;
    }
    void task(string taskName, int a, int b);
    void stopper(){mMsgTaskPtr -> ThreadStopper();}
    bool checkForEmpty(){return mMsgTaskPtr -> checkQueueStatus();}
    pthread_t* getThreadInstanceOfMsgThrd(){return mMsgTaskPtr -> getThreadInstance();}
};
