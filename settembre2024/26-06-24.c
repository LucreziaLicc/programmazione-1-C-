#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include<time.h>


    typedef struct {
        char*input;
        int n;
        char*output;
    }parametri;

    typedef struct nodo {
        char* data;            // Campo dati per memorizzare il valore dell'elemento
        struct nodo* next;   // Puntatore al prossimo nodo della lista
    } Nodo;

    typedef struct {
        Nodo* head;  // Puntatore al primo nodo della coda
        Nodo* tail;  // Puntatore all'ultimo nodo della coda
    } coda;
//PUNTO A
    parametri decodeParameters(int argc, char*argv[]){
        parametri p;

        if (argc!=4){
            fprintf(stderr, "errore, i parametri da inserire sono 3.\n");
            exit(-1);
        }
        int l=strlen(argv[1]);
        p.input=malloc(sizeof(char)*(l+1));
        strcpy(p.input,argv[1]);

        FILE*f=fopen(p.input,"r");
        if (f==NULL){
            fprintf(stderr, "errore nell'apertura del file.\n");
            exit(-1);
        }
        char buffer[100];

        while (fscanf(f,"%s",buffer)==1){
            int len=strlen(buffer);

            if(len<8||len>12){
                fprintf(stderr, "Errore, la stringa contenuta nel file deve vere lunghezza compresa fra 8 e 12, inclusi.\n");
                exit(-1);
            }

        }

        fclose(f);

        p.n=atoi (argv[2]);

        if(p.n<3 || p.n>12){
                fprintf(stderr, "Errore, l'intero inserito deve essere  compres0 fra 3 e 12, inclusi.\n");
                exit(-1);            
        }

        int l1=strlen(argv[3]);
        p.output=malloc(sizeof(char)*(l1+1));
        strcpy(p.output,argv[3]);

        printf("i parametri inseriti sono:\ninput:%s\nn:%d\noutput:%s\n",p.input,p.n,p.output);

        return p;

    }
//PUNTO B

int fibonacci(int n){
    if (n<=1){
        return n;//caso base
    }
    else{
        return fibonacci(n-1)+fibonacci(n-2);
    }
}
     
int*creaArray(int n){
    int*A=malloc(sizeof(int)*n);
    for(int i=0; i<n; i++){
        A[i]=fibonacci(i);
    }
    printf("\nl'array A:\n");

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

char*sampleString(char*alfabeto, int h){
    char*str=malloc(sizeof(char)*(h+1));
    if (str==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }
int len=strlen(alfabeto);
    for(int i =0; i<h; i++){
        str[i] = alfabeto[get_random() % len];//lascio l'ultimo carattere per '\0'
            }
  
str[h]='\0';
  return str;
}


char*getStrFromFile(char*filename){
    FILE*f=fopen(filename,"r");
        if (f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }

 char*str=malloc(sizeof(char)*100);
         if (str==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }
   if(fgets(str,100,f)==NULL){
        fprintf(stderr,"errore nella lettura del file.\n");
        exit(-1);    
   }
fclose(f);
 str[strcspn(str, "\n")] = '\0'; // Rimuovi il newline finale, se presente
 return str;

}

char**getStringArray(int*A,int n,char*alfabeto){
    char** B=malloc(sizeof(char*)*n);
    if (B==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    for(int i=0; i<n; i++){
        int len=A[i];
        B[i]=malloc(sizeof(char)*(len));
        for(int j=0; j<len; j++)
        B[i]=sampleString(alfabeto,len);
    }
printf("\nl'array B è:\n");

for (int i=0;i<n;i++){
    printf("%s\n",B[i]);
}
    return B;
}
//PUNTO D

coda* createQueue(){
    coda*queue=malloc(sizeof(coda));
     if (queue==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }   

    queue->head=NULL;
    queue->tail=NULL;
    return queue;
}

int isEmpty(coda*queue){
    return queue->head==NULL;
}

void enqueue(coda*queue, char*data){
    Nodo*new=malloc (sizeof(Nodo));
     if (new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }    


    new->data=malloc(strlen(data)+1);
     if (new->data==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }       

    strcpy(new->data,data);
    new->next=NULL;

    if(queue->tail==NULL){//se la coda è vuota
        queue->head=new;
        queue->tail=new;

    }else{
        queue->tail->next=new;
        queue->tail=new;
    }
}

char* dequeue(coda*queue){
    if(isEmpty(queue)){
        fprintf(stderr,"Errore, la coda è vuota.\n"),
        exit(-1);
    }
    Nodo*tmp=queue->head;
    char*data=tmp->data;

    queue->head=queue->head->next;

    if(queue->head==NULL){
        queue->tail=NULL;
    }

    free(tmp);
    return data;
}

void printCoda(coda*queue){
    Nodo*curr=queue->head;

    while(curr!=NULL){

        printf("%s\n",curr->data);
        curr=curr->next;
    }
}

void getQueue(coda*queue, char**B,int n ){
    for(int i=0; i<n; i++){
        int len=strlen(B[i]);
        if(len%2==1 && !isEmpty(queue)){//lunghezza dispari e coda non vuota
        char*dequeuestr=dequeue(queue);
        //concateno le due stringhe
        int newLen=strlen(dequeuestr)+len+1;//somma delle due stringhe più la terminazione

        char*concatenedStr=malloc(newLen);
            if (concatenedStr==NULL){
                fprintf(stderr,"errore nell'allocazione della memoria.\n");
                exit(-1);
            }    
        strcpy(concatenedStr,dequeuestr);//copio la prima stringha
        strcat(concatenedStr,B[i]);
        enqueue(queue,concatenedStr);

        free(dequeuestr);
        free(concatenedStr);

        }else{
            enqueue(queue,B[i]);
        }
    }

    printf("========================D========================\nQueue:\n");
    printCoda(queue);
}

//PUNTO E

void freequeue(coda*queue){
    while (!isEmpty(queue))
    {   
        char*data=dequeue(queue);
        free(data);
        }
    free(queue);
}

void writeToFile(char*filename, coda*queue){
    FILE*f=fopen(filename,"w");
                if (f==NULL){
                fprintf(stderr,"errore nell'apertura del file.\n");
                exit(-1);
            }  

            Nodo*curr=queue->head;

            while (curr!=NULL)
            {
                fprintf(f,"%s\n",curr->data);
                curr=curr->next;
            }
            fclose(f);
            free(curr);
            freequeue(queue);

}

int main(int argc, char*argv[]){
    srand(time(NULL));
    //PUNTO A
    parametri p=decodeParameters(argc,argv);
    
    //PUNTO B
    int*A=creaArray(p.n);
    //PUNTO C
    char*alfabeto=getStrFromFile(p.input);
    char**B=getStringArray(A,p.n,alfabeto);
    //PUNTO D
    coda*coda=createQueue();
    getQueue(coda,B,p.n);
    //PUNTO E
    writeToFile(p.output,coda);
    return 0;
}