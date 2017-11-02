/* this file contain the user side of the implementation of message passing. */

#include "library_for_client.h"

//FREE => WAIT_XFER => XFER_DONE => AVAILABLE => FREE.

void submit(struct task q[], int pos){ 
    __CPROVER_assume(pos > 0 && pos < 2);       
    assert(q[pos].state == FREE);
    q[pos].state = WAIT_XFER;
    assert(q[pos].state == WAIT_XFER);
}

void acknowledge(struct task q[], int pos){    
    assert(q[pos].state == AVAILABLE);    
    q[pos].state=FREE;
    assert(q[pos].state == FREE);
}

int wait_some(struct task q[], int posArray[]){
    int res=0;
    while(res==0){
        for(int i=0;q[i].state!=UNUSED;i++){
            assert(q[i].state == (WAIT_XFER || XFER_DONE));
            
#ifdef SEPERATE_TEST            
            if (q[i].state == WAIT_XFER){
                q[i].state = XFER_DONE;
                assert(q[i].state == XFER_DONE);
            }
#endif;                                              

            if (q[i].state == XFER_DONE){
                posArray[res] = i;
                q[i].state = AVAILABLE;
                res++;
                assert(q[i].state == AVAILABLE);
            }
            assert(q[i].state == (AVAILABLE || WAIT_XFER || XFER_DONE));
        }
    }

    assert(res >= 0 && res <= 2);
    return res;
}
