#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<time.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct {
    int N;
    char w;
}parameters;

struct node{
    char data[16];
    struct node*next;
};
typedef struct node Node;


//readInput: funzione che prenda in input gli argomenti della funzione main argv ed argc,
 //controlli i requisiti dei parametri e restituisca al chiamante un record (struct) che contenga tutti i parametri.
 parameters readInput(int argc, char*argv[]){
    if(argc!=3){
        fprintf(stderr,"Errore, gli argomenti da input devono essere 2.\n");
        exit(-1);
    }
    char*str=argv[1];
    for(int i=0;i<strlen(str);i++){
        if(!isdigit(str[i])){
            fprintf(stderr,"Errore, il primo parametro inserito deve essere un numero intero.\n");
            exit(-1);
        }
    }
    int value =atoi(str);
    if(value<10 || value>20){
        fprintf(stderr,"Errore, il numero inserito deve essere compreso fra 10 e 20.\n");
        exit(-1);
    }
parameters p={value,argv[2][0]};
return p;
 }
void insertHead(Node**head, char*str){
    if(*head==NULL){//Se la lista è vuota (*head == NULL), viene allocata memoria sufficiente per un nuovo nodo testa (Node).
        *head=malloc(sizeof(Node));
        strcpy((*head)->data,str);//la funzione copia la stringa passata ad argomento nel campo 'data' del nodo da inserire
        (*head)->next=NULL;//next punta a null perchè in questo caso è l'unico nodo dela lista
    
    }else{
        Node*new=malloc(sizeof(Node));//se la lista non è vuota, si alloca la memoria per un nuovo nodo e crea il puntatore 'new'
        strcpy(new->data, str);//Copia la stringa fornita (str) nel campo data del nuovo nodo (new).
        new->next=*head;//si punta alla testa che è diventata il nodo appena creato
        *head=new;
    }
}

void insertString(Node**head,char*str){
    if(*head==NULL){
        insertHead(head,str);//se la lista è vuota si chiama la funzione che genera la testa della lista
        return;
    }

    Node*ptr=*head;//questo puntatore serve per scorrere la lista
    Node*prev=NULL;//questo puntstore tiene trsccis del nodo precedente, inizialmente a NULL

    while(ptr && strcmp(ptr->data,str)<0){//il ciclo score attraveso la lista per trovare il posto giusto dove inserire il nodo (ordine lessicografico)
    //strcmp(ptr->data, string) confronta la stringa string con la stringa contenuta nel nodo corrente (ptr->data):
    //Se il risultato è negativo (< 0), significa che ptr->data viene alfabeticamente prima di string, quindi la ricerca continua.
    //Se il risultato è positivo o zero, la ricerca si ferma, poiché string deve essere inserita prima di ptr->data per mantenere l'ordine.
        prev=ptr;//se il risultato è positivo, il nodo precedete diventa quello corrente
        ptr=ptr->next;
    }
    if(prev==NULL) {//se è verificato, significa che la stringa va inserita in cima perchè viene alfabeticamente prima di tutte
        insertHead(head, str);//quindi si chiama questa funzione
        return;
    }

    Node *new = malloc(sizeof(Node));//si crea un nuovo nodo dove copiare la stringa e inserirla coì nella lista

    strcpy(new->data, str);
    prev->next = new;
    new->next = ptr;
}




//bool deletehead(Node**head){//lascio per dopo (funzione non necessaria)



//genString: funzione che restituisca una stringa di caratteri pseudo-casuali appartenenti 
//ad un determinato intervallo specificato mediante opportuni parametri formali. 
char*genString( int L, const char range[2]){//range[2] sarebbe il range ffra i due caratteri '' e 'w'
    char*s=calloc(L+1, sizeof(char));//alloca dinamicamete la meomoria per una stringa di lunghezza L+1(il carattere \0).
    if (s==NULL){
        fprintf(stderr, "Errore nell'allocazione della memoria.\n");
        exit(-1);
    }
    for(int i=0; i<L; i++){
        s[i]=rand() % (range[1]-range[0]+1)+ range[0];//Ad esempio, se range[0] è 'a' (che ha valore ASCII 97) e range[1] è 'z'
                                                        // (che ha valore ASCII 122), la differenza sarà 122 - 97 = 25,
                                                    // e con l'aggiunta di 1 si ottiene 26, che è il numero di caratteri da 'a' a 'z' inclusi.

    }
    s[L]='\0';//aggiungo il terminatore di stringa
    return s;
}




//genList: funzione che si occupa di creare e riempire la lista di stringhe come richiesto nel punto B;
// generi, mediante successivi inserimenti, una lista concatenata semplice (ordinata in modo crescente - ordinamento lessicografico)
// che contenga N stringhe con caratteri pseudo-casuali in [‘a’-’z’] di lunghezza pseudo-casuale L nell'intervallo [5,15];
Node**genList(int N){//N è il numero di nodi da inserire
    Node**head=malloc(sizeof(Node));//alloco la memoria per la testa della lista
    *head=NULL;//inizialmente la lista è vuota (NULL)

    char range[2]={'a','z'};//i caratteri validi delle stringhe
    char*tmp=NULL;//questo puntatore memorizzerà momentaneamente la stringa generata a ogni ciclo
        
    for(int i=0; i<N; i++){//ad ogni iterazione verrà generata una stringa (N volte)
        int L = get_random() % (15-5+1)+5;//genera la lunghezza casuale della sttringa (fra 5 e 15)
        tmp = genString(L,range);//genera tramite la funzione una stringa di caratteri casuali della dimensione stabilita
        insertString(head,tmp);//inserisce tramite la funzione la stringa neòla lista
        free(tmp);//libera la memoria del puntatore temporaneo
    }

return head;//restituisce il puntatore alla cima


}


//printList:stampi sullo standard output l'intera lista; 
void printList(Node*head){
    Node*tmp =head;//faccio un punatore temporaneo per scorere la lista

    while(tmp){
        printf("%s\n",tmp->data);
        tmp=tmp->next;
    }
    
}

//printOcc: funzione che stampa sullo standard output il numero totale di occorrenze del carattere w 
//in tutte le stringhe della lista, come specificato nel punto D.
void printOcc(Node*head, char w){
    Node*tmp=head;//punatore temporaneo

    int count=0;//contatore di occorrenze
    while(tmp){//il ciclo continua finchè non è null il puntatore (la lista è finita)
        char*s=tmp->data;//prende la stringa del nodo per analizzarla
        for(int i=0;i<strlen(s);i++){//scorre i caratteri della stringa
        if(s[i]== w)
            count++;
        }

            tmp=tmp->next;

        }
printf("Numero totale di occorrenze di %c: %d\n", w, count);
    
}

 int main(int argc, char*argv[]){
     srand(time(NULL));//srand(time) per funzionare deve essere chiamato una sola volta all'inizio, nel main
    parameters f=readInput( argc, argv);
    printf("I parametri inseriti sono: %d, %c\n", f.N,f.w);
    Node**head=genList(f.N);
    printList(*head);
    printOcc(*head,f.w);
    return 0;

 }