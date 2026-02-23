#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


typedef struct {
    char*input;
    char*output;
}parametri;


typedef struct {
    char nome[255];
    char cognome[255];
    int eta;
    int peso;
    int altezza;
    char sesso;
}persona;


struct node{
    persona data;
    struct node*next;
};
typedef struct node Node;
//PUNTO A

parametri readInput(int argc, char*argv[]){
    parametri p;
    if(argc!=3){
        fprintf(stderr,"Errore, i prametri da inserire sono 2.\n");
        exit(-1);
    }

    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);

    if(len1<4 ||len2<4 || strcmp(argv[1]+len1-4,".txt")!=0 ||strcmp(argv[2]+len2-4,".txt")!=0){
        fprintf(stderr,"Errore, i parametri da inserire sono due nomi di file con estensione '.txt'.\n");
        exit(-1);

    }

    p.input=malloc(sizeof(char)*len1+1);
    p.output=malloc(sizeof(char)*len2+1);

    strcpy(p.input,argv[1]);
    strcpy(p.output, argv[2]),

    printf("i parametri inseriti sono:\n%s\n%s\n", p.input,p.output);
    return p;

}

//PUNTO B
void printList(Node**head){
    Node*tmp=*head;

    while(tmp!=NULL){
        printf("%s %s %d %d %d %c\n",tmp->data.nome, tmp->data.cognome, tmp->data.eta,tmp->data.peso, tmp->data.altezza, tmp->data.sesso);
        tmp=tmp->next;
    }
}


Node*createNode(char*nome, char*cognome, int eta, int peso, int altezza, char sesso){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"Errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    strcpy(new->data.nome,nome);
    strcpy(new->data.cognome, cognome);
    new->data.eta=eta;
    new->data.peso=peso;
    new->data.altezza=altezza;
    new->data.sesso=sesso;
    new->next=NULL;

    return new;
}

void insertInOrder(Node**head, Node* new){
    if(*head==NULL || new->data.eta<(*head)->data.eta){//se la lista è vuota o bisogna inserire come primo elemento
        new->next=*head;
        *head=new;
    }else{
        Node*curr=*head;
        while (curr->next!=NULL && curr->next->data.eta<=new->data.eta){

            curr=curr->next;
        }

        new->next=curr->next;
        curr->next=new;
        
    }


}


void readFile(char*filename, Node**head){
    FILE*f=fopen(filename,"r");
        if(f==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);
    }
    char nome[255];
    char cognome[255];
    int eta;
    int peso;
    int altezza;
    char sesso;

    while (fscanf(f,"%s %s %d %d %d %c",nome,cognome,&eta,&peso,&altezza,&sesso )==6){
        Node*new=createNode(nome,cognome,eta,peso,altezza,sesso);
        insertInOrder(head, new);
    
    }

    fclose(f);

    printf("\nla lista in ordine di età è:\n");
    printList(head);

}

//PUNTO C

float imc(Node*p){
    float imc=p->data.peso/((p->data.altezza/100.0)*(p->data.altezza/100.0));
    return imc;
}

Node* getMax(Node**head){
    Node*tmp=*head;
    Node*maxnode=tmp;

    float IMC=0;
    while (tmp!=NULL)
    {
        float x= imc(tmp);

        if(x>IMC){
            IMC=x;
            maxnode=tmp;
        }

        tmp=tmp->next;
    }
    return maxnode;
}
//PUNTO D

void deleteNode(Node**head, Node*target){
    if (*head==NULL){
     printf("La lista è vuota.\n");
        return;
    }

    Node*tmp=*head;
    Node*prev=NULL;

    if(tmp!=NULL && tmp==target){//se il nodo da eliminare fosse la testa
        *head=tmp->next;
        free(tmp);
        return;
    }

    while (tmp!=NULL && tmp!=target)
    {
       prev=tmp;
       tmp=tmp->next;//scorro la lista

    }
    if(tmp==NULL){
        printf("nodo non trovato il lista.\n");
        return;
    }

    prev->next=tmp->next;//elimmino il nodo
    free(tmp);

}

Node*listaB(Node**head){
    Node*B=NULL;


    for(int i=0; i<3; i++ ){
         Node*maxNode=getMax(head);

         if(maxNode==NULL) break;

         Node*new=malloc(sizeof(Node));

         new->data=maxNode->data;
         new->next=B;
         B=new;
         deleteNode(head, maxNode);
    }

    printf("\nla lista A modificata è:\n");
    printList(head);

    printf("\nla nuova lista B è:\n");
    printList(&B);   

return B;

}

//PUNTO E


void writeFile(char*filename, Node**B){
    FILE*f=fopen(filename,"w");
        if(f==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);
    }

    Node*tmp=*B;

    while (tmp!=NULL)
    {
        fprintf(f,"%s %s %d %d %d %c\n",tmp->data.nome, tmp->data.cognome, tmp->data.eta, tmp->data.peso, tmp->data.altezza, tmp->data.sesso);
        tmp=tmp->next;
    }
    
}



int main(int argc, char*argv[]){
    //PUNTO A
    parametri p=readInput(argc,argv);
    //PUNTO B
    Node*A=NULL;
    readFile(p.input,&A);
    //PUNTO C
    Node*maxnode=getMax(&A);
    printf("\nl'elemento con imc più alto è:%s %s, con un imc di:%f\n",maxnode->data.nome, maxnode->data.cognome,imc(maxnode));
    //PUNTO D
    Node*B=listaB(&A);
    //PUNTO E
    writeFile(p.output,&B);
    return 0;
}
