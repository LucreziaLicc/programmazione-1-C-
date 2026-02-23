#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

typedef struct {
    char*in_filename;
    char*out_filename;
    char c;
}parametri;

struct node{
    char data;
    struct node*next;
};
typedef struct node Node;

parametri decodeParameters(int argc, char*argv[]){
    if(argc!=4){
        fprintf(stderr, "errore,i parametri da inserire sono 3: due stringhe e un carattere.\n");
        exit(-1);
}

    parametri p;

    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);

    p.in_filename=malloc(sizeof(char)*(len1+1));
    p.out_filename=malloc(sizeof(char)*(len2+1));

    if(len1>50 ||len2>50){
        fprintf(stderr, "errore,le due stringhe da inserire devono essere lunghe massimo 50 caratteri.\n");
        exit(-1);        
    }

    strcpy(p.in_filename,argv[1]);
    strcpy(p.out_filename,argv[2]);

    if(!isalpha(argv[3][0])|| strlen(argv[3])!=1){
        fprintf(stderr, "errore,il terzo parametro da inserire è un singolo carattere.\n");
        exit(-1);          

    }
    p.c=argv[3][0];

    printf("PUNTO A:\nin_filename:%s\nout_filename:%s\nc:%c\n",p.in_filename,p.out_filename,p.c);

return p;

}

//PUNTO B

Node*insertChar(Node**head,char data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    new->data=data;
    new->next=*head;
    *head=new;

    return new;
}

Node* readFile(char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }

    Node*L=NULL;

    char temp;

    while (fscanf(f,"%c",&temp)==1)
    {
        if(temp!='\n'){
        Node*new=insertChar(&L,temp);
        }
       
    }
    fclose(f);
    
    printf("\nPUNTO B\nLISTA L:\n");

    return L;

}

void printList(Node**head){
    Node*tmp=*head;

    while (tmp!=NULL)
    {
       printf("%c\n",tmp->data);
       tmp=tmp->next;
    }
    
}
//PUNTO C

int countOccurrences(Node**L, char x){
    Node*tmp=*L;

    int o=0;

    while (tmp!=NULL)
    {
        if(tmp->data== x ||tmp->data==toupper(x)){
            o++;
        }
        tmp=tmp->next;
    }
    return o;
    
}

//PUNTO D
void deletenode(Node**head, Node*target){
    if(*head==target){
        *head=target->next;
    }else{
    Node*tmp=*head;
    while (tmp != NULL && tmp->next!=target)
    {
        tmp=tmp->next;
    }
        if (tmp == NULL) return;

    tmp->next=target->next;
    }

    free(target);
}

void processL(Node** L, int o) {
     if (*L == NULL) return;

    bool deletion_made;//variabile booleana per tenere traccia se è stata efettuata una cancellazione
    do {//si ripete fino a quando current è uguale a null (lista finita)
        deletion_made = false;//si assume che non ci sono eliminazioni
        Node* current = *L;//cursore che scorre la lista
        
        while (current != NULL) {//condizione del do
            int p = countOccurrences(L, current->data);//Conta quante volte il valore del nodo corrente (current->data) appare nella lista.

            if (p >= o) {//condizione dell'eliminazione
                Node* to_delete = current;//identifica il nodo da eliminare per usarlo nella funzione deleteNode
                current = current->next;//sposta il cursore al nodo successivo
                deletenode(L, to_delete);//elimina il nodo
                deletion_made = true;//imposta il flag a true perchè è avvenuta una eliminazione
                break;  // Ricomincia la scansione dall'inizio
            } else {//se il valore del nodo corrente non soddisfa la conodizione, 
                current = current->next;//passsa avanti al prossimo
            }
        }
    } while (deletion_made);//il ciclo continua fino a quando nessun nodo viene elimnato

    printf("\nPUNTO D\nLISTA L dopo la rimozione:\n");
    printList(L);
}

//PUNTO E

void writeToFile(char*filename, Node**L){
    FILE*f=fopen(filename,"w");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }

    Node*tmp=*L;
    while (tmp!=NULL)
    {
        fprintf(f,"%c ",tmp->data);
        tmp=tmp->next;
    }
    
}

int main(int argc, char*argv[]){
    //PUNTO A
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    Node*L=readFile(p.in_filename);
    printList(&L);
    //PUNTO C

    printf("\nPUNTO C\no:\n");
    int o=countOccurrences(&L,p.c);
    printf("%d\n",o);
    //PUNTO D
    processL(&L,o);
    //PUNTO E
    writeToFile(p.out_filename,&L);



    return 0;
}