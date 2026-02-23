#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct {
    char*simboli;
    int n;
    char*output;
}parametri;


struct node{
    char*data;
    struct node* next;
    };
typedef struct node Node;

//PUNTO A
parametri decodeParameters(int argc, char*argv[]){
    parametri p;

    if(argc!=4){
        fprintf(stderr,"Errrore, i parametri da inserire sono 3.\n");
        exit(-1);
    }

    int len1=strlen(argv[1]);
    int len2=strlen(argv[3]);

    p.simboli=malloc(sizeof(char)*(len1+1));
    p.output=malloc(sizeof(char)*(len2+1));

    if(len1<10 || len1>20){
        fprintf(stderr,"Errrore, il primo parametro da inserire è una stringa di lunghezza fra 10 e 20.\n");
        exit(-1);        
    }

    strcpy(p.simboli,argv[1]);
    strcpy(p.output,argv[3]);

    p.n=atoi(argv[2]);

    if(p.n<8 || p.n>18){
        fprintf(stderr,"Errrore, il primo parametro da inserire è una stringa di lunghezza fra 10 e 20.\n");
        exit(-1);         
    }

    printf("i parametri inseriti sono:\n%s\n%d\n%s\n",p.simboli,p.n, p.output);

    return p;
}
//PUNTO B

int fattoriale(int n){
    if(n==0){
        return 1;
    }

    else{
        return n*fattoriale(n-1);
    }
}


int*readInput(int n){
    int num;
    int*W=malloc(sizeof(int)*n);


    for(int i=0; i<n; i++){
        printf("inserire un numero\n");
        scanf("%d",&num);
        W[i]=fattoriale(num);

    }
    puts("\nPunto B - Contenuto di W:\n");
for (int y=0; y<n; y++){
    printf("%d ",W[y]);
}
printf("\n");
    return W;
}

//PUNTO C 

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

//funzione che prende in input la stringa simboli e un intero h e restituisca una
//stringa di h caratteri casuali campionati dalla stringa simboli.
char* sampleString(char*simboli,int h){
  int n=strlen(simboli);
  char*str=malloc(sizeof(char)*(h+1));

  for (int i=0; i<h; i++){

    int randindex=get_random()%n;
    str[i]=simboli[randindex];

  }

  str[h]='\0';
  return str;

}


//funzione che prende in input l’array W e la stringa simboli e permette di
//ottenere l’array di stringhe Q come specificato nel punto C.
char**getStringArray(int*W,char*simboli,int n){
    char**Q=malloc(sizeof(char*)*n);//alloco la memoria per le righe
    if (Q == NULL) {
        fprintf(stderr, "Errore nell'allocazione della memoria per l'array di stringhe.\n");
        exit(EXIT_FAILURE);
    }

    int L=strlen(simboli);

    for (int i=0; i<n; i++){
        int size=W[i]%L;//calcolo la dimensione della stringa 

    if (size == 0) {
        size = 1;  // Per evitare stringhe di lunghezza 0
        }

        Q[i]=sampleString(simboli,size);
        
    }
printf("\nPunto C - Contenuto di Q:\n");
    for(int y=0; y<n; y++){
        printf("%s\n",Q[y]);
    }

    return Q;

}

//PUNTO D

bool isempty(Node*head){
    return head==NULL;

}

Node*push(Node**head,char*data){
    Node*new=malloc(sizeof(Node));
        if (new == NULL) {
        fprintf(stderr, "Errore nell'allocazione della memoria per l'array di stringhe.\n");
        exit(-1);
    }

    new->data=data;
    new->next=*head;
    *head=new;
    
    return new;
}

char*pop(Node**head){
    if(isempty (*head)){
        printf("la lista è vuota.\n");
        exit(EXIT_FAILURE);
    }
    Node*tmp=*head;

    char*value=malloc(strlen(tmp->data)+1);

    strcpy(value,tmp->data);

    *head=tmp->next;
    free(tmp->data);
    free(tmp);

    return value;

    
}

void printstack(Node**head){
    Node*tmp=*head;

    while (tmp!=NULL)
    {
        printf("%s\n",tmp->data);
        tmp=tmp->next;
    }
    
}

Node* getStack(char**Q,int n){
    Node*head=NULL;

    for(int i=0; i<n; i++){

        int h=strlen(Q[i]);

        if(h%2==0 || isempty(head)){//se è pari
   
            char*str=malloc(sizeof(char)*(h+1));
            strcpy(str,Q[i]);
            push(&head, str);

        }else{
            char*a=pop(&head);
            int len2=strlen(a);

            char*b=malloc(sizeof(char)*(h+1));
            int index=0;

            for (int j=0;j<h; j++ ){
                for(int y=0; y<len2; y++){
                    if(Q[i][j]==a[y]){
                        b[index++]=Q[i][j];
                        break;


                    }
                }
            }
            
            b[index]='\0';

            head=push(&head,b);

            free(a);

       

        }//else
    }//for 
    printf("\nPunto D - Contenuto della pila:\n");
    printstack(&head);
        return head;
}
//PUNTO E

void writeStackToFile(char*filename,Node**stack){
    FILE*f=fopen(filename,"w");
         if (f == NULL) {
        fprintf(stderr, "Errore nell'apertura del file.\n");
        exit(-1);
    }
        Node*tmp=*stack;

    while(tmp->next!=NULL){
        fprintf(f,"%s\n",tmp->data);
        tmp=tmp->next;
    }
    free(tmp);
    fclose(f);

}

int main(int argc, char*argv[]){
    //PUNTO A
    parametri p=decodeParameters(argc,argv);
    //PUNTO B
    int*W=readInput(p.n);
    //PUNTO C
    char**Q=getStringArray(W,p.simboli,p.n);
    //PUNTO D
    Node*stack=getStack(Q,p.n);
    //PUNTO E
    writeStackToFile(p.output,&stack);


    return 0;
}