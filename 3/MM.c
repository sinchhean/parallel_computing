#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define TIMES 3
#define MAT(p,j,i) p[(j)*N +(i)]

void mat_gen(float *, float *, float *, double *, double *, double *, int);
void mat_mult_float(float *, float *, float *, int N, int c);
void mat_mult_double(double *, double *, double *, int N, int c);
double e_time(void);

void main(int argc, char* argv[]){
//int N = [8,16,32,64,128,256,512,1024,2048];
int n_N = argc-1;
int i,j,k,m;
int M[n_N];
int N;
float *Af, *Bf, *Cf;
double *Ad, *Bd, *Cd;
double st, en;
double avg_etime_float = 0;
double avg_etime_double = 0;
srand(time(NULL)); //seed for the random number

for(i = 0; i < n_N; i++){
  M[i] = atoi(argv[i+1]);
}

for(i = 0; i < n_N; i++){ 
  for(j = 0; j < TIMES; j++){
    Af = (float *)malloc(sizeof(float)*M[i]*M[i]);
    Bf = (float *)malloc(sizeof(float)*M[i]*M[i]);
    Cf = (float *)malloc(sizeof(float)*M[i]*M[i]);
    Ad = (double *)malloc(sizeof(double)*M[i]*M[i]);
    Bd = (double *)malloc(sizeof(double)*M[i]*M[i]);
    Cd = (double *)malloc(sizeof(double)*M[i]*M[i]);
    
    N = M[i];

    mat_gen(Af,Bf,Cf,Ad,Bd,Cd,M[i]);

    st = e_time();
    mat_mult_float(Af,Bf,Cf,N,3);
    en = e_time();
    avg_etime_float += en-st;

    st = e_time();
    mat_mult_double(Ad,Bd,Cd,N,1);
    en = e_time();
    avg_etime_double += en-st;

    free(Af);
    free(Bf);
    free(Cf);
    free(Ad);
    free(Bd);
    free(Cd);
  }
  printf("N=%d : float_avgt = %.10lf, double_avgt = %.10lf\n",M[i],avg_etime_float/TIMES,avg_etime_double/TIMES);
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
      for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
          for(k = 0; k < N; k++){
            MAT(zf,i,j) += MAT(xf,i,k) * MAT(yf,k,j);
          }
        }
      }
      break;
    case 2: //jki
      for(j = 0; j < N; j++){
        for(k = 0; k < N; k++){
          for(i = 0; i < N; i++){
            MAT(zf,i,j) += MAT(xf,i,k) * MAT(yf,k,j);
          }
        }
      }
      break;
    case 3: //kij
      for(k  = 0; k < N; k++){
        for(i = 0; i < N; i++){
          for(j = 0; j < N; j++){
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
      for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
          for(k = 0; k < N; k++){
            MAT(zf,i,j) += MAT(xf,i,k) * MAT(yf,k,j);
          }
        }
      }
      break;
    case 2: //jki
      for(j = 0; j < N; j++){
        for(k = 0; k < N; k++){
          for(i = 0; i < N; i++){
            MAT(zf,i,j) += MAT(xf,i,k) * MAT(yf,k,j);
          }
        }
      }
      break;
    case 3: //kij
      for(k  = 0; k < N; k++){
        for(i = 0; i < N; i++){
          for(j = 0; j < N; j++){
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
