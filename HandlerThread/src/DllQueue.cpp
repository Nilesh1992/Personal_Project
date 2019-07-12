#include"../inc/DllQueue.h"
using namespace std;

int DllQueue::enqueue(LocMsg *msg)
{
    pthread_mutex_lock( &mQueueMutex );
    Error_type = ENQUEUE_SUCCESS;
    node* tmp = NULL;
    if( (NULL != msg) ) {
        tmp = new node();
        tmp->ptr = msg;
        tmp->next = NULL;
        tmp->prev = NULL;  
        if( NULL == head) {
            head = tmp;
        } else { 
            tmp->prev  = tail;
            tail->next = tmp;
        } 
        tail = tmp;
    } else {
        cout << "No enqueuing anything as msg is empty..." << endl;
        Error_type = ENQUEUE_GENERAL_FAILURE;
    }
    pthread_mutex_unlock( &mQueueMutex );
    return Error_type;
}

node* DllQueue::dequeue()
{
    pthread_mutex_lock( &mQueueMutex );
    node *tmp = NULL;
    if(NULL != head) {
        tmp = head;
        head = head -> next; 

    } else {
        cout << "Queue is empty!!!" << endl;
    }
    pthread_mutex_unlock( &mQueueMutex );
    return tmp;
}

bool DllQueue::isempty()
{
    bool queueState = true;
    pthread_mutex_lock( &mQueueMutex );
    if ((NULL != head)) {
        queueState = false;
    }
    pthread_mutex_unlock( &mQueueMutex );
    return queueState;
}
