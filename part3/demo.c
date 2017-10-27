/*
  compile with: gcc -std=c99 -pthread -I. -o demo demo.c client.c server.c library.c
*/

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//#include "library.h"
#include "library_for_client.h"
//#include "library_for_server.h"
//#include "library1.h"

extern struct task queue0[];

extern struct task queue1[];

void* io_daemon(void*arg){
    struct task** queues=(struct task**)arg;
    int N=0;
    while(queues[N]!=NULL)N++;
    printf("managing %d queues\n",N);
    for(;;){
        for(int w=0;w<N;w++){
            for(int i=0;queues[w][i].state!=UNUSED;i++){
                if (queues[w][i].state==WAIT_XFER){
                    int dw=queues[w][i].dest_worker;
                    if (dw<0) continue;
                    int ds=queues[w][i].dest_position;
                    if (queues[dw][ds].state==WAIT_XFER){
                        queues[dw][ds].arg=queues[w][i].arg;
                        queues[w][i].state=XFER_DONE;
                        queues[dw][ds].state=XFER_DONE;
                    }
                }
            }
        }
    }
}

struct task* my_queues[]={queue0,queue1,NULL};

extern void* client(void*arg);

extern void* server(void*arg);

int main(int argc,char*argv[]){
    pthread_t io;
    pthread_t thr0;
    pthread_t thr1;
    if (pthread_create(&io,NULL,io_daemon,my_queues)) {
        printf("startup of io daemon failed");
		exit(1);
	}
    if (pthread_create(&thr0,NULL,client,NULL)) {
        printf("startup of io daemon failed");
		exit(1);
	}
    if (pthread_create(&thr1,NULL,server,NULL)) {
        printf("startup of io daemon failed");
		exit(1);
	}
    pthread_join(thr0,NULL);
	return 0;
}

