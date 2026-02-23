#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


typedef struct {
    char*input;
    char*output;

}parametri;

typedef struct {
    char nome[255];
    char cognome[255];
    int eta;
    int peso; 
    int altezza;
    char sesso;
}persona;

struct node{
    persona data;
    struct node*next;
};
typedef struct node Node;

//PUNTO A
parametri readInput (int argc, char*argv[]){
    if(argc!=3){
        fprintf(stderr,"Errore i parametri da inserire sono due stringhe.\n");
        exit(-1);
    }

    parametri p;
    
    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);

    p.input=malloc(sizeof(char)*(len1+1));
    p.output=malloc(sizeof(char)*(len2+1));

    if(len1<4 || len2<4 || strcmp(argv[1]+len1-4, ".txt")!=0 || strcmp(argv[2]+len2-4, ".txt")!=0){
        fprintf(stderr,"Errore, le stringhe da inserire devono essere due nomi di file con estensione '.txt'\n");
        exit(-1);
    }

    strcpy(p.input,argv[1]);
    strcpy(p.output,argv[2]);

    printf("PUNTO A:\ninput:%s\noutput:%s\n",p.input,p.output);

    return p;

}

//PUNTO B

Node*insertNode(Node**head, persona data){

    Node*new=malloc(sizeof(Node));
    new->data=data;
    if(*head==NULL || (*head)->data.eta >= new->data.eta){
        new->next=*head;
        *head=new;
    }else{
    
        Node*tmp=*head;  
        while (tmp->next!=NULL && tmp->data.eta<new->data.eta) {
            tmp=tmp->next;
        }
            new->next=tmp->next;
            tmp->next=new;
        }
       
    return new;
    }

void printList(Node**head){
    Node*tmp=*head;

    while (tmp!=NULL)
    {
        printf("%7s %10s %4d %6d %6d %4c\n",tmp->data.nome,tmp->data.cognome,tmp->data.eta,tmp->data.peso,tmp->data.altezza,tmp->data.sesso);
        tmp=tmp->next;
    }
    
}

Node* readFile(char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }

    Node*head=NULL;
    persona r;

    while(fscanf(f,"%s %s %d %d %d %c",r.nome,r.cognome,&r.eta,&r.peso,&r.altezza,&r.sesso)==6){
        insertNode(&head,r);
    }
    fclose(f);
    printf("\nPUNTO B:\n");
     printList(&head);

    return head;

}
//PUNTO C
float imc(int p, int a){
    float IMC=(float)p/(((float)a/100)*((float)a/100));
    return IMC;
}

Node* getMax(Node**head){
    Node*tmp=*head;
    Node*max=*head;

    while (tmp!=NULL)
    {
        if(imc(tmp->data.peso,tmp->data.altezza)>imc(max->data.peso,max->data.altezza)){
            max=tmp;
        }
        tmp=tmp->next;
    }
   return max;
    
}
//PUNTO D
void insertHead(Node**head,persona data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"erroe nell'allocazione della memoria.\n");
        exit(-1);
    }

    new->data=data;
    new->next=*head;
    *head=new;
}

void delete(Node **head, Node *node) {
    if(*head == node) {
        *head = (*head)->next;
        free(node);
    }

    Node *tmp = *head;

    while(tmp!=NULL && tmp->next != node) {
        tmp = tmp->next;
    }

    if(tmp!=NULL && tmp->next == node) {
      tmp->next = node->next;
        free(node);
    }
}


Node*listaB(Node**head){
    Node*B=NULL;

for (int i = 0; i < 3; i++){
      Node*max=getMax(head);
      
      insertHead(&B,max->data);
      delete(head,max);
}

printf("\nPUNTO D:\n");
printList(&B);

return B;

}
//PUNTO E

void writeFile(char*filename,Node**B){
    FILE*f=fopen(filename,"w");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }

    Node*tmp=*B;

    while(tmp!=NULL){
        fprintf(f,"%7s %10s %4d %6d %6d %4c\n",tmp->data.nome,tmp->data.cognome,tmp->data.eta,tmp->data.peso,tmp->data.altezza,tmp->data.sesso);
        tmp=tmp->next;
    }
    fclose(f);

}

int main(int argc, char*argv[]){
    //PUNTO A
    parametri p=readInput(argc,argv);
    //PUNTO B
   Node*A=readFile(p.input);
   //PUNTO C
   Node*max=getMax(&A);
    printf("\nPUNTO C:\nla persona con imc più alto è: %s %s %d %d %d %c\n", max->data.nome,max->data.cognome,max->data.eta,max->data.peso,max->data.altezza,max->data.sesso);
   //PUNTO D
   Node*B=listaB(&A);
   //PUNTO E
   writeFile(p.output,&B);


    return 0;
}