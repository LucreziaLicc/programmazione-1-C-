#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char input[255];
    char output[255];
}parametri;

parametri readInput(int argc, char*argv[]){
    if (argc!=3){
        fprintf(stderr, "Errore, il numero di parametri da inserire è 2.\n");
        exit(-1);
    }
parametri p;

strcpy(p.input, argv[1]);
strcpy(p.output, argv[2]);

int l1=strlen(p.input);
int l2=strlen(p.output);

if(l1>255||l2>255){
    fprintf(stderr,"errore, la lunghezza delle sringhe da input deve essere di massimo 255 caratteri.\n");
    exit(-1);
}
return p;

}


//legga una matrice A di puntatori float di dimensioni n x m dal file “input”
float***createMatrix(char filename[], int*n, int*m){//restituisce un puntatote alla matrice bidimensionale, prende come paarmetri puntatori alle dimensioni della matrice
    FILE*f=fopen(filename, "r");//apro il file  in modalità lettura
    if (f==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");//controllo degli errori
        exit(-1);
    }
    char buffer[1000];//stringa per leggere le righedel file
    char*end;//puntatore per il controllo di fine file

    *n=0;//definisco le varibili puntatori alle dimensioni della matrice
    *m=0;

    //CALCOLO LE DIMENSIONI DELLA MATRICE
    do {
        end=fgets(buffer, 1000,f);//legge una riga dal file f e la memorizza nell'array, 
        //la variabile end memorizza il valoro restituito da fgets per verificare se ci sono ancora righe da leggere 
        (*n)++;//contatore delle rigghe che viene incrementato dopo la lettura di un ariga
        if(*m==0){//qui verifici se il numero di righe è già stato contato
            char*tok;//definisco un puntatore alle sottostringhe separate da spazi
            char*tmp=buffer;//puntatore temporaneo che contiene la riga appena letta
            do{
                tok=strtok(tmp,"\n");//la funzione estrae la prima parola separata da uno spazio della riga letta tramite tmp e lo salva in took
                tmp=NULL;//reimposto il puntatore a null
                (*m)++;//incremento il conteggio delle parole 
            }while(tok);//il ciclo continua fin quando il puntatore *tok non sarà a null

        }

    }while(end);//il ciclo continua fin quando il puntatore *end non sarà null: fgets restituisce null

(*n)--;
(*m)--;

fseek(f,0, SEEK_SET);//porta il puntatore del file ll'inizio

    float***A=calloc(*n, sizeof(float**));//allocazione della matrice 3D di puntatori a float
    for (int i =0; i<*n;i++){//ciclo sulle righe che alloca lo spazio di una colonna per ogni elemento della riga 
        A[i]=calloc(*m, sizeof(float*));
        for (int j=0; j<*m;j++){
            A[i][j]=NULL;//inizialmente la matrice è vuota
        }
    }for(int i=0;i<*n;i++){//ciclo per popolare la matrice
        end=fgets(buffer,1000,f);//prendo le righe dal file
        char*tok;
        char*tmp=buffer;

        for (int j=0; j<*m; j++){
            tok=strtok(tmp," \n");
            tmp=NULL;
            if(tok){
                A[i][j]=malloc(sizeof(float));
                *(A[i][j])=strtof(tok,NULL);//conversione della stringa a float
            }
        }

    }

    fclose(f);
    return A;




}


// per ogni riga calcolare la media totale ed eliminare i valori della stessa riga che supèerano la media
//(far puntare a NULL i puntatori relativi ai valori identificati e liberare la relativa memoria);
void sparsify(float***A,int n, int m){
    for (int i =0; i<n; i++){//scorro le righe
        float mean =0;//mantiene la somma dei valori per calcolare la media
        int count=0;//mantiene ilconto per poter dividere e fare la media
        for (int j=0; j<m; j++){//scorro le colonne
            if(A[i][j]){//se il puntatore (valore) è non null
                mean+= *A[i][j];//aggiungo il valore puntato alla somma
                count++;//incremento il puntatore
            }
        }
        mean/= count;//calcolo la media della riga
        for(int j=0;j<m;j++){//scorro le colonne per eliminare i valori maggiori ispetto alla media
            if(A[i][j]&& *A[i][j]>mean){// se il valore è non null e MAGGIORE della media
                float*tmp=A[i][j];//salvo il valore in un puntatore temporaneo 
                A[i][j]=NULL;//impostoo a null il valore
                free(tmp);//libero la memoria del puntatore temporaneo
            }
        }

    }

}

//inserisca i valori puntati dai puntatori non nulli in A in un array di float; 
float*collect(float***A,int n, int m, int*num){
    *num=0; //questo puntatore conterrà il numero totale dei valori dell'array
    for(int i=0; i<n;i++){//scorro righe
        for(int j=0;j<m; j++){//scorro colonne
            if(A[i][j]){//se il valore è valido
                (*num)++;//incremento il puntatore
            }
        }
    }

float*out=calloc(*num, sizeof(float));//alloco dinamicamente l'array
int c=0;//contatore per inserire gli elementi nell'array
for(int i =0; i<n; i++){//scorro la matrice
    for(int j=0; j<m; j++){
        if(A[i][j]){
            out[c++]=*A[i][j];//se il valore è valido, lo inserisco nell'array
        }
    }
}
return out;
}

void writeToFile(char output[],float*array, int num){
    FILE*f=fopen(output, "w");
    for (int i=0;i<num;i++){
        fprintf(f,"%f\n",array[i]);
    }

}

int main(int argc, char*argv[]){
    parametri p=readInput(argc, argv);
    int m, n;
    float***A=createMatrix(p.input, &n, &m);
    int num;
    sparsify(A,n,m);
    float*array=collect(A,n,m,&num);
    writeToFile(p.output,array,num);


    

    return 0;
}
