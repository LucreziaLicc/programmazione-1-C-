#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>


typedef struct {
    int n;
    char*input_filename;
}parametri;

struct node{
    float data;
    struct node*next;
};
typedef struct node Node;

parametri decodeParameters(int argc, char*argv[]){
    parametri p;

    if(argc!=3){
        fprintf(stderr,"Errore, bisogna inserire due parametri\n");
        exit(-1);
    }
    if(atoi(argv[1])<5 || atoi (argv[1])>20){
        fprintf(stderr,"errore, l'intero inserito deve essere compreso fra 5 e 20\n");
        exit(-1);
    }
    p.n=atoi(argv[1]);

    int len=strlen(argv[2]);

    if(len<4 || strcmp(argv[2]+len-4,".dat")!=0){
        fprintf(stderr,"errore, il nome del file inserito deve avere estensione '.dat'\n");
        exit(-1);        
    }

    p.input_filename=malloc(sizeof(char)*(len+1));
    strcpy(p.input_filename,argv[2]);

    printf("\nPunto A - Parametri inseriti: n= %d,inputFileName= %s\n",p.n,p.input_filename);

    return p;
}
//PUNTO B
int*readInput(int*size, char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file\n");
        exit(-1);            
    }
    *size=0;
    int data;
    while(fscanf(f,"%d",&data)==1){
        (*size)++;
    }
    rewind(f);

    int*A=malloc(sizeof(int)*(*size));
    for(int i=0; i<*size; i++){
        fscanf(f,"%d",&A[i]);

    }
    fclose(f);

    for(int i=0; i<*size; i++){
        printf("%d\n",A[i]);
    }

    return A;
}

//PUNTO C

bool isempty(Node*head){
    return head==NULL;
}

void push(Node**head, float data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria\n");
        exit(-1);
    }
    new->data=data;
    new->next=*head;
    *head=new;
}

float pop(Node**head){
    if(isempty(*head)){
        fprintf(stderr,"la pila è vuota\n");
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

    while(tmp!=NULL){
        printf("%0.2lf\n",tmp->data);
        tmp=tmp->next;
    }
}

Node*createStack(int*A, int size, int n){
    Node*P=NULL;

    for(int i=0; i<size; i++){
        if((A[i]%n)!=0){
            float x=pop(&P);
            float somma=x+(float)A[i];
            float media=somma/2;
            push(&P,media);
        }else{
            push(&P,(float)A[i]);
        }
    }

    printList(&P);

    return P;
}
//PUNTO D

void findMinMaxMean(Node**head,float *min, float *max, float *mean){
    Node*tmp=*head;
    float somma=0;
    float count=0;
    *min=tmp->data;
    *max=tmp->data;
    tmp=tmp->next;

    while(tmp!=NULL){
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
    printf("\nmin=%0.2lf\nmax=%0.2lf\nmean=%0.2lf\n",*min,*max,*mean);

}
int main(int argc, char*argv[]){
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    int size;
    int*A=readInput(&size,p.input_filename);
    //PUNTO C
    printf("\nPunto C - Contenuto di P:\n");
    Node*P=createStack(A,size,p.n);
    //PUNTO D
    float min,max,mean;
    findMinMaxMean(&P,&min,&max,&mean);

    return 0;
}