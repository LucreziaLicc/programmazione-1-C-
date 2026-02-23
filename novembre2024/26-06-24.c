#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char*input;
    int n;
    char*output;

}parametri;

struct node {
    char*data;
    struct node*next;
};

typedef struct node Node;

struct queue{
    Node*head;
    Node*tail;
};
typedef struct queue Queue;

parametri decodeParameters(int argc, char*argv[]){
    if(argc!=4){
        fprintf(stderr,"errore, il numero di argomenti da inserire deve essere 3.\n");
        exit(-1);
    }

    parametri p;

    p.input=malloc(strlen(argv[1])+1);
    if(p.input==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }    

    strcpy(p.input,argv[1]);

    FILE*f=fopen(p.input,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }      

    char buffer[100];
    fgets(buffer,sizeof(buffer),f);

    if(strlen(buffer)<8 || strlen(buffer)>12){
        fprintf(stderr,"errore la stringa input inserita deve essere di lunghezza compresa fra 8 e 12 inclusi.\n");
        exit(-1);        
    }

    if(atoi(argv[2])<3 ||atoi(argv[2])>12){
        fprintf(stderr,"errore l'intero inserito deve essere compreso fra 3 e 12 inclusi.\n");
        exit(-1);            
    }
    p.n=atoi(argv[2]);

    p.output=malloc(strlen(argv[3])+1);
    strcpy(p.output,argv[3]);


    printf("\nPUNTO A:\ni parametri inseriti sono:\ninput:%s\nn:%d\noutput:%s\n",p.input,p.n,p.output);

    fclose(f);

    return p;

}
//PUNTO B
int fibonacci(int i){
    if(i<=1){
    return i;
    }else{
        return fibonacci(i-1)+fibonacci(i-2);
    }
}
void printArray(int*A,int n){
    for(int i=0; i<n; i++){
        printf("%d ",A[i]);
    }

}

int* ArrayA(int n){
    int*A=malloc(sizeof(int)*n);
    for(int i=0; i<n; i++){
        A[i]=fibonacci(i);
    }
    printf("\nPUNTO B:\n");
    printArray(A,n);

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

// funzione che prende in input la stringa alfabeto e un intero h e restituisca una
//stringa di h caratteri casuali campionati dalla stringa alfabet
char*sampleString(char*alfabeto,int h){
    char*newStr=malloc(sizeof(char)*(h+1));
       
        if(newStr==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }  

    int lenAlf=strlen(alfabeto);

    for(int i=0; i<h; i++){
        newStr[i]=alfabeto[get_random()%lenAlf];

    }
    newStr[h]='\0';
    return newStr;

}

char**getStringArray(int*A,char*filename,int n){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }      

    char alfabeto[100];
    fgets(alfabeto,sizeof(alfabeto),f);
    
    char**B=malloc(sizeof(char*)*n);
    for(int i=0; i<n; i++){
        B[i]=sampleString(alfabeto,A[i]);
    }

    for(int j=0; j<n;j++){
        printf("%s\n",B[j]);
    }

    fclose(f);

    return B;
}
//PUNTO D

Queue*createQueue(){
    Queue*coda=malloc(sizeof(Queue));
        if(coda==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }     
    coda->head=NULL;
    coda->tail=NULL;

    return coda;

}

bool isEmpty(Queue*coda){
    return coda->head==NULL;
}


void enqueue(Queue*coda, char*data){
    Node*new=malloc(sizeof(Node));
        if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }    

    new->data=malloc(strlen(data)+1);
    strcpy(new->data,data);
    new->next=NULL;//imposta il next a null perchè questo sarà l'ultimo nodo della coda

    if(isEmpty(coda)){//CODA VUOTA, imposta sia testa che coda al nuovo nodo che è l'unico
        coda->head=new;
        coda->tail=new;
    }else{
        coda->tail->next=new;//aggiorna la coda per puntare al nuovo nodo
        coda->tail=new;//la tail diventa il nuovo nodo
    }
}

char* dequeue(Queue*coda){//restituisce l'elemento in cima alla coda e lo elimina
    if(isEmpty(coda)){
        fprintf(stderr,"coda vuota.\n");
        return NULL;
    }
    Node*tmp=coda->head;//puntatore temporaneo alla testa
    char*data=tmp->data;//memorizza la stringa del nodo da cancellare

    coda->head=coda->head->next;//aggiorna la testa per puntare al nodo successivo

    if(isEmpty(coda)){//se dopo aver tolto il nodo, la testa diventa null(coda vuota), anche la tail viene impostata a null
        coda->tail=NULL;
    }
    free(tmp);
    return data;
}


void printQueue(Queue*coda){
    Node*tmp=coda->head;
    while (tmp!=NULL)
    {
       printf("%s\n",tmp->data);
       tmp=tmp->next;
    }
    
}


Queue* getQueue(char**B,int n){
    Queue*coda=createQueue();

    for(int i=0; i<n; i++){
        if(i==0){
            enqueue(coda,B[i]);
            
        }else{
            if((strlen(B[i])%2)!=0){
                char*str=dequeue(coda);
                char*newstr=malloc(strlen(str)+strlen(B[i])+1);
                strcpy(newstr,B[i]);
                strcat(newstr,str);
                enqueue(coda,newstr);
                free(str);
                free(newstr);
            }else{
            enqueue(coda,B[i]);
            }
        }
    }
    return coda;

}

//PUNTO E

void writeToFile(char*filename, Queue*coda){
    FILE*f=fopen(filename,"w");
        if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }  

    Node*tmp=coda->head;

    while (tmp!=NULL)
    {
        fprintf(f,"%s\n",tmp->data);
        tmp=tmp->next;
    }
    fclose(f);
    
}


int main(int argc, char*argv[]){
    parametri p=decodeParameters(argc,argv);
    //PUNTO B
    int*A=ArrayA(p.n);
    //PUNTO C
    printf("\nPUNTO C:\n");
    char**B=getStringArray(A,p.input,p.n);
    //PUNTO D
    printf("\nPUNTO D:\n");
    Queue*coda=getQueue(B,p.n);
    printQueue(coda);
    //PUNTO E 
    writeToFile(p.output,coda);

    Node* tmp;
    while (!isEmpty(coda)) {
        tmp = coda->head;
        dequeue(coda);
    }
    free(coda);


    return 0;
}