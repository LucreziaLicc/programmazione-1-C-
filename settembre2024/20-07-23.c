#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

typedef struct {
    int n;
    int m;
}parametri;


parametri decodeParameters(int argc, char*argv[]){
    parametri p;
    if (argc!=3){
        fprintf(stderr,"Errore, i parametri da inserire sono due interi, n e m.\n");
        exit(-1);
    }
p.n=atoi(argv[1]);
p.m=atoi( argv[2]);

    if(p.n<0||p.m<0||p.n<3 || p.n>7||p.m<3 || p.m>7){
         fprintf(stderr,"Errore, i parametri da inserire sono due interi, n e m, positivi e compresi fra 3 e 7 inclusi.\n");
        exit(-1);       
        
    }



printf("Punto A - Parametri inseriti: n=%d, m=%d\n",p.n,p.m);
return p;


}


//PUNTO B

unsigned int get_random() {
static unsigned int m_w = 424242;
static unsigned int m_z = 242424;
m_z = 36969 * (m_z & 65535) + (m_z >> 16);
m_w = 18000 * (m_w & 65535) + (m_w >> 16);
return (m_z << 16) + m_w;
}



int randomNum(int h){

    return get_random()%(h+1);

}



void printMatrix(int ***A, int n, int m) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(A[i][j])
                printf("%5d",*A[i][j]);
            else
                printf("    *");
        }
        printf("\n");
    }
}


int***getRandomMatrix(int n,int m, int* h){
    int***A=malloc(sizeof(int**)*n);//alloco le righe 
        printf("\ninserire un numero fra 10 e 100, inclusi.\n");
        scanf("%d",h);

    if (*h<10 ||*h>100){
    fprintf(stderr,"errore, il numero inserito deve essere fra 10 e 100, inclusi.\n");
    exit(-1);
    }

    for (int i =0; i<n; i++){
        A[i]=malloc(sizeof(int*)*m);
        for(int j=0; j<m; j++){
            A[i][j]=malloc(sizeof(int));//devo allocare prim la memoria di ogni casella per poterla liberare dopo
            *A[i][j]=randomNum(*h);
        }
    }

    printf("Punto B - Contenuto di A:\n");

printMatrix(A,n,m);

return A;

}

//PUNTO C

    // funzione che prende in input la matrice A, la dimensione n e un indice di
//colonna col, e rimuove il massimo valore nella colonna 'col' come indicato nel punto C;
 
 void removeMax(int***A,int n, int col){

    int max;//conterrà il valore massimo trovato nella colonna specificata
    bool init=false;//serve a controllare se il massimo è stato inizializzato
    int maxrowindex=-1;//contiene l'indice della riga, inizialmente nulla (-1)

    for(int i=0; i<n; i++){
        if(A[i][col]){//verifica che l'elemento non sia a NULL
            if(!init || max<*A[i][col]){//
            max=*A[i][col];
            maxrowindex=i;  //
            init=true;//
            }


    }
    }
           if(maxrowindex>=0){
            free(A[maxrowindex][col]); 
            A[maxrowindex][col]=NULL;
           }
 }



void modifyMatrix(int***A, int n, int m){
    for (int col=0; col<m; col++){//ciclo
        for(int y=0; y <3; y++){
        removeMax(A,n,col);

        }
    }
    printf("Punto C - Contenuto di A dopo la modifica:\n");
    printMatrix(A,n,m);

}
//PUNTO D

int rowMinNull(int***A, int n, int m){
    int min=m;
    int indxmin=-1;

    for (int i=0; i<n; i++){
        int numnull=0;
        for(int j=0; j<m; j++){
            if(!A[i][j]){
                numnull++;
            }
        }
        if(numnull<min){
           min =numnull;
            indxmin=i;
        }

    }
    return indxmin;

}

void printRow(int***A, int row, int m){
    for(int i=0; i<m; i++){
        if(A[row][i]){
            printf("%5d",*A[row][i]);
        }else{
            printf("    *");
        }
    }
}

int main(int argc, char*argv[]){
    srand(time(NULL));
    //PUNTO A
    parametri p=decodeParameters(argc,argv);
    //PUNTO B
    int h;
    int ***A=getRandomMatrix(p.n,p.m,&h);
    //PUNTO C
    modifyMatrix(A,p.n,p.n);
    //PUNTO D
    int row=rowMinNull(A,p.n,p.m);
    printf("Punto D - Riga con minor numero di NULL:\n");
    printRow(A,row,p.m);







    return 0;
}