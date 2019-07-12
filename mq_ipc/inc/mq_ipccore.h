/*************************i************
//Bottom line is 
// A given process should one its process queue in readonly mode
// If a given process want to send any hing to other process the it should open 
// the other process queue in write only mode
 ***********************************/

#include<iostream>
#include<string.h>
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
            int destroyMq(mqd_t);
            //int subscribeToMq();
            //int unsubscribeToMq();
            //virtual bool sendToMq();
            //virtual bool recvFromMq();
    };
}



