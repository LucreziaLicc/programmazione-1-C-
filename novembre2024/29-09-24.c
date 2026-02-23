#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
    char*input_filename;
    char*output_filename;    
}parametri;

struct node{
    char*data;
    struct node *next;
};
typedef struct node Node;

parametri decodeParameters(int argc,char*argv[]){
    if(argc!=3){
        fprintf(stderr,"errore, i parametri da inserire sono due stringhe\n");
        exit(-1);
    }

    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);

    parametri p;

    p.input_filename=malloc(sizeof(char)*(len1+1));
    p.output_filename=malloc(sizeof(char)*(len2+1));

    if(len1<5 || len2<7 || strcmp(argv[1]+len1-5,".text")!=0 || strcmp(argv[2]+len2-7,".output")!=0 ) {
        fprintf(stderr,"errore, l'estensione della prima stringa è '.text', mentre l'estensione della seconda stringa è '.output'\n");
        exit(-1);
    }       

    strcpy(p.input_filename,argv[1]);
    strcpy(p.output_filename,argv[2]);

    printf("\nPUNTO A:\ninput:%s\noutput:%s\n",p.input_filename,p.output_filename);

    return p;

}
//PUNTO B

Node*insertInOrder(Node**head,char*data){
    Node*new=malloc(sizeof(Node));
    new->data=strdup(data);
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    if(*head==NULL|| strlen((*head)->data) >= strlen(new->data)){//se la lista è vuota
        new->next=*head;
        *head=new;   
        return new;
    }

    Node*tmp=*head;
    while (tmp->next!= NULL && strlen(tmp->next->data)< strlen(new->data))
    {
        tmp=tmp->next;
    }
    new->next=tmp->next;
    tmp->next=new;

    return new;
}
void printList(Node**head){
    Node*tmp=*head;

    while (tmp!=NULL)
    {
        printf("%s\n",tmp->data);
        tmp=tmp->next;
    }
    

}

Node*readFile(char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }    

    Node*X=NULL;
    char buffer[200];

    while(fscanf(f,"%s",buffer)==1){
        Node*new=insertInOrder(&X,buffer);
    }

    printList(&X);

    return X;

}
//PUNTO C

short countVocals(char*str){
    short conto=0;

    int len=strlen(str);

    for(int i=0; i<len; i++){
        if(str[i]== 'a' ||str[i]== 'e'||str[i]== 'i'||str[i]== 'o'||str[i]== 'u'){
            conto++;
        }
    }
    return conto;
}

void printArray(short*Y,int size){
    for(int i=0; i<size; i++){
        printf("%hd ",Y[i]);
    }  
}

short* getArray(Node**X,int*count){
    Node*tmp=*X;
    *count=0;
    while(tmp!=NULL){
       ( *count)++;
        tmp=tmp->next;
    }

    tmp=*X;

    short*Y=malloc(sizeof(short)*(*count));

    while (tmp!=NULL){

        for(int i=0; i<*count; i++){
            short conto=countVocals(tmp->data);
            Y[i]=conto;
            tmp=tmp->next;
        }
    }

return Y;

}
//PUNTO D

float media(short*Y,int conto){
    float somma=0;
    for(int i =0; i<conto; i++){
        somma+=(float)Y[i];
    }
       float mean=somma/conto;

       return mean; 
}

void deletenode(Node**head,char*value){
    if(*head==NULL){
        printf("la lista è vuota.");
        return;
    }
    Node*tmp=*head;
    Node*prev=NULL;

    if(tmp!=NULL && strcmp(tmp->data,value)==0){//se il nodo è la testa
        *head=tmp->next;
        free(tmp);
        return;
    }

    while(tmp!=NULL && strcmp(tmp->data,value)!=0){
        prev=tmp;
        tmp=tmp->next;
    }
    if(tmp==NULL){
        printf("valore non trovato in lista.\n");
        return;
    }
    prev->next=tmp->next;
    free(tmp);

}

void filterList(short*Y,int conto,Node**X){
    float mean=media(Y,conto);

    Node*curr=*X;
    Node*prev=NULL;

    while(curr!=NULL){
       
       short vocals=countVocals(curr->data);
       Node*next=curr->next;

       if((float)vocals > mean){
         deletenode(X,curr->data);

         if(prev==NULL){
            curr=*X;
         }else{
            curr=next;
            prev->next=curr;
            
            }
         }else{
            prev=curr;
            curr=next;
            }

         }
       
       
    }

    //PUNTO E
    void writeToFile(char*filename,Node**X){
        FILE*f=fopen(filename,"w");
        if(f==NULL){
            fprintf(stderr,"errore nell'apertura del file.\n");
            exit(-1);
        } 
            Node*tmp=*X;

    while (tmp!=NULL)
    {
        fprintf(f,"%s\n",tmp->data);
        tmp=tmp->next;
    }

    fclose(f);
    
    

    }









int main(int argc, char*argv[]){
    parametri p=decodeParameters(argc,argv);
    //PUNTO B
    printf("\nPUNTO B:\nlista X:\n");
    Node*X=readFile(p.input_filename);
    //PUNTO C
    int conto;
    short*Y=getArray(&X,&conto);
    printArray(Y,conto);
    //PUNTO D
    float mean=media(Y,conto);
    printf("\nmedia di Y: %0.2f\n",mean);
    filterList(Y,conto,&X);
    printf("\nlista modificata:\n");
    printList(&X);
    //PUNTO E
    writeToFile(p.output_filename,&X);

    return 0;
}