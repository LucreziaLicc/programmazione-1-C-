#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
    int n;
    int m;
    char*filename;
}parametri;

parametri decodeParameters(int argc, char*argv[]){
    parametri p;
    if(argc!=4){
        fprintf(stderr,"errore, il numero di parametri inseriti deve essere 3.\n");
        exit(-1);
    }
p.n=atoi(argv[1]);
p.m=atoi(argv[2]);

if(p.n<3 || p.n>7 ||p.m<3 || p.m>7){
        fprintf(stderr,"errore, gli interi inseriti devono essere compresi fra 3 e 7, inclusi.\n");
        exit(-1);    

}
int len=strlen(argv[3]);
p.filename=malloc(sizeof(char)*(len+1));
    if (!p.filename) {
        fprintf(stderr, "Errore di allocazione della memoria per il nome del file.\n");
        exit(1);
    }

if (len<4 || strcmp(argv[3]+len-4,".txt")!=0){
     fprintf(stderr,"errore, la stringa inserita deve essere con estensione '.txt'.\n");
        exit(-1);    
   
}
strcpy(p.filename,argv[3]);

printf("======Stampa Parametri======\nn:%d\nm:%d\nfilename:%s\n",p.n,p.m,p.filename);
return p;
}

//PUNTO B
void printMatrix(double**X,int n, int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf("%lf ", X[i][j]);
        }
        printf("\n");
    }
}

double**readFile(char*filename, int n, int m){
    FILE*f=fopen(filename,"r");
    if (!f) {
        fprintf(stderr, "Errore nell'apertura del file.\n");
        exit(1);
    }    
    
    double**X=malloc(sizeof(double*)*n);
    for(int i=0; i<n; i++){
        X[i]=malloc(sizeof(double)*m);
    if (!X[i]) {
        fprintf(stderr, "Errore nell'allocazione della memoria.\n");
        exit(1);

        for(int y=0; y<n;y++){
            free(X[y]);
        }
        free(X);
        exit(-1);
    }         

      
    
     for(int j=0; j<m;j++){
            if(fscanf(f,"%lf",&X[i][j])!=1){
                fprintf(stderr,"errore nella lettura del file.\n");
                exit(-1);
                fclose(f);

        for(int y=0; y<n;y++){
            free(X[y]);
        }
        free(X);
        exit(-1);

            }
            if(j<m-1){
                fscanf(f,",");//salta la virgola
            }
        }
    }
    fclose(f);
    printf("======Stampa X======\n");
    printMatrix(X,n,m);

    return X;    
}
//PUNTO C

void getMeanMinMax(double**X, int col, float *mean, float *min, float*max){
    




}







int main(int argc, char*argv[]){
    //PUNTO A
    parametri p=decodeParameters(argc,argv);
    //PUNTO B
    double**X=readFile(p.filename,p.n,p.m);
    //PUNTO C


    return 0;
}