#include <stdio.h>
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

//PUNTO A
parametri decodeParameters(int argc, char*argv[]){
    parametri p;
    if (argc!=2){
        fprintf(stderr,"errore, bisogna inserire un parametro, il nome del file di input con estensione '.txt'.\n");
        exit(-1);
    }

     int len=strlen(argv[1]);

     if(len<4 || len>100 || strcmp(argv[1]+len-4, ".txt")!=0){
        fprintf(stderr,"errore,il nome del file di input deve essere con estensione '.txt' e di massimo 100 caratteri.\n");
        exit(-1);

     }

     p.filename=malloc((len+1)*sizeof(char));
     strcpy(p.filename ,argv[1]);

     printf("==========PUNTO A==========\nNome del file:%s\n", p.filename);

     return p;


}
//PUNTO B

void push(Node**head, int data){
    Node*new=malloc (sizeof(Node));//alloco la memoria per il nuuovo nodo
    if (new==NULL){//se la pila è vuota
        fprintf(stderr,"Errore, nell'allocazione della memoria.\n");
        exit(-1);

    }
    new->data=data;//inserisco il dato nel nodo
    new->next=*head;//punto alla cima
    *head=new;//il nuovo nodo diventa la cima
}

bool isempty(Node*head){
    return head==NULL;//se la cima sarà null (pila vuota), restituirà true
}

void printList(Node*head){
    Node*tmp=head;

    while(tmp!=NULL){
        printf("%d\n",tmp->data);
        tmp=tmp->next;
    }
}


Node*readFile(char*filename){
    FILE*f=fopen(filename, "r");
    if (f==NULL){
        fprintf(stderr,"Errore, nell'apertura del file.\n");
        exit(-1);

    }

    Node*P=NULL;
   int value;
    while (fscanf(f, "%d", &value) != EOF) {
        push(&P, value);
    }
    fclose(f);

    printf("==========PUNTO B==========\nContenuto della pila:\n");

    printList(P);

    return P;


}
//PUNTO C
// [5 punti] Estragga da P gli interi mediante delle operazioni di pop. Inserisca la media degli
//elementi estratti da P in una variabile m.
//Si stampi il valore contenuto in m.
int pop(Node**head){
    if (isempty(*head)){//se la pila è vuota
        fprintf(stderr,"Errore, la pila è vuota.\n");
        return -1;
    }

    Node*tmp=*head;//tramite il puntatore temporaneo salvo il nodo da rimuovere
    int value=tmp->data;
    *head=(*head)->next;//il prossimo nodo diventa la nuova cima
    free(tmp);
    return value;
}

float getMean(Node**P){
    int somma=0;
    int count=0;


    while(!isempty(*P)){
    somma+=pop(P);
    count++;
    }
        if (count==0){
            fprintf(stderr,"Errore: la lista è vuota.\n");
            return 0;
        }
    float m= ((float)somma)/count;

    printf("==========PUNTO C==========\nMedia dei valori in P:%f\n",m);

    return m;

}
//PUNTO D
void fillP(char*filename, Node**P,float m){
    FILE*f=fopen(filename, "r");
     if (f==NULL){
        fprintf(stderr,"Errore, nell'apertura del file.\n");
        exit(-1);

    }

    *P=NULL;
    int value;
    if(fscanf(f, "%d", &value) == EOF){
        fprintf(stderr,"Errore, file vuoto.\n");
        exit(-1);
    }
    push(P,value);

    while (fscanf(f, "%d", &value) != EOF) {
        if(value> m){
            push(P, value);

        }else{
            int y=pop(P);
            push(P,(value+y)/2);

        }
    }

    printf("==========PUNTO D==========\nContenuto della pila:\n");
    printList(*P);

fclose(f);

}
//PUNTO E

void sort(int array[], int n){//uso insertion sort
    for(int i=1; i<n; i++){
        int key=array[i];
        int j = i-1;

        while(j>=0 && array[j]>key){
            array[j+1]=array[j];
            j=j-1;
        }
        array[j+1]=key;
    }

}

int*transferP(Node**P){

    Node*tmp=*P;
    int count=0;

    while(tmp!=NULL){
        count++;
        tmp=tmp->next;
    }

    int*A=calloc(count,sizeof(int));

    Node*ttp=*P;
    for(int i=0;i<count;i++){
        A[i]=ttp->data;
        ttp=ttp->next;
    }

sort(A,count);


    printf("==========PUNTO E==========\n");

     for(int i=0;i<count;i++){
        printf("%d\n",A[i]);
    }
return A;

}

int main(int argc, char*argv[]){
    //PUNTO A
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    Node*P=readFile(p.filename);
    //PUNTO C
    float m=getMean(&P);
    //PUNTO D
    fillP(p.filename,&P,m);
    //PUNTO E
    int *A=transferP(&P);
    return 0;
}