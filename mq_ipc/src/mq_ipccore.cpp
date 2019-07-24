#include "../inc/mq_ipccore.h"

using namespace mq_ipccore;


mqd_t IpcCore::createMq(const char* name, int create_flags, mode_t mode = O_RDONLY, 
        struct mq_attr *attrs = NULL)
{
    mqd_t queue_id;
    if(name == NULL || create_flags <= 0){
        cout << "Something went wrong!!!" << endl;
        return -1;
    }

    if(NULL == attrs){
        attrs = &default_attrs;
    }

    if ((create_flags & O_CREAT) > 0){
        queue_id = mq_open(name, create_flags, mode, attrs);
        error_code = errno;
        cout << "Recieved creation error code" << error_code << create_flags << O_RDONLY << O_WRONLY<< O_CREAT<< endl;
    }
    if (NULL != name && queue_id >=0  && ((create_flags & (~O_CREAT)) == 0)) {
        //We should allow to delete a queue only if it has open in read only mode
        mqueue_id = queue_id;  
        queue_name = new char(sizeof(name) + 1);
        memcpy(queue_name, name, sizeof(name));
        queue_name[sizeof(name) + 1] = '\0';
        cout << "Current queue name opened in read mode is ->>" << queue_name << endl;
    }
    return queue_id; 
} 

int IpcCore::closeConnectionMq(mqd_t queue_id)
{
    return mq_close(queue_id);
}

void notifyDataAvailableCallback(union sigval nofication)
{
    struct mq_attr attr;
    ssize_t nr;
    char *buf;
    mqd_t mqdes = nofication.sival_int; 
    cout << "Recieved queue id:-"<< mqdes << " inside" << __func__ << endl;
    if (mq_getattr(mqdes, &attr) == -1) {
        cout << "Failed to get the msg attributes!!!" << endl;
        return;
    }
    buf = new char(attr.mq_msgsize);
    if (NULL == buf){
        cout << "malloc failed to allocate the no. of bytes" << endl;
        return;
    }

    nr = mq_receive(mqdes, buf, attr.mq_msgsize, NULL); //for now lets keep this once we have our recieve
    //api we will update here too
    if (nr == -1) {
        cout << "mqueu seems empty!!!" << endl;
    }
    printf("Read %zd bytes from MQ\n", nr);
    free(buf);
    exit(0);
}

int IpcCore::subscribeToMq()
{
    mqd_t mqdes;
    if (NULL == notifyCallbackInfo) {
        notifyCallbackInfo = new struct sigevent;
        notifyCallbackInfo -> sigev_notify = SIGEV_THREAD;
        notifyCallbackInfo -> sigev_notify_function = &notifyDataAvailableCallback;
        notifyCallbackInfo -> sigev_notify_attributes = NULL;
    }
    notifyCallbackInfo -> sigev_value.sival_int = mqueue_id;   /* Arg. to thread func. */

    if (mq_notify(mqueue_id, notifyCallbackInfo) == -1) {
        cout << "Failed to subscribe to msg queue" << endl;
    }
}

int IpcCore::unsubscribeToMq()
{
    if(NULL != queue_name) {
        cout << "Going to unsubscribe from the queue -->"  << queue_name << endl;
        mq_notify(mqueue_id, NULL);  
    }
}

int IpcCore::destroyMq()
{
    if (NULL != queue_name) {
        cout << "Going to delete the queue-->" << queue_name << endl; 
        mq_unlink(queue_name); 
    }else {
        cout << "Seems queue was open in write/readwrite mode .." << endl;
    }
    return 0;
}

int main()
{
    mqd_t queue_id = -1 ;
    char name[] = "This is nilesh string one";
    char name1[] = "This is nilesh stting two";
    char receiver[MAX_QUEUE_LENGTH];
    IpcCore *mq_sender_client = new mq_ipccore::IpcCore();
    //queue_id = mq_sender_client->createMq("/Niles", O_CREAT|O_WRONLY, 0644);
    //cout << mq_send(queue_id, name, sizeof(name), 0) << endl;
    //cout << "Closing the connection" << mq_sender_client->closeConnectionMq(queue_id)<<endl;  
    //queue_id = mq_sender_client->createMq("/Niles", O_CREAT|O_RDONLY, 0664);
    //mq_sender_client->subscribeToMq();
    //mq_sender_client->unsubscribeToMq();
    //mq_sender_client -> destroyMq();
    /*cout << queue_id << endl;
      mq_sender_client->subscribeToMq(queue_id);
      queue_id = mq_sender_client->createMq("/Niles", O_CREAT|O_WRONLY, 0644);
      cout << mq_send(queue_id, name1, sizeof(name), 0) << endl; 
      cout << "Closing the connection" << mq_sender_client->closeConnectionMq(queue_id)<<endl;*/
    //cout << mq_receive(queue_id, receiver, MAX_QUEUE_LENGTH, 0) << endl; 
    //cout << "Received data is  --> " << receiver << endl;
    //cout << mq_receive(queue_id, receiver, MAX_QUEUE_LENGTH, 0) << endl; 
    //cout << "Received data is  --> " << receiver << endl;
    //cout << "Closing the connection" << mq_sender_client->closeConnectionMq(queue_id)<<endl; 
    return 0;
    //  pause();
}
