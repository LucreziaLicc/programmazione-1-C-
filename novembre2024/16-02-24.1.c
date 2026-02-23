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

parametri readInput(int argc, char*argv[]){
    if(argc!=3){
        fprintf(stderr,"errore, bisogna inserire il nome di due file con estensione '.txt'\n");
        exit(-1);
    }

    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);

    if(len1<4 || len2<4 || strcmp(argv[1]+len1-4,".txt")!=0 ||strcmp(argv[2]+len2-4,".txt")!=0 ){
            fprintf(stderr,"errore, bisogna inserire il nome di due file con estensione '.txt'\n");
            exit(-1);    
    }

    parametri p;
    p.input=malloc(sizeof(char)*(len1+1));
    p.output=malloc(sizeof(char)*(len2+1));

    strcpy(p.input,argv[1]);
    strcpy(p.output,argv[2]);


    printf("\n=======PUNTO A=======\ninput = %s, output = %s\n",p.input,p.output);

    return p;

}
//PUNTO B


Node* insertOrdered(Node**head, persona data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }
    
    new->data=data;

    if(*head==NULL || (*head)->data.eta >= new->data.eta){
        new->next=*head;
        *head=new;
    }else{    
        Node*tmp=*head;

        while (tmp->next !=NULL && tmp->next->data.eta<new->data.eta){
            tmp=tmp->next;
        }
        new->next=tmp->next;
        tmp->next=new;
    }
    return new;

}

void printList(Node**head){
    Node*tmp=*head;
    while (tmp!=NULL)
    {
        printf("%7s %10s %4d %6d %6d %4c\n",tmp->data.nome,tmp->data.cognome,tmp->data.eta,tmp->data.peso,tmp->data.altezza,tmp->data.sesso);
        tmp=tmp->next;
    }
    
}

Node*readFile(char*filename){
    FILE*f=fopen(filename,"r");
        if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }

    Node*A=NULL;

    persona t;

    while(fscanf(f,"%s %s %d %d %d %c",t.nome,t.cognome,&t.eta,&t.peso,&t.altezza,&t.sesso)==6){
        insertOrdered(&A,t);
    }
    fclose(f);

    printf("\nPUNTO B:\n");
    printList(&A);

    return A;

}
//PUNTO C
float imc(int p, int a){
    float IMC=(float)p/(((float)a/100)*((float)a/100));
    return IMC;
}

Node* getMax(Node**head){
    Node*tmp=(*head)->next;
    float max=imc((*head)->data.peso,(*head)->data.altezza);

    Node*maxnode=NULL;

    while(tmp!=NULL){
        float currimc=imc(tmp->data.peso,tmp->data.altezza);
        if(currimc>max){
            max=currimc;
            maxnode=tmp;
        }
        tmp=tmp->next;
    }

    printf("\n=======PUNTO C=======\nla persona con l'imc maggiore è %s %s, con un imc di %0.2f\n",maxnode->data.nome,maxnode->data.cognome,imc(maxnode->data.peso,maxnode->data.altezza));

    return maxnode;


}
//PUNTO D

void deleteNode(Node**head, Node*target){
    if(*head==NULL){
        fprintf(stderr,"la lista è vuota.\n");
        exit (-1);
    }

    if(*head==target){
        *head=(*head)->next;
        free(target);
    }
    Node*tmp=*head;

    while (tmp!=NULL && tmp!=target){
        tmp=tmp->next;  
        }

        if(tmp!=NULL && tmp==target){
            tmp->next=target->next;
            free(target);
        }
}

void insertHead(Node**head,persona data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"erroe nell'allocazione della memoria.\n");
        exit(-1);
    }

    new->data=data;
    new->next=*head;
    *head=new;
}

Node*listaB(Node**head){
    Node*B=NULL;

    for(int i =0;  i < 3; i++){
        Node*max=getMax(head);
        insertHead(head,max->data);
        deleteNode(head,max);

    }
printf("\nPUNTO D:\n");
printList(&B);

return B;
}

int main(int argc,char*argv[]){
    parametri p=readInput(argc,argv);
    //PUNTO B
    Node*A=readFile(p.input);
    //PUNTO C
    Node*maxnode=getMax(&A);
    //PUNTO D
    Node*B=listaB(&A);
    printf("\nlista A modificata:\n");
    printList(&A);


    return 0;
}