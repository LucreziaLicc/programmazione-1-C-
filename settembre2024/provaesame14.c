#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char*input_filename;
    char*output_filename;
}parametri;

//PUNTO A
parametri decodeParameters(int argc, char*argv[]){
    parametri p;
    if (argc!= 3){
        fprintf(stderr, "Errore, i parametri da inserire sono 2: nome del file input, nome del file output");
        exit(-1);
    }

    int len1=strlen(argv[1]);
    int len2=strlen(argv[2]);
    p.input_filename=malloc(sizeof(char)*len1+1);
    p.output_filename=malloc(sizeof(char)*len2+1);

    strcpy(p.input_filename,argv[1]);
    strcpy(p.output_filename,argv[2]);

    if(strcmp(p.input_filename+len1-4,".txt")!=0 || strcmp(p.output_filename+len2-4,".txt")!=0){
        fprintf(stderr, "Errore, i parametri da inserire sono due nomi di file con estensione '.txt'");
        exit(-1);        

    }

    printf("======A Stampa Parametri======\ninput_filename = %s\noutput_filename = %s\n",p.input_filename,p.output_filename);
return p;
}

//PUNTO B
void readHeader(char*inputname, int*n, int*m){
    FILE*f=fopen(inputname, "r");
        if (f== NULL){
        fprintf(stderr, "Errore nell'apertura del file.\n");
        exit(-1);
    }
    if(fscanf(f,"%d %d",n,m)!=2){
        fprintf(stderr, "Errore nella lettura del file.\n");
        exit(-1);

    }
    fclose(f);

    printf("======B Valori n e m======\nn=%d\nm=%d\n",*n,*m);
}


// funzione che legge il contenuto delle restanti righe del file e restituisce la matrice
//X come definito nel punto B del testo;
double**readFile(int *n, int* m, char*inputname){
   readHeader(inputname,n,m);

   double**X=calloc(*n,sizeof(double*));//alloco le righe
       if (X == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        exit(-1);
    }

   for(int i=0; i<*n; i++){//alloco le colonne 
    X[i]=calloc(*m,sizeof(double)); }  
      if (X == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        exit(-1);
    }

   FILE*f=fopen(inputname,"r");
           if (f== NULL){
        fprintf(stderr, "Errore nell'apertura del file.\n");
        exit(-1);
    }
fscanf(f,"%*d %*d");//salto la prima riga, con le dimensioni della matrice

for(int x=0; x<*n;x++){//scorro le righe
    for(int j=0; j<*m; j++){//riempio le colonne
        if(fscanf(f,"%lf",&X[x][j])!=1){
        fprintf(stderr, "Errore nella lettura del file.\n");
         fclose(f);
        exit(-1);
    }
    }
}
    fclose(f);
printf("======B Matrice X======\n");
    for(int x=0; x<*n;x++){//scorro le righe
    for(int j=0; j<*m; j++){//riempio le colonne
        printf("%.2lf ",X[x][j]);
    }
    printf("\n");
    }


    return X;

}

//PUNTO C

void Sort(double*Y, int n){
    for(int pass=0; pass<n-1; pass++){
        int min=pass;
        for(int i=pass; i<Y[min]; i++){
            if(Y[i]<Y[min])
                min=i;
            
            double tmp=Y[pass];
            Y[pass]=Y[min];
            Y[min]=tmp;
        }
    }

}


double*getArray(double**X,int n,int m ){
    double*Y=calloc(n,sizeof(double));

    for(int i=0; i<n; i++){
        Y[i]=0;
        int num=0;
        for(int j=0; j<m;j++){
             if (X[i][j] != 0) {  // Se l'elemento è diverso da zero
                Y[i] += X[i][j];  // Somma il valore alla somma corrente
                num++;  // Incrementa il numero di elementi non nulli
            }
        }
        if(num>0){
            Y[i]/=num;//calcolo la media
        }
            
    }

        printf("======C Array Y======:\n");

        for(int i=0; i<n; i++){
            printf("%lf\n",Y[i]);
        }

    Sort(Y,n);

        printf("======C Array Y Ordinato======\n");

        for(int i=0; i<n; i++){
            printf("%lf\n",Y[i]);
        }



    return Y;
}

//PUNTO D

int main(int argc, char*argv[]){
    //punto a
    parametri p= decodeParameters(argc,argv);
    //punto b
    int n;
    int m;
   double**X=readFile(&n,&m,p.input_filename);
   //punto c
   double*Y= getArray(x,n,m);
   //punto d


    return 0;
}