#include"../inc/MsgTask.h"
using namespace std;

void* run(void*);
MsgTask::MsgTask(string name)
{
    mThreadname = name;
    mstop = false;
    mLinkedList = new DllQueue();
    ThreadCreator(); 
}

MsgTask::~MsgTask()
{
    delete mLinkedList; 
}


void MsgTask::ThreadCreator()
{
    pthread_create( &thread1, NULL, &run, (void*)this);
}

void* run(void* MsgTaskptr) 
{
    cout << ((MsgTask*)MsgTaskptr)->mThreadname <<" is created and now started running" << endl;
    while(!(((MsgTask*)MsgTaskptr) -> mstop)) {
        if(!((MsgTask*)MsgTaskptr)->mLinkedList->isempty()){
            ((MsgTask*)MsgTaskptr)->mLinkedList->dequeue()->ptr -> proc() ;
        } else {
        //cout << "No tasks present as of now to execute :(" << endl;       
 }
    }   
    cout << ((MsgTask*)MsgTaskptr)->mThreadname <<"is going to stop now" << endl;
}

int MsgTask::add_message(LocMsg *ptr)
{
   mLinkedList -> enqueue(ptr);
   return 1;
}
