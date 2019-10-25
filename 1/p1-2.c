#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double e_time(void){
  static struct timeval now;
  gettimeofday(&now, NULL);
  return (double)(now.tv_sec + now.tv_usec/1000000.0);
}

double f(double a){
  return (4.0/(1.0+a*a));
}

int main(int argc, char *argv[]){
  int n, id, np, i;
  double PI25DT = 3.141592653589793238462643;
  double h, sum, x, mypi;
  double st, en;
  
  n = atoi(argv[1]);
  //n = 1000;
  printf("n is %d.\n",n);
  h = 1.0/(double)n;
  sum = 0.0;
  //main loop
  st = e_time();
  for(i=0; i<n; i++){
    x = h*((double)i - 0.5);
    sum += f(x);
  }
  mypi = h*sum;
  en = e_time();

  printf("pi is approximately %.16f, Error is %.16f\n", mypi, fabs(mypi - PI25DT));
  printf("Elapse time is %.16f.\n", en-st);
  return 0;
}


