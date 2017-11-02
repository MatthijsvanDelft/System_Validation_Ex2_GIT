#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

//#include "library.h"
//#include "library_for_client.h"
//#include "library_for_server.h"
#include "library1.h"

struct task queue1[]={
{-1,-1,  FREE,0},      /* slot for receiving call form 0 */
{ 0, 1,  FREE,0},      /* slot for sending return to 0 */
{ 0, 0,UNUSED,0}       /* end of array marker */
};

void do_work(){
    int posArray[2];
    int K = wait_some(queue1, posArray);
    for(int i=0;i<K;i++){

        if (posArray[i] == 0) {
            int tmp=queue1[0].arg;
            printf("thr1: got %d\n",tmp);

            assert(queue1[1].state == FREE);
            while(queue1[1].state != FREE){
                printf("thr1: nested loop\n");
                do_work();
            }
            queue1[1].arg = tmp;
            submit(queue1, 1);
            submit(queue1, 0);
            printf("thr1: return %d\n",tmp);
        }

        //Is not always acknowledged.  
        if (posArray[i] == 1) {
            acknowledge(queue1, 1);
        }
    }
}

void* server(void*arg){
    submit(queue1,0);
    for(;;){
        printf("thr1: main loop \n");
        do_work();
    }
}

#ifdef SEPERATE_TEST
void main()
{
    server(NULL);
}
#endif

