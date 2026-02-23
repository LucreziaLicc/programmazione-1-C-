#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
    int n;
    int m;
}parametri;

parametri decodeParameters(int argc, char*argv[]){
    if(argc!=3){
        fprintf(stderr, "errore, bisogna inserire due parametri: due interi.\n");
        exit(-1);
    }

    if(!atoi(argv[1])||!atoi(argv[2])||atoi(argv[1])<0 || atoi(argv[2])<0){
        fprintf(stderr, "errore, i due interi inseriti devono essere positivi e compresi fra 3 e 7, inclusi.\n");
        exit(-1);
    }

    if(atoi(argv[1])<3||atoi(argv[1])>7||atoi(argv[2])<3 || atoi(argv[2])>7){
        fprintf(stderr, "errore, i due interi inseriti devono essere positivi e compresi fra 3 e 7, inclusi.\n");
        exit(-1);
    }

    parametri p;
    p.n=atoi(argv[1]);
    p.m=atoi(argv[2]);

    printf("\nPunto A - Parametri inseriti: n=%d, m=%d\n",p.n,p.m);

    return p;
}

//PUNTO B

int getNum(){
    printf("\ninserire un intero fra 10 e 100\n");
    int h;
    scanf("%d",&h);
    if(h<10 || h>100){
        fprintf(stderr,"Errore, ilnumero inserito deve essere compreso fra 10 e 100\n");
        exit(-1);
    }
    printf("\nnumero inserito: %d\n",h);
    return h;
}

unsigned int get_random() {
static unsigned int m_w = 424242;
static unsigned int m_z = 242424;
m_z = 36969 * (m_z & 65535) + (m_z >> 16);
m_w = 18000 * (m_w & 65535) + (m_w >> 16);
return (m_z << 16) + m_w;
}

int getRandomNum(int h){
    int range=h+1;
    int x=get_random()%range;
    return x;
}

void printMatrix(int***A, int n, int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(A[i][j]== NULL){
                printf("%3s","*");
            }else{
            printf("%3d",*A[i][j]);
            }
        }
        printf("\n");
    }
}

int*** getRandomMatrix(int n, int m){
    int h= getNum();

    int***A=malloc(sizeof(int**)*n);

    for(int i=0; i<n; i++){
       A[i]= malloc(sizeof(int*)*m);
       for(int j=0; j<m; j++){
        A[i][j]=malloc(sizeof(int));
        *A[i][j]=getRandomNum(h);

       }
    }

    printf("\nPunto B - Contenuto di A:\n");

    printMatrix(A,n,m);

    return A;
}
//PUNTO C


void removeMax(int***A, int n, int col){
    if (A == NULL || n <= 0 || col < 0) {
    fprintf(stderr, "Errore: parametri non validi.\n");
    return;
}

    int max;//supponiamo che il primo elemento sia il maggiore
    int maxRow=-1;//indice che contiene la riga del massimo


    for (int i=0; i<n;i++){
        if(A[i][col]!=NULL ){
            if(maxRow==-1 || *A[i][col]>max){
                max=*A[i][col];
                maxRow=i;
            } 
        }
    }

    if(maxRow!=-1){
        free(A[maxRow][col]);
        A[maxRow][col] = NULL;
    }
  
}

void modifyMatrix(int***A, int n, int m){
   if (A == NULL || *A == NULL || n <= 0 || m <= 0) {
       fprintf(stderr, "Errore: matrice non valida o dimensioni non corrette.\n");
        return;
    }

    for(int x=0; x<3; x++){
        for (int i=0; i<m; i++){
            removeMax(A,n,i);
        }
    }

    printf("\nPunto C - Contenuto di A dopo la modifica:\n");
    printMatrix(A,n,m);


}
//PUNTO D
/*. Si stampino su standard output i valori della riga contenente il numero minore di valori NULL.
NOTA: qualora più righe dovessero avere lo stesso numero 𝑥 di valori NULL, sarà sufficiente
stampare una qualsiasi riga contenente 𝑥 valori NULL.*/
int findNumNull(int***A,int row, int m){
    int num=0;
    for(int i=0; i<m; i++){
        if(A[row][i]==NULL){
            num++;
        }
    }
    return num;
}

void rowMinNull(int***A,int n, int m){
    int minRow=findNumNull(A,0,m);
    int index=0;

    for(int i=1; i<n; i++){
        int x=findNumNull(A,i,m);
        if(x<minRow){
            minRow=x;
            index=i;
        }
    }

    for (int j=0; j<m; j++){
        if(A[index][j]==NULL){
            printf("%3s","*");
        }else{
        printf("%3d ",*A[index][j]);
        }
    }


}







int main(int argc,char*argv[]){
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    int***A=getRandomMatrix(p.n,p.m);
    //PUNTO C
    modifyMatrix(A,p.n,p.m);
    //punto E
    printf("\nPunto D - Riga con minor numero di NULL:\n");
    rowMinNull(A,p.n,p.m);




    return 0;
}