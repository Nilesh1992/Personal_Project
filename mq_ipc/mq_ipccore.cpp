#include<iostream>
#include<string.h>
//#include"mq_common.h"
#ifdef __cplusplus
extern "C" {
#endif
#define MAX_QUEUE_LENGTH 1000
#define MAX_MSG_SIZE 300
#include <mqueue.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>
#include <errno.h>
    /* For mode constants */
#ifdef __cplusplus
}
#endif
using namespace std;

namespace mq_ipccore {
    class IpcCore {
        private:
            mqd_t queue_id;
            int error_code;
            struct mq_attr default_attrs;
        public:
            IpcCore():queue_id(-1),error_code(0){
                memset(&default_attrs,0,sizeof(default_attrs)); 
                default_attrs.mq_maxmsg = 10;
                default_attrs.mq_msgsize = 100;
            };
            mqd_t createMq(const char* name, int create_flags, mode_t mode, 
                    struct mq_attr *attrs);
            //int destroyMq();
            //int subscribeToMq();
            //int unsubscribeToMq();
            //virtual bool sendToMq();
            //virtual bool recvFromMq();
    };

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
            error_code = errno;
            cout << "Error received --->" << error_code << endl;
        }
            return queue_id; 
    } 
}


int main()
{
    mqd_t queue_id = -1 ;
    char name[] = "This is nilesh string one";
     char name1[] = "This is nilesh stting two";
     char receiver[MAX_QUEUE_LENGTH];
    mq_ipccore::IpcCore *mq_sender_client = new mq_ipccore::IpcCore();
    queue_id = mq_sender_client->createMq("/Niles", O_CREAT|O_RDWR, 0644);
   cout << mq_send(queue_id, name, sizeof(name), 0) << endl; 
    queue_id = mq_sender_client->createMq("/Niles", O_CREAT|O_RDWR, 0644);
   cout << mq_send(queue_id, name1, sizeof(name), 0) << endl; 
    queue_id = mq_sender_client->createMq("/Niles", O_CREAT|O_RDONLY, 0644);
    cout << queue_id << endl;
   cout << mq_receive(queue_id, receiver, MAX_QUEUE_LENGTH, 0) << endl; 
   cout << "Received data is  --> " << receiver << endl;
   cout << mq_receive(queue_id, receiver, MAX_QUEUE_LENGTH, 0) << endl; 
   cout << "Received data is  --> " << receiver << endl;
    return 0;
}
