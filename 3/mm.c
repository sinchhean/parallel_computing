#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define RND_MAX 10
#define LOOP 3 //ijk, jki ,kij
#define TIMES 10 //repeat this number of time
//double e_time(void); //measuring elapse time.
//random number into matrices
//void mat_gen(double **Ad, double **Bd, double ***Cd, float **Af, float **Bf, float ***Cf, int n);


void main(int argc, char *argv[]){
  int n;
  int loop_order;
  int i,j,k,nt;
  double **Ad,**Bd,***Cd;
  float **Af,**Bf,***Cf;
  double st_double[LOOP][TIMES], et_double[LOOP][TIMES];
  double st_float[LOOP][TIMES], et_float[LOOP][TIMES];
  double avg_et_double = 0;
  double avg_et_float = 0;
//initialize
  n = atoi(argv[1]);
  Ad = (double **)malloc(sizeof(double *)*n);
  Bd = (double **)malloc(sizeof(double *)*n);
  Af = (float **)malloc(sizeof(float *)*n);
  Bf = (float **)malloc(sizeof(float *)*n);
  Cd = (double ***)malloc(sizeof(double **)*LOOP);
  Cf = (float ***)malloc(sizeof(float **)*LOOP);
  for(i = 0; i < LOOP; i++){
    Cd[i] = (double **)malloc(sizeof(double *)*n);
    Cf[i] = (float **)malloc(sizeof(float *)*n);
  }
  for(i = 0; i < n; i++){
    Ad[i] = (double *)malloc(sizeof(double)*n);
    Bd[i] = (double *)malloc(sizeof(double)*n);  
    Af[i] = (float *)malloc(sizeof(float)*n);
    Bf[i] = (float *)malloc(sizeof(float)*n);
  }
  for(i = 0; i < LOOP; i++){
    for(j = 0; j < n; j++){
      Cd[i][j] = (double *)malloc(sizeof(double)*n);
      Cf[i][j] = (float *)malloc(sizeof(float)*n);
    }
  }

/*
  for(i = 0; i < 3; i++){
    for(j = 0; j < TIMES; j++){
    st_double[i][TIMES] = 0;
    et_double[i][TIMES] = 0;
    st_float[i][TIMES] = 0;
    et_float[i][TIMES] = 0;
    }
  }
*/

  srand(time(NULL)); //seed for the random number
  mat_gen(Ad,Bd,Cd,Af,Bf,Cf,n); //generate random numbers;
//matrix multiplication
  for(nt = 0; nt < TIMES; nt++){  //repeat TIMES

    
  /*-------------float mm start-----------*/
/*
    st_double[0][nt]  = e_time(); 
    for(i = 0; i < n; i++){
      for(j = 0; j < n; j++){
        for(k = 0; k < n; k++){
          Cd[0][i][j] += Ad[i][k] * Bd[k][j];
        }
      }
    }
    et_double[0][nt]  = e_time();
*/
  /*-------------float mm end-----------*/


  /*-------------float mm start-----------*/
/*
    st_float[0][nt]  = e_time(); //start timer 
    for(i = 0; i < n; i++){
      for(j = 0; j < n; j++){
        for(k = 0; k < n; k++){
          Cf[0][i][j] += Af[i][k] * Bf[k][j];
        }
      }
    }
    et_float[0][nt]  = e_time(); //end timer
*/
  /*-------------float mm end-----------*/
  }

//calculate elapse time
/*
  for(i = 0; i < TIMES; i++){
    avg_et_double += (et_double[0][i] - st_double[0][i]);
    avg_et_float += (et_float[0][i] - st_float[0][i]);
  }
  avg_et_double = avg_et_double/TIMES;
  avg_et_float = avg_et_float/TIMES;
*/
//printf("Ad00 = %lf, Af00 = %f,\nCd00 = %lf, Cf00 = %f\n",Ad[0][0],Af[0][0],Cd[0][0],Cf[0][0]);
/*
printf("%d\n",loop_order);
printf("Double MM elapse time: %.16lf\n",avg_et_double);
printf("Float MM elapse time : %.16lf\n",avg_et_float);
*/
//free allocated memory
/*
  for(i = 0; i < n; i++){
    free(Ad[i]);
    free(Bd[i]);
    free(Af[i]);
    free(Bf[i]);
    for(j = 0; j < n; j++){
      free(Cd[i][j]);
      free(Cf[i][j]);
    }
    free(Cd[i]);
    free(Cf[i]);
  }
  free(Ad);
  free(Bd);
  free(Cd);
  free(Af);
  free(Bf);
  free(Cf);
*/
  return;
}

/*
void mat_gen(double **Ad, double **Bd, double ***Cd, float **Af, float **Bf, float ***Cf, int n){
  int i, j, k;
  
  
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      Ad[i][j] = (double)(rand()%RND_MAX);
      Af[i][j] = (float)Ad[i][j];
      Bd[i][j] = (double)(rand()%RND_MAX);
      Bf[i][j] = (float)Bd[i][j];
      for(k = 0; k < LOOP; k++){
        Cd[k][i][j] = 0;
        Cf[k][i][j] = 0;
      }

    }
  }
}


double e_time(void){
  static struct timeval now;
  gettimeofday(&now, NULL);
  return (double)(now.tv_sec + now.tv_usec/1000000.0);
}
*/
