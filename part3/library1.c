/* this file contain the user side of the implementation of message passing. */

//#include "library.h"
//#include "library_for_client.h"
//#include "library_for_server.h"
#include "library1.h"

void submit(struct task q[],int pos){
    q[pos].state=WAIT_XFER;
}

void acknowledge(struct task q[],int pos){
    q[pos].state=FREE;
}

int wait_some(struct task q[],int pos[]){
    int res=0;
    while(res==0){
        for(int i=0;q[i].state!=UNUSED;i++){
            if (q[i].state==XFER_DONE){
                pos[res]=i;
                q[i].state=AVAILABLE;
                res++;
            }
        }
    }
    return res;
}

