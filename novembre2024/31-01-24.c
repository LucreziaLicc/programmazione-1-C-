#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct  {
    char*input_filename;
    char*output_filename;

}parametri;


parametri decodeParameters(int argc, char*argv[]){

    if(argc!=3){
        fprintf(stderr,"errore, il numero di parametri da isnerire è 2.\n");
        exit(-1);
    }

    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);

    if(len1<4 || len2<4 || strcmp(argv[1]+len1-4,".txt")!=0 ||strcmp(argv[2]+len2-4, ".txt")!=0){
        fprintf(stderr, "errore, le estensioni dei nomi di file da inserire devono essere '.txt'.\n");
        exit(-1);
    }

    parametri p;

    p.input_filename=malloc(sizeof(char)*(len1+1));
    p.output_filename=malloc(sizeof(char)*(len2+1));

    strcpy(p.input_filename,argv[1]);
    strcpy(p.output_filename,argv[2]);

    printf("======A Stampa Parametri======\ninput_filename = %s\noutput_filename = %s\n",p.input_filename,p.output_filename);

    return p;

}
//PUNTO B
FILE*RFile(char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr, "errore nell'apertura del file.\n");
        exit(-1);

    }

    return f;
}
 FILE*WFile(char*filename){
    FILE*f=fopen(filename,"w");
    if(f==NULL){
        fprintf(stderr, "errore nell'apertura del file.\n");
        exit(-1);

    }

    return f;
}
void readHeader(char*filename,int*n,int*m){
    FILE*f=RFile(filename);
    fscanf(f,"%d %d",n, m);
    printf("\nn:%d\nm:%d\n",*n,*m);
}

void printMatrix(double***X,int n, int m){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
            printf("%0.2lf ",*X[i][j]);
            }
            printf("\n");
    }

}

double***readFile(char*filename,int n, int m){
    FILE*f= RFile(filename);

    double***X=malloc(sizeof(double**)*n);

    char buffer[100];
    fgets(buffer,100,f);

    for(int i=0; i<n; i++){
        X[i]=malloc(sizeof(double*)*m);
        for(int j=0; j<m; j++){
            X[i][j]=malloc(sizeof(double));
            fscanf(f,"%lf",X[i][j]);
        }
    }

printMatrix(X,n,m);

    return X;

}
//PUNTO C

double getmean(double**X,int m){
    double somma=0;

    for(int i=0; i<m; i++){
        somma += *X[i];
    }

    double media=somma/m;

    return media;
}

void selectionSort(double*Y,int n){
    for(int i=0; i<n-1;i++){
        int min=i;
        for(int j=i+1; j<n; j++){
            if(Y[j]<Y[min]){
                min = j;
            }
            double temp=Y[min];
            Y[min]=Y[i];
            Y[i]=temp;
        }
    }
}

double*getArray(double***X,int n, int m){
    double*Y=malloc(sizeof(double)*n);

    for(int i=0; i<n; i++){
        double media=getmean(X[i],m);
        Y[i]=media;
    }

    printf("\n======C Array Y======\n");

    for(int j=0; j<n; j++){
        printf("%0.2lf ",Y[j]);
    }
    printf("\n======C Array Y ordinato ======\n");
    selectionSort(Y,n);
    for(int j=0; j<n; j++){
        printf("%0.2lf ",Y[j]);
    }    
    return Y;
    
}
//PUNTO D
void processX(double***X,double*Y,int n, int m){
    for(int i=0; i<n;i++){
        for(int j=0; j<m; j++){
            if(*X[i][j]>Y[i]){
                free(X[i][j]);
                X[i][j] = NULL;
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(X[i][j]==NULL){
               printf("%6s ", "*");
            }else{
                printf("%6.2lf ",*X[i][j]);
            }
        }
        printf("\n");
    }
}

//PUNTO E
void writeToFile(char*filename,double***X,int n, int m ){
    FILE*f=WFile(filename);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(X[i][j]==NULL){
               fprintf(f,"%6s ", "*");
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
    printf("\n======B Valori n e m======\n");
    int n;
    int m;
    readHeader(p.input_filename,&n,&m);
    printf("\n======B Matrice X======\n");    
    double***X=readFile(p.input_filename,n,m);
    //PUNTO C
    double*Y=getArray(X,n,m);
    //PUNTO D
    printf("\n======D Matrice X modificata======\n");
    processX(X,Y,n,m);
    //PUNTO E

    writeToFile(p.output_filename,X,n,m);





    return 0;
}