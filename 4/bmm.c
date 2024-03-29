#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_BLOCKSIZE 256
#define MAT(p,j,i) p[(j)*N +(i)]
#define BIGGEST_DIFF 1.0e-5
#define SMALLEST_DIFF 1.0e-15

int* convert_string_to_int_array(char*, int*);
void reset_mat(float *,double *, int);
void mat_gen(float *, float *, float *, double *, double *, double *, float *, double *, int); //make random data for float and double
void mat_mult_float(float *, float *, float *, int, int );  //MM of float
void mat_mult_double(double *, double *, double *, int, int );  //MM of double
void block_mm_float(float *, float *, float *, int, int); //blocked MM of float
void block_mm_double(double *, double *, double *, int, int); //blocked MM of double
double e_time(void);

int main(int argc, char** argv){
	int i,j,k,m;
	int I,J,K;
	int *block;
	int option;
	int N;
	int *M;
	float *Af, *Bf, *Cf;
	double *Ad, *Bd, *Cd;
	float *Cb_float;
	double *Cb_double;
	double st, en;
	double etime_float = 0;
	double etime_double = 0;
	double etime_block_float = 0;
	double etime_block_double = 0;
	int c;
	int index;
	int n_N = 0;
	int n_block = 0;
	char *ovalue = "";
	char *dvalue = "";
	char *bvalue = "";

	srand(time(NULL));                                 //seed for the random number

//option arguments handling
	while((c = getopt(argc, argv, "o:d:b:")) != -1) {
		switch(c)
		{
		case 'o':
			ovalue = optarg;
			break;
		case 'd':
			dvalue = optarg;
			break;
		case 'b':
			bvalue = optarg;
			break;
		case '?':
			if (isprint(optopt))
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf (stderr,
				         "Unknown option character `\\x%x'.\n",
				         optopt);
			return 1;
		default:
			abort();
		}
	}

	//handling non-option argument
	for (index = optind; index < argc; index++) {
		if(atoi(argv[index]) == 0)
			printf ("Non-option argument %s\n", argv[index]);
	}


//setting default option
	if(strcmp(ovalue, "") == 0) {
		printf("Loop order set to ijk.\n");
		ovalue = "ijk";
	}
	if(strcmp(dvalue, "") == 0) {
		printf("Default matrix sizes are 8 and 16 set with : -d \"8 16\"\n");
		dvalue = "8 16";
	}
	if(strcmp(bvalue, "") == 0) {
		printf("Default bloack size is set to 2 : -b 2\n");
		bvalue = "2";
	}

	M = convert_string_to_int_array(dvalue, &n_N);
	block = convert_string_to_int_array(bvalue, &n_block);



//setting loop order
	if(strcmp(ovalue, "ijk") == 0) {
		option = 1;
	}else if(strcmp(ovalue, "jki") == 0) {
		option = 2;
	}else if(strcmp(ovalue, "kij") == 0) {
		option = 3;
	}else{
		printf("There is no \"%s\" loop order set. Setting to default loop order ijk.\n",ovalue);
		option = 1;
	}

	printf("%5s %4s %20s %20s %20s %20s\n","block","N","etime_float","etime_block_float","etime_double","etime_block_double");

//begin calculation loop
	for(j = 0; j < n_block; j++) {
		for(i = 0; i < n_N; i++) {
			//if(block[j] <= MAX_BLOCKSIZE && block[j] <= M[i]) {

				Af = (float *)malloc(sizeof(float)*M[i]*M[i]);
				Bf = (float *)malloc(sizeof(float)*M[i]*M[i]);
				Cf = (float *)malloc(sizeof(float)*M[i]*M[i]);
				Ad = (double *)malloc(sizeof(double)*M[i]*M[i]);
				Bd = (double *)malloc(sizeof(double)*M[i]*M[i]);
				Cd = (double *)malloc(sizeof(double)*M[i]*M[i]);
				Cb_float = (float*)malloc(sizeof(float)*M[i]*M[i]);
				Cb_double = (double *)malloc(sizeof(double)*M[i]*M[i]);

				N = M[i];

				//initialize data
				mat_gen(Af,Bf,Cf,Ad,Bd,Cd,Cb_float,Cb_double,N);

				//naive matrix multiplication
				st = e_time();
				mat_mult_float(Af,Bf,Cf,N,option);
				en = e_time();
				etime_float = en-st;

				st = e_time();
				mat_mult_double(Ad,Bd,Cd,N,option);
				en = e_time();
				etime_double = en-st;


				//blocked matrix multiplication
				st = e_time();
				block_mm_float(Af,Bf,Cb_float,N,block[j]);
				en = e_time();
				etime_block_float = en-st;

				st = e_time();
				block_mm_double(Ad,Bd,Cb_double,N,block[j]);
				en = e_time();
				etime_block_double = en-st;


				printf("%5d %4d %20.10e %20.10e %20.10e %20.10e\n",block[j], N, etime_float, etime_block_float, etime_double, etime_block_double);

////////////checking start//////////////////////////
/*
        for(m = 0; m < N; m++){
        for(k = 0; k < N; k++){
                printf("%.16f ",Cf[(m)*N +(k)]);
        }
        printf("\n");
        }
        printf("\n\n");

        for(m = 0; m < N; m++){
        for(k = 0; k < N; k++){
                printf("%.16f ",Cb_float[(m)*N +(k)]);
        }
        printf("\n");
        }
        printf("\n\n");

        for(m = 0; m < N; m++){
        for(k = 0; k < N; k++){
                printf("%.16lf ",Ad[(m)*N +(k)]);
        }
        printf("\n");
        }
        printf("\n\n");

        for(m = 0; m < N; m++){
        for(k = 0; k < N; k++){
                printf("%.16lf ",Bd[(m)*N +(k)]);
        }
        printf("\n");
        }
        printf("\n\n");

				int test = 0;
				for(m = 0; m < N; m++) {
					for(k = 0; k < N; k++) {
						double diff = abs(Cd[(m)*N +(k)] - Cb_double[(m)*N +(k)]);
						if(diff <= BIGGEST_DIFF && diff >= SMALLEST_DIFF) {
						}else{
							printf("There is different between ");
							printf("%.32e, %.32e : ",Cd[(m)*N +(k)], Cb_double[(m)*N +(k)]);
							printf("%.32e\n",diff);
							test++;
						}
					}
				}

				printf("test=%d",test);
				printf("\n");
*/
/////////////checking end//////////////////////////
				free(Af);
				free(Bf);
				free(Cf);
				free(Ad);
				free(Bd);
				free(Cd);
				free(Cb_float);
				free(Cb_double);
			//}
		}
	}
	return 0;
}

void reset_mat(float *xf,double *xd, int N){
	int i,j;
	for(j = 0; j < N; j++) {
		for(i = 0; i < N; i++) {
			MAT(xf,j,i) = 0.0;
			MAT(xd,j,i) = 0.0;
		}
	}
}
void mat_gen(float *xf, float *yf, float *zf, double *xd, double *yd, double *zd, float *bf, double *bd, int N){
	int i,j;
	for(j = 0; j < N; j++) {
		for(i = 0; i < N; i++) {
			MAT(xd,j,i) = (double)rand()/(double)(RAND_MAX - 1);
			MAT(yd,j,i) = (double)rand()/(double)(RAND_MAX - 1);
			MAT(xf,j,i) = (float)MAT(xd,j,i);
			MAT(yf,j,i) = (float)MAT(yd,j,i);
			MAT(zf,j,i) = 0.0;
			MAT(zd,j,i) = 0.0;
      MAT(bf,j,i) = 0.0;
      MAT(bd,j,i) = 0.0;
		}
	}
}

void block_mm_float(float *xf, float *yf, float *zf, int N, int bsize){
	int I, J, K;
	int i, j, k;
	int block = bsize;
	if(block > N) block = N;
	for(I = 0; I < N; I+=block) {
		for(J = 0; J < N; J+=block) {
			for(K = 0; K < N; K+=block) {
				for(i = 0; i < block; i++) {
					for(j = 0; j < block; j++) {
						for(k = 0; k < block; k++) {
							MAT(zf,I+i,J+j) += MAT(xf,I+i,K+k) * MAT(yf,K+k,J+j);
						}
					}
				}
			}
		}
	}
}

void block_mm_double(double *xf, double *yf, double *zf, int N, int bsize){
	int I, J, K;
	int i, j, k;
	int block = bsize;
	if(block > N) block = N;
	for(I = 0; I < N; I+=block) {
		for(J = 0; J < N; J+=block) {
			for(K = 0; K < N; K+=block) {
				for(i = 0; i < block; i++) {
					for(j = 0; j < block; j++) {
						for(k = 0; k < block; k++) {
							MAT(zf,I+i,J+j) += MAT(xf,I+i,K+k) * MAT(yf,K+k,J+j);
						}
					}
				}
			}
		}
	}
}

void mat_mult_float(float *xf, float *yf, float *zf, int N, int c){
	int i,j,k;
	switch(c)
	{
	case 1:                                 //ijk
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				for(k = 0; k < N; k++) {
					MAT(zf,i,j) += MAT(xf,i,k) * MAT(yf,k,j);
				}
			}
		}
		break;
	case 2:                                 //jki
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
				for(i = 0; i < N; i++) {
					MAT(zf,i,j) += MAT(xf,i,k) * MAT(yf,k,j);
				}
			}
		}
		break;
	case 3:                                 //kij
		for(k  = 0; k < N; k++) {
			for(i = 0; i < N; i++) {
				for(j = 0; j < N; j++) {
					MAT(zf,i,j) += MAT(xf,i,k) * MAT(yf,k,j);
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
	case 1:                                 //ijk
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				for(k = 0; k < N; k++) {
					MAT(zf,i,j) += MAT(xf,i,k) * MAT(yf,k,j);
				}
			}
		}
		break;
	case 2:                                 //jki
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
				for(i = 0; i < N; i++) {
					MAT(zf,i,j) += MAT(xf,i,k) * MAT(yf,k,j);
				}
			}
		}
		break;
	case 3:                                 //kij
		for(k  = 0; k < N; k++) {
			for(i = 0; i < N; i++) {
				for(j = 0; j < N; j++) {
					MAT(zf,i,j) += MAT(xf,i,k) * MAT(yf,k,j);
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

int* convert_string_to_int_array(char* c, int* n)
{
	int len = 0;
	sscanf(c, "%*[^0-9]%n", &len);
	char *p = c + len;
	char *start = p;
	int v;
	while(1 == sscanf(p, "%d%n", &v, &len)) {
		++*n;  //count elements
		p += len;
	}
	int *array=(int*)malloc(*n*sizeof(int));
	char *endp = NULL;
	int i;
	for(i = 0; i < *n; ++i) {
		array[i] = strtol(start, &endp, 10);
		start = endp + 1;
	}
	return array;

}
