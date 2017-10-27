#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//#include "library.h"
#include "library_for_client.h"
//#include "library_for_server.h"
//#include "library1.h"

struct task queue0[]={
{ 1, 0,  FREE,0},       /* slot for sending call to 1 */
{-1,-1,  FREE,0},       /* slot for receiving return from 1 */
{ 0, 0,UNUSED,0}        /* end of array marker */
};

void* client(void*arg){
    int pos[2];
    for(int i=0;i<10;i++){
        // prepare request
        queue0[0].arg=i;
        // send request
        submit(queue0,0);
        wait_some(queue0,pos);
        acknowledge(queue0,0);
        // receive response
        submit(queue0,1);
        wait_some(queue0,pos);
        // print reponse
        printf("thr0: incr(%d)=%d\n",i,queue0[1].arg);
    }
    return NULL;
}

