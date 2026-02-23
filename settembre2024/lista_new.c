#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{
    int data;
    struct node*next;
};
typedef struct node Node;

Node*createNode(int data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"Errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    new->data=data;
    new->next=NULL;

    return new;
}

bool isEmpty(Node*head){
    return head==NULL;
}

void insertAtBeginning(Node**head, int data){
    Node*new=createNode(data);
        if(new==NULL){
        fprintf(stderr,"Errore nell'allocazione della memoria.\n");
        exit(-1);
    }
    new->next=*head;//imposto come prossimo nodo del nuuovo creato la testa che già c'era
    *head=new;//il nuovo nodo diventa la nuova testa
}

void insertInOrder(Node**head, int data){//implementazione per un ordine crescente dei dati
    Node*new=createNode(data);
        if(new==NULL){
        fprintf(stderr,"Errore nell'allocazione della memoria.\n");
        exit(-1);
    }
        if(*head==NULL || new->data<(*head)->data){//se la lista è vuota oppure è più piccolo della testa
            new->next=*head;
            *head=new;
            return;
            }

    Node*curr=*head;

    while(curr->next!=NULL && curr->next->data<new->data){
        curr=curr->next;
    }
    new->next=curr->next;
    curr->next=new;

}

void deleteNode(Node**head, int value){
    if(*head==NULL){//lista vuota
        printf("la lista è vuota.\n");
        return;
    }
    Node*tmp=*head;
    Node*prev=NULL;

    if(tmp!=NULL && tmp->data==value){//elimino la testa
       *head=tmp->next;
        free(tmp);
        return;
    }
    if(tmp!=NULL && tmp->data!=value){// cerco il nodo da eliminare 
        prev=tmp;//il corrente diventa il precedente 
        tmp=tmp->next;//passo al suo successivo

    }

    if(tmp==NULL){
        printf("nodo non trovato.\n");
        return;
    }

    prev->next=tmp->next;
    free(tmp);

}

void printList(Node**head){
    Node*tmp=*head;

    while(tmp!=NULL){
        printf("%d->",tmp->data);
        tmp=tmp->next;
    }
        printf("NULL\n");


}

int main(){
    Node*head=createNode(12);
    insertInOrder(&head,2);
    insertInOrder(&head,66);
    insertInOrder(&head,8);
    insertInOrder(&head,13);
    insertInOrder(&head,1);
    insertInOrder(&head,80);

    printList(&head);




    return 0;
}
