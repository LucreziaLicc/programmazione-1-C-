#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
typedef struct{
    int k;
    char w;
    int N;
    int M;
}record;

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

//A prenda un input da tastiera (argomenti della funzione main()) un intero k in [10,15], 
//un carattere w in [‘a’-’z’] e due interi N ed M in [4,8]; se gli argomenti a riga di comando non 
//rispondono ai suddetti requisiti, il programma  stampa un messaggio di errore sullo standard error 
//e termina la propria esecuzione con codice di errore “-1”; 
record readInput(int argc, char*argv[]){
    record p={0,0,0,0};
    if(argc!=5){
        fprintf(stderr,"Errore, i parametri da inserire sono 4.\n");
        exit(-1);
    }


    char**end=malloc(sizeof(char*));//si alloca memoria per il puntatore per la funziione 'strtol'
    *end=NULL;

    p.k=(int)strtol(argv[1],end,0);//Il primo argomento (argv[1]) dovrebbe essere un intero. 
    //Viene convertito da stringa a intero utilizzando strtol, e il valore risultante viene memorizzato in d.k.
    if(**end){//La variabile end serve per rilevare eventuali errori nella conversione: 
    //se *end non è NULL, significa che non tutta la stringa era un numero valido 
         fprintf(stderr,"Il primo parametro deve essere un intero in 10-15.\n");
        exit(-1);
    }
    if(p.k<10|| p.k>15){
        fprintf(stderr,"Il priimo parametro deve essere un intero in 10-15.\n");
        exit(-1);
    }
     if(strlen(argv[2])!=1){
        fprintf(stderr,"errore, ilsecondo parametro deve essere un carattere in 'a'-'z'.\n");
        exit(-1);
     }
     p.w=argv[2][0];
     if(p.w<'a'||p.w>'w'){
        fprintf(stderr,"errore, ilsecondo parametro deve essere un carattere in 'a'-'z'.\n");
        exit(-1);
     }

     p.N=(int)strtol(argv[3],end,0);
if(**end){
         fprintf(stderr,"Il terzo parametro deve essere un intero in 4-8.\n");
        exit(-1);
    }
 if(p.N<4|| p.N>8){
        fprintf(stderr,"Il terzo parametro deve essere un intero in 4-8.\n");
        exit(-1);
 }
     p.M=(int)strtol(argv[4],end,0);
if(**end){
         fprintf(stderr,"Il quarto parametro deve essere un intero in 4-8.\n");
        exit(-1);
    }
 if(p.M<4|| p.M>8){
        fprintf(stderr,"Il quarto parametro deve essere un intero in 4-8.\n");
        exit(-1);
    
}
return p;
}

char***allocateS(int N,int M){
    char***S=malloc(N*sizeof(char*));//alloco la memoria per 'N' righe

    if(S==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    for(int i=0;i<N;i++){
       S[i]=malloc(M*sizeof(char));//alloco per ogni riga lo spazio per M caratteri(lunghezza di ogni riga)
       if(S[i]==NULL){
          fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
       }
    }
    return S;
}
char*genString(int k,char min,char max){//genera una stringa con caratteri pseudocasuali in 'a'-'z'
    char*s=calloc(k,sizeof(char*));
    for(int i=0;i<k;i++){
        s[i]=rand()%(max-min+1)+min;
    }
        s[k] = '\0';  // Aggiungi il terminatore di stringa

return s;
}
void fillS(char***S, int N, int M, int k){
    for (int i=0;i<N;i++){//ciclo esterno righe
        for(int j=0;j<M;j++){//ciclo interno colonne
            S[i][j]=genString(k,'a','z');//Riempie ogni cella con una stringa casuale
        }
    }

}


//D ordini ogni colonna della matrice S in modo crescente (ordinamento lessicografico) 
//con un algoritmo di ordinamento a scelta tra Insertion Sort e Bubble Sort;
//sortS: funzione di ordinamento della matrice come specificato nel punto D; NB: si faccia uso, al suo interno, della funzione di libreria strcmp()
void sortS(char***S, int N, int M){//N:numero di righe, M:numero di colonne della matrice
    for(int j=0;j<M;j++){//scorro le colonne
    for (int pass=0; pass<N-1; pass++){//BUBBLE SORT:questo ciclo rappresenta il numero di passaggi per il sort, in totale n-1.
        for(int i=0; i<N-1-pass;i++){//per ogni passaggio si confrontanbo copiie adiacenti di stringhe
            if(strcmp(S[i][j], S[i+1][j])>0){
                char*tmp=S[i][j];
                S[i][j]=S[i+1][j];
                S[i+1][j]=tmp;
            }
        }
        
    } 

    }

}

void printMatrix(char***S,int N, int M){//N:numero di righe, M:numero di colonne della matrice
    for(int i=0; i<N; i++){//scorro le righe
        for(int j=0;j<M;j++){//scorro le colonne
            printf("%s ", S[i][j]);
        

        }
puts("\n");
    }

}
int conta(char*s, char w){//funzione che conta il numero di occorrenze del carattere nella stringa
    int c=0;//contatore
    for(int i=0; i<strlen(s);i++){//scorre i caratteri della stringa
        if(s[i]== w)
        c++;//se la condizione è verificata, incrementa il contatore

    }
return c;
}

void printstring(char***S, int N, int M, char w){//La funzione printMax esplora una matrice di stringhe e trova la stringa 
//che contiene il maggior numero di occorrenze di un carattere specifico. 
//Inoltre, stampa questa stringa sostituendo tutte le occorrenze del carattere trovato con un asterisco ('*').
    int i_max=0;//indice della riga della str con il maggior n di occorrenze
    int j_max=0; //indice della colonna della str ...
    int max=0; //numero max di occorrenze trovate

    for(int i=0; i<N;i++){
        for(int j=0; j<M;j++){

            int count= conta(S[i][j], w);//usa la funzione conta per trovare il numero di occorrenze
            if (count > max){//se la stringa corrente è maggiore del conteggio precedente, si aggiorna il max
            max=count;
            i_max=i;//le due variabili salvano gli indici della stringa con più ricorrenze
            j_max=j; 

            }
        }
    }

    printf("\nLa stringa %d numero di occorrenze del carattere '%c' è trovata agli indici %d,%d: ", max, w, i_max, j_max);
    for (int i=0; i< strlen(S[i_max][j_max]); i++){
        char c=S[i_max][j_max][i];
        c=(c==w)? '*': c;
        printf("%c",c);
    }
printf("\n");
}

int main(int argc, char*argv[]){
    record p= readInput(argc,argv);
    char***S=allocateS(p.N, p.M);
    fillS(S,p.N,p.M,p.k);
    sortS(S,p.N,p.M);
    printMatrix(S,p.N,p.M);
    printstring(S,p.N,p.M,p.w);

    return 0;

}