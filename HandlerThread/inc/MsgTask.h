#include<string.h>
#include <pthread.h>
#include"DllQueue.h"


class MsgTask
{
    string mThreadname;
    DllQueue *mLinkedList;
    pthread_t thread1;
    bool mstop;
    public:
    MsgTask(string);
    ~MsgTask(); 
    friend void* run(void*);
    void ThreadCreator();
    void ThreadStopper()
    {
          mstop = true;
    }
    int add_message(LocMsg*);
    bool checkQueueStatus()
    {
        return mLinkedList -> isempty();
    }
    pthread_t* getThreadInstance()
    {
        return &thread1;
    }
    
};
