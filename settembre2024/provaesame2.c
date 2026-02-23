#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<stdbool.h>

 typedef struct 
{
   char word[100];//prima parola della riga
   int count;//numero di occorrenze della parola nella riga//punta alla riga successiva
}riga;

struct node{
    riga data;
    struct node*next;
};
typedef struct node Node;


//FUNZIONI
                                //funzione che permette di leggere l’intero n come parametro passato da riga di comando.
                                //Questa funzione dovrà gestire correttamente eventuali errori di input, stampare messaggi di errore su standard error e 
                                //terminare il programma opportunamente ove necessario
int readN(int argc,char*argv[]){
    if(argc!=2){
        perror("bisogna inserire un prametro intero da riga di comando\n.");
        exit(-1);
    }
    char*end;
    int n =strtol(argv[1],&end,0);//per verificare che il parametro sia un intero si unsa 'strtol'. Si inizializza un puntatore stringa alla fine (end),
    // e i parametri della funzione sno la stringa da analizzare, end dereferenziato (&end), la base di conversione.

    if(*end != '\0'|| n<0){
    perror("il parametro pasato deve essere un intero positivo");
    exit(-1);}
    return n;

}

bool inserthead(Node**head, riga r){
    Node*newnode=malloc(sizeof(Node));//alloco la memoria per il nuovo nodo (testa della lista)
    if(newnode == NULL) return false;//cntrollo

    newnode->data= r; //si inserisce una riga nella lista utilizzando il campo data del nuovo nodo
    newnode->next=*head;//il nuovo nodo viene collegato alla testa della lista
    *head=newnode;// si aggiorna il puntatore alla testa con il nuovo nodo così diventa la nuova testa

    return true;// se tutto è andato a buon fine restituisce true
}

bool inserttail(Node**head, riga r){//la funzione inserisce un nodo alla fine della lista
    if (*head==NULL){
        return inserthead(head, r);//se la lista è vuota, utilizza la funzione 'inserthead'
    }
    Node *ptr=*head;//viene creato un nuovo puntatore che serve per scorrere la lista
    while(ptr->next){//il ciclo scorre la lista fino all'ultimo nodo
        ptr=ptr->next;
    }

    Node*newnode=malloc(sizeof(Node));//allocazione memoria per il nuovo nodo

    if (newnode==NULL) return false;//controllo

    newnode->data=r;//si inserisce la riga nel campo data del nuovo nodo
    newnode->next=NULL;//il campo next del nuovo nodo è impostato a NULL perchè è l'ultimo della lista

    ptr->next= newnode;//il nuovo nodo viene collegato al prossimo della lista

    return true;


}


Node* readFile(char* name) {
    Node* head = NULL;  // Usa un singolo puntatore
    FILE* f = fopen(name, "r");
    if (f == NULL) {
        perror("Errore nell'apertura del file.\n");
        return NULL;
    }

    char s[1000];
    bool done = false;

    while (!done) {
        char* out = fgets(s, 1000, f);
        if (out != NULL) {
            char* tok = strtok(s, " \n");
            char* firstTok = tok;
            int count = 0;

            do {
                if (strcmp(firstTok, tok) == 0) {
                    count++;
                }
            } while ((tok = strtok(NULL, " \n")) != NULL);

            riga r;
            r.count = count;
            strcpy(r.word, firstTok);
            inserttail(&head, r);  // Passa il puntatore alla testa
        } else {
            done = true;
        }
    }

    fclose(f);  // Chiudi il file
    return head;  // Ritorna il puntatore alla testa
}
void printList(Node *head) {
    Node *ptr = head;

    while(ptr) {
        riga *r = &ptr->data;
        printf("%s %d\n", r->word, r->count);
        ptr = ptr->next;
    }
}
    
bool deletehead(Node**head){//cancella il primo nodo della lista se questa non è vuota
//Il motivo per cui si usa un doppio puntatore è che la funzione potrebbe modificare il puntatore alla testa della lista 
//(cioè potrebbe cambiare quale nodo è la nuova testa).
    if(*head){//verifica se la lista è vuota (il puntatore *head non è NULL)
    Node *tmp=*head;//assegno un puntatatore temporaneo alla testa della lista
    *head=(*head)->next;//passo il puntatore alla testa al nodo successivo
    free(tmp);//libero la memoria del puntatore temporaneo
    return true;
    }else{
return false;
    }
}


void filterList(Node**head,int n){// funzione che elimina dalla lista le parole con meno di “n” occorrenze;
    Node *ptr=*head;//puntatatore per scorrere la lista
    Node*prevptr=NULL;//puntatore al nodo precedente

    while(ptr!=NULL){//il ciclo scorre la lista fino all'ultimo nodo
        
        if(ptr->data.count<n){//condizione per eliminare il nodo (la ricorrenza di parole è minore dell'argomento inserito)
            if(prevptr==NULL){
               deletehead(head);
                ptr=*head;
                continue;
            }else{
              Node*tmp=ptr;
              prevptr->next=ptr->next;
                free(tmp);
                ptr=prevptr;
            }
        }
            prevptr=ptr;
            ptr=ptr->next;
        
    }



}

int main(int argc,char*argv[]){
    int n=readN(argc,argv);
    Node**head=malloc(sizeof(Node*));
    *head=readFile("input.txt");
    
    filterList(head,n);
    printList(*head);


return 0;
    
}
