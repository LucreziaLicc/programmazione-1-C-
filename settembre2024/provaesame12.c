#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include<ctype.h>

typedef struct {
    char*input_filename;
     char*output_filename;

}parametri;

struct node{
    char*data;
    struct node*next;
};
typedef struct node Node;

//PUNTO A
parametri decodeParameters(int argc, char*argv[]){
    parametri p;

    if (argc!=3){
        fprintf(stderr, "Errore, i parametri da inserire sono 2.\n");
        exit(-1);
    }

    p.input_filename=malloc(strlen(argv[1])+1);
    p.output_filename=malloc(strlen(argv[2])+1);

    if (p.input_filename==NULL || p.output_filename==NULL){
        fprintf(stderr, "Errore nell'allocazione della memoria.\n");
        exit(-1);
    }


    strcpy(p.input_filename, argv[1]);
    strcpy(p.output_filename, argv[2]);

    int len1=strlen(p.input_filename);
    int len2=strlen(p.output_filename);


    if(len1<4||strcmp(&p.input_filename[len1-5], ".text")!=0){
        fprintf(stderr, "Errore, il primo parametro da inserire è un file con estensione '.text'.\n");
        exit(-1);

    }


    if(len2<7||strcmp(&p.output_filename[len2-7],".output")!=0){
        fprintf(stderr, "Errore, il secondo parametro da inserire è un file con estensione '.output'.\n");
        exit(-1);

    }

    
    printf("====== A Stampa Parametri ======\ninput_filename = %s\noutput_filename = %s\n", p.input_filename, p.output_filename);

return p;

}
//PUNTO B
Node*createnode(char*data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr, "Errore nell'allocazione della memoria.\n");
        exit(-1);

    }
    new->data= malloc(strlen(data)+1);//alloco la stringa
    if(new->data==NULL){
        fprintf(stderr, "Errore nell'allocazione della memoria.\n");
        free(new);
        exit(-1);

    }

    strcpy(new->data, data);
    new->next=NULL;

    return new;
}

Node *insertInOrder(Node* head, Node* new) {
    if(head==NULL || strlen(head->data) > strlen(new->data)){//quando la lista è vuota o il nodo è più piccolo della testa
        new->next=head;
        return new;
    }else{
        Node*cur = head;
        while(cur->next != NULL && strlen(cur->next->data) <= strlen(new->data))//nodo da inserire nel mezzo 
        {
            cur=cur->next;
    }
    new->next=cur->next;
    cur->next=new;
    return head;
    }
}


Node*readFile(char*input){
    FILE*f=fopen(input, "r");
     if(f==NULL){
        fprintf(stderr, "Errore nell'apertura del file.\n");
        exit(-1);

    }
    Node*X=NULL;
    char buffer[256];

    while(fgets(buffer, sizeof(buffer), f)){ 
        buffer[strcspn(buffer,"\n")]='\0';//rimuovo il newline e aggiungo il carattere di terminazione
        Node*newnode=createnode(buffer);
        X=insertInOrder(X, newnode);

    }
    fclose(f);
    return X;
}

void printlist(Node*head){
    Node*tmp=head;
    while(tmp!=NULL){
        printf("%s ->  ", tmp->data);
        tmp=tmp->next;
    }
    printf("NULL\n");
}


void deletelist(Node**head){
    Node*current=*head;
    Node*next;

    while(current != NULL){
        next=current->next;
        free(current->data);//libera la memoria per la stringa
        free(current);
        current=next;
    }
    *head=NULL;//imposta la testa a null
}

//PUNTO C
int countvowels(char*str){
    int count=0;
    for(int i=0; str[i]; i++){
        char c= tolower(str[i]);
        if( c=='a' || c=='e' || c=='o'||c=='u'||c=='i'){
            count++;
        }
    }
    return count;
    
}

short* getArray(Node*X, int*size){
    
    *size=0;
    Node*temp=X;
    while(temp!=NULL){
       (*size)++; 
       temp=temp->next;
    }

short*Y=calloc(*size,sizeof(short));
if (Y == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        exit(-1);
    }

Node*tmp=X;
for(int i=0;i<(*size);i++){
    int vocali=countvowels(tmp->data);
    Y[i]=(short)vocali;
    tmp=tmp->next;
}
printf("====== C Array Y (numero di vocali) ======\n");

for(int i=0; i<*size; i++){
    printf("%hd\n", Y[i]);
}

return Y;

}
//PUNTO D

void filterList(short*Y, int size, Node**X){
    int somma=0;
    for(int i=0;i<size;i++){
        somma+=Y[i];
    }

    float media=((float)somma)/size;

    Node*current=*X;//puntatore per modificare la testa della lista
    Node*prev=NULL;//necessario tenere traccia dei nodi precedenti per cancellare i nodi

    int index=0;//tine traccia dell'indice, sia in lista che array

    while (current!=NULL){
        int vocali=countvowels(current->data);
        if(vocali>media){

            if(prev==NULL){//se la condizione è verificata siamo alla testa della lista
                *X=current->next;//aggiorna la testa al nodo successivo
                free(current->data);//libero la stringa
                free(current);//libero il nodo
                current=*X;//imposto il puntatore temporaneo alla nuova testa
            }else{//se tmp non è null, siamo all'intero della lista
                prev->next = current->next;//colleghiamo il nodo precedente al nodo successivo del corrente, stiamo saltando il corrente, perchè da eliminare
                free(current->data);
                free(current);
                current = prev->next;//aggiorno il nodo da considerare corrente
            }

        }else{//il nodo non deve essere cancellato
            prev=current;//aggiorno il precedente con il corrente, scorro la lista
            current=current->next;//aggiorno il puntatore al nodo corrente con il prossimo

        }
        index++;//aggiorno il contatore per l'array Y
        
    }
       printf("====== D Media di Y e lista dopo filtro ======\n");

    printf("Media di Y:%f\n", media);
   printf("Contenuto di X:\n");
   printlist(*X);
    
}
//PUNTO E
void writeToFile(char*output,Node*X){
    FILE*f=fopen(output,"w");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }
    Node*tmp=X;
    while(tmp!=NULL){
        fprintf(f,"%s\n",tmp->data);
        tmp=tmp->next;
    }
}


int main(int argc, char*argv[]){
    //PUNTO A
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    Node*X=readFile(p.input_filename);
    printf("====== B Lista ordinata per lunghezza ======\n");
    printlist(X);
    //PUNTO C
    int size;
    short*Y=getArray(X,&size);
    //PUNTO D
    filterList(Y,size,&X);
    //PUNTO E
    writeToFile(p.output_filename,X);
    return 0;
}