#include "mq_ipccore.h"
using namespace mq_ipccore;

mqd_t IpcCore::createMq(const char* name, int create_flags, mode_t mode = O_RDONLY, 
        struct mq_attr *attrs = NULL)
{
    if(name == NULL || create_flags <= 0)
    {
        cout << "Something went wrong!!!" << endl;
        return -1;
    }

    if(NULL == attrs)
    {
        attrs = &default_attrs;
    }

    if ((create_flags & O_CREAT) > 0)
    {
        queue_id = mq_open(name, create_flags, mode, attrs); 
    }
    return queue_id; 
} 

int IpcCore::destroyMq(mqd_t queue_id)
{
    return mq_close(queue_id);
}

int main()
{
        mqd_t queue_id = -1 ;
    char name[] = "This is nilesh string one";
    char name1[] = "This is nilesh stting two";
    char receiver[MAX_QUEUE_LENGTH];
    IpcCore *mq_sender_client = new mq_ipccore::IpcCore();
    queue_id = mq_sender_client->createMq("/Niles", O_CREAT|O_WRONLY, 0644);
    cout << mq_send(queue_id, name, sizeof(name), 0) << endl;
    cout << "Closing the connection" << mq_sender_client->destroyMq(queue_id)<<endl; 
    queue_id = mq_sender_client->createMq("/Niles", O_CREAT|O_WRONLY, 0644);
    cout << mq_send(queue_id, name1, sizeof(name), 0) << endl; 
    cout << "Closing the connection" << mq_sender_client->destroyMq(queue_id)<<endl; 
    queue_id = mq_sender_client->createMq("/Niles", O_CREAT|O_RDONLY, 0644);
    cout << queue_id << endl;
    cout << mq_receive(queue_id, receiver, MAX_QUEUE_LENGTH, 0) << endl; 
    cout << "Received data is  --> " << receiver << endl;
    cout << mq_receive(queue_id, receiver, MAX_QUEUE_LENGTH, 0) << endl; 
    cout << "Received data is  --> " << receiver << endl;
    cout << "Closing the connection" << mq_sender_client->destroyMq(queue_id)<<endl; 
    return 0;
}
