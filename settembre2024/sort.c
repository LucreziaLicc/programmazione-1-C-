#include <stdio.h>

/*
void insertionSort(int*A,int size){//si lavora su porzioni di array
    for(int i=1; i<size; i++){//ciclo di scansione
       int elem= A[i];//elemento corrente
       int j=i-1;//cursore che parte dall'ultimo elemento ordinato(più grande per ora)

       while( j>=0 && A[j]>elem){//ciclo continua fino a fine array o fino a trovare un elemento più piccolo nell'array già ordinato
            A[j+1]=A[j];//shifto gli elementi in avanti 
            j=j-1; //torno indietro con il cursore
         }

       A[j+1]=elem;//inserisco l'elemento nella sua posizione

    }

}
*/

/*
void selectionSort(int*A, int size){//si cerca il minimo e si posiziona all'inizio
    for(int i=0; i<size-1; i++){
     int min=i;
     for(int j=i+1; j<size; j++){
        if(A[j]<A[min]){
            min=j;
        }
     }  
        int temp=A[min];
        A[min]=A[i];
        A[i]=temp;
     
    }

}
*/

/*
void bubbleSort(int*A, int size){
    for(int i=0; i<size-1;i++){
        int flag=0;

        for(int j=0; j<size-i-1; j++){
            if(A[j]>A[j+1]){
                int temp=A[j];
                A[j]=A[j+1];
                A[j+1]=temp;
                flag=1;

            }
        }
        if(flag==0){
            break;
        }
    }
    
}
*/


int main(){

int size=5;
int A[]={80,6,3,0,30};

//insertionSort(A,size);
//selectionSort(A,size);
bubbleSort(A,size);

for(int i=0;i<size;i++){
    printf("%d ",A[i]);
}


    return 0;
}