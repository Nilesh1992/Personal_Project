#include"../inc/DriverClass.h"
void DriverClass::task(string taskName, int a , int b)
{
    struct Message : public LocMsg{
        string mtaskName;
        int ma, mb;
        Message(string taskName, int a, int b):mtaskName(taskName),ma(a),mb(b)
        {
           cout<< "Task->" <<  mtaskName <<" Constructor is called :)" << endl;
        } 
        void proc()
        {
           cout <<"\nGoing to run now task -> " << mtaskName << ":" << ma + mb << endl;
        }          
    }; 
    mMsgTaskPtr->add_message(new Message(taskName, a, b));   
}
