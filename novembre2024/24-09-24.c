#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct {
    char*input_filename;
    char*output_filename;

}parametri;

struct node{
    char*data;
    struct node*next;
};
typedef struct node Node;

parametri decodeParameters(int argc, char*argv[]){
    if(argc!=3){
        fprintf(stderr,"errore, i parametri da inserire sono due stringhe (nomi di file)\n");
        exit(-1);
    }
    parametri p;

    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);

    if(len1<5 || strcmp(argv[1]+len1-5,".text")!=0){
        fprintf(stderr,"errore, il primo parametro da inserire è un nome di file con estensione '.text'\n");
        exit(-1);        
    }
     if(len2<7 || strcmp(argv[2]+len2-7,".output")!=0){
        fprintf(stderr,"errore, il secondo parametro da inserire è un nome di file con estensione '.output'\n");
        exit(-1);        
    }
    p.input_filename=malloc(sizeof(char)*(len1+1));
    p.output_filename=malloc(sizeof(char)*(len2+1));

    strcpy(p.input_filename,argv[1]);
    strcpy(p.output_filename,argv[2]);

    printf("\n====== A Stampa Parametri ======\ninput_filename = %s\noutput_filename = %s\n",p.input_filename,p.output_filename);
    return p;
}
//PUNTO B

bool isempty(Node**list){
    return *list==NULL;
}

void insertOrdered(Node**list, char*data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della emomoria\n");
        exit(-1);
    }
    int len=strlen(data);
    new->data=malloc(sizeof(char)*(len+1));
    strcpy(new->data,data);
    new->next=NULL;

    if(*list==NULL || strlen((*list)->data)>=len){
        new->next=*list;
        *list=new;
        return;
    }

    Node*tmp=*list;

    while(tmp->next!=NULL && strlen(tmp->next->data)<len){
        tmp=tmp->next;
    }
    new->next=tmp->next;
    tmp->next=new;
}

int main(int argc, char*argv[]){
    return 0;
}
