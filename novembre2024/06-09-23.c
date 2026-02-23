#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct {
    int n;
    char*inputFileName;
}parametri;

struct node{
    float data;
    struct node*next;
};
typedef struct node Node;

parametri decodeParameters(int argc,char*argv[]){
    if( argc!=3){
        fprintf(stderr,"errore, ili numero di parametri da inserire è due\n");
        exit(-1);
    }

    parametri p;

    if(atoi(argv[1])<5 || atoi(argv[1])>20){
        fprintf(stderr,"errore, l'intero da inserire deve essere compreso fra 5 e 20, inclusi\n");
        exit(-1);
    }

    p.n=atoi(argv[1]);

    int len=strlen(argv[2]);
    if(len<4||strcmp(argv[2]+len-4,".dat")!=0){
        fprintf(stderr,"il nome di file da inserire deve avere estensione '.dat'\n");
        exit(-1);
    }

    p.inputFileName=malloc(sizeof(char)*(len+1));
    strcpy(p.inputFileName,argv[2]);


    printf("\nPunto A - Parametri inseriti: n=%d,\ninputFileName=%s\n",p.n,p.inputFileName);

    return p;
}
//PUNTO B

int*readInput(char*filename,int*size){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nella lettura del file\n");
        exit(-1);
    }
    *size=0;
    int num;
    while (fscanf(f,"%d",&num)==1){
       (*size)++;
    }
    rewind(f);

    int*A=malloc(sizeof(int)*(*size));
    for(int i=0; i<*size; i++){
        fscanf(f,"%d",&A[i]);
    }

    for(int j=0; j<*size; j++){
        printf("%d\n",A[j]);
    }


    return A;

}

//PUNTO C

bool isEmpty(Node*head){
    return head==NULL;
}

void push(Node**head,float data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }
    new->data=data;
    new->next=*head;
    *head=new;
}


float pop(Node**head){
    if(isEmpty(*head)){
        fprintf(stderr,"la pila è vuota.\n");
        exit(-1);
    }    

    Node*tmp=*head;

    float data=tmp->data;
    *head=tmp->next;
    free(tmp);

    return data;
}



void printList(Node**head){
    Node*tmp=*head;

    while (tmp!=NULL)
    {
        printf("%0.2f\n",tmp->data);
        tmp=tmp->next;
    }
    
}

Node*createStack(int n,int*A,int size){
    Node*P=NULL;
    push(&P,(float)A[0]);

    for (int i=1; i<size; i++){
        if((A[i]%n)!=0){
            float x=pop(&P);
            float media=(x+(float)A[i])/2;
            push(&P,media);
        }else{
            push(&P,(float)A[i]);
        }

    }

    printList(&P);
    return P;

}
//PUNTO C

void findMinMaxMean(float*min, float*max, float*mean,Node**head){

    Node*tmp=*head;
    *min=tmp->data;
    *max=tmp->data;
    tmp=tmp->next;

    int somma=0;
    int count=0;

    while (tmp!=NULL){
        if(tmp->data<*min){
            *min=tmp->data;
        }
            if(tmp->data>*max){
            *max=tmp->data;
            }
            somma+=tmp->data;
            count++;
            tmp=tmp->next;

    }
    
    *mean=somma/count;

}



int main(int argc,char*argv[]){
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    int size;
    printf("\n\nPunto B - Contenuto di A:\n");
    int*A=readInput(p.inputFileName,&size);
    //PUNTO C
    printf("\n\nPunto C - Contenuto di P:\n");
    Node*P=createStack(p.n,A,size);
    //PUNTO D
    float min, max, mean;
    findMinMaxMean(&min,&max,&mean,&P);
    fprintf(stdout,"\n%0.2f %0.2f %0.2f\n",min,max,mean);

    return 0;
}