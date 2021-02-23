#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

void vecCp(int size,float *vec1, float *vec2){
    #pragma omp parallel for
    for(int i=0;i<size;i++){
        vec1[i]=vec2[i];
    }
    return;
}

void vecSub(int size, float *vec1, float *vec2){
    #pragma omp parallel for
    for(int i=0; i<size; i++){
      vec1[i]-=vec2[i];
   }
   return;
}

void vecmult(int size, float *retVec, float a, float *vec){
    #pragma omp parallel for
    for(int i=0; i<size; i++){
      retVec[i]=vec[i]*a;
   }
   return;
}  

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
   int sizeVec=0;
   if(argc<3){
       printf("Not enough arguments\n Expecting Number of Vectors, Size of Vectors\n");
       return 0;
   }else{
       numVec=atoi(argv[1]);
       sizeVec=atoi(argv[2]);
   }
   float **V = (float **)malloc(numVec*sizeof(float*));
   float **U = (float **)malloc(numVec*sizeof(float*));
   for(int i = 0; i<numVec;i++){
      V[i] = (float*)malloc(sizeVec*sizeof(float));
      U[i] = (float*)malloc(sizeVec*sizeof(float));
   }
   initalizeVec(numVec,sizeVec,V);
   /* Time */
   double time;
   /* Start Timer */
   
   initialize_timer ();
   start_timer();
   vecCp(sizeVec,U[0],V[0]);
   for(int i=1; i<numVec; i++){
      vecCp(sizeVec,U[i],V[i]);
      #pragma omp parallel for
      for(int j=0; j<i; j++){
         float temp[sizeVec];
         vecmult(sizeVec,temp,DotProduct(sizeVec,U[j],V[i])/DotProduct(sizeVec,U[j],U[j]),U[j]); 
         vecSub(sizeVec,U[i],temp);
      }
   }
   Nomalize(numVec,sizeVec,U);
   
   /* stop timer */
   
   stop_timer();
   time=elapsed_time ();
    
   printf("%lf\n", time);
   if(0){
      PrintVec(numVec, sizeVec, V);
      PrintVec(numVec, sizeVec, U);
   }
   for(int i = 0; i<numVec;i++){
      free(V[i]);
      free(U[i]);
   }
   free(V);
   free(U);
   return 0;
}


