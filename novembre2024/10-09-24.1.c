#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<ctype.h>

typedef struct {
    char*in_filename;
    char*out_filename;
    char c;
}parametri;


struct node{
    char data;
    struct node*next;
};
typedef struct node Node;


parametri decodeParameters(int argc, char*argv[]){
    if(argc!=4){
        fprintf(stderr,"errore, bisogna inserire 3 parametri da input.\n");
        exit(-1);
    }

    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);

    if(len1>50 || len2>50){
         fprintf(stderr,"errore, i nomi di file inseriti devono essere di massimo 50 caratteri.\n");
        exit(-1);       
    }

    parametri p;

    p.in_filename=malloc(sizeof(char)*(len1+1));
    p.out_filename=malloc(sizeof(char)*(len2+1));

    strcpy(p.in_filename,argv[1]);
    strcpy(p.out_filename,argv[2]);

    if(!isalpha(argv[3][0])){
        fprintf(stderr,"errore, bisogna inserire come terzo parametro un singolo carattere.\n");
        exit(-1);
    }

    p.c=argv[3][0];

    printf("\n==========PUNTO A==========\nNome del file di input: %s\nNome del file ouput: %s\nValore di c: %c\n",p.in_filename,p.out_filename,p.c);
    return p;
}

//PUNTO B

void insertNode(Node**head, char data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    new->data=data;
    new->next=NULL;

    if(*head==NULL){
        *head=new;
    }else{
        Node*tmp=*head;
        while (tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=new;
        
    }

}

void printlist(Node**head){
    Node*tmp=*head;

    while (tmp!=NULL)
    {
        printf("%c",tmp->data);
        tmp=tmp->next;
    }
    
}

Node*readFile(char*filename){
    Node*head=NULL;

    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
        exit(-1);
    }    
    
    char data;
    while (fscanf(f,"%c\n",&data)==1){
        insertNode(&head,data);
        
    }
    fclose(f);
    printlist(&head);

    return head;


}

//PUNTO C

int countOccurrences(Node**head,char c){
    int o=0;
    Node*tmp=*head;

    while (tmp!=NULL)
    {
      if(tmp->data==c || tmp->data==toupper(c)){
        o++;
      }
      tmp=tmp->next;
    }
    return o;

}
//PUNTO D

void deleteNode(Node**head, Node*target){
    if(*head==target){
        *head=target->next;
    }else{
        Node*tmp=*head;
        while(tmp!=NULL && tmp->next!=target){
            tmp=tmp->next;
        }
        if(tmp==NULL) return;
        tmp->next=target->next;
    }
    free(target);
}

void processL(Node**head,int o){
    if(*head==NULL) return;

    bool deletion_made;
    do{
        deletion_made=false;
        Node*curr=*head;
        while (curr!=NULL)
        {
           int p=countOccurrences(head,curr->data);
           if(p>=o){
            Node*to_delete=curr;
            curr=curr->next;
            deleteNode(head,to_delete);
            deletion_made=true;
            break;
           }else{
            curr=curr->next;
           }
        }
        
    }while (deletion_made);

    printf("\n==========PUNTO D==========\nContenuto della lista:\n");
    printlist(head);
}

// PUNTO E
void wrteTofile(char*filename,Node**head){
    FILE*f=fopen(filename,"w");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file\n");
        exit(-1);
    }

    Node*tmp=*head;
    while (tmp!=NULL)
    {
        fprintf(f,"%c",tmp->data);
        tmp=tmp->next;
    }
    fclose(f);
}

int main(int argc, char*argv[]){
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    printf("\n==========PUNTO B==========\nContenuto della lista:\n");
    Node*L=readFile(p.in_filename);
    //PUNTO C
    int o=countOccurrences(&L,p.c);
    printf("\n==========PUNTO C==========\nOccorrenze di %c in L:%d\n",p.c,o);
    //PUNTO D
    processL(&L,o);
    //PUNTO E
    wrteTofile(p.out_filename,&L);

    


    return 0;
}