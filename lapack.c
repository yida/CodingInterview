#include <lapacke.h>
#include <stdio.h>

int main()
{
  // note, to understand this part take a look in the MAN pages, at section of parameters.
  char  TRANS = 'N';
  int   INFO=3;
  int   LDA = 3;
  int   LDB = 3;
  int   N = 3;
  int   NRHS = 1;
  int   IPIV[3] ;

  double  A[9] =
  {
 2.5056, 1.2905, 1.4870,
    1.2905,  0.8665,  0.5052,
     1.4870,  0.5052,  1.8278
  };

  double B[3] =
  {
  -4,
  -1,
  -2
  };
// end of declarations

  printf("compute the LU factorization...\n");
  //void LAPACK_dgetrf( lapack_int* m, lapack_int* n, double* a, lapack_int* lda, lapack_int* ipiv, lapack_int *info );
  LAPACK_dgetrf(&N,&N,A,&LDA,IPIV,&INFO);

  // checks INFO, if INFO != 0 something goes wrong, for more information see the MAN page of dgetrf.
  if(INFO)
  {
    printf("an error occured : \n");
  }else{
    printf("solving the system...\n");
    int i, j;
    for (i = 0;i<N;i++) {
      for (j = 0; j<N; j++) {
        printf("%f ", A[i+N*j]);
      }
      printf("\n");
    }
    printf("leading dimensions %d \n", LDA);
    for (i = 0;i<N;i++)
      printf("pivot indices %d \n", IPIV[i]);
//    // void LAPACK_dgetrs( char* trans, lapack_int* n, lapack_int* nrhs, const double* a, lapack_int* lda, const lapack_int* ipiv,double* b, lapack_int* ldb, lapack_int *info );
//    dgetrs_(&TRANS,&N,&NRHS,A,&LDA,IPIV,B,&LDB,&INFO);
//    if(INFO)
//    {
//      // checks INFO, if INFO != 0 something goes wrong, for more information see the MAN page of dgetrs.
//     printf("an error occured : \n");
//    }else{
//     printf("print the result : {\n");
//      int i;
//      for (i=0;i<N;i++)
//      {
//        printf("%f ", B[i]);
//      }
//     printf("}\n");
//    }
  }

  printf("program terminated.\n");
  return 0;
}

