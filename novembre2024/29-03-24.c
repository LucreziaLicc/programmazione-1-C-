#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
    char*filename;
}parametri;

struct node{
    int data;
    struct node*next;
};

typedef struct node Node;

parametri decodeParameters(int argc, char*argv[]){
    if(argc!=2){
        fprintf(stderr,"errore, bisogna inserire il nome del file di input, con estensione '.txt'\n");
        exit(-1);
    }

    int len=strlen(argv[1]);
    parametri p;

    if(len<4 || strcmp(argv[1]+len-4,".txt")!=0){
        fprintf(stderr,"errore, bisogna inserire il nome del file di input, con estensione '.txt'\n");
        exit(-1);       
    }

    p.filename=malloc(sizeof(char)*(len+1));
    strcpy(p.filename,argv[1]);

    printf("\n==========PUNTO A==========\nNome del file: %s\n",p.filename);

    return p;
}
//PUNTO B
bool isempty(Node*head){
    return head==NULL;
}

Node* insertNode(Node*head,int data){


    Node*new=malloc(sizeof(Node));
        if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria\n");
        exit(-1);       
    }

    new->data=data;

        if (isempty(head)) {
        // Se la pila è vuota, il nodo diventa la testa
        new->next = NULL;
        }else{

            new->next=head;
        }

    head=new;


    return head;
}



int deleteNode(Node**head){
    if(isempty(*head)){
        fprintf(stderr,"la pila è vuota\n");
        return -1;
    }

    int data=(*head)->data;
    Node*tmp=*head;
    *head=tmp->next;
    free(tmp);

    return data;



}

void printList(Node**head){
    Node*tmp=*head;
    while(tmp!=NULL){
        printf("%d\n",tmp->data);
        tmp=tmp->next;
    }
}

Node* readFile(char*filename){
    FILE*f=fopen(filename,"r");
        if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file\n");
        exit(-1);       
    }

    Node*head=NULL;

    int buffer;
    while (fscanf(f,"%d",&buffer)==1)
    {
       head= insertNode(head,buffer);
    }
    fclose(f);

    printList(&head);
    
    return head;

}
//PUNTO C

float getMean(Node**head,int* conto){

    float somma=0;
     *conto=0;

    while((*head)!=NULL){
        int data=deleteNode(head);
        somma+=(float)data;
        (*conto)++;
    }

    float media=somma/(float)(*conto);

    printf("\n==========PUNTO C==========\nMedia dei valori in P: %0.2f\n",media);

    return media;
    



}

//PUNTO D


Node* fillP(char*filename,Node*head,float m){
    FILE*f=fopen(filename,"r");
            if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file\n");
        exit(-1);       
    }

    char buffer[100];
    if(fgets(buffer,sizeof(buffer),f)==NULL){
        fprintf(stderr,"errore nella lettura del file\n");
        fclose(f);
        exit(-1);    

    }

    int x;
    while(fscanf(f,"%d",&x)==1){
        if(x<m){
            int y=deleteNode(&head);
            y=(x+y)/2;

            head=insertNode(head,y);
        }else{
            head=insertNode(head,x);
        }
    }

    printList(&head);

    return head;



    
}



int main(int argc, char*argv[]){
    //PUNTO A
    parametri p=decodeParameters(argc,argv);
    //PUNTO B
    printf("\n==========PUNTO B==========\nContenuto della pila:\n");
    Node*P= readFile(p.filename);
    //PUNTO C
    int conto;
    float m=getMean(&P,&conto);
    //PUNTO D
    printf("\n\n\n");
    P= fillP(p.filename,P,m);




    return 0;
}
