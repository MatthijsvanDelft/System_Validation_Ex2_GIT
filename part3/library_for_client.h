
#ifndef LIBRARY_FOR_CLIENT_H
#define LIBRARY_FOR_CLIENT_H

#define WAIT_XFER 1
#define XFER_DONE 2
#define AVAILABLE 3
#define FREE      4
#define UNUSED    0

struct task {
    int dest_worker;  // [SEND] The worker number of the intended receiver of the message/task.
                      // [RECV] set to -1 to indicate a buffer used for receiving.
    int dest_position; // [SEND] The position of the buffer into which the message must be placed.
                       // [RECV] set to -1 to indicate a buffer used for receiving.
    int state;        // contains the state of the buffer.
                      // The end of a buffer array (queue) is indiced by the UNUSED state.
    int arg;          // contains the data of the message or argument of the task.
};

/*
    Submit the buffer q[pos] for sending.
    
    requires  q[pos].state==FREE
    ensures   q[pos].state==WAIT_XFER
    
 */
extern void submit(struct task q[],int pos);

/*
    Acknowledge that processing of buffer q[pos] has been completed.
    
    requires  q[pos].state==AVAILABLE
    ensures   q[pos].state==FREE
    
 */
extern void acknowledge(struct task q[],int pos);

/*
    Wait for at least one new message transfer to succeed.
    
    Returns the number of completed message tranfers.
    The indices of the new transfers are put into 
    the array pos. Therefor, the array pos has to be big
    enough to hold the maximum number of new transfers possible.
 */
extern int wait_some(struct task q[],int pos[]);

#endif

