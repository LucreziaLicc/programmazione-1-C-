#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    char filename[100];
}parametri;

struct node{
    int data;
    struct node*next;
};
typedef struct node Node;


parametri decodeParameters(int argc, char*argv[]){
    if(argc!=2){
        fprintf(stderr, "errore, bisogna inserire un parametro 'filename' con estenzione '.txt', di massimo 100 caratteri.\n");
        exit(-1);
    }

    int len=strlen(argv[1]);
    if(len<4 || strcmp(argv[1]+len-4,".txt")!=0){
         fprintf(stderr, "errore, bisogna inserire un parametro 'filename' con estenzione '.txt', di massimo 100 caratteri.\n");
        exit(-1);       
    }

    parametri p;
    strcpy(p.filename,argv[1]);

    printf("\n==========PUNTO A==========\nNome del file:%s\n",p.filename);

    return p;
}
//PUNTO B
bool isempty(Node*head){
    return head==NULL;
}

void printStack(Node**head){
    Node*tmp=*head;

    while (tmp!=NULL)
    {
       printf("%d\n",tmp->data);
       tmp=tmp->next;
    }
}

Node*insertNode(Node*head, int data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr, "errore nell'allocazione della memoria.\n"),
        exit(-1);
    }
    new->data=data;
    if(isempty(head)){
        new->next=NULL;
    }else{
        new->next=head;
    }
    head=new;
    return head;

}

Node* readFile(char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr, "errore nell'apertura del file.\n"),
        exit(-1);
    }  

    Node*head=NULL;

    int buffer;  
    while (fscanf(f,"%d",&buffer)==1)
    {
        head=insertNode(head,buffer);
    }
    fclose(f);

    printStack(&head);

    return head;
    


}
//PUNTO C

int pop(Node**head){
    if(isempty(*head)){
        fprintf(stderr,"la pila è vuota.\n");
        exit(-1);
    }
    int x=(*head)->data;
    Node*tmp=*head;
    *head=tmp->next;

    free(tmp);

    return x;
}


float getMean(Node**head){
    float conto=0;
    float somma=0;

    while (*head!=NULL)
    {
       int data=pop(head);
       somma +=(float)data;
       conto++;
    }
    float media=somma/conto;

    printf("%0.2f",media);
    return media;

    
}
//PUNTO D

void fillP(Node**head,char*filename, float m){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr, "errore nell'apertura del file.\n");
        exit(-1);
    }

    int x;  
    fscanf(f,"%d",&x);
    *head=insertNode(*head,x);

    
    while (fscanf(f,"%d",&x)==1)
    {
        if(x<m){
           int y=pop(head);
           *head=insertNode(*head,(x+y)/2);

        }else{
        *head=insertNode(*head,x);
        }
    }
    fclose(f);
    printStack(head);

}
//PUNTO D

void sort(int*A,int size){
    for(int j=1; j<size; j++){
        int elem=A[j];
        int i=j-1;
        while (i>=0 && A[i]>elem){
           A[i+1]=A[i];
           i=i-1;
        }
        A[i+1]=elem;
        
    }
}

int*transferP(Node**head){
    Node*tmp=*head;
    int size=0;

    while (tmp!=NULL)
    {
        size++;
        tmp=tmp->next;
    }
    
    int*A=malloc(sizeof(int)*size);
    tmp=*head;
    for(int i=0; i<size; i++){
        A[i]=tmp->data;
        tmp=tmp->next;
    }

    sort(A,size);
    
    for(int j=0; j< size; j++){
        printf("%d ",A[j]);
    }

    return A;

}

int main(int argc, char*argv[]){
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    printf("\n==========PUNTO B==========\nContenuto della pila:\n");
    Node*P=readFile(p.filename);
    //PUNTO C
    printf("\n\n==========PUNTO C==========\nMedia dei valori in P:");
    float m=getMean(&P);
    //PUNTO D
    printf("\n\n==========PUNTO D==========\nContenuto della pila:\n");
    fillP(&P,p.filename,m);
    //PUNTO E
    printf("\n\n==========PUNTO E==========\n");
    int*A=transferP(&P);


    return 0;
}