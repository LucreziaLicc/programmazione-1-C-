#include <stdio.h>
#include <stdlib.h>
#include<string.h>


int main(){

    FILE*fptr;
    fptr = fopen ("test.txt", "r");//collego il main con il file già esistente
    
    char text[1000];
    
    if (fptr != NULL){

       while (fgets(text,1000,fptr)){//con il while riesco a stampare tutte le righe di testo
         printf ("%s",text);

       }
       

    }else{
        printf("file open unsuccessful");
        }

fclose(fptr);
return 0;


}