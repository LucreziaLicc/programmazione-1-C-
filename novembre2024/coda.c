#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
    int data;
    struct node*next;
};

typedef struct node Node;


struct coda{
    Node*head;
    Node*tail;
};

typedef struct coda Coda;


void enqueue(Coda*queue, int data){
    Node*new=malloc(sizeof(Node));
    new->data=data;
    new->next=NULL;
    
    if(queue->head==NULL){
        queue->head=new;
        queue->tail=new;
    }else{
        queue->tail->next=new;
        queue->tail=new;

    }
}


int dequeue(Coda*queue){
    if(queue->head==NULL && queue->tail==NULL){
        fprintf(stderr, "la coda è vuota\n");
        exit(-1);
    }
        Node*tmp=queue->head;
        int data=tmp->data;
        queue->head=queue->head->next;
    
    if(queue->head==NULL){
        queue->tail=NULL;
    }
    free(tmp);

    return data;

}

void printQueue(Coda*queue){
    Node*tmp=queue->head;
    while(tmp!=NULL){
        printf("%d ",tmp->data);
        tmp=tmp->next;
    }
}

int main(){
    Coda*queue=malloc(sizeof(Coda));
    for(int i=1; i<=10; i++){
        enqueue(queue,i);
    }
    printQueue(queue);

}