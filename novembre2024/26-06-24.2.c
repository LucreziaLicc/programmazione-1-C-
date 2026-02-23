#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


typedef struct{
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


parametri decodeParameters(int argc,char*argv[]){
    if(argc!=4){
        fprintf(stderr,"errore, bisogna inserire tre parametri\n");
        exit(-1);
    }

    parametri p;

    p.input=malloc(strlen(argv[1])+1);
    strcpy(p.input,argv[1]);

    FILE*f=fopen(p.input,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file\n");
        exit(-1);        
    }

    char buffer[13];
    fscanf(f,"%s",buffer);
    fclose(f);

    if(strlen(buffer)<8 || strlen(buffer)>12){
        fprintf(stderr,"errore, il primo parametro inserito deve essere il nome di un file input, che contiene una stringa di lunghezza compresa fra 8 e 12\n");
        exit(-1);         
    }

    if(atoi(argv[2])<3 || atoi(argv[2])>12){
        fprintf(stderr,"errore, il secondo parametro inserito deve essere un intero compreso fra 3 e 12\n");
        exit(-1);        
    }
    p.n=atoi(argv[2]);


    p.output=malloc(strlen(argv[3])+1);
    strcpy(p.output,argv[3]);

    printf("\n========================A========================\nParameters:\ninputFile=%s\nn=%d\noutputFile=%s\nInput string:%s\n",p.input,p.n,p.output,buffer);

    return p;
}

//PUNTO B

int fibonacci(int i){
    if(i==1 || i==0){
        return i;
    }
    i=fibonacci(i-1)+fibonacci(i-2);
    return i;
}

int*arrayA(int n){
    int*A=malloc(sizeof(int)*n);
    if(A==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria\n");
        exit(-1);        
    }    
    for(int i=0; i<n; i++){
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
char*sampleString(char*alfabeto, int h){
    char*new=malloc(sizeof(char)*(h+1));
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria\n");
        exit(-1);        
    }      

    for(int i=0; i<h; i++){
        new[i]=alfabeto[get_random()%strlen(alfabeto)];
    }
    new[h]='\0';

    return new;
}

char*getAlfabeto(char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file\n");
        exit(-1);        
    }

    char*buffer=malloc(sizeof(char)*(12+1));
    fscanf(f,"%s",buffer);
    fclose(f);
    return buffer;
}
//funzione che prende in input l’array A e la stringa alfabeto e permette di
//ottenere l’array di stringhe B come specificato nel punto C.

char**getStringArray(int*A, char*alfabeto, int n){
    char**B=malloc(sizeof(char*)*n);
    if(B==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria\n");
        exit(-1);        
    }    

    for(int i=0; i<n; i++){
        B[i]=malloc(sizeof(char)*(A[i]+1));
        B[i]=sampleString(alfabeto,A[i]);
    }
    printf("\n========================C========================\nString array B:\n");
    for(int j=0; j<n; j++){
        printf("%s\n",B[j]);
    }

    return B;

}

//PUNTO D

/*Inizializzi una coda vuota, scorra gli elementi di B nell’ordine in cui essi appaiono
e li inserisca nella coda. Prima di ciascuna operazione di inserimento (ad eccezione del primo
inserimento), il programma controlla se la stringa B[i] da inserire ha lunghezza dispari. In tal
caso, il programma estrae una stringa dalla coda, la concatena con la stringa B[i] e inserisce
nella coda la stringa risultato della concatenazione. Nel caso in cui la stringa B[i] da inserire
ha lunghezza pari, essa viene inserita regolarmente nella coda.
Si stampi a schermo il contenuto della coda.*/

void insertTail(Coda*queue,char*data){
    Node*new=malloc(sizeof(Node));
    new->data=malloc(sizeof(char)*(strlen(data)+1));
    strcpy(new->data,data);
    new->next=NULL;

    if(queue->tail ==NULL){
        queue->head=new;
        queue->tail=new;
    }else{
        queue->tail->next=new;
        queue->tail=new;
    }
    
}

char*dequeue(Coda*queue){
    if(queue->head==NULL && queue->tail==NULL){
        fprintf(stderr,"la coda è vuota\n");
        exit(-1);
    }

    Node*tmp=queue->head;
    char*data=tmp->data;

    queue->head=queue->head->next;

    if(queue->head==NULL){
        queue->tail=NULL;

    }
    free(tmp);
    return data;
}



Coda*getQueue(char**B, int n){   

    printf("\n========================D========================\nQueue:\n");

    Coda*queue=malloc(sizeof(Coda));
    queue->head=NULL;
    queue->tail=NULL;
    insertTail(queue,B[0]);

    for(int i=1; i<n; i++){
        if(strlen(B[i])%2 != 0){
            char*str=dequeue(queue);
            char*newstr=malloc(sizeof(char)*(strlen(B[i])+strlen(str)+1));
            strcpy(newstr,B[i]);
            strcat(newstr,str);
            insertTail(queue,newstr);
        }else{
            insertTail(queue,B[i]);
        }

    }
    Node*tmp=queue->head;
    while(tmp!=NULL){
        printf("%s\n",tmp->data);
        tmp=tmp->next;
    }
    return queue;
}
//PUNTO E

void writeToFile(char*filename, Coda*queue){
    FILE*f=fopen(filename,"w");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file\n");
        exit(-1);        
    }    
    
    while (queue->head != NULL){
        char*data=dequeue(queue);
        fprintf(f,"%s\n",data);
        free(data);

        }

        fclose(f);
    
}
int main(int argc, char*argv[]){
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    int*A=arrayA(p.n);
    //PUNTO C
    char*alfabeto=getAlfabeto(p.input);
    char**B=getStringArray(A,alfabeto,p.n);
    //PUNTO D
    Coda*queue=getQueue(B,p.n);
    //PUNTO E
    writeToFile(p.output,queue);



    return 0;
}

