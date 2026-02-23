#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

 struct parametri{
    int n;
    char*inputFileName;
};
struct node{
    float data;
    struct node*next;
};
typedef struct node Node;


struct parametri decodeParameters(int*n, char*inputFileName){
    struct parametri p;
 printf("inserire un intero n tra 5 e 20 inclusi.\n");
    scanf("%d",n);

    printf("inserire il nome di un file con estensione '.dat'.\n");
    scanf("%s",inputFileName);


if(*n<5||*n>20){
     fprintf(stderr, "Errore, il primo parametro da inserire deve essere un intero tra 5 e 20 inclusi.\n");
        exit(-1);

}

int len=strlen(inputFileName);

if(len<4 || strcmp(&inputFileName[len-4],".dat")!=0){
    fprintf(stderr, "Errore, il nome del file inserito deve avere l' estensione '.dat'.\n");
    exit(-1);
}

p.n=*n;
p.inputFileName=inputFileName;

printf("Punto A: parametri inseriti\nn=%d\ninputFlieName=%s\n",p.n,p.inputFileName);

return p;
}

//readInput: funzione che legge i numeri contenuti nel file di input e restituisce un array A contenente tali numeri;
int *readInput(char*filename, int *size){
    FILE*f=fopen(filename, "r"); 
     if (f == NULL) {
        fprintf(stderr, "Errore: impossibile aprire il file %s.\n", filename);
        exit(1);
    }

    int count=0;//contatore per l'array
    int tmp;

    while(fscanf(f,"%d", &tmp)==1){//scanf legge un intero per volta da un file. se la condizione di lettura è verificata (1), i contatore è incrementato
        count++;

    }


    int *A=(int*)malloc(count*sizeof(int));//alloco la memoria per l'array
    if (A==NULL){
        fprintf(stderr, "Errore nell'allocazione della memoria.\n");
        fclose(f);
        exit(-1);
    }
rewind(f);

    for(int i=0; i<count; i++){//secondo ciclo 
        fscanf(f,"%d",&A[i]);
        
    }

    fclose(f);

    printf("\nPunto B - Contenuto di A:\n");
     for(int i=0; i<count; i++){
        printf("%d\n", A[i]);
    }
    *size=count;//così ho nel main la dimensione dell'array utilizzabile

return A;

}

bool isempty(Node*head){//verifica tramite variabile booleana se lo stack è vuoto o no
    return head==NULL;
}

void pop(Node**head){
    if (isempty(*head)){//controllo se la pila è vuota
        fprintf(stderr, "Errore, pila vuota.\n");
        exit(-1);

    }
    Node*tmp=*head;//salvo tramite un nodo temporaneo la cima della lista, da rimuovere
    *head =(*head)->next;//aggiorno alla nuova cima

    free(tmp);

}
void push(Node**head, float x){
    Node*new=(Node*)malloc(sizeof(Node));
     if (new == NULL) {
        fprintf(stderr, "Errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    new->data=x;
    new->next=*head;//punto alla cima

    *head=new;//il nuovo nodo diventa la cima
}

float top(Node*head){
    if(isempty(head)){
        fprintf(stderr,"errore, pila vuota.\n");
        exit(-1);
    }
    return head->data;//ottengo la cima della pila senza fare pop
}

void printpila(Node*head){
    printf("contenuto della pila:\n");

    while(head!=NULL){
        printf("%.2f\n", head->data);
        head=head->next;
    }
}

Node*createStack(int*A,int n, int size){
   
    Node*head=NULL;//è inizialmente vuota (null)

    for (int i=0; i<size; i++){
        if(A[i]%n==0){
            push(&head,(float)A[i]);

        }else if (!isempty(head)){
           float topvalue=top(head);
           pop(&head);
           float media=(topvalue + (float)A[i])/2;
           push(&head, media);
        }
    }
    printf("\nPunto C - Contenuto di P:\n");
  printpila(head);
  
  return head;

}

void findMinMaxMean(Node*head, float*min, float*max, float*med){//funzione che prende in input un riferimento alla pila e restituisce al chiamante il valore massimo, minimo e medio della pila.
    float somma=0;
    int count=0;

    *min=head->data;
    *max=head->data;

    while(head!=NULL){
        float valore=head->data;
        somma+=valore;

        if(valore>*max){
            *max=valore;
        }
          if(valore<*min){
            *min=valore;
        }

        count++;

        head=head->next;
     
    }

     *med=somma/count;


printf("\nPunto D:\n");
printf("il valore massimo in pila è:%f\n",*max);
printf("il valore minimo in pila è:%f\n",*min);
printf("il valore medio in pila è:%f\n",*med);



}

int main (){
    int n;
    char inputFileName[100];

    struct parametri p=decodeParameters(&n,inputFileName);

    int size;
    int *A=readInput(p.inputFileName,&size);

    Node*pila=createStack(A,p.n,size);

    free(A);

    float min;
    float max;
    float med;

    findMinMaxMean(pila,&min,&max,&med);
    while (!isempty(pila)){
        pop(&pila);
    }


    free(p.inputFileName);




    return 0;
}