#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


typedef struct parameters{
    int n;
    int m;
    int p;
}parameters;

//DICHIARAZIONE STACK
   struct node{
    int data;
    struct node* next;//prossimo nodo
 };

typedef struct node Node;

//FUNZIONI
parameters readInput(int argc, char *argv[]);

int***initArray(int n, int m, int p);

int** initB(int***A, int n, int m, int p);

void freeB (int**B);

void freearray(int***A, int n, int m);

//FUNZIONI DI MANIPOLAZIONE STACK


bool is_empty(Node *head);

bool is_full(Node *head);

void push(Node **head,int x);//inserisco un elemento in cima
int pop(Node**head);

Node**initStack(int**B, int n);

void saveStack(Node**head);//funzione che crea un file e salva la pila in senso inverso

//MAIN
int main(int argc, char* argv[]){

parameters pam =readInput(argc,argv);

int ***A= initArray(pam.n,pam.m, pam.p);
int **B=initB(A,pam.n,pam.m,pam.p);

Node**head=initStack(B,pam.n);
saveStack(head);

    return 0;

}



//FUNZIONI

parameters readInput(int argc, char *argv[]){

parameters c={0,0,0};

    if(argc!=4){
        fprintf(stderr,"gli argomenti da inserire devono essere 3.\n");
        exit (-1);
    }

    char*end;

    c.n=(int)strtol(argv[1], &end, 0);
        if (*end!='\0'){
            fprintf(stderr,"il primo argomento da inserire deve essere un intero.\n");
        exit (-1);
        }

    
    c.m=(int)strtol(argv[2], &end, 0);
        if (*end!='\0'){
            fprintf(stderr,"il secondo argomento da inserire deve essere un intero.\n");
        exit (-1);
        }

    
    c.p=(int)strtol(argv[3], &end, 0);
        if (*end!='\0'){
            fprintf(stderr,"il terzo argomento da inserire deve essere un intero.\n");
        exit (-1);
        }

return c;
}

int***initArray(int n, int m, int p){//crea un ARRAY TRIDIMENSIONALE e alloca dinamicamente le sue parti 
                                        //lo popola con i valori input forniti dall'utente

   int*** A= calloc (n,sizeof (int**));//alloco un array di puntatori a puntatori di dimensione 'n'-- A è un puntatore a un 
                                        //array di puntatori doppi (int **), dove ciascun puntatore 
                                         //doppio punta a un array di puntatori singoli (int *).
    for(int i=0; i<n; n++){
        A[i]=calloc (m,sizeof(int*));// Alloca un array di puntatori (dimensione m) per ogni A[i]
    

    for (int j=0; j<m; j++){
        A[i][j]=calloc(p,sizeof(int));// Alloca un array di interi (dimensione p) per ogni A[i][j]
    

        for (int k=0; k<p; k++){
            scanf("%d", &A[i][j][k]);// Riceve input per ogni elemento dell'array tridimensionale
        }
    }
    }
return A;

}

int** initB(int***A, int n, int m, int p){//creo un array di puntatori  a interi (int**)

    int **B= calloc(n, sizeof(int*));
    for(int i=0; i<n; i++){
        int* max=&A[i][0][0];// Inizializza max al primo elemento della matrice A[i]
    
        for (int j =0; j<m; j++){
                    for (int k=0; k<p; k++){
            if (A[i][j][k]>*max){ // Se un elemento è maggiore del valore massimo attuale
                                     // Aggiorna il puntatore max al nuovo valore massimo
                max=&A[i][j][k];
                
            }
        }  
      
    }
    B[i]=max;

}
return B;
}

void freearray(int***A, int n, int m){
for (int i=0; i<n; i++){//libero la memoria allocata
    for (int j=0; j<m; j++){

        free(A[i][j]);
    }
    free(A[i]);
}
free(A);
}

void freeB (int**B){
    free(B);
}

//Stack *create_stack(int capacity){

  //  if(capacity<=0) return NULL;//verifichiamo che la capacità della pila sia >0

    //Stack *stack= malloc(sizeof (Stack));//allochiamo la memoria per lo stack
    //if(stack==NULL) return NULL;//se l'azione cre aerrore restituirà NULL

   // stack->collection=malloc(sizeof(int)*capacity);//alloco la memoria per l'array che conterrà gli elementi dello stack (moltiplico per la capacità dell'array)
   // if(stack->collection == NULL)
    //{
    //free(stack);//se l'allocazione da errore, libera lo stack 
   // return NULL;
   // }

   // stack->capacity=capacity;//creo lo stack della stabilita dimensione
   // stack->size=0;//inizializzo a 0 perchè ancora vuoto
   // return stack;//restituisce un puntatore di tipo Stack

//}

bool is_empty( Node *head){
  return head==NULL;

}

void push(Node **head,int x){
  
     Node *tmp = *head;//tmp è un è un puntatore alla testa della pila
    *head = malloc(sizeof(Node)); //alloco la memoria per creare un nuovo nodo !!!le PARENTESI servono perche -> ha maggiore precedenza rispetto a *!!!

if (*head==NULL){
    perror("errore nell'allocazione della memoria");
    exit(EXIT_FAILURE);
}
    (*head)->next = tmp; //il puntatore next viene inizializzato con il punatore al nodo che era precedentemente la testa della lista(tmp)
    (*head)->data = x;//si inizializza il dato del nuovo nodo dall'argomento della funzione
}

int pop(Node**head){

    if(is_empty(*head)){
        return -1;//controllo se la pila è vuota
    }

    int out=(*head)->data;//accedo al valore data del nodo e lo salvo in 'out' 

    Node*tmp=*head;//il puntatore temporaneo (tmp) punta alla cima della lista, il nodo da rimuovere
    *head=(*head)->next;//la cima della lista diventa iil nodo seguente
    free(tmp);//libero la memoria del nodo rimosso
    return out;//la funzione restituisce il valore 'data' del nodo rimosso

}

Node**initStack(int**B, int n){//Questa funzione prende come input un array bidimensionale di interi B e il suo numero di righe n,
                                    // e poi inserisce i valori di ogni riga dell'array B nella pila.

    Node**head=malloc(sizeof(Node*));

    if (*head==NULL){
    perror("errore nell'allocazione della memoria");
    exit(EXIT_FAILURE);
    }

    *head=NULL;//puntatore alla testa ddella pila, dopo naverne allocato la memoria

    for (int i=0; i<n; i++){//itera su ogni riga dell'array 
        push(head, B[i][0]);//tramite push inserisce il valore di *B[i](primo elemento della riga puntata)
    }
return head;//restituisce il puntatore a puntatore della pila 

}

void saveStack(Node**head){//funzione che permette di scrivere i valori della pila su file in senso inverso.

    FILE*newfile=fopen("out.txt","w");//creo e scrivo su un nuovo file
        if(newfile==NULL){
            perror("errore nell'apertura del file");
            return;
        }
        
    while(!is_empty(*head)){//cicla finchè la pila non è vuota
        int x=pop(head);//estrae il valore dalla pila
        fprintf(newfile,"%d\n",x);//scrive nel file--siccome la pila è LIFO, i valori saranno scritti nel file dall'ultimo inserito al primo
    }
fclose(newfile);
}