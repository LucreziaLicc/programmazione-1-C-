#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
    char*input;
    char*output;
}parametri;

typedef struct{
    char nome [255];
    char cognome [255];
    int età;
    int peso; 
    int altezza; 
    char sesso;
}persona;

struct node{
    persona data;
    struct node*next;

};
typedef struct node Node;

parametri readInput(int argc, char*argv[]){
    if(argc!=3){
        fprintf(stderr,"errore, bisogna inseire due nomi di file con estensione '.txt'\n");
        exit(-1);
    }
    parametri p;

    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);

    if(len1<4 || len2<4 || strcmp(argv[1]+len1-4,".txt")!=0 || strcmp(argv[2]+len2-4,".txt")!=0 ){
        fprintf(stderr,"errore, bisogna inseire due nomi di file con estensione '.txt'\n");
        exit(-1);        
    }

    p.input=malloc(sizeof(char)*(len1+1));
    p.output=malloc(sizeof(char)*(len2+1));

    strcpy(p.input,argv[1]);
    strcpy(p.output,argv[2]);

    printf("\n=======PUNTO A=======\ninput = %s, output = %s\n",p.input, p.output);
    return p;
}

//PUNTO B
//funzione per la lettura del contenuto del file. La funzione prende in input il nome
//del file da leggere e restituisce un riferimento alla testa della lista concatenata.

Node*insertOrdered(Node**head, persona data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria\n");
        exit(-1);
    }
    new->data=data;
    new->next=NULL;

    if(*head==NULL || (*head)->data.età > new->data.età){
        new->next=(*head);
        (*head)=new;
        return new;
    }

    Node*tmp=*head;
    while(tmp->next!=NULL && tmp->next->data.età <= new->data.età){
        tmp=tmp->next;
    }
    new->next=tmp->next;
    tmp->next=new;
    return new;
}

void printList(Node**head){
    Node*tmp=*head;
    while(tmp!=NULL){
        printf("%7s %9s %4d %6d %6d %4c\n",tmp->data.nome,tmp->data.cognome,tmp->data.età,tmp->data.peso,tmp->data.altezza,tmp->data.sesso);
        tmp=tmp->next;
    }
}

Node*readFile(char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file\n");
        exit(-1);
    }

    persona data;
    Node*A=NULL;

    while(fscanf(f,"%s %s %d %d %d %c",data.nome, data.cognome, &data.età, &data.peso, &data.altezza, &data.sesso)==6){
        Node*new=insertOrdered(&A,data);
    }
    fclose(f);
    printList(&A);
    return A;
}

//PUNTO C
float IMC(int peso, int altezza){
    float imc=(float)peso/(((float)altezza/100)*((float)altezza/100));
    return imc;
}


Node* getMax(Node**head){
    Node*tmp=*head;
    Node*maxNode=NULL;
    float maxImc=0;
    while(tmp!=NULL){
        float x=IMC(tmp->data.peso, tmp->data.altezza);
        if(x>maxImc){
            maxImc=x;
            maxNode=tmp;
        }
        tmp=tmp->next;
    }

  return maxNode;
}

//PUNTO D

void deletenode(Node**head, Node* key){
    if(*head==NULL){
        fprintf(stderr,"la lista è vuota\n");
        exit(-1);
    }

    if(*head==key){//se è la testa
        *head=(*head)->next;
        free(key);
    }
    Node*tmp=*head;
   
    while(tmp!=NULL && tmp->next!=key){//ricerco in mezzo
        tmp=tmp->next;
    }
    if(tmp!=NULL && tmp->next==key){
        tmp->next=key->next;
        free(key);
    }
}

void insertHead(Node**head,persona data){
    Node*new=malloc(sizeof(Node));
    new->data=data;
    new->next=*head;
    *head=new;
}

Node*listaB(Node**head){
    Node*B=NULL;
    for(int i=0; i<3; i++){
        Node*max=getMax(head);
        insertHead(&B,max->data);
        deletenode(head,max);
    }
    printf("\nlista A:\n");
    printList(head);
    printf("\nlista B:\n");
    printList(&B);
    return B;
}

//PUNTO E

void writeFile(char*filename,Node**B){
    FILE*f=fopen(filename,"w");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file\n");
        exit(-1);
    }    

    Node*tmp=*B;
    while(tmp!=NULL){
        fprintf(f,"%7s %9s %4d %6d %6d %4c\n",tmp->data.nome,tmp->data.cognome,tmp->data.età,tmp->data.peso,tmp->data.altezza,tmp->data.sesso);
        tmp=tmp->next;        
    }

}



int main(int argc, char*argv[]){
    parametri p=readInput(argc, argv);
    //PUNTO B
    printf("\n=======PUNTO B=======\n");
    Node*A=readFile(p.input);
    //PUNTO C
    Node*maxNode=getMax(&A);
    printf("\n=======PUNTO C=======\n");
    printf("%7s %9s %4d %6d %6d %4c\n",maxNode->data.nome,maxNode->data.cognome,maxNode->data.età,maxNode->data.peso,maxNode->data.altezza,maxNode->data.sesso);
   
    //PUNTO D
    Node*B=listaB(&A);
    //PUNTO E
    writeFile(p.output,&B);
    return 0;
}