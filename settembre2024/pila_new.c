#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node*next;
};

typedef struct node Node;


Node*createNode(int data){//creare un nodo
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"Errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    new->data=data;
    new->next=NULL;

    return new;

}


void push(Node**head,int data){//inserire un nodo in cima
    Node*new=createNode(data);

    new->next=*head;
    *head=new;
}


bool isEmpty(Node*head){//verifica se la pila è vuota
    return head==NULL;
}


void pop(Node**head){//spila
    if(isEmpty(*head)){
        printf("la pila è vuota.\n");
        return;
    }

    Node*tmp=*head;

    int value=tmp->data;

    *head=(*head)->next;

    free(tmp);
}


int pop(Node**head){//spila restituendo il valore tolto
    if(isEmpty(*head)){
        printf("la pila è vuota.\n");
        return;
    }

    Node*tmp=*head;

    int value=tmp->data;

    *head=(*head)->next;

    free(tmp);

    return value;
}

int cima(Node**head){
    if(isEmpty(*head)){
        printf("la pila è vuota.\n");
        return;
    }

    return (*head)->data;

}


int main(){
    return 0;
}