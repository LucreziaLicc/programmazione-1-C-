#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct{
    char*filename;
    int n;
}parametri;

typedef struct{
    int numeroConto;
    char nome[256];
    char cognome[256];
    double saldo;
}record;

struct node{
    record data;
    struct node*next;
};

typedef struct node Node;


parametri decodeParameters(int argc,char*argv[]){
    if(argc!=3){
        fprintf(stderr,"errore, bisogna inserire due parametri, una stringa 'filename' e un intero 'n'\n");
        exit(-1);
    }

    int len=strlen(argv[1]);
    if(len<4 || strcmp(argv[1]+len-4,".bin")!=0){
        fprintf(stderr,"errore, bisogna inserire una stringa 'filename' con estensione '.bin'\n");
        exit(-1);        
    }
    parametri p;

    p.filename=malloc(sizeof(char)*(len+1));
    if(p.filename==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria\n");
        exit(-1);        
    }
    strcpy(p.filename,argv[1]);


    if(atoi(argv[2])<3 || atoi(argv[2])>5){
        fprintf(stderr,"errore, bisogna inserire un intero compreso fra 3 e 5, inclusi\n");
        exit(-1);         
    }
    p.n=atoi(argv[2]);

    printf("\nPUNTO A - valori dei parametri presi in input:\nfilename = %s\nn = %d\n",p.filename,p.n);

    return p;
}
//PUNTO B

Node* insertNode(Node**head, record data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria\n");
        exit(-1);        
    }    

    new->data=data;
    new->next=*head;
    *head=new;

    return new;


}

record readRecord(){
    record r;
    printf("inserisci dei record nel formato: numeroConto nome cognome saldo\n premi EOF per terminare\n" );
    if(scanf("%d %255s %255s %lf",&r.numeroConto,r.nome,r.cognome,&r.saldo)==4){
        return r;
    }
    if (feof(stdin)) {
        printf("Fine dell'input rilevata.\n");
    } else {
        printf("Errore nella lettura dell'input.\n");
    }
    r.numeroConto=-1;
    return r;
    
}


void printList(Node**L){
    Node*tmp=*L;

    while (tmp!=NULL)
    {
        printf("%d %s %s %lf\n",tmp->data.numeroConto,tmp->data.nome,tmp->data.cognome,tmp->data.saldo);
        tmp=tmp->next;
    }
    
}

Node*loadRecords(){
    Node*L=NULL;
    record r;

    while (1){
        r=readRecord();
        if(r.numeroConto== -1){//verifica se si è terminato l'input
            break;
        }
        Node*new=insertNode(&L, r);        
    }
    printf("\n\nPUNTO B - Contenuto di L:\n");
    printList(&L);
    
return L;

}

//PUNTO C

double saldoMedio(record*X,int conto){
    double somma=0;
    for(int i=0; i<conto; i++){
       somma+= X[i].saldo;
    }
    double m=somma/conto;

    return m;

}

void selectionSort(record*X,int conto,double m ){
    for(int i=0; i<conto-1; i++){
        int min=i;
        for(int j=i+1; j<conto; j++){
            if(((X[j].saldo-m)*(X[j].saldo-m))<((X[min].saldo-m)*(X[min].saldo-m))){
                min=j;
            }
        }
        record temp=X[min];
        X[min]=X[i];
        X[i]=temp;
    }
}

record* getArray(Node**L ,int*conto){
    Node*tmp=*L;
    *conto=0;
    while (tmp!=NULL){
        (*conto)++;
        tmp=tmp->next;
    }

    tmp=*L;
    record*X=malloc(sizeof(record)*(*conto));
    for(int i=0; i<*conto; i++){
        X[i]=tmp->data;
        tmp=tmp->next;
    }
    double m= saldoMedio(X,*conto);
    selectionSort(X,*conto,m);

    return X;
}

void printArray(record*X,int conto){
    for(int i=0; i<conto; i++){
        printf("%d %s %s %0.2lf\n",X[i].numeroConto,X[i].nome,X[i].cognome,X[i].saldo);
    }
}

int main(int argc,char*argv[]){
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    Node*L=loadRecords();
    //PUNTO C
    int conto;
    record*X=getArray(&L,&conto);
    printf("\n\nPUNTO C - contenuto ordniato di X:\n");
    printArray(X,conto);
    //PUNTO D
    


    
    
    return 0;
}