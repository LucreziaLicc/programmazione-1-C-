#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct {
    int k;
    char w;
    int N;
    int M;
}parametri;

parametri readInput(int argc, char*argv[]){
    if(argc!=5){
        fprintf(stderr,"errore, i parametri da inserire sono 4.\n");
        exit(-1);
    }
    parametri p;

    if(atoi(argv[1])<10 || atoi(argv[1])>15){
        fprintf(stderr,"errore, il primo intero da inserire deve essere compreso fra 10 e 15, inclusi.\n");
        exit(-1);
    }
    p.k=atoi(argv[1]);

    if(strlen(argv[2])!=1 || argv[2][0]<'a' || argv[2][0]>'z'){
        fprintf(stderr,"errore, il secondo paramatro è un singolo carattere fra 'a'-'z'\n");
        exit(-1);
    }
    p.w=argv[2][0];

    if(atoi(argv[3])<4|| atoi(argv[3])>8 || atoi(argv[4])<4|| atoi(argv[4])>8){
        fprintf(stderr,"errore, il terzo e il quarto intero da inserire devono essere compresi fra 4 e 8, inclusi.\n");
        exit(-1);        
    }
    p.N=atoi(argv[3]);
    p.M=atoi(argv[4]);

    printf("\nPUNTO A-parametri :\n%d\n%c\n%d\n%d\n",p.k,p.w,p.N,p.M);

    return p;



}

//PUNTO B

char***allocateS(int N, int M){
    char***S=malloc(sizeof(char**)*N);
    for(int i=0; i<N; i++){
        S[i]=malloc(sizeof(char*)*M);
    };
    return S;
}

//PUNTO C
unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

char*genString(int k){
    char*newstr=malloc(sizeof(char)*(k+1));

    for(int i=0; i<k; i++){
        newstr[i]=get_random()%('z'-'a'+1)+'a';
    }
    newstr[k]='\0';
    return newstr;

}
void printMatrix(char***S,int N,int M){
        for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            fprintf(stdout,"%s  ",S[i][j]);
        }
        fprintf(stdout,"\n");
    }
}

void fillS(char***S, int N,int M, int k){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            S[i][j]=genString(k);
        }
    }
    printMatrix(S,N,M);
    
}

//PUNTO D
void sort(char**S, int N){//ordina una singola colonna
    for(int i=0; i<N; i++ ){
        char*elem=S[i];
        int j=i-1;
        while (j>=0 && strcmp(S[j],elem)>0)
        {
            S[j+1]=S[j];
            j=j-1;
        }
        S[j+1]=elem;
    }
}

void sortS(char***S,int N, int M){
   for(int j=0;j<M;j++ ){
    char**column=malloc(N*sizeof(char*));
    for(int i=0; i<N; i++){
        column[i]=S[i][j];//viene estrett atemporaneamente una singola colonna per ordinarla 
    } 
    sort(column,N);//si ordina
    for(int i=0; i<N; i++){
    S[i][j]=column[i];//si reinserisce ordinata
    }
    free(column);//si libera la memoria ussata
   } 
   printf("\nmatrice S ordinata:\n");
   printMatrix(S,N,M);

}

//PUNTO E
int conta (char*s, char w){
    int c=0;
    for(int i=0; i<strlen(s); i++){
        if(s[i]==w){
            c++;

        }
    }
    return c;
}

void printMax(char***S, int N, int M,char w){
    int i_max=0;
    int j_max=0;
    int max=0;
    for(int i=1; i<N; i++){
        for(int j=1; j<M; j++){
            int count=conta(S[i][j],w);
            if(count>max){
                max=count;
                i_max=i;
                j_max=j;
            }
        }
    }
    printf("\nStringa con %d occorrenze di '%c' trovata agli indici %d, %d: ", max, w, i_max, j_max);

    for(int i=0; i<strlen(S[i_max][j_max]);i++){
        if(S[i_max][j_max][i]==w){
        fprintf(stdout,"*");
        }else{
            fprintf(stdout,"%c",S[i_max][j_max][i]);
        }
    }    
}


int main(int argc, char*argv[]){
    parametri p=readInput(argc,argv);
    //PUNTO B
    char***S=allocateS(p.N,p.M);
    //PUNTO C
    printf("\nmatrice S:\n");    
    fillS(S,p.N,p.M,p.k);
    //PUNTO D
    sortS(S,p.N,p.M);
    //PUNTO E
    printMax(S,p.N,p.M,p.w);     




    return 0;
}