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
    int numero_conto;
    int anno_apertura;
    float saldo;
}persona;

struct node{
    persona data;
    struct node*next;
};
typedef struct node Node;

//PUNTO A
parametri readInput(int argc, char*argv[]){
    if(argc!=3){
        fprintf(stderr, "errore, il numero di paramaetri da inserire è 2.\n");
        exit(-1);
    }

    parametri p;

    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);
    p.input=malloc(sizeof(char)*(len1+1));
    p.output=malloc(sizeof(char)*(len2+1));


    if(len1<4 || len2<4 || strcmp(argv[1]+len1-4,".txt")!=0 ||strcmp(argv[2]+len2-4,".txt")!=0){
        fprintf(stderr, "errore,le due stringhe da inserire sono due nomi di file con termiazione '.txt,.\n");
        exit(-1);        
    }

    strcpy(p.input,argv[1]);
    strcpy(p.output,argv[2]);


    printf("\nPUNTO A:\ninput:%s\noutput:%s\n",p.input,p.output);

    return p;
}
//PUNTO B

bool isempty(Node*head){
    return head==NULL;
}

Node* insertInOrder(Node**head,persona data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria\n");
        exit(-1);
    }

    new->data=data;
    new->next=NULL;

    if(isempty(*head) || new->data.anno_apertura<(*head)->data.anno_apertura){
        new->next=*head;
        *head=new;
        return new;

    }

    Node*tmp=*head;
    Node*prev=NULL;

    while (tmp->next!=NULL && new->data.anno_apertura >= tmp->data.anno_apertura)
    {
        prev=tmp;
        tmp=tmp->next;
    }
    
    new->next=tmp;
    if(prev!=NULL){
    prev->next=new;
    }

return new;

}

Node* readFile(char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file\n");
        exit(-1);
    }    

    persona r;
    Node*lista=NULL;

    while (fscanf(f,"%s %s %d %d %f",r.nome,r.cognome,&r.numero_conto,&r.anno_apertura,&r.saldo)==5)
    {
       insertInOrder(&lista,r);
    }
    fclose(f);
        printf("\nPUNTO B:\n");
    return lista;
    
}


void printlist(Node**head){
    Node*tmp=*head;
    while (tmp!= NULL)
    {
        printf("%s %s %d %d %f\n",tmp->data.nome,tmp->data.cognome, tmp->data.numero_conto,tmp->data.anno_apertura,tmp->data.saldo);
        tmp=tmp->next;
    }
    
}

//PUNTO C



int main(int argc, char*argv[]){
    //PUNTO A
    parametri p=readInput(argc, argv);
    //PUNTO B
    Node*lista=readFile(p.input);
    printlist(&lista);

    return 0;
}