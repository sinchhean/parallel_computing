#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUMBER_OFN 9
#define TIMES 10
#define MAT(p,j,i) p[(j)*N +(i)]

void mat_gen(float *, float *, float *, double *, double *, double *, int);
void mat_mult_float(float *, float *, float *, int N, int c);
void mat_mult_double(double *, double *, double *, int N, int c);
double e_time(void);

void main(int argc, char* argv[]){
int N = [8,16,32,64,128,256,512,1024,2048];
int nt;
int i,j,k;
float *Af, *Bf, *Cf;
double *Ad, *Bd, *Cd;
double st, en;
double avg_etime_float = avg_etime_double = 0;
srand(time(NULL)); //seed for the random number
for(i = 0; i < NUMBER_OFN; i++){ 
  for(j = 0; j < TIMES; j++){
    Af = (float *)malloc(sizeof(float)*N[nt]*N[nt]);
    Bf = (float *)malloc(sizeof(float)*N[nt]*N[nt]);
    Cf = (float *)malloc(sizeof(float)*N[nt]*N[nt]);
    Ad = (double *)malloc(sizeof(double)*N[nt]*N[nt]);
    Bd = (double *)malloc(sizeof(double)*N[nt]*N[nt]);
    Cd = (double *)malloc(sizeof(double)*N[nt]*N[nt]);

    mat_gen(Af,Bf,Cf,Ad,Bd,Cd,N[nt]);

    st = e_time();
    mat_mult_float(Af,Bf,Cf,N[nt],1);
    en = e_time();
    

    st = e_time();
    mat_mult_double(Ad,Bd,Cd,N[nt],1);
    en = e_time();
 
      

    free(Af);
    free(Bf);
    free(Cf);
    free(Ad);
    free(Bd);
    free(Cd);
  }
  for(j = 0; j < TIMES; j++){
    
  }
}



}

void mat_gen(float *xf, float *yf, float *zf, double *xd, double *yd, double *zd, int N){
  int i,j;
  for(j = 0; j < N; j ++){
    for(i = 0; i < N; i++){
      MAT(xf,j,i) = (float)rand()/(float)(RAND_MAX + 1);
      MAT(yf,j,i) = (float)rand()/(float)(RAND_MAX + 1);
      MAT(xd,j,i) = (double)MAT(xf,j,i);
      MAT(yd,j,i) = (double)MAT(yf,j,i);
      MAT(zf,j,i) = 0.0;
      MAT(zd,j,i) = 0.0;
    }
  }  
}

void mat_mult_float(float *xf, float *yf, float *zf, int N, int c){
  int i,j,k;
  switch(c)
  {
    case 1: //ijk
      for(i = 0; j < N; j++){
        for(j = 0; i < N; i++){
          for(k = 0; k < N; k++){
            MAT(zf,j,i) += MAT(xf,j,k) * MAT(yf,k,i);
          }
        }
      }
      break;
    case 2: //jik
      for(j = 0; j < N; j++){
        for(i = 0; i < N; i++){
          for(k = 0; k < N; k++){
            MAT(zf,j,i) += MAT(xf,j,k) * MAT(yf,k,i);
          }
        }
      }
      break;
    case 3: //kij
      for(k = 0; j < N; j++){
        for(i = 0; i < N; i++){
          for(j = 0; k < N; k++){
            MAT(zf,j,i) += MAT(xf,j,k) * MAT(yf,k,i);
          }
        }
      }
      break;
  }
}
void mat_mult_double(double *xf, double *yf, double *zf, int N, int c){
  int i,j,k;
  switch(c)
  {
    case 1: //ijk
      for(i = 0; j < N; j++){
        for(j = 0; i < N; i++){
          for(k = 0; k < N; k++){
            MAT(zf,j,i) += MAT(xf,j,k) * MAT(yf,k,i);
          }
        }
      }
      break;
    case 2: //jik
      for(j = 0; j < N; j++){
        for(i = 0; i < N; i++){
          for(k = 0; k < N; k++){
            MAT(zf,j,i) += MAT(xf,j,k) * MAT(yf,k,i);
          }
        }
      }
      break;
    case 3: //kij
      for(k = 0; j < N; j++){
        for(i = 0; i < N; i++){
          for(j = 0; k < N; k++){
            MAT(zf,j,i) += MAT(xf,j,k) * MAT(yf,k,i);
          }
        }
      }
      break;
  }
}
double e_time(void){
  static struct timeval now;
  gettimeofday(&now, NULL);
  return (double)(now.tv_sec + now.tv_usec/1000000.0);
}
