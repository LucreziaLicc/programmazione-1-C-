#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
    char*alfabeto;
    int n;
    char*output;
}parametri;

//PUNTO A
parametri decodeParameters (int argc, char*argv[]){
    if (argc!=4){
        fprintf(stderr, "erroe, il numero di parametri da inserire è 3.\n");
        exit(-1);
    }
parametri p;

int len=strlen(argv[1]);

if(len<5 || len >15){
    fprintf(stderr, "erroe, la stringa da inserire deve essere di lunghezza compresa fra 5 e 15 caratteri .\n");
    exit(-1);    
}

p.alfabeto=malloc(sizeof(char)*(len+1));

strcpy(p.alfabeto,argv[1]);

if(atoi(argv[2])<5 ||atoi(argv[2])<5 ){
     fprintf(stderr, "erroe, l'intero da inserire deve essere compreso fra 5 e 20.\n");
    exit(-1);      
}

p.n=atoi(argv[2]);

int len2=strlen(argv[3]);
p.output=malloc(sizeof(char)*(len2+1));
strcpy(p.output,argv[3]);

printf("i parametri sono:\nalfabeto:%s\nn:%d\noutput:%s\n",p.alfabeto,p.n,p.output);

return p;

}
//PUNTO B
int* readInput(int n, int*x){
    int conto=0;
printf("inserire %d interi.\n",n);
    for(int i=0; i<n; i++){
        scanf("%d",&(*x));
    }
}

int main(int argc, char*argv[]){
    //PUNTO A
    parametri p=decodeParameters(argc,argv);
    //PUNTO B

    return 0;
}

