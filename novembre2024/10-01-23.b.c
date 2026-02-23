#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>


typedef struct{
    int N;
    char w;
}parametri;

struct node{
    char*data;
    struct node*next;
};
typedef struct node Node;

parametri readInput(int argc, char*argv[]){
    if(argc!=3){
        fprintf(stderr,"errore, i paranetri da inserire sono 2: un intero N e un carattere w\n");
        exit(-1);
    }
    parametri p;

    if(atoi(argv[1])<10 || atoi(argv[1])>20){
        fprintf(stderr,"errore, il primo paranetro da inserire deve essere un intero N, compreso fra 10 e 20, inclusi\n");
        exit(-1);        
    }
    p.N=atoi(argv[1]);

    if(strlen(argv[2])!=1){
        fprintf(stderr,"errore, il secondo paranetro da inserire deve essere un carattere\n");
        exit(-1);         
    }
    p.w=argv[2][0];

    printf("PUNTO A:\nN:%d\nw:%c\n",p.N,p.w);

    return p;
}

//PUNTO B
unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}


char*genString(){
    char*newstr=malloc(sizeof(char)*(15+1));
    int range=15-5+1;
    int len=get_random()%range+5;

    for(int i=0; i<len; i++){
        newstr[i]=get_random()%('z'-'a'+1)+'a';
    }

    newstr[len]='\0';
    return newstr;

}

Node*insertString(Node**head,char*data){
    Node*new=malloc(sizeof(Node));
    if(new==NULL){
        fprintf(stderr, "errore nell'allocazione della memoria\n");
        exit(-1);
    }
    new->data=data;
    new->next=NULL;

    if(*head==NULL || strcmp(data, (*head)->data) < 0){//se la lista è vuota o la testa è più grande del nuovo nodo

        new->next=*head;
        *head=new;
    }else{
        Node*tmp=*head;
        while (tmp->next !=NULL && strcmp(data,tmp->next->data)>0)
        {
            tmp=tmp->next;
        }
        new->next=tmp->next;
        tmp->next=new;
    }

    return new;

}

void printList(Node**head){
    Node*tmp=*head;
    while(tmp!=NULL){
        fprintf(stdout,"%s\n",tmp->data);
        tmp=tmp->next;
    }
}

Node*genList(int N){
    Node*head=NULL;

    for(int i=0; i<N; i++){
        char*s=genString();
        Node*new=insertString(&head,s);
    }
    printf("\nPUNTO B - lista:\n");
    printList(&head);

    return head;
}
//PUNTO D
int countOcc(char*data, char w){
    int len=strlen(data);
    int count=0;
    for(int i=0; i<len; i++){
        if(data[i]==w){
            count++;
        }
    }
return count;
}

void printOcc(Node**head,char w){
    Node*tmp=*head;
    int count=0;

    while(tmp!=NULL){
        int x=countOcc(tmp->data,w);
            count+=x;
            tmp=tmp->next;
    }

    fprintf(stdout,"\nil numero di occorrenze di %c è: %d\n",w,count);

}

int main(int argc, char*argv[]){
    parametri p=readInput(argc, argv);
    //PUNTO B
    Node*list=genList(p.N);
    //PUNTO D
    printOcc(&list,p.w);

}