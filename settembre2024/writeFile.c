#include<stdio.h>

int main (){

FILE*fptr;

fptr=fopen("text.txt","w");
char *nome="dio cane";

if (fptr!=NULL){
    printf("file open successful");

    fprintf(fptr,"culone io\nodio\nfedez");
}else{
    printf("file open unsuccessful");
}

    fclose(fptr);
    return 0;


}



Node*readFile(char*name){
    Node**head=malloc(sizeof(Node*));//alloco un puntatore a puntatore per la testa della lista
    *head=NULL;//inizialmente è vuota (NULL)
    FILE*f=fopen(name,"r");//apro il file in modalità lettura
    if(f==NULL){
        perror("errore nell'apertura del file.\n");//gestione errori
        return NULL;
    }
char s[1000];//righe da analizzare

bool done=false;//una variabile booleana che serve per controllare iil ciclo whilw chw continua finchè ci sono righe da leggere

while(!done){
    char*out=fgets(s,1000,f);//fgets lege una riga dal file detto, di massimo 1000 caratteri
    if(out != NULL){
        char*tok=strtok(s," \n");//la funzione strtok divide la riga in 'tken', parole separate da spazi
        char*firstTok=tok;//salva la prima parola della riga (il controllo)
        int count=0;//contatore delle occorrenze della parola

        do{
            if(strcmp(firstTok,tok)==0){//compara la prima parola della riga con le restanti, se uguali aumenta il contatore
                count++;
            }
        }while(tok==(strtok(NULL," \n")));
        riga r;//creazione di una riga
        r.count=count;//inserisco il numro di ricorrenze trovato
        strcpy(r.word, firstTok);//la funzione strcpy copia il contenuto di una stringa sorgente in una destinazione
                                 //quindi copia la prima parola della riga analizzata nella struct riga creata
        inserttail(head,r);//inserisco la riga nella lista

    }else{
        done=true;
    }

}
return *head;//restituiusce un puntatore alla testa della lista

}