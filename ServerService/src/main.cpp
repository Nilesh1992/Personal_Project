#include<iostream>
#include"../inc/DriverClass.h"
int main()
{
    DriverClass *DC = new DriverClass();
    DC -> task("Task1",10,20);
    DC -> task("Task2",20,30);
    DC -> task("Task3",40,50);
    while(!(DC -> checkForEmpty()))
    {  
    }
    DC -> stopper();
    pthread_join(*(DC->getThreadInstanceOfMsgThrd()), NULL);
    return 0;
}
