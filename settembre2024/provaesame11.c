#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

unsigned int get_random() {
static unsigned int m_w = 424242;
static unsigned int m_z = 242424;
m_z = 36969 * (m_z & 65535) + (m_z >> 16);
m_w = 18000 * (m_w & 65535) + (m_w >> 16);
return (m_z << 16) + m_w;
}


typedef struct{
    char*input;
    int n;
    char*output;
}parametri;

struct node {
    char*str;
    struct node*next;
};


struct queue{
    struct node*front;
    struct node*rear; 
};


//PUNTO A
parametri decodeParameters(int argc, char*argv[]){
    parametri p;
    if(argc!=4){
        fprintf(stderr, "errore, bisogna inserire 3 parametri.\n");
        exit(-1);
    }

    p.input=malloc(strlen(argv[1])+1);//IMPORTANTE bisogna allocare la memoria per i puntatori (input e output)
    p.output=malloc(strlen(argv[2])+1);
    if (p.input == NULL || p.output == NULL) {
        fprintf(stderr, "Errore, allocazione della memoria fallita.\n");
        exit(-1);
    }


    
    strcpy(p.input,argv[1]);

    FILE*f=fopen(p.input,"r");
     if (!f) {
        fprintf(stderr,"Errore nell'apertura del file");
        exit(-1);
     }

    char str[13];
    if (fgets(str, sizeof(str), f)== NULL){
        fprintf(stderr,"Errore nell'apertura del file");
        fclose(f);
        exit(-1);

    }

    int len=strlen(str);
    if(str[len-1]=='\n'){
        str[len-1]='\0';//rimuove il carattere di newline
        len--;
    }


    if (len<8 || len>12){
        fprintf(stderr,"Errore, il file di input deve contenere una stringa di lunghezza fra 8 e 12 (inclusi) caratteri.\n");
        exit(-1);

    }

    p.n=atoi(argv[2]);//converto in un itero il secondo parametro

    if (p.n<3 || p.n>12){
        fprintf(stderr,"Errore, il secondo parametro inserito deve essere un intero fra 3 e 12 (inclusi).\n");
        exit(-1);

    }
    strcpy(p.output, argv[3]);

    printf("questi sono i parametri inseriti: %s %d %s.\n",p.input,p.n, p.output);

    return p;


}

//PUNTO B: Costruisca un array A di lunghezza n e inserisca al suo interno i primi n numeri della sequenza di Fibonacci(siconsideri𝐹 =0,𝐹 =1,𝐹 =1,...).
//Si stampi a schermo il contenuto dell’array A.
int* fibonacci(int n){
    int *A=malloc(sizeof(int)*n);
    if (A == NULL) {
        fprintf(stderr, "Errore, allocazione della memoria fallita.\n");
        exit(-1);
    }

    if (n>0){
       A[0]=0; //primo numero della sequenza
    } 
    if (n>1){
       A[1]=1; //secondo numero della sequenza
    } 

    for(int i=2; i<n; i++){
        A[i]=A[i-1]+A[i-2];
    }

printf("array con i primi %d della sequenza di fibonacci:\n",n);
for (int i=0; i<n; i++){
    printf("%d\n", A[i]);
}
return A;

}

//PUNTO C
char*sampleString(char*filename, int h){//funzione che genera una stringa casuale partendo dalla stringa nel file input
    FILE*f=fopen(filename, "r");
    if (!f) {
        fprintf(stderr,"Errore nell'apertura del file");
        exit(-1);
     }
      char str[13];
    if (fgets(str, sizeof(str), f)== NULL){
        fprintf(stderr,"Errore nell'apertura del file");
        fclose(f);
        exit(-1);

    }
    fclose(f);

    str[strcspn(str,"\n")]='\0';

    int alfabeto_len=strlen(str);
    char*randomstring=malloc(sizeof(char)*(h+1));
     if (randomstring == NULL) {
        fprintf(stderr, "Errore, allocazione della memoria fallita.\n");
        exit(-1);
    }
    for(int i=0;i<h;i++){
        randomstring[i]=str[get_random()% alfabeto_len];
    }
    randomstring[h]='\0';
    return randomstring;

}


char**genstringarray(int n, int*A, char*filename){
        char **B=malloc(sizeof(char*)*n);
        if (B == NULL) {
        fprintf(stderr, "Errore, allocazione della memoria fallita.\n");
        exit(-1);
    }
    for(int i=0; i<n;i++){
        B[i]=sampleString(filename,A[i]);
    }
    for (int i = 0; i < n; i++) {
        printf("B[%d] = %s (lunghezza: %d)\n", i, B[i], A[i]);
    }
    return B;

}

//PUNTO D

struct node* newnode(char*data){//funzione per creare il nuovo nodo
    struct node*tmp=(struct node*)malloc(sizeof(struct node));
    if (tmp == NULL) {
        fprintf(stderr, "Errore, allocazione della memoria fallita per il nodo.\n");
        exit(-1);
    }
    tmp->str=data;
    tmp->next= NULL;
    return tmp;

} 

struct queue* createqueue(){
    struct queue*q=(struct queue*)malloc(sizeof(struct queue));
     if (q == NULL) {
        fprintf(stderr, "Errore, allocazione della memoria fallita per la coda.\n");
        exit(-1);
    }
    q->front=q->rear=NULL;
    return q;


}

// Funzione per aggiungere una stringa alla coda
void enqueue(struct queue* q, char* data) {
    // Creiamo un nuovo nodo
    struct node* temp = newnode(data);

    // Se la coda è vuota, il nuovo nodo è sia front che rear
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    // Aggiungiamo il nuovo nodo alla fine della coda e aggiorniamo il rear
    q->rear->next = temp;
    q->rear = temp;
}

int isempty(struct queue* q){//controlla se la coda è vuota
    return q->front==NULL;
}


char* dequeue(struct queue* q) {//per togliere un nodo
    // Se la coda è vuota, ritorniamo -1
    if (q->front == NULL) {
        printf("Coda vuota\n");
        return NULL;
    }

    // Memorizziamo il nodo corrente in un puntatore temporaneo
    struct node* temp = q->front;

    // Spostiamo il front al nodo successivo
    q->front = q->front->next;

    // Se il front diventa NULL, impostiamo anche rear a NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }

    char* data = temp->str;
    free(temp); // Liberiamo la memoria del nodo rimosso
    return data;
}

// Funzione per ottenere l'elemento front senza rimuoverlo
char* front(struct queue* q) {
    if (!isempty(q)) {
        return q->front->str;
    }
    return NULL; // Coda vuota
}

//Inizializzi una coda vuota, scorra gli elementi di B nell’ordine in cui essi appaiono
//e li inserisca nella coda. Prima di ciascuna operazione di inserimento (ad eccezione del primo
//inserimento), il programma controlla se la stringa B[i] da inserire ha lunghezza dispari. In tal
//caso, il programma estrae una stringa dalla coda, la concatena con la stringa B[i] e inserisce
//nella coda la stringa risultato della concatenazione. Nel caso in cui la stringa B[i] da inserire
//ha lunghezza pari, essa viene inserita regolarmente nella coda.
void getQueue(struct queue*q, char**B, int n){
    for(int i=0; i<n; i++){
        int len =strlen(B[i]);//verifico la lunghezza delle stringhe di B[]
    

    if (len%2!=0){
        if(!isempty(q)){
            char*frontstr=dequeue(q);//se la stringa ha lunghgezza dispari, la prendo
            char*concatenata= malloc(strlen(frontstr)+len+1);//alloco la memoria per la nuova stringa concatenata

            if (concatenata == NULL) {
                    fprintf(stderr, "Errore, allocazione della memoria fallita per la concatenazione.\n");
                    exit(-1);
                }

                strcpy(concatenata, frontstr);//copio la prima stringa nella nuova 
                strcat(concatenata, B[i]);//concateno con la funzione la stringa dall'array B

                enqueue(q, concatenata);
                free(frontstr);


        }else{
            enqueue(q,B[i]);
        }
    }else{
        enqueue(q,B[i]);
        
        
        }
    }

}

void printqueue(struct queue*q){
    struct node*tmp=q->front;
    printf("contenuto della coda:\n");
    while(tmp!=NULL){
        printf("%s\n", tmp->str);
        tmp=tmp->next;
    }
}
//PUNTO E
void writeToFile(char*output, struct queue*q){
    FILE*f=fopen(output, "w");
    if (!f) {
        fprintf(stderr,"Errore nell'apertura del file");
        exit(-1);
     }
while(!isempty(q)){
    char* str =dequeue(q);
    fprintf(f,"%s\n",str);
    free(str);

}
fclose(f);
}

int main(int argc, char*argv[]){
    //PUNTO A
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    int*A=fibonacci(p.n);
    //PUNTO C
    char**B=genstringarray(p.n, A,p.input);
    //PUNTO D
    struct queue *q=createqueue();
    getQueue(q, B, p.n);
    printqueue(q);
    //PUNTO E
    writeToFile(p.output,q);

    for (int i=0; i<p.n; i++){
        free(B[i]);

    }
    free(B);
    free(A);



    return 0;
}
