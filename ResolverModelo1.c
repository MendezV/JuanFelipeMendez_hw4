#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI 3.14159265

float *load_matrix(char *filename);
int main(int argc, char **argv){
  float *matrix_A;
    float *matrix_C;
  float *matrix_At;
  float *matrix_AtA;
  float *Lematrix;
  float *LematrixT;
  float *vector_B;
  float *vector_X;
  float *vector_Y;
  float *vector_AtB;
  int n_row, n_cols,n;
  int i, j,k,m,l;
  char c;
  double  producto,suma;

    FILE *in;
    char filename[100]="ai_coef.dat";
    in = fopen(filename,"w");
    
    if(!in){
        printf("problems opening the file %s\n", filename);
        exit(1);
    }

  n_row=884;
  n_cols=2;
  n=2;

  matrix_C = load_matrix(argv[1]);
  matrix_A = malloc(n_row * n * sizeof(float));
  matrix_At = malloc(n_row * n * sizeof(float));
  matrix_AtA = malloc(n*n*sizeof(float)); 
  Lematrix = malloc(n*n*sizeof(float)); 
  LematrixT = malloc(n*n*sizeof(float)); 
  vector_B = malloc(n_row * 1 * sizeof(float)); 
  vector_X = malloc(n*sizeof(float));
  vector_Y = malloc(n*sizeof(float));  
  vector_AtB = malloc(n*sizeof(float)); 

// genera la matriz de parametros de theta
    for(i=0;i<n_row;i++){
        for(j=0;j<n;j++){
            
            matrix_A[i*3 + j]=pow(cos(2*matrix_C[i*2 +0]* PI / 180.0),j);
         
            
            
        }
        
    }


//genera el vector b de posiciones finales
for(i=0;i<n_row;i++){
      vector_B[i]=matrix_C[i*2 +1];

 }

 
// conseguir At
   for(j=0;j<n;j++){
for(i=0;i<n_row;i++){
      matrix_At[j*n_row + i]=matrix_A[i*n + j];
   }
}

// conseguir AtA
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      matrix_AtA[i*n + j]=0.0;
        for(k=0;k<n_row;k++){
             matrix_AtA[i*n + j] =matrix_AtA[i*n + j]+matrix_At[i*n_row + k]*matrix_A[k*n + j];
}

    }
  }

// conseguir AtB
for(i=0;i<n;i++){
    for(j=0;j<1;j++){
      vector_AtB[i*1 + j]=0.0;
        for(k=0;k<n_row;k++){
             vector_AtB[i*1 + j] =vector_AtB[i*1 + j]+matrix_At[i*n_row + k]*vector_B[k*1 + j];
}
    }

  }

//Descomponer en cholesky AtA
for(i=0;i<n;i++){
    for(j=0;j<1;j++){
      Lematrix[i*n + j]=0.0;
}
    }

Lematrix[0*n +0]= sqrt(matrix_AtA[0*n + 0]);
 for(i=0;i<n;i++){
    Lematrix[i*n + 0]= matrix_AtA[i*n + 0]/Lematrix[0*n +0];
    }


 for(i=1;i<n;i++){
    for(j=1;j<i+1;j++){
      
      suma=0;
      for(k=0;k<j;k++){
        suma= suma +  Lematrix[i*n + k]* Lematrix[j*n + k];
      }
  
      if(j==i){
	Lematrix[i*n + j]=sqrt(matrix_AtA[i*n + j]-suma);
    }
      else{
	Lematrix[i*n + j]=(matrix_AtA[i*n + j]-suma)/Lematrix[j*n + j];
      }
 
   }
  }



//conseguir Lt
for(j=0;j<n;j++){
for(i=0;i<n;i++){
     LematrixT[j*n + i]=Lematrix[i*n + j];
   }
}


//resolver LY=AtB

for(i=0;i<n;i++)
{
  vector_Y[i]=0;
}

 vector_Y[0]=(vector_AtB[0])/Lematrix[(0)*n +(0)];
   
 for(i=1;i<n;i++){
   producto=0;
   for(j=0;j<n;j++){
     producto= producto + vector_Y[j]*Lematrix[(i)*n +j];
   }
   vector_Y[i]=(vector_AtB[i]-producto)/Lematrix[(i)*n +(i)];
}




// resolver LTX=Y
for(i=0;i<n;i++)
{
  vector_X[i]=0;
}

 vector_X[n-1]=(vector_Y[n-1])/LematrixT[(n-1)*n +(n-1)];
   
 for(i=1;i<n;i++){
   producto=0;
   for(j=0;j<n;j++){
     producto= producto + vector_X[j]*LematrixT[(n-1-i)*n +j];
   }
   vector_X[n-1-i]=(vector_Y[n-1-i]-producto)/LematrixT[(n-1-i)*n +(n-1-i)];
}

/*for(i=0;i<n;i++)
{
printf("%f \n", vector_X[i]);  
 
}
*/

    for(i=0;i<n;i++)
    {
        fprintf(in ,"%f \n", vector_X[i]);
        
    }
    
    
   

 


}


float *load_matrix(char *filename){
  float *matrix;
  FILE *in;
  int n_row, n_cols;
  int i;
  int j;

  n_row=884;
  n_cols=2;

  if(!(in=fopen(filename, "r"))){
    printf("Problem opening file %s\n", filename);
    exit(1);
  }


  matrix = malloc(n_row * n_cols * sizeof(float));

  for(i=0;i<n_row;i++){
    for(j=0;j<n_cols;j++){
      fscanf(in, "%f", &matrix[i*n_cols + j]);
    }
  }    
 
  return matrix;
}
