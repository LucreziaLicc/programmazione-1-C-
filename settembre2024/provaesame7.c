#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct {
    int N;
}record;

struct node{
    char data;
    struct node*next;
};
typedef struct node Node;

//A prenda un input da tastiera (argomenti della funzione main) costituito da un intero positivo N. 
//Il programma deve verificare che N sia inserito nel formato corretto e restituire un messaggio di errore terminando 
//il programma opportunamente nel caso in cui il formato di N non dovesse essere corretto;
record readInput(int argc, char*argv[]){
    record p;
    if (argc!=2){
        fprintf(stderr,"Bisogna inserire un parametro da input: un numero intero positivo.\n");
        exit(-1);
    }
char*end;
p.N=strtol(argv[1],&end,0);

if(*end||p.N<0){
    fprintf(stderr,"Bisogna inserire come parametro un numero intero positivo.\n");
        exit(-1);

}
return p;

}
//B generi una sequenza di N operazioni di inserimento (push) di caratteri pseudo-casuali in [A-Z,a-z,1-9]
// in una struttura dati LIFO dinamica (pila o stack) da implementare mediante lista concatenata semplice 
//(top==testa della lista), nel seguente modo:

bool isempty(Node*head){//funzione che verifica se la pila è vuota
    return head ==NULL;//se la pila è vuota, quindi la testa è null, la funzione retituirà TRUE
}

void push(Node**head, char x){//si utilizza un doppio puntatore alla testa, perchè bisogna modificare un puntatore stesso, puntandolo
    Node*new=malloc(sizeof(Node));//alloco la memoria per un puntatore a un nuovo nodo
    new->data=x;//nel campo data della sruct inserisco il carattere da impilare
    new->next=*head;//collego il nuovo nodo alla pila, tramite il puntatore alla testa
    *head=new;//il puntatore alla testa viene aggiornato con il nodo creato, che diventa la nuova cima
}

char pop(Node**head){
    if(isempty(*head)){//controllo se la pila è vuota
        fprintf(stderr, "Errore, la pila è vuota.\n");
        exit(-1);
    }
    char x=(*head)->data;//salvo il contenuto del nodo in cima alla pila per poterlo prelevare
    Node*tmp=*head;//creo un puntatore temporamneo alla cima della pila
    (*head)=(*head)->next;
    free(tmp);

    return x;

}
char getrandomchar(char*s){//funzione che prende in input una stringa e restituisce un carattere casuale dalla data stringa,
// serve da supporto per poter prendere o sollo vocali o solo consonanti con le successive funzioni 
    return s[get_random()%strlen(s)];

}

char genVowel(){
    return getrandomchar("AEIOUaeiou");

}
char genConsonant(){ 
    return getrandomchar("QWRTYPSDFGHJKLZXCVBNMqwrtypsdfghjklzxcvbnm");
    
}

int char2int(char c){//utilizzo la funzione atoi
    char tmp[2];//creo un arrey di un solo caratter e il carattere nullo, perchè atoi funziona con le stringhe e non con i char
    tmp[0]=c;
    tmp[1]='\0';

    int x=atoi(tmp); //converte la stringa e preleva solo la parte intera
    return x;

}


Node** fillStack(int N){
    Node**head=malloc(sizeof(Node*));//allocolo per un puntatoe alla testa della pila
    *head=NULL;//è inizialmente vuota (null)

    for(int i=0; i<N; i++){
        char x=getrandomchar("123456789");//genero N volte un numero casuale da 1 a 9
        
        if(x>='1' && x<='4'){
            for(int j=0;j<char2int(x); j++){
           push (head,genVowel());
        }
        push(head,x);
        }else{
          for(int j=0;j<char2int(x); j++){
            char c=genConsonant();
            if(c=='v'){
                c='*';
            }
            if(c=='w'){
                c='?';
            }
            push(head,c);

          }
          push(head, x);
        }
    }
    return head;
}


//emptyStack(Node **head, int N) svuota una pila (head), estraendo i valori da essa e 
//costruendo un array bidimensionale di caratteri (char**). 
//L'array restituito avrà una struttura particolare, con ogni elemento (sottostringa) 
//il cui contenuto dipende dai valori presenti nella pila.
 char**emptyStack(Node**head,int N){
    char**array=calloc(N,sizeof(char*));
    int i=0;//contatore per scorrere l'array
    while(!isempty(*head)){
        char c=pop(head);//si estrae il caratter edalla lisa e si inserisce nella variabile c
        char x=char2int(c);//si converte in intero il caratter e si salva in x
        array[i]=calloc(x, sizeof(char)+1);//allocazione della stringa più il carattere nullo
        for(int j=0;j<x;j++){//Il ciclo for rimuove x caratteri dalla pila e li inserisce nella stringa array[i].
        //Alla fine di questo processo, array[i] conterrà x caratteri estratti dalla pila.
            array[i][j]=pop(head); //la funzione pop non è void, ma restituisce un carattere  
        }
                i++;//si passa al posto successivo nell'array
    }
return array;

}

void printArray(char** array, int N) {
    for(int i=0; i<N; i++) {
        printf("%s\n",array[i]);
    }
}

int main(int argc, char*argv[]){
    record p=readInput(argc, argv);
    Node**head=fillStack(p.N);
    char**array=emptyStack(head, p.N);
    printArray(array,p.N);

    return 0;
}



