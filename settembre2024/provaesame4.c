#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>


//A chieda all'utente di inserire un intero “n” (si assuma n<256), una stringa "s1", una stringa “s2”, 
//e un carattere "c" da tastiera. Si verifichi che entrambe le stringhe siano di lunghezza “n”. In caso contrario, 
//si stampi un errore su standard error e si termini il programma con un opportuno codice di terminazione;
void readInput(int *n, char*s1, char*s2, char*c){
   
    printf("Inserire un intero 'n'.\n");
    scanf("%d",n);
    printf("Inserire una stringa di lunghezza %d.\n",*n);
    scanf("%s",s1);
    printf("Inserire una seconda  stringa di lunghezza uguale a n.\n");
    scanf("%s",s2);
        getchar();
    printf("Inserire un carattere 'c'.\n");
    scanf("%c",c);


if (*n >=256){
     fprintf(stderr, "Errore, l' intero da inserire deve essere <256.\n");
        exit(-1);
}
int lung1=strlen(s1);
int lung2=strlen(s2);

if(lung1!=*n || lung2 != *n){
    fprintf(stderr, "Errore, le stringhe da inserire devono essere  della stessa lunghezza dell'intero inserito.\n");
        exit(-1);

}


}

//replaceChar: funzione che riceve come input le stringhe "s1", “s2” e il carattere "c" 
//e restituisce la stringa con le occorrenze di "c" in “s1” sostituite dai corrispondenti valori in “s2. 
//Ad esempio, se s1=”abcacba”, s2=”fhsuika” e c=’a’, allora il risultato sarà “fbcucba”;
char*replaceChar(char*s1, char*s2, char c){
    

    int L1=strlen(s1);
    int L2=strlen(s2);

    char*s3= malloc((L1+1)*sizeof(char));//alloco la memoria di grandezza char moltiplicato per la lunghezza della stringa + 1 (carattere '\0')
    if(s3==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }


    for (int i=0; i<L1; i++){//ciclo che scorre le due stringhe allo stesso indice
            if (s1[i]== c){
                s3[i]=s2[i];    
        }else{
        s3[i]=s1[i];//Se s1[i] non corrisponde a c, il carattere viene copiato direttamente in s3 senza sostituzioni.
        }
    }
    s3[L1]='\0';
    return s3;
}

//invertString: funzione che costruisce una stringa a partire da una stringa in input invertendono i caratteri;
char*invertString(char*s2){
    int L=strlen(s2);
     char*s4= calloc((L+1),sizeof(char));//alloco la memoria di grandezza char moltiplicato per la lunghezza della stringa + 1 (carattere '\0')
    if(s4==NULL){
        fprintf(stderr,"errore nell'allocazione della memoria.\n");
        exit(-1);
    }

    for (int i=0; i<L; i++){
        s4[L-i-1]=s2[i];//tramite questo calcolo, il carattere copiato verrà posizionato nella nuova stringa in ordine inverso

    }
    s4[L]=0;
    return s4;

}

void sort(char*s){//sort: funzione che permetta di ordinare una stringa in ordine lessicografico;
    int L=strlen(s);

    for (int pass=0; pass<L; pass++){
        for(int i=0; i<L-1-pass; i++){
        if(s[i]>s[i+1]){
            char c=s[i];//variabile per mantenere il dato
            s[i]=s[i+1];
            s[i+1]=c;
            }
            
        }
    }
}
//D concateni le stringhe “s3” e “s4” in una nuova stringa “s5” e la ordini in ordine lessicografico ascendente
//usando un algoritmo di ordinamento a scelta;
char*nuovastringa(char*s3, char*s4){
    int L1=strlen(s3);
    int L2=strlen(s4);

    char*s5= malloc(sizeof(char)*(L1+L2+1));//crea la stringa di max 255 caratteri

    for (int i=0; i<L1; i++){//copio s3 in s5
        s5[i]=s3[i];
    }

 for (int j=0; j<L2; j++){//copio s3 in s5
        s5[L1+j]=s4[j];//inserisco i caratteri a fine stringa s3
    }
s5[L1+L2]='\0';//inserisco il carattere di fine stringa

int L3=strlen(s5);
    for(int m=0; m<L3; m++){
        if (((int)s5[m])%2==1){
            s5[m]='*';
        }
    }
    sort(s5);
return s5;
}
void printresult(char*s5){
    printf("%s.\n",s5);

}
int main(int argc, char *argv[]) {
    char s1[255];
    char s2[255];
    int n;
    char c;
    readInput(&n,s1,s2,&c);
    char*s3=replaceChar(s1,s2,c);
    char*s4=invertString(s2);
    char*s5=nuovastringa(s3,s4);
    printresult(s5);



    return 0;
}
