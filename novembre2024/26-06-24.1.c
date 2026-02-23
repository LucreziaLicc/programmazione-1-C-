#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>


typedef struct {
    char*input;
    int n;
    char*output;
}parametri;


struct node{
    char*data;
    struct node*next;
};
typedef struct node Node;

struct coda{
    Node*head;
    Node*tail;
};
typedef struct coda Coda;

FILE*Rfile(char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }

    return f;

}

FILE*Wfile(char*filename){
    FILE*f=fopen(filename,"w");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }

    return f;

}


parametri decodeParameters(int argc, char*argv[], char alfabeto[13]){
    if(argc!=4){
        fprintf(stderr,"errore, i parametri da iserire sono 4.\n");
        exit(-1);
    }

    if(atoi(argv[2])<3 || atoi(argv[2])>12){
        fprintf(stderr,"errore, bisogna inserire come secondo parametro un intero compreso fra 3 e 12 inclusi.\n");
        exit(-1);
    }
    parametri p;

    p.input=malloc(strlen(argv[1])+1);
    strcpy(p.input,argv[1]);

    FILE*f= Rfile(p.input);

    if(fscanf(f,"%s",alfabeto)!=1){
        fprintf(stderr,"errore nella lettura del file.\n");
        exit(-1);
    }

    if(strlen(alfabeto)<8 || strlen(alfabeto)>12){
        fprintf(stderr,"errore, la stringa contenuta nel file deve aere lunghezza compresa fra 8 e 12 caratteri, inclusi.\n");
        exit(-1);
    }

    p.output=malloc(strlen(argv[3])+1);
    strcpy(p.output,argv[3]);    

    p.n=atoi(argv[2]);

    printf("\n========================A========================\nParameters: inputFile=%s, n=%d, outputFile=%s\nInput string: %s\n",p.input,p.n,p.output,alfabeto);
    fclose(f);

    return p;

    
}

//PUNTO B

int fibonacci(int n){
    if(n==0 || n==1){
        return n;
    }else{
        n=fibonacci(n-1)+fibonacci(n-2);
        return n;
    }
}


int*arrayA(int n){
    int*A=malloc(sizeof(int)*n);

    for (int i=0; i<n; i++){
        A[i]=fibonacci(i);
    }

    printf("\n========================B========================\nFibonacci array:\n");
    for(int j=0; j<n; j++){
        printf("%d ",A[j]);
    }
    return A;
}
//PUNTO C

unsigned int get_random() {
static unsigned int m_w = 424242;
static unsigned int m_z = 242424;
m_z = 36969 * (m_z & 65535) + (m_z >> 16);
m_w = 18000 * (m_w & 65535) + (m_w >> 16);
return (m_z << 16) + m_w;
}

//funzione che prende in input la stringa alfabeto e un intero h e restituisca una
//stringa di h caratteri casuali campionati dalla stringa alfabeto.
char*sampleString(char*alfabeto,int h){
    char*str=malloc(sizeof(char)*(h+1));
    if(str==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    int len=strlen(alfabeto);

    for(int i=0; i<h; i++){
        str[i]=alfabeto[get_random()%len];
    }
    str[h]='\0';

    return str;
}


//funzione che prende in input l’array A e la stringa alfabeto e permette di
//ottenere l’array di stringhe B come specificato nel punto C.

char**getStringArray(int*A, char*alfabeto, int n){
    char**B=malloc(sizeof(char*)*n);

    for(int i=0; i<n; i++){
        int len=A[i];
        B[i]=sampleString(alfabeto,len);
    }

    for(int i=0; i<n; i++){
        printf("%s\n",B[i]);
    }

    return B;

}

//PUNTO D

void insertNode(Coda*queue,char*data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }
    new->data=data;
    new->next=NULL;

    if(queue->tail==NULL){//se la coda è vuota
        queue->head=new;
        queue->tail=new;
    }else{
        queue->tail->next=new;//si scorre la coda e si inserisce nella tail
        queue->tail=new;
    }
}


char* dequeue(Coda*queue){
    if(queue->head==NULL){
        fprintf(stderr,"la lista è vuota.\n");
        exit(-1);
    }

    char*str=malloc(strlen(queue->head->data)+1);
    strcpy(str,queue->head->data);

    Node*tmp=queue->head;
    queue->head=queue->head->next;
    if(queue->head==NULL){
        queue->tail=NULL;
    }
    free(tmp);
    return str;
}

void printQueue(Coda*queue){
    Node*tmp=queue->head;

    while (tmp!=NULL)
    {
        printf("%s\n",tmp->data);
        tmp=tmp->next;
    }
    
}

/*Inizializzi una coda vuota, scorra gli elementi di B nell’ordine in cui essi appaiono
e li inserisca nella coda. Prima di ciascuna operazione di inserimento (ad eccezione del primo
inserimento), il programma controlla se la stringa B[i] da inserire ha lunghezza dispari. In tal
caso, il programma estrae una stringa dalla coda, la concatena con la stringa B[i] e inserisce
nella coda la stringa risultato della concatenazione. Nel caso in cui la stringa B[i] da inserire
ha lunghezza pari, essa viene inserita regolarmente nella coda.
Si stampi a schermo il contenuto della coda.*/
Coda* getQueue(char**B, int n){

    Coda*Q=malloc(sizeof(Coda));
    if(Q==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    Q->head=NULL;
    Q->tail=NULL;

    insertNode(Q,B[0]);//inserisco la prima stringa  

    for(int i=1; i<n; i++){
        if(strlen(B[i])%2!=0){
            if(Q->head!=NULL){
                char*str=dequeue(Q);
                int newLen=strlen(B[i])+strlen(str)+1;

                char*newStr=malloc(newLen);
                 if (newStr == NULL) {
                    fprintf(stderr, "Errore nell'allocazione della memoria.\n");
                    exit(-1);
                }

                strcpy(newStr,B[i]);
                strcat(newStr,str);
                free(str);
                insertNode(Q,newStr);
            }
        }else{
            insertNode(Q,B[i]);
        }

    }

    return Q;
}

//PUNTO E
void freeQueue(Coda*queue){
        Node* tmp;
    while (queue->head!=NULL) {
        tmp = queue->head;
        dequeue(queue);
    }
    free(queue);
}

void writeToFile(char*filename,Coda*queue){
    FILE*f= Wfile(filename);
    Node*tmp=queue->head;

    while (tmp!=NULL){
        fprintf(f,"%s\n",tmp->data);
        tmp=tmp->next;

    }
    fclose(f);

}



int main(int argc, char*argv[]){
    char alfabeto[13];
    parametri p=decodeParameters(argc, argv,alfabeto);
    //PUNTO B
    int*A=arrayA(p.n);
    //PUNTO C
    printf("\n\n========================C========================\nString array B:");
    char**B=getStringArray(A,alfabeto,p.n);
    //PUNTO D
    printf("\n\n========================D========================\nQueue:\n");
    Coda*Q=getQueue(B,p.n);
    printQueue(Q);
    //PUNTO E
    writeToFile(p.output,Q);
    freeQueue(Q);



    return 0;
}