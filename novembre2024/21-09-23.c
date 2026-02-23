#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct{
    int min;
    int max;
    int n;
}parametri;

parametri decodeParameters(int argc, char*argv[]){
    if(argc!=4){
        fprintf(stderr,"errore, bisogna inserire tre interi come parametri\n");
        exit(-1);
    }

    if(atoi(argv[1])<7 ||atoi(argv[1])>12 ||atoi(argv[2])<7 ||atoi(argv[2])>12 ){
        fprintf(stderr,"errore, bisogna inserire i primi due parametri come due interi compresi fra 5 e 7, inclusi\n");
        exit(-1);        
    }
    if(atoi(argv[1])>atoi(argv[2])){
        fprintf(stderr,"errore, il primo parametro deve essere più piccolo del secondo\n");
        exit(-1);        
    }

    parametri p;

    p.min=atoi(argv[1]);
    p.max=atoi(argv[2]);

    if(atoi(argv[3])<=0){
        fprintf(stderr,"errore, il terzo parametro deve essereun intero positivo, diverso da 0\n");
        exit(-1);          
    }

    p.n=atoi(argv[3]);

    printf("\nPunto A - Parametri inseriti: min=%d, max=%d, n=%d\n",p.min,p.max,p.n);

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


char*generateString(int min, int max){
    char*string=malloc(sizeof(char)*(max+1));
    if(string==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }


    int range=max-min+1;
    int x=min+get_random()%range;

    const char vowels[]="aeiou";
    int len=strlen(vowels);

    for(int i=0; i<x; i++){

        string[i]=vowels[get_random()%len];
    }

    string[x]='\0';

    return string;

}

void printArray(char**A,int n){
    for(int i=0; i<n; i++){
        printf("%s\n",A[i]);
    }    
}

char**makeArray(int n, int min, int max){
    char**A=malloc(sizeof(char*)*n);
    if(A==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }   

    for(int i=0; i<n; i++){
        A[i]=generateString(min, max);
    }
    printf("\nPunto B:\n");
    printArray(A,n);

    return A;
}
//PUNTO C

void sort(char**A,int n){
    for (int i=1; i<n; i++){
        char*key=A[i];
        int j=i-1;
        while(j<=0 && strcmp(A[j],key)>0){
            A[j+1]=A[j];
            j=j-1;
        }
        A[j+1]=key;
    }
}

char* concatString(char**A, int n){
    int len=0;

    for(int i=0; i<n; i++){
        len+=strlen(A[i]);
    }
    char*newStr=malloc(sizeof(char)*(len+1));

    strcpy(newStr,A[0]);
    for(int j=1; j<n; j++ ){
        strcat(newStr,A[j]);
    }
    
    printf("\nPunto C - Stringa concatenata:\n");
        for (int i = 0; i < len; i += 50) {  // Segmenta l'output in blocchi di 50 caratteri
        printf("%.50s\n", &newStr[i]);
    }


    return newStr;
}
//PUNTO D




int main(int argc, char*argv[]){
    parametri p=decodeParameters(argc,argv);
    //PUNTO B
    char**A=makeArray(p.n,p.min,p.max);
    //PUNTO C
    sort(A,p.n);
    char*B=concatString(A,p.n);
    //PUNTO D

    return 0;
}