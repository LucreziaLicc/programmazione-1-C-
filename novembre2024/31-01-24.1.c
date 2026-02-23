#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    char*input_filename;
    char*output_filename;
}parametri;

parametri decodeParameters(int argc, char*argv[]){
    if(argc!=3){
        fprintf(stderr, "errore, i parametri da inserire sono due nomi di file con estensione '.txt'\n");
        exit(-1);
    }

    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);

    if(len1<4 || len2<4 || strcmp(argv[1]+len1-4,".txt")!=0 ||strcmp(argv[2]+len2-4,".txt")!=0){
        fprintf(stderr, "errore, i parametri da inserire sono due nomi di file con estensione '.txt'\n");
        exit(-1);        
    }
    parametri p;
    p.input_filename=malloc(sizeof(char)*(len1+1));
    p.output_filename=malloc(sizeof(char)*(len2+1));

    strcpy(p.input_filename,argv[1]);
    strcpy(p.output_filename,argv[2]);

    printf("\n======A Stampa Parametri======\ninput_filename = %s\noutput_filename = %s\n",p.input_filename,p.output_filename);

    return p;

}
//PUNTO B

void readHeader(int*n, int*m, char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr, "errore nell'apertura del file\n");
        exit(-1);
    }

    if(fscanf(f,"%d %d",n,m)!=2){
        fprintf(stderr, "errore nella letttura del file\n");
        exit(-1);        
    }
    fclose(f);
}

void printMatrix(int n, int m, double***X){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(X[i][j]==NULL){
                printf("%6s ","*");
            }else{
                printf("%6.2lf ",*X[i][j]);
            }
        }
        printf("\n");
    }

}

double***readFile(int n, int m, char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr, "errore nell'apertura del file\n");
        exit(-1);
    }

    char buffer[100];
    fgets(buffer, sizeof(buffer),f);

    double***X=malloc(sizeof(double**)*n);
    for(int i=0; i<n; i++){
        X[i]=malloc(sizeof(double*)*m);
        for(int j=0; j<m; j++){
            X[i][j]=malloc(sizeof(double));
            fscanf(f,"%lf",X[i][j]);
        }
    }
    fclose(f);
    printMatrix(n,m,X);

    return X;

}

//PUNTO C
double getMean(double**X,int m){
    double somma=0; 

    for(int i=0; i<m; i++){
        somma+=*X[i];
    }

    double mean=somma/(double)m;

    return mean;
}


void selectionSort(double*Y,int n){
    for(int i=0; i<n-1;i++){
        int min=i;
        for(int j=i+1; j<n; j++){
            if(Y[j]<Y[min]){
                min=j;
            }
            double temp=Y[min];
            Y[min]=Y[i];
            Y[i]=temp;
        }
    }
}


void printarray(double*Y,int n){
    for(int j=0; j<n; j++){
        printf("%0.2lf ", Y[j]);
    }
}

double*getArray(double***X, int n, int m){
    double*Y=malloc(sizeof(double)*n);

    for(int i=0; i<n; i++){
        Y[i]=getMean(X[i],m);
    }

    printf("\n\n======C Array Y======\n");
    printarray(Y,n);

    selectionSort(Y,n);
    printf("\n\n======C Array Y ordinato======\n");
    printarray(Y,n);    


    return Y;

    
}

//PUNTO D

void processX(double***X, double*Y, int n, int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(*X[i][j]>Y[i]){
                free(X[i][j]);
                X[i][j]=NULL;
            }
        }
    }

    printf("\n\n======D Matrice X modificata======\n");

    printMatrix(n,m,X);
}
//PUNTO E

void writeToFile(char*filename,double***X,int n, int m){
    FILE*f=fopen(filename,"w");
    if(f==NULL){
        fprintf(stderr, "errore nell'apertura del file\n");
        exit(-1);
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(X[i][j]==NULL){
                fprintf(f,"%6s ","*");
            }else{
                fprintf(f,"%6.2lf ",*X[i][j]);
            }
        }
        fprintf(f,"\n");
    }
        
}


int main(int argc, char*argv[]){
    parametri p=decodeParameters(argc,argv);
    //PUNTO B
    int n,m;
    readHeader(&n,&m,p.input_filename);
    printf("\n\n======B Matrice X======\n");
    double***X=readFile(n,m,p.input_filename);
    //PUNTO C
    double*Y=getArray(X,n,m);
    //PUNTO D
    processX(X,Y,n,m);
    //PUNTO E
    writeToFile(p.output_filename,X,n,m);




    return 0;
}