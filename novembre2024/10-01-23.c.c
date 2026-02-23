#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct{
    int N;
}parametri;

struct node{
    char data;
    struct node*next;
};

typedef struct node Node;

parametri readInput(int argc, char*argv[]){
    if(argc!=2){
        fprintf(stderr,"errore, bisogna inserire un parametro, un intero N\n");
        exit(-1);
    }

    parametri p;

    if(atoi(argv[1])<0){
        fprintf(stderr,"l'intero N deve essere positivo\n");
        exit(-1);        
    }

    p.N=atoi(argv[1]);

    return p;
}

//PUNTO B

Node*push(Node**head, char data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria\n");
        exit(-1);
    }
    new->data=data;
    new->next=*head;
    *head=new;

    return new;

}

char pop(Node**head){
    Node*tmp=*head;
    char x=tmp->data;
    *head=tmp->next;
    free(tmp);
    return x;
}


unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

char genNum(){
    char*num="123456789";
    int len=strlen(num);
    char new=num [get_random()%len];


    return new;    

}

char genVowel(){
    char*vowels="AEIOUaeiou";
    int len=strlen(vowels);
    char new=vowels [get_random()%len];


    return new;
}

char genConsonant(){
    char*consonant="QWRTYPSDFGHJKLZXCVBNMqwrtypsdfghjklzxcvbnm";
    int len=strlen(consonant);
    char new=consonant[get_random()%len];


    return new;
}

Node*fillStack(int N){
    Node*head=NULL;
    char x=genNum();
for(int i=0; i<N; i++){
    if(x>='1' && x<='4'){
        for(int i=0; i<x-'0'; i++){
            char vow=genVowel();
            Node*new= push(&head,vow);
        }
        Node*new=push(&head,x);
    }
        if(x>='5' && x<='9'){
        for(int i=0; i<x-'0'; i++){
            char con=genConsonant();
            if(con=='v'){
                Node*new= push(&head,'*');                
            }
            if(con=='w'){
                Node*new= push(&head,'?');                
            }            
            Node*new= push(&head,con);
        }
       Node*new= push(&head,x);
    }
}
    return head;
    
}

void printStack(Node**head){
    Node*tmp=*head;
    while(tmp!=NULL){
        printf("%c\n",tmp->data);
        tmp=tmp->next;
    }
}

int main(int argc, char*argv[]){
    parametri p=readInput(argc,argv);

    Node*P=fillStack(p.N);
    printStack(&P);

    return 0;
}