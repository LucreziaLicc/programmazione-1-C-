#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct 
{
  char input[256];
  char output[256];
}parametri;

 struct persona{
    char nome[255];
    char cognome[255];
    int età;
    int peso;
    int altezza;
    char sesso;
};

struct node
{
    struct persona n;
    struct node*next;
};
typedef struct node Node;

parametri readInput(int argc, char*argv[]){
    parametri p;
    if(argc!=3){
        fprintf(stderr,"Errore, i parametri da inserire sono 2\n");
        exit(-1);
    }
    
    strcpy(p.input,argv[1]);
    strcpy(p.output,argv[2]);

    int len1=strlen(p.input);
    int len2=strlen(p.output);

if (len1<4 || len2<4||strcmp(&p.input[len1-4],".txt")!=0||strcmp(&p.output[len2-4],".txt")!=0){
    fprintf(stderr, "Errore, l'estensione dei due nomi dei file da inserire devono avere entrambi l'estensione '.txt'\n");
}

printf("i parametri inseriti dall'utente sono: %s\n%s\n",p.input,p.output);

return p;
}

Node*createNode(char*nome, char*cognome, int età, int peso, int altezza, char sesso){
    Node*new=(Node*)malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"Errore nell'allocazione della memoria\n");
        exit(-1);
    }

 strcpy(new->n.nome,nome);
  strcpy(new->n.cognome,cognome);
  new->n.età=età;
    new->n.peso=peso;
  new->n.altezza=altezza;
    new->n.sesso=sesso;
    new->next=NULL;
    return new;
}



void printList(Node*head){
    Node*tmp=head;
    while(tmp!=NULL){
        printf("%s %s, età:%d, peso:%d, altezza:%d, sesso:%c\n",tmp->n.nome,tmp->n.cognome,tmp->n.età,tmp->n.peso,tmp->n.altezza,tmp->n.sesso);
        tmp=tmp->next;
    }
}

void insertInOrder(Node** head, Node* new) {
    if(*head==NULL || (*head)->n.età >new->n.età){//quando la lista è vuota o il nodo è più picco,o della testa
        new->next=*head;
        *head=new;
    }else{
        Node*cur = *head;
        while(cur->next != NULL && cur->next->n.età <= new->n.età)//nodo da inserire nel mezzo 
        {
            cur=cur->next;
    }
    new->next=cur->next;
    cur->next=new;
    }
}
float IMC(Node*p){
    float imc= p->n.peso/((p->n.altezza/100.0)*(p->n.altezza/100.0));
    return imc;
}


Node* getmax(Node*head){
    if (head==NULL) return NULL;

    Node*maxnode=head;
    float maximc=IMC(head);

    Node*cur=head->next;
    while(cur!= NULL){
        float currentimc=IMC(cur);
        if(currentimc>maximc){
            maximc=currentimc;
            maxnode=cur;
        }
        cur=cur->next;
    }

    return maxnode;
}

void readFile(char*input, Node**head){
    FILE*f=fopen(input, "r");
    if (f==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);
    }

    char nome[256], cognome[256], sesso;
    int età, peso, altezza;

    while(fscanf(f, "%255s %255s %d %d %d %c", nome, cognome, &età, &peso, &altezza, &sesso)==6){

    Node*new=createNode(nome, cognome, età, peso, altezza, sesso);
    insertInOrder(head, new);
    
}
fclose(f);
printf("\nla lista A in ordine di età è:\n");
    printList(*head);
    puts("\n");
Node*maxnode=getmax(*head);
    printf("l'elemento con l'IMC più alto è:%s %s %d %d %d %c\n",maxnode->n.nome,maxnode->n.cognome, maxnode->n.età, maxnode->n.peso,maxnode->n.altezza,maxnode->n.sesso);

}



void deletenode(Node**head, Node*target){
    Node*tmp=*head;
    Node*prev=NULL;

    if(tmp!=NULL && tmp==target){
        *head=tmp->next;
        free(tmp); 
        return;
    }

    while(tmp!= NULL && tmp != target){
        prev=tmp;
        tmp=tmp->next;
    }

    if(tmp== NULL) return;

    prev->next=tmp->next;
    free(tmp);
}

Node*listaB(Node**head){
    Node*B=NULL;//inizializzo la nuova lista B

    for (int i=0; i<3; i++){
        Node*maxnode= getmax(*head);
        if (maxnode==NULL) break;
        Node*new=(Node*) malloc(sizeof(Node));
        new->n=maxnode->n;
        new->next=B;
        B=new;
        deletenode(head, maxnode);
    }  
    
    printf("\nla nuova lista B è questa:\n");
    printList(B);

    printf("\nla nuova lista A modificata è questa:\n");
    printList(*head);

    return B;
  
}

void writeFile(char*output, Node*B){
    FILE*f=fopen(output, "w");
    if(f==NULL){
        fprintf(stderr, "Errore nell'apertura del file.\n");
        exit(-1);
    }
     Node*tmp=B;
    while(tmp!=NULL){
        fprintf(f,"%s %s %d %d %d %c\n",tmp->n.nome,tmp->n.cognome,tmp->n.età,tmp->n.peso,tmp->n.altezza,tmp->n.sesso);
        tmp=tmp->next;
    }
}


int main(int argc, char*argv[]){
    parametri p=readInput(argc, argv);
    Node*head=NULL;
    readFile(p.input,&head);

    Node*B=listaB(&head);
    writeFile(p.output, B);



    return 0;
}