#include "queue.h"
#include <stdlib.h>

typedef  struct node_t{
    void* m_value;
    struct node_t* m_next;
}* Node;

struct queue_t{
    Node head, tail;
    int size;
    itemCopy copy_func;
    itemDestroy destroy_func;
};

Queue queueCreate(itemCopy copy_func, itemDestroy destroy_func){
    if(!copy_func || !destroy_func){
        return NULL;
    }
    Queue queue = malloc(sizeof(*queue));
    if(!queue){
        return NULL;
    }
    queue->copy_func = copy_func;
    queue->destroy_func = destroy_func;
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

QueueResult queueEnqueue(Queue queue, void* val){
    if(!queue || !val){
        return QUEUE_PARAM_ERORR;
    }
    void* inner_val = queue->copy_func(val);
    if(!inner_val){
        return QUEUE_MEMORY_ERROR;
    }
    Node new_node = malloc(sizeof(*new_node));
    if(!new_node){
        queue->destroy_func(inner_val);
        return QUEUE_MEMORY_ERROR;
    }
    new_node->m_value = inner_val;
    new_node->m_next = NULL;
    if(queue->size!=0){
        queue->tail->m_next=new_node;
        queue->tail = new_node;
    }
    else{
        queue->head = new_node;
        queue->tail = new_node;
    }
    queue->size++;
    return QUEUE_SUCCESS;
}

static void fillResult(QueueResult* result_p, QueueResult result_val){
    if(result_p){
            *result_p = result_val;
    }
}

void* queueDequeue(Queue queue, QueueResult* result){
    if(!queue){
        fillResult(result, QUEUE_PARAM_ERORR);
        return NULL;
    }
    if(queueSize(queue)<=0){
        fillResult(result, QUEUE_EMPTY);
        return NULL;
    }
    void* val = queue->head->m_value;
    Node tmp = queue->head;
    queue->head = queue->head->m_next;
    if(!queue->head){
        queue->tail = NULL;
    }
    free(tmp);
    queue->size--;
    return val;
}
void* queueDequeue(Queue queue){
    return queueDequeue(queue, NULL);
}

int queueSize(Queue queue){
    if(!queue){
        return -1;
    }
    return queue->size;
}

QueueResult queueDestory(Queue queue){
    if(!queue){
        return QUEUE_PARAM_ERORR;
    }
    Node tmp = NULL;
    while(queue->head){
        tmp = queue->head;
        queue->head = queue->head->m_next;
        queue->destroy_func(tmp->m_value);
        free(tmp);
    }
    free(queue);
    return QUEUE_SUCCESS;
}