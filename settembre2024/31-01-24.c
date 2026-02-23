#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct{
    char*input_filename;
    char*output_filename;
}parametri;

//PUNTO A
parametri decodeParameters(int argc, char*argv[]){
    if(argc!=3){
        fprintf(stderr,"Errore, il numero dei parametri da inserire è 2.\n");
        exit(-1);
    }

    parametri p;
    p.input_filename=malloc(strlen(argv[1])+1);
    if(p.input_filename==NULL){
        fprintf(stderr,"Errore nell'allocazione della memoria.\n");
        exit(-1);        
    }
    p.output_filename=malloc(strlen(argv[2])+1);
    if(p.output_filename==NULL){
        fprintf(stderr,"Errore nell'allocazione della memoria.\n");
        exit(-1);        
    }    
   
   int len1=strlen(argv[1]);
   int len2=strlen(argv[2]);

   if(len1<4 || len2<4 ||strcmp( argv[1]+len1-4, ".txt")!=0 ||strcmp( argv[2]+len2-4, ".txt")!=0){
        fprintf(stderr,"Errore, i parametri da inserire sono due stringhe di nome file con estensione '.txt'.\n");
        exit(-1);       
   }

   strcpy(p.input_filename,argv[1]);
   strcpy(p.output_filename,argv[2]);


printf("======A Stampa Parametri======\ninput_filename = %s\noutput_filename = %s\n", p.input_filename,p.output_filename);
   return p;

}
//PUNTO B

void readHeader(int*n, int*m,char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);        
    }

    if(fscanf(f,"%d %d",n,m)!=2){
        fprintf(stderr,"Errore nella lettura del file.\n");
        exit(-1);         
    }

}


void printMatrix(double***X, int n, int m){
    for(int i=0 ; i<n; i++ ){
        for(int j=0; j<m; j++){
            if(X[i][j]!= NULL){
            printf("%6.2lf ", *X[i][j]);
            }else{
                printf("%7s","* ");
            }
        }
        printf("\n");
    }
}

double*** readFile(int n, int m, char*filename){
        FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        exit(-1);        
    }

        char buffer[256];
    if (fgets(buffer, sizeof(buffer), f) == NULL) {
        fprintf(stderr, "Errore nella lettura della prima riga del file.\n");
        fclose(f);
        exit(-1);
    }

    double***X=malloc(sizeof(double**)*n);
    if(X==NULL){
        fprintf(stderr,"Errore nell'allocazione della memoria.\n");
        exit(-1);        
    }     

    for(int i=0; i<n; i++){
        X[i]=malloc(sizeof(double*)*m);
        for(int j=0; j<m; j++){
            X[i][j]=malloc(sizeof(double));
            fscanf(f,"%lf", X[i][j]);
        }
    }
fclose(f);
printf("\n======B Matrice X======\n");
printMatrix(X,n,m);

    return X;

}
//PUNTO C
void selectionSort(double*Y,int n){
    for(int i=0; i<n-1; i++){
        int min=i;
        for(int j=i+1;j<n; j++ ){
            if(Y[j]<Y[min]){
                min =j;
            }
        }
        double temp=Y[min];
        Y[min]=Y[i];
        Y[i]=temp;
    }
}

void printArray(double*Y, int n){
    for(int i=0; i<n; i++){
    printf("%0.2lf ",Y[i]);
}
}

double* getArray(int n,int m,double***X){
    double*Y=malloc(sizeof(double)*n);
    if(Y==NULL){
        fprintf(stderr,"Errore nell'allocazione della memoria.\n");
        exit(-1);        
    }     

    for(int i=0; i<n;i++){
        Y[i]=0;
        int conto=0;
        for(int j=0; j<m; j++){
            if(X[i][j]){
                Y[i]+=*X[i][j];//sommo ogni numero nella casella y
                conto++;//sommo al contatore per dividere
            }


        }
        Y[i]/=conto;//faccio la media
    }
printf("\n======C Array Y======\n");
printArray(Y,n);

selectionSort(Y,n);
printf("\n======C Array Y Ordinato======\n");
printArray(Y,n);

    return Y;

}
//PUNTO D

void processX(double***X,int n, int m, double*Y){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++ )
        if(X[i][j] && Y[i]<*X[i][j]){
            free(X[i][j]);
            X[i][j]=NULL;
        }
    }
printf("\n======D Matrice X modificata======\n");
printMatrix(X,n,m);

}

//PUNTO E
void writeToFile(char*filename,double***X, int n, int m ){
   FILE*f=fopen(filename, "w");
   if(f==NULL){
    fprintf(stderr,"Errore nell'apertura del file.\n");
    exit(-1);
   }

    for(int i=0 ; i<n; i++ ){
        for(int j=0; j<m; j++){
            if(X[i][j]!= NULL){
            fprintf(f,"%6.2lf ", *X[i][j]);
            }else{
                fprintf(f,"%7s","* ");
            }
        }
        fprintf(f,"\n");
    }


}

int main (int argc, char*argv[]){
    //PUNTO A
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    int n;
    int m;
    readHeader(&n,&m,p.input_filename);
    printf("\n======B Valori n e m======\nn:%d\nm:%d\n",n,m);
    double***X=readFile(n,m,p.input_filename);
    //PUNTO C
    double*Y=getArray(n,m,X);
    //PUNTO D
    processX(X,n,m,Y);
    //PUNTO E
    writeToFile(p.output_filename,X,n,m);


    return 0;
}