#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

/*
    Define macro for a matrix described in Lec04
*/

/*
    Insert e_time() explained in Ex01
*/

int main (int argc, char* argv[]) {
    unsigned int i, j, k;
    unsigned int N;
/*
    Declare pointers for matrix
*/
    double st, en;
  
    if (argc != 2) {
        N = 128;
    } else {
/*
    Input N, that is size of matrix, from a command line argument
*/    
    }

/*
    Allocate memory for matrices as explained in Lec04
*/

/*
    Initialize the input matrices with random numbers
*/
  
    st = e_time();
/*
    Compute matrix-multiplication
*/
    en = e_time();
  
    printf("%.10e\n", en - st);

/*
    Release memory for matrices
*/
    return 0;
}
