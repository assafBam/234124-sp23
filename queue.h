#ifndef QUEUE_H_
#define QUEUE_H_

typedef enum {QUEUE_SUCCESS, QUEUE_MEMORY_ERROR, QUEUE_PARAM_ERORR, QUEUE_EMPTY, QUEUE_ERROR} QueueResult;

typedef void*(*itemCopy)(void*);
typedef void (*itemDestroy)(void*);

typedef struct queue_t* Queue;

Queue queueCreate(itemCopy copy_func, itemDestroy destroy_func);

QueueResult queueEnqueue(Queue queue, void* val);

void* queueDequeue(Queue queue, QueueResult* result);
void* queueDequeue(Queue queue);

int queueSize(Queue queue);

QueueResult queueDestory(Queue queue);

#endif