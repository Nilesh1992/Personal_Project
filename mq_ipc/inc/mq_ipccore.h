/*************************i************
//Bottom line is
// A given process should one its process queue in readonly mode
// If a given process want to send any hing to other process the it should open
// the other process queue in write only mode
 ***********************************/

#include<iostream>
#include<string.h>
#include<signal.h>
#ifdef __cplusplus
extern "C" {
#endif
#define MAX_QUEUE_LENGTH 1000
#define MAX_MSG_SIZE 300
#include <mqueue.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
    /* For mode constants */
#ifdef __cplusplus
}
#endif
using namespace std;
namespace mq_ipccore {
    class IpcCore {
        private:
            int error_code;
            struct mq_attr default_attrs;
            struct sigevent *notifyCallbackInfo;
        public:
            mqd_t mqueue_id;
            char* queue_name;
            IpcCore():mqueue_id(-1),error_code(0),queue_name(NULL),
            notifyCallbackInfo(NULL){
                memset(&default_attrs,0,sizeof(default_attrs));
                default_attrs.mq_maxmsg = 10;
                default_attrs.mq_msgsize = 100;
            };
            mqd_t createMq(const char* name, int create_flags, mode_t mode,
                    struct mq_attr *attrs);
            int destroyMq();
            int ParamForceDestroy(const char*);
                int closeConnectionMq(mqd_t);
            int subscribeToMq();
            friend void notifyDataAvailableCallback(union sigval);
            int unsubscribeToMq();
            bool sendToMq(mqd_t,char*, size_t, unsigned int);
            bool recvFromMq(char*, size_t, unsigned int*);
    };
}



