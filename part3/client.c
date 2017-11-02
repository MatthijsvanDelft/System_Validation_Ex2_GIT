#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

//#include "library.h"
//#include "library_for_client.h"
//#include "library_for_server.h"
#include "library1.h"

struct task queue0[]={
{ 1, 0,  FREE,0},       /* slot for sending call to 1(server) */
{-1,-1,  FREE,0},       /* slot for receiving return from 1(server) */
{ 0, 0,UNUSED,0}        /* end of array marker */
};

void* client(void*arg){
    int posArray[2];

    for(int i=0;i<10;i++){
        // prepare request
        queue0[0].arg = i;

        // send request
        submit(queue0, 0);
        wait_some(queue0, posArray);
        acknowledge(queue0, 0);

        // receive response
        //WRONG: SECOND ITERATION THIS SUMBIT ASSERT SHOULD NOT HOLD!
        submit(queue0,1);
        wait_some(queue0, posArray);        
        //acknowledge(queue0, 1);

        // print reponse
        printf("thr0: incr(%d)=%d\n",i,queue0[1].arg);
    }
    return NULL;
}

#ifdef SEPERATE_TEST
void main()
{
    client(NULL);
}
#endif