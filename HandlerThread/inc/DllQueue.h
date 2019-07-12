#include<iostream>
#include"LocMsg.h"
using namespace std;
typedef struct node
{
    struct node* next;
    struct node* prev;
    LocMsg *ptr;
}node;

enum {
    ENQUEUE_SUCCESS = 0,
    ENQUEUE_GENERAL_FAILURE
}Error_type;

class DllQueue
{
    pthread_mutex_t mQueueMutex = PTHREAD_MUTEX_INITIALIZER;
    node* head;
    node* tail;
    public:
    DllQueue():head(NULL), tail(NULL){};
    ~DllQueue()
    {
        node* temp = head;
        node* temp1 = temp; 
        while(temp)
        {
            cout << "Going to delete the allocated space";  
                temp1 = temp -> next;
            delete temp;
            temp = temp1;  
        }
    }
    int enqueue(LocMsg* msg);
    node* dequeue();
    bool isempty();
};
