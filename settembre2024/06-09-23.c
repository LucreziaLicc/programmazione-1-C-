#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


typedef struct{
    int n;
    char*inputFileName;
}parametri;

struct node{
    float data;
    struct node*next;
};

typedef struct node Node;

//PUNTO A
parametri decodeParameters(int argc, char*argv[]){
    if(argc!=3){
        fprintf(stderr,"errore, il numero di parametri da inserire è due.\n");
        exit(-1);
    }
parametri p;
    if(atoi(argv[1])<5 ||atoi(argv[1])>20  ){
        fprintf(stderr,"errore, il primo parametro da inserire è un intero compreso fra 5 e 20, inclusi.\n");
        exit(-1);        
    }
    
    p.n=atoi(argv[1]);

    int len=strlen(argv[2]);
    if(len<4 || strcmp(argv[2]+len-4,".dat")!=0){
        fprintf(stderr,"errore, il secondo parametro da inserire è una stringa 'inputFileName', con estensione '.dat'.\n");
        exit(-1);            
    }

    p.inputFileName=malloc(sizeof(char)*(len+1));
    strcpy(p.inputFileName,argv[2]);

    printf("punto A:\nn:%d\ninputFileName:%s\n",p.n,p.inputFileName);

    return p;

    
}

//PUNTO B

int*readInput(char*filename, int*conto){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);
    }
    int temp;
    *conto=0;

    while(fscanf(f,"%d",&temp)==1){
        (*conto)++;
    }
        rewind(f);

    int*A=malloc(sizeof(int)*(*conto));

    for(int i=0; i<*conto; i++){
        if (fscanf(f,"%d",&A[i])!=1){
            fprintf(stderr,"errore nella lettura del file.\n");
            exit(-1);
        }
    }

    printf("\npunto B:\narray A:\n");
    for(int j=0; j<*conto; j++){
        printf("%d\n",A[j]);
    }
return A;

}
//PUNTO C


bool isEmpty(Node*head){
    return head==NULL;
}

void push(Node**head, float data){
    Node*newnode=malloc(sizeof(Node));
    if(newnode==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    newnode->data=data;
    newnode->next=*head;
    *head=newnode;
}


float pop(Node**head){
    if(isEmpty(*head)){
        fprintf(stderr, " la lista è vuota.\n");
        exit(-1);
    }

    Node*tmp=*head;
    float data=tmp->data;
    *head=tmp->next;

    free(tmp);

    return data;

}

void printlist(Node**head){
    Node*tmp=*head;
    while(tmp!=NULL){
        printf("%0.2f\n",tmp->data);
        tmp=tmp->next;
    }
}

Node* createStack(int*A, int n, int conto){
    Node*P=NULL;

    push(&P,(float)A[0]);



    for(int i=1; i<conto; i++){
        if(A[i]%n ==0){
            push(&P,(float)A[i]);
        }else{         
            float x=pop(&P);
            float media=(x+(float)A[i])/2;
            push(&P,media);
            
        }
    }

    printf("\nla pila è:\n");
    printlist(&P);

    return P;

    

}

//PUNTO D

void findMinMaxMean(float*min, float*max, float*mean, Node*head){
    Node*tmp=head;

     *min=tmp->data;
     *max=tmp->data;
     int somma=0;
     int conto=0;
   
    while (tmp!=NULL)
    {
        if (tmp->data < *min){
            *min=tmp->data;
        }
        if (tmp->data > *max){
            *max=tmp->data;
        }
       somma +=tmp->data;
       conto++;
       tmp=tmp->next;
    }   
    
    *mean=somma/conto;

    printf("\nmin:%0.2f\nmax:%0.2f\nmean:%0.2f\n",*min,*max,*mean);

}

int main(int argc, char* argv[]){
    //PUNTO A
    parametri p=decodeParameters(argc,argv);
    //PUNTO B
    int conto=0;
    int*A=readInput(p.inputFileName,&conto);
    //PUNTO C
    Node*P=createStack(A,p.n,conto);
    //PUNTO D
    float min, max, mean;
    findMinMaxMean(&min,&max,&mean,P);


    return 0;
}