#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

float DotProduct(int size, float *vec1, float *vec2){
   float result=0;
   #pragma omp parallel for
   for(int i = 0; i<size; i++){
      result += vec1[i]*vec2[i];
   }
   return result;
}  

void Nomalize(int numVec , int sizeVec, float **U){
    #pragma omp parallel for
    for(int i=0; i<numVec; i++){
        float A = sqrt(DotProduct(sizeVec,U[i],U[i]));
        for(int j=0; j<sizeVec; j++){
            U[i][j]=U[i][j]/A;
        }
    }
    return;
}

void PrintVec(int numVec , int sizeVec,float **V){
    for(int i=0; i<sizeVec; i++){
        for(int j=0; j<numVec; j++){
            printf("%f ",V[j][i]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void initalizeVec(int numVec,int sizeVec, float **V){
   for(int i = 0; i<numVec; i++){
      for(int j = 0; j<sizeVec; j++){
         V[i][j]=(float)(0+(rand()%10000));
      }
   }
}

int main(int argc, char **argv) {
   int numVec=0;
   if(argc<2){
       printf("Not enough arguments\n Expecting N\n");
       return 0;
   }else{
       numVec=atoi(argv[1]);
   }
   float **V = (float **)malloc(numVec*sizeof(float*));
   for(int i = 0; i<numVec;i++){
      V[i] = (float*)malloc(numVec*sizeof(float));
   }
   initalizeVec(numVec,numVec,V);
   /* Time */
   double time;
   /* Start Timer */
   initialize_timer ();
   start_timer();
   for(int i=1; i<numVec-1; i++){
      #pragma omp parallel for
      for(int j=i+1; j<numVec; j++){
         float temp= V[j][i]/V[i][i];
         for(int k = i+1;k<numVec;k++){
            V[j][k] -= temp*V[i][k];
         }
      }
   }
   Nomalize(numVec,numVec,V);
   
   /* stop timer */
   
   stop_timer();
   time=elapsed_time ();
    
   printf("%lf\n", time);
   if(0){
      PrintVec(numVec, numVec, V);
   }
   for(int i = 0; i<numVec;i++){
      free(V[i]);
   }
   free(V);
   return 0;
}


