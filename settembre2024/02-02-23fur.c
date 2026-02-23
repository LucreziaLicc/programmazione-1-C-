#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct {
    char*input;
    char*output;
}parametri;

struct persona{
    char nome[255];
    char cognome[255]; 
    int numero_conto;
    int anno_apertura;
    float saldo;
};

struct nodo
{
    struct persona data;
   struct nodo*next;
};
typedef struct nodo Nodo;


//PUNTO A
parametri readInput(int argc, char*argv[]){

    parametri p;

    if(argc!=3){
        fprintf(stderr, "Errore, i parametri da inserire sono 2.\n");
        exit(-1);
    }


    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);

    p.input=calloc(len1+1,sizeof(char));
    p.output=calloc(len2+1,sizeof(char));


    strcpy(p.input, argv[1]);
    strcpy(p.output, argv[2]);


    if (len1<4||len2<4 ||strcmp(&p.input[len1-4],".txt")!=0 || strcmp(&p.output[len2-4],".txt")!=0){
        fprintf(stderr, "Errore, i parametri da inserire sono 2 nomi di file (input e output), con estensione '.txt'.\n");
        exit(-1);

    }


    printf("i parametri inseriti sono:\n%s\n%s\n\n", p.input,p.output);

    

return p;

}

//PUNTO B

bool isempty(Nodo*head){
    return head==NULL;

}

Nodo*createNode(struct persona data){
    Nodo*new=malloc(sizeof(Nodo));
        if(new==NULL){
        fprintf(stderr, "Errore, nell'allocazione della memoria.\n");
        exit(-1);
    }

    new->data=data;
    new->next=NULL;
    return new;
}


void insertOrdered(Nodo**head,struct persona p){
    Nodo*new= createNode(p);
            if(new==NULL){
        fprintf(stderr, "Errore, nell'allocazione della memoria.\n");
        exit(-1);
    }

    if(*head==NULL || (*head)->data.anno_apertura<p.anno_apertura){//se la lista è vuota o il conto da inserire è più vecchio della testa
        new->next=*head;
        *head=new;
    }else{//trovo la posizione giusta
    Nodo*curr=*head;
    while(curr->next!=NULL && curr->next->data.anno_apertura<=p.anno_apertura){
        curr=curr->next;
    }
    new->next=curr->next;
    curr->next=new;

    }

}

void printList(Nodo*head){
    Nodo*tmp=head;
    while(tmp!=NULL){
        printf("%s %s %d %d %f\n",tmp->data.nome,tmp->data.cognome,tmp->data.numero_conto,tmp->data.anno_apertura,tmp->data.saldo);
        tmp=tmp->next;
    }
    printf("NULL\n");
}

Nodo* readFile(char*inputname, Nodo**head){
    FILE*f=fopen(inputname,"r");
                if(f==NULL){
        fprintf(stderr, "Errore, nell'apertura del file.\n");
        exit(-1);
    }

        struct persona d;
        while (fscanf(f, "%s %s %d %d %f", d.nome, d.cognome, &d.numero_conto, &d.anno_apertura, &d.saldo)==5)
        {
        insertOrdered(head,d);
        }
    
    
    fclose(f);
    printList(*head);

return *head;

}
//PUNTO C

float getMax(Nodo**head){
    if(*head==NULL){
        fprintf(stderr, "Errore, la lista è vuota.\n");
        exit(-1);
    }
      Nodo*curr=*head;//inizializzo il cursore per scorrere la lista
        float max=curr->data.saldo;//inizializzo con il nodo in testa

    while(curr!=NULL){
        if(curr->data.saldo>=max){
         max=curr->data.saldo;

        } 
       curr=curr->next;
    }

    printf("\nil saldo massimo è:%f.\n",max);
return max;

}

void deleteNode(Nodo**head, struct persona key){
    Nodo*tmp=*head; 
    Nodo*prev=NULL;//tengo traccia del nodo precedente

    if(tmp!=NULL && tmp->data==key){
        *head=tmp->next;// elimino il nodo
        free(tmp);
        return
    }
    while (tmp!= NULL && tmp->data!=key)
    {
       
    }
    
    
}

float computeX(struct persona d, float m) {
    float x = (float)(2023-d.anno_apertura)/5;
    if (x>1)
        x =1;
    return x*d.saldo/m;
}

void removeAccount(Nodo**head, float max){
    Nodo*tmp=*head;

    while(tmp!=NULL){


    }
}


int main(int argc,char*argv[]){
    //PUNTO A
    parametri p=readInput(argc,argv);
    //PUNTO B
    Nodo*A=NULL;
    readFile(p.input, &A);
    //PUNTO C
    float max=getMax(&A);







    return 0;
}
