#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>

typedef struct{
    int min;
    int max;
    int n;
}parametri;
//PUNTO A 
parametri decodeParameters(int argc,char*argv[]){
    if(argc!=4){
        fprintf(stderr,"Errore, i parametri da inserire sono tre interi.\n");
        exit(-1);
    }

    parametri p;

    if(atoi(argv[1])<7 ||atoi(argv[1])>12 || atoi(argv[2])<7 ||atoi(argv[2])>12 || atoi(argv[1]) >atoi(argv[2])){
        fprintf(stderr,"Errore, i primi due parametri da inserire sono due interi fra 7 e 12, inclusi. Il primo inserito deve essere minore del secondo\n");
        exit(-1);        
    }

    if(atoi(argv[3])<=0){
        fprintf(stderr,"Errore, il terzo parametro da inserire è un intero positivo e diverso da zero\n");
        exit(-1);             

    }

    p.min=atoi(argv[1]);
    p.max=atoi(argv[2]);
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



char* generateString(int min, int max){
    char*newStr=malloc(sizeof(char)*(max+1));
    
    int range=max-min+1;
    int x=min+(get_random()% range);

    const char vowels[]= "aeiou";
    int numvowels=strlen(vowels);

    for(int i =0; i<x; i++){
        newStr[i]=vowels[get_random()% numvowels];
    }

    newStr[x]='\0';

    return newStr;
}


void printArray(char**A, int n){
    for(int i=0; i<n; i++){
        printf("%s\n",A[i]);
    }
}


char** makeArray(int min, int max, int n){
    char**A=malloc(sizeof(char*)*n);
    if(A==NULL){
       fprintf(stderr,"Errore nell'allocazione della memoria.\n");
       exit(-1);
    }

    for (int i=0; i<n; i++){
        A[i]=generateString(min, max);
    }
    printf("\nPunto B:\n");
    printArray(A,n);
    return A;
}

//PUNTO C
void sortArray(char**A, int n){

    for (int i=1; i<n; i++){
        char* key=A[i];
        int j=i-1;

        while(j>=0 && strcmp(A[j],key )>0){
            A[j+1]=A[j];
            j=j-1;
        }
        A[j+1]=key;
    }
}

char* concatString(char**A, int n){
    sortArray(A,n);

    int len=0;
    for (int j=0; j< n; j++){
        len+=strlen(A[j]);//calcolo la dimensione da allocare
    }

        char*B=malloc(sizeof(char)*(len+1));

        strcpy(B,A[0]);//copio la prima stringa

        for(int y=1; y<n; y++){
            strcat(B,A[y]);
        }
//non serve inserire il carattere di terminazione perchè strcat lo inserisce già in automatico
        printf("\nPunto C - Stringa concatenata:\n");
    for (int i = 0; i < len; i += 50) {  // Segmenta l'output in blocchi di 50 caratteri
        printf("%.50s\n", &B[i]);
    }

return B;
}

//PUNTO D

void replaceCharacters(char*B){
    int i=0; 
    char last=' ';

    while (B[i])
    {
        if(B[i]=='u' && last=='e'){
            B[i]='*';
        } 
         last=B[i];
         i++ ;
    }
    printf("\npunto D, stringa modificata:\n%s",B);
}


int main(int argc,char*argv[]){
    srand(time(NULL));
    //PUNTO A
    parametri p=decodeParameters(argc, argv);
    //PUNTO B 
    char**A=makeArray(p.min,p.max,p.n);
    //PUNTO C
    char*B=concatString(A,p.n);
    //PUNTO D
    replaceCharacters(B);


    free(A);
    free(B);
    return 0;
}