#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct {
    int N;
    double x;
    double y;

}record;

record readInput(int argc, char*argv[]){ //due numeri in virgola mobile positivi x,y. Dovra' essere 5.0 < x < y < 30.0;
    record p;
    if (argc!=4){
        fprintf(stderr, "Errore, i parametri da inserire sono 3.\n");
        exit(-1);
    }
    char**end=malloc(sizeof(char*));
    *end=NULL; 
    p.N=strtol(argv[1], end, 0);
    if(**end){
        fprintf(stderr, "Errore, il primo parametro da inserire deve essere un intero.\n");
        exit(-1);
    }
    if(p.N<10||p.N>20){
        fprintf(stderr, "Errore, il primo parametro da inserire deve essere un intero in 10-20.\n");
        exit(-1);

    }
     *end=NULL; 
    p.x=strtod(argv[2],end);
 
    if(**end){
        fprintf(stderr, "Errore, il secondo parametro da inserire deve essere un numero in virgola mobile.\n");
        exit(-1);
    }
    *end=NULL; 
    p.y=strtod(argv[3],end);

    if(**end){
        fprintf(stderr, "Errore, il terzo parametro da inserire deve essere un numero in virgola mobile.\n");
        exit(-1);
    }
    
      if(p.x<5.0||p.x>p.y||p.x>30.0){
        fprintf(stderr, "Errore, il secondo parametro da inserire (x) deve essere un numero in virgola mobile che rispetta: 5.0<x<y<30.0.\n");
        exit(-1);

    }
return p;
}

double genDouble(double x, double y){
  return ((double)get_random()/UINT_MAX)*(y-x+1)+x;//NB: Ai fini della generazione di numeri in virgola mobile, 
  //si faccia uso della costante UINT_MAX (<limits.h>) unitamente alla funzione get_random(). 

}

double**genMatrix(double x,double y,int N){
    double**A=calloc(N,sizeof(double*));
    for(int i =0; i<N;i++){
        A[i]=calloc(N,sizeof(double));
        for (int j=0; j<N; j++){
            A[i][j]=genDouble(x,y);
        }
    }
return A;
}

int computeMinMax(double**A, int N,double*mind, double *maxd){//La funzione cerca il minimo sulla diagonale principale e il massimo sulla diagonale opposta.
//Quindi conta quanti elementi della matrice sono compresi tra questi due valori.
    *mind=A[0][0];//puntatore alla variabile che conterrà il minimo sulla diagonale principale, quindi punta al primo elemento a sx (0,0)
    *maxd=A[N-1][0];//puntatore alla variabile che conterrà il massimo della diagonale opposta, punta al  primo elemento in basso a sx (0,0)

    for (int i=0; i<N; i++){
        if(A[i][i]<*mind){//Diagonale principale: Gli elementi si trovano nella forma [i][i] (esempio: [0][0], [1][1], ...).
            *mind=A[i][i];
        }
        if(A[i][N-1-i]){//Diagonale secondaria: Gli elementi si trovano nella forma [i][N-1-i] (esempio: [0][N-1], [1][N-2], ...)
            *maxd=A[i][N-1-i];

        }
    }
    int count=0;//contatore di quanti elementi della matrice sono compresi tra questi due valori.

    for(int i=0;i<N;i++){//scorro righe 
        for(int j=0; j<N; j++){//scorro colonne
            if(A[i][j]<=*maxd && A[i][j]>=*mind){//confronto ogni elemento con il max e min 
                count++;//se trovo un elemento che rientra nel range, addiziono nel conto
            }
        }
    }
    return count;
}

double *createArray(double**A, int N, double mind, double maxd , int count){
     double*AA=(double*)calloc(count,sizeof(double));
     int m=0;//contatore per passare all'elemento succeaaivo di AA (nuovo array)
    for(int i=0;i<N;i++){//scorro righe 
        for(int j=0; j<N; j++){//scorro colonne
            if(A[i][j]<=maxd && A[i][j]>=mind){//confronto ogni elemento con il max e min 
           AA[m]=A[i][j];//inserico l'elemento trovato
            m++;//aggiorno la posizione
        }
    }

}
return AA;
}

void sortArray(double* AA, int count) { //usando il selection sort
    for (int i = 0; i < count - 1; i++) { 
        int min_idx = i; // Inizializza l'indice minimo
        for (int j = i + 1; j < count; j++) {
            if (AA[j] < AA[min_idx]) { // Trova il valore minimo
                min_idx = j; // Aggiorna l'indice del minimo
            }
        }
        // Scambia l'elemento corrente con l'elemento minimo trovato
        if (min_idx != i) {
            double temp = AA[i];
            AA[i] = AA[min_idx];
            AA[min_idx] = temp;
        }
    }
}
void printArray(double* AA, int count) {
     printf("l'array ordinato è:\n");
    for (int i = 0; i < count; i++) {
        printf("%lf\n ", AA[i]);
    }
    printf("\n");
    double somma=0;
 for (int i = 0; i < count; i++) {
     
     somma+= AA[i];
    }
    double media=somma/count;
    printf("la media matematica è %lf.\n", media);

}


int main(int argc, char*argv[]){
    record p=readInput(argc,argv);
    double **A=genMatrix(p.x,p.y,p.N);
    double mind, maxd;

    int num=computeMinMax(A,p.N,&mind,&maxd);
    double*array=createArray(A,p.N,mind,maxd,num);

    sortArray(array,num);
    printArray(array, num);



    return 0;
}