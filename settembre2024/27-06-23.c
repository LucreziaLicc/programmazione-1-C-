#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct {
    int n;
    char*filename;
}parametri;

typedef struct {
    int numeroConto;
    char nome[255];
    char cognome[255];
    float saldo;
}record;

struct node{
    record data;
    struct node*next;
};
typedef struct node Node;

parametri decodeParameters(int argc, char*argv[]){
    if(argc!=3){
        fprintf(stderr,"errore, il numero di parametri da inserire è 3.\n");
        exit(-1);
    }
parametri p;

    if(atoi(argv[1])<3 ||atoi(argv[1])>5){
        fprintf(stderr,"errore, l'intero da inserire deve essere compreso fra 3 e 5.\n");
        exit(-1);        
    }


    p.n=atoi(argv[1]);

   int len=strlen(argv[2]);

    if(len<4 || strcmp(argv[2]+len-4, ".bin")!=0){
        fprintf(stderr,"errore, il nome del file da inserire deve esserecon estensione '.bin'.\n");
        exit(-1);         
    }

    p.filename=malloc(sizeof(char)*len+1);
    strcpy(p.filename,argv[2]);

    printf("\nFilename:%s\nn:%d\n",p.filename,p.n);

    return p;
}
//PUNTO B

bool isEmpty(Node*head){
    return head==NULL;
}

Node* insertNode(Node**head, record data){
    Node*new=malloc(sizeof(Node));

        new->data=data;
        new->next=*head;
        *head=new;

        return new;
}


record readRecord(void){
    record r;
    printf("Inserire il record nel formato: numeroConto nome cognome saldo, premere EOF per terminare\n");
    if(scanf("%d %255s %255s %f",&r.numeroConto,r.nome,r.cognome,&r.saldo)==4){
          return r;
    }
      r.numeroConto=-1;//se l'utente non inserisce i 4 valori, il numero conto viene impostato a -1 e termina
      return r;
}


Node* loadRecords(void){
    Node*L=NULL;

    printf("Inserire i record, premere EOF per terminare.\n");

    while(1){//così il ciclo è infinito fino al raggiungimento del break
        record r=readRecord();
        if(r.numeroConto== -1){//verifica se si è terminato l'input
            break;
        }
        Node*new=insertNode(&L, r);
    }

    printf("\nla lista L è:\n");
    Node*tmp=L;
    while (tmp!=NULL)
    {
        printf("%d %s %s %f\n",tmp->data.numeroConto, tmp->data.nome, tmp->data.cognome, tmp->data.saldo);
        tmp=tmp->next;
    }
    free(tmp);

    return L;
    
}
//PUNTO C
void sort(record*X, float medio, int conto){
    for(int i=0; i<conto-1; i++){
        int min=i;
        float mindist= (X[i].saldo -medio)*(X[i].saldo -medio);
        for(int j=i+1; j<conto; j++){
            if((X[j].saldo -medio)*(X[j].saldo -medio)<(X[min].saldo -medio)*(X[min].saldo -medio)){

                min=j;

            }
        }
        record temp=X[min];
        X[min]=X[i];
        X[i]=temp;
    }
}

void printArray(record*X, int conto){

        for (int i=0; i<conto; i++)
    {
        printf("%d %s %s %f\n",X[i].numeroConto,X[i].nome, X[i].cognome, X[i].saldo);
    }

}

record* getArray(Node**L){

    Node*tmp=*L;
    int conto=0;
    float somma=0;


    while(tmp!=NULL){
        conto++;
        somma += tmp->data.saldo;
        tmp=tmp->next;   
    }

    float medio= somma/(float)conto;
    
    record*X=malloc (sizeof(record)*conto);

    tmp=*L;

    for(int i=0; i<conto; i++){
        X[i]=tmp->data;
        tmp=tmp->next;
    }

    printf("\nl'array X:\n");
    printArray(X,conto);

    sort(X,medio,conto);

    printf("\nl'array X ordinato:\n");
    printArray(X,conto);

    return X;

}



int main(int argc, char*argv[]){ 
    //PUNTO A
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    Node*L=loadRecords();
    //PUNTO C
    record*X=getArray(&L);

    return 0;
}