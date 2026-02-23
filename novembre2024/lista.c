#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


struct node{
    int data;
    struct node*next;

};
typedef struct node Node;

void insertOrdered(Node**head, int data){
    Node*new=malloc(sizeof(Node));
    new->data=data;
    new->next=NULL;

    if(*head==NULL || (*head)->data > new->data ){
        new->next=(*head);
        *head=new;
        return;
    }
    Node*tmp=*head;
    while(tmp->next!=NULL && tmp->next->data < new->data){
        tmp=tmp->next;
    
    }
  
        new->next=tmp->next;
        tmp->next=new; 
}



void printList(Node* head) {
    Node* tmp = head;
    while (tmp != NULL) {
        printf("%d -> ", tmp->data);
        tmp = tmp->next;
    }
    printf("NULL\n");
}

int main(){
     Node* head = NULL;

    insertOrdered(&head, 5);
    insertOrdered(&head, 2);
    insertOrdered(&head, 8);
    insertOrdered(&head, 1);
    insertOrdered(&head, 3);
    printList(head);

    Node*key=malloc(sizeof(Node));
    key->data=8;
    key->next=NULL;

    deletenode(&head,key);
    printf("\n");
    printList(head);
    
    return 0;

}
