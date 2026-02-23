#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
    char*input_filename;
}parametri;

parametri decodeParameters(int argc,char*argv[]){
    if(argc!=2){
        fprintf(stderr,"errore, bisogna inserire un parametro stringa, il nome di un file input.\n");
        exit(-1);
    }

    parametri p;

   int len=strlen(argv[1]);
   if(len<4 ||strcmp( argv[1]+len-4,".csv")!=0){
        fprintf(stderr,"errore, il parametro stringa deve abvere estensione '.csv'.\n");
        exit(-1);   
   }

   p.input_filename=malloc(sizeof(char)*(len+1));
   strcpy(p.input_filename,argv[1]);

   printf("\nPUNTO A:\ninput_filename:%s\n",p.input_filename);
   return p;
}

//PUNTO B
FILE*openFile(char*filename){
        FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file.\n");
    }
    return f;
}

void readHeader(char*filename,int*n, int*m){
    FILE*f=openFile(filename);
    if(fscanf(f,"%d,%d",n,m)!=2){
        fprintf(stderr,"errore nella lettura del file.\n");
        exit(-1);
    }

    printf("\nPUNTO B:\nLa prima riga del file è:%d %d\n",*n,*m);


}
void printMatrix(short***X,int n ,int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf("%2hd ",*X[i][j]);
        }
        printf("\n");
    }
}

short***readFile(char*filename,int n,int m){
    FILE*f=openFile(filename);

    char buffer[100];
    if (fgets(buffer, sizeof(buffer), f) == NULL) {//salto la prima riga
        fprintf(stderr, "Errore nella lettura della prima riga.\n");
        fclose(f);
        exit(-1);
    }

    short***X=malloc(sizeof(short**)*n);

    for (int i = 0; i < n; i++) {
        X[i] = (short**) malloc(m * sizeof(short*));
        for (int j = 0; j < m; j++) {
            X[i][j] = malloc(sizeof(short));
            fscanf(f, "%hu,", X[i][j]);
        }
    }
    return X;

}

//PUNTO C

short getMax(short**X,int m){
    short max=*X[0];
    for(int i=1; i<m; i++){
        if(*X[i]>max){
            max=*X[i];
        
    }
}
    return max;
}


void printArray(short*Y,int n){
     for (int j=0; j<n; j++){
        printf("%hd ", Y[j]);
    }
}

void sort(short*Y,int n){
    for(int i=0; i<n-1; i++){
        short flag=0;
        for(int j=0; j<n-i-1; j++){
            if(Y[j]<Y[j+1]){
                short temp=Y[j];
                Y[j]=Y[j+1];
                Y[j+1]=temp;
                flag=1;

            }

        }
        if (flag==0){
        break;
        }
    }
}

short*getArray(short***X,int n,int m){
    short*Y=malloc(sizeof(short)*n);

    for(int i=0; i<n; i++){
        Y[i]=getMax(X[i],m);
    }
    printf("\n\nArray Y:\n");
    printArray(Y,n);

    sort(Y,n);
    printf("\n\nArray Y ordinato:\n");    
    printArray(Y,n);

    return Y;

}

//PUNTO D
void processX(short***X,int n, int m,short*Y){
    for (int i=0; i<n;i++){
        for(int j=0; j<m; j++){
            if(*X[i][j]>Y[i]/2+1){
                free(X[i][j]);
                X[i][j]=NULL;
            }
        }
    }

    printf("\n\nPUNTO D:\narray X modificato:\n");

        for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(X[i][j]==NULL){
                printf(" * ");
            }else{
            printf("%2hd ",*X[i][j]);
            }
        }
        printf("\n");
    }
    


}

//PUNTO E
void printStderr(short***X,int n,int m){
    fprintf(stderr,"\nmatrice su standard error:\n");
        for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(X[i][j]==NULL){
                fprintf(stderr," - ");
            }else{
            fprintf(stderr,"%2hd ",*X[i][j]);
            }
        }
        fprintf(stderr,"\n");
    }
}

int main(int argc,char*argv[]){
    parametri p=decodeParameters(argc,argv);
    //PUNTO B
    int n,m;
    readHeader(p.input_filename,&n,&m);
    short***X=readFile(p.input_filename,n,m);
    printf("\nmatrice X:\n");
    printMatrix(X,n,m);
    //PUNTO C
    short*Y=getArray(X,n,m);
    //PUNTO D
    processX(X,n,m,Y);
    //PUNTO E
    printStderr(X,n,m);



    return 0;

}