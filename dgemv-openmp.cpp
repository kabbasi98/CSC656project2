#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

const char* dgemv_desc = "OpenMP dgemv.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */

void my_dgemv(int n, double* A, double* x, double* y) {

   #pragma omp parallel
   {
      int nthreads = omp_get_num_threads();
      int thread_id = omp_get_thread_num();
      //printf("Hello world: thread %d of %d checking in. \n", thread_id, nthreads);
   }

   // insert your dgemv code here. you may need to create additional parallel regions,
   // and you may want to comment out the above parallel code block that prints out
   // nthreads and thread_id so as to not taint your timings

   #pragma omp parallel for reduce(+:sum)

   for(int j = 0; j <= n; j++){

      A[j] = 0.0;

      for(int i = 0; i <= n; i++){

         A[j] += A[i] * x[i] + y[i];
      }
    
   }

   for (int row=0; row < n; row++){

     int rowOffset = row*n;

   for (int col=0; col < n; col++) {

      y[row] += A[col+rowOffset]*x[col];

   }
}


}

