#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void quicksort_asc(double *, int, int);
void quicksort_desc(double *, int, int);

int main(){
  FILE *fp;
  char filename[100];

  int xco, yco; // number of x and y coordinates
  int i,j,k; //for looping
  double **data; //save data as a 2 dimensionals array
  double *x_dire, *y_dire; //x and y direction first order
  double sumx_dire = 0,sumy_dire = 0; //x and y direction first order summation
  char c; //comma

  printf("Enter file name: ");
  scanf("%100s", filename);
  printf("----------------------------\n");

  fp = fopen(filename, "r");
  if(fp == NULL){
    printf("error: file no tfound.\n");
    exit(1);
  }

  printf("file name is %s.\n",filename);

//xco and yco
  fscanf(fp, "%d", &xco);
  fscanf(fp, "%d", &yco);
  printf("xco is %d, yco is %d.\n",xco, yco);

//initilize size of data based on xco and yco
  data = (double **)malloc(sizeof(double *)*yco);
  for(i = 0; i < yco; i++){
    data[i] = (double *)malloc(sizeof(double)*xco);
  }
  x_dire = (double *)malloc(sizeof(double)*xco*yco);
  y_dire = (double *)malloc(sizeof(double)*xco*yco);

//read data
  for(i = 0; i < yco; i++){
    for(j = 0; j < xco; j++){
      fscanf(fp,"%lf%c",&data[i][j], &c); 
    }
  }
//x and y summations

  k = 0;
  for(i = 0; i < yco; i++){
    for(j = 0; j < xco; j++){
      x_dire[k++] = data[i][j];
      sumx_dire = sumx_dire + data[i][j];
    }
  }
  k = 0;
  for(i = 0; i < xco; i++){
    for(j = 0; j < yco; j++){
      y_dire[k++] = data[j][i];
      sumy_dire = sumy_dire + data[j][i];
    }
  }
printf("x-dire = %.16lf. y-dire = %.16lf.\n", sumx_dire, sumy_dire);

//sort ascending
  quicksort_asc(x_dire,0,(xco*yco)-1);
  quicksort_asc(y_dire,0,(xco*yco)-1);

  sumx_dire = 0,sumy_dire = 0;
  for(i = 0; i < yco*xco; i++){
    sumx_dire = sumx_dire + x_dire[i];
    sumy_dire = sumy_dire + y_dire[i];
  }
  
printf("After asc-sort x-dire = %.16lf. y-dire = %.16lf.\n", sumx_dire, sumy_dire);
/*
printf("asceding sort\n");
  for(i=0; i<xco*yco; i++){
    printf("%f ", x_dire[i]);
  }
  printf("\n");
  for(i=0; i<xco*yco; i++){
    printf("%f ", y_dire[i]);
  }
  printf("\n");
*/

//sort descending

  quicksort_desc(x_dire,0,xco*yco-1);
  quicksort_desc(y_dire,0,xco*yco-1);

  sumx_dire = 0,sumy_dire = 0;
  for(i = 0; i < yco*xco; i++){
    sumx_dire = sumx_dire + x_dire[i];
    sumy_dire = sumy_dire + y_dire[i];
  }
  
printf("After desc-sort x-dire = %.16lf. y-dire = %.16lf.\n", sumx_dire, sumy_dire);

//checking read data
/*
printf("descending sort\n");
  for(i=0; i<xco*yco; i++){
    printf("%f ", x_dire[i]);
  }
  printf("\n");
  for(i=0; i<xco*yco; i++){
    printf("%f ", y_dire[i]);
  }
  printf("\n");

  for(i = 0; i < yco; i++){
    for(j = 0; j < xco; j++){
      
      if(j < xco -1){
        printf("%f,", data[i][j]);
      }else{
        printf("%f", data[i][j]);
      }
    }
    printf("\n");
  }
*/

//free memory
for(i = 0; i < yco; i++) free(data[i]);
free(data);
free(x_dire);
free(y_dire);
fclose(fp);

}

void quicksort_asc(double *number, int left, int right){
  int i, j, pivot;
  double temp;

  pivot = right;
  i = left;
  j = right;
    
  while(1){
    while(number[i] < number[pivot]) 
    {
      i++;
    }
    while(number[j] > number[pivot])
    {
      j--;
    }
    if(i >= j){
      break;
    }
    temp = number[i];
    number[i] = number[j];
    number[j] = temp;
    i++;
    j--;
  }
  if(left < right){
    quicksort_asc(number, left, i-1);
    quicksort_asc(number, j+1, right); 
  }
}
void quicksort_desc(double *number, int left, int right){
  int i, j, pivot;
  double temp;

  pivot = (left+right)/2;
  i = left;
  j = right;
    
  while(1){
    while(number[i] > number[pivot]) 
    {
      i++;
    }
    while(number[j] < number[pivot])
    {
      j--;
    }
    if(i > j){
      break;
    }
    temp = number[i];
    number[i] = number[j];
    number[j] = temp;
    i++;
    j--;
  }
  if(left > right){
    quicksort_desc(number, left, i-1);
    quicksort_desc(number, j+1, right); 
  }
}
