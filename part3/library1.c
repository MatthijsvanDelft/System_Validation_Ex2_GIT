/* this file contain the user side of the implementation of message passing. */

//#include "library.h"
//#include "library_for_client.h"
//#include "library_for_server.h"
#include "library1.h"

void submit(struct task q[],int pos){
    __CPROVER_assume(pos > 0 && pos < 2);       
    assert(q[pos].state == FREE);
    q[pos].state=WAIT_XFER;
    assert(q[pos].state == WAIT_XFER);
}

void acknowledge(struct task q[],int pos){
    assert(q[pos].state == AVAILABLE);
    q[pos].state=FREE;
    assert(q[pos].state == FREE);
}

int wait_some(struct task q[],int pos[]){
    int res=0;
    while(res==0){
        for(int i=0;q[i].state!=UNUSED;i++){

            if (q[i].state==XFER_DONE){
                pos[res]=i;
                q[i].state=AVAILABLE;
                res++;
                assert(q[i].state == AVAILABLE);
            }
        }
    }
    assert(res >= 0 && res <= 2);
    return res;
}

