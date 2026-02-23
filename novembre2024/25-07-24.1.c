#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
    char*input_filename;
}parametri;

parametri decodeParameters(int argc, char*argv[]){
    if(argc!=2){
        fprintf(stderr,"errore, bisogna inseirire un nome di file con estensione '.csv'\n");
        exit(-1);
    }
        int len=strlen(argv[1]);
        parametri p;

        if(len<4 || strcmp(argv[1]+len-4, ".csv")!=0){
            fprintf(stderr,"errore, bisogna inseirire un nome di file con estensione '.csv'\n");
            exit(-1);
        }

        p.input_filename=malloc(sizeof(char)*(len+1));
        strcpy(p.input_filename,argv[1]);


        printf("\nPUNTO A: input_filename:%s\n",p.input_filename);

        return p;
    



}
//PUNTO B

/*
void bubbleSort(int*A, int size){
    for(int i=0; i<size-1; i++){
        int flag=0;
        for(int j=0; j<size-i-1; i++){
            if (A[j]>A[j+1]){
                int temp=A[j];
                A[j]=A[j+1];
                A[j+1]=temp;
            }
            flag =1;
        }
        if(flag==0){
            break;
        }
    }
}
*/
void readHeader(int*m, int*n, char*filename){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file\n");
        exit(-1);
    }

    if(fscanf(f,"%d, %d",n,m)!=2){
        fprintf(stderr,"errore nella lettura del file\n");
        exit(-1);
    }
    printf("\n======B Valori n e m======\nn=%d m=%d\n", *n, *m);
    fclose(f);

}


void printMatrix(short***X,int n, int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(X[i][j]==NULL){
                printf("%2s ","*");
            }else{
            printf("%2hd ",*X[i][j]);
            }
        }
        printf("\n");
    }      
}

short***readFile(char*filename, int n, int m){
    FILE*f=fopen(filename,"r");
    if(f==NULL){
        fprintf(stderr,"errore nell'apertura del file\n");
        exit(-1);
    }

    short***X=malloc(sizeof(short**)*n);

    char buffer[100];
    fgets(buffer,sizeof(buffer),f);

    for(int i=0; i<n; i++){
        X[i]=malloc(sizeof(short*)*m);
        for(int j=0; j<m; j++){
            X[i][j]=malloc(sizeof(short));
            fscanf(f,"%hd,",X[i][j]);
        }
    }    
    printMatrix(X,n,m);

    fclose(f);
    return X;
}
//PUNTO C

short getmax(short**X, int m){
    short max=0;
    for(int i=0; i<m; i++){
        if(*X[i]>max){
            max=*X[i];
        }
    }
    return max;
}
void printArray(short*Y, int n){
        for(int j=0; j<n; j++){
        printf("%hd ",Y[j]);
    }

}


void bubbleSort(short*Y, int n){
    for(int i=0; i<n-1; i++){
        int flag=0;
        for(int j=0; j<n-i-1; j++){
            if(Y[j]<Y[j+1]){
                short temp=Y[j];
                Y[j]=Y[j+1];
                Y[j+1]=temp;
                flag=1;
            }

        }       
            if(flag==0){
                break;
            }
    }

}


short*getArray(short***X,int n, int m){
    short*Y=malloc(sizeof(short)*n);
    for(int i=0; i<n; i++){
        Y[i]=getmax(X[i],m);
    }


    printf("\n======C Array Y======\n");
    printArray(Y,n);
        bubbleSort(Y,n);
    printf("\n======C Array Y ordinato======\n");
    printArray(Y,n);

    return Y;


}

//PUNTO D

void processX(short***X, short*Y, int n, int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            short x=(Y[i]/2)+1;
            if(*X[i][j]>x){
                free(X[i][j]);
                X[i][j]=NULL;
            }
        }
    }
    printMatrix(X,n,m);
}

//PUNTO E

void printfErr(short***X, int n, int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(X[i][j]==NULL){
                fprintf(stderr,"%2s ","-");
            }else{
            fprintf(stderr,"%2hd ",*X[i][j]);
            }
        }
        fprintf(stderr,"\n");
    }  
    
}

int main(int argc, char*argv[]){
    parametri p=decodeParameters(argc, argv);
    //PUNTO B
    int m;
    int n;
    readHeader(&m, &n, p.input_filename);
    printf("\n======B Matrice X======\n");
    short***X=readFile(p.input_filename, n, m);
    //PUNTO C
    short*Y=getArray(X,n,m);
    //PUNTO D
    printf("\n======D Matrice X modificata======\n");
    processX(X,Y,n,m);
    //PUNTO E
    printf("\n======D Matrice X stderr======\n");    
    printfErr(X,n,m);







    return 0;
}