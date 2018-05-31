#include <stdlib.h>
#include "matmul.h"

#include <stdio.h>

Matrix Allocate2ndMatrix(int height, int width, int init);

void matmul( float*, const float*, const float*, unsigned int, unsigned int, unsigned int);

////////////////////////////////////////////////////////////////////////////////
//! C = A * B
//! @param C          result matrix
//! @param A          matrix A 
//! @param B          matrix B
//! @param hA         height of matrix A
//! @param wB         width of matrix B
////////////////////////////////////////////////////////////////////////////////

// Write a 16x16 floating point matrix to file
void PrintMatTest(Matrix M)
{
  /*** Print results ***/
  fprintf(stderr,"Printing Matrix:\n");
  for (unsigned int i=0; i<M.height; i++)
  {
    for (unsigned int j=0; j<M.width; j++)
      fprintf(stdout, "%.2f ", M.elements[i*M.width+j]);
    fprintf(stdout, "\n");
  }
  fprintf(stderr,"******************************************************\n");
}

void matmul(float* C, const float* A, const float* B, unsigned int hA, 
    unsigned int wA, unsigned int wB)
{
  for (unsigned int i = 0; i < hA; ++i)
    for (unsigned int j = 0; j < wB; ++j) {
      double sum = 0;
      for (unsigned int k = 0; k < wA; ++k) {
        double a = A[i * wA + k];
        double b = B[k + j * wA];
        sum += a * b;
      }
      C[i * wA + j] = (float)sum;
    }
}

// Allocate a matrix of dimensions height*width
Matrix Allocate2ndMatrix(int height, int width)
{
  Matrix M;
  M.width = M.pitch = width;
  M.height = height;
  int size = M.width * M.height;
  M.elements = NULL;

  M.elements = (float*) malloc(size*sizeof(float));

  for(unsigned int i = 0; i < M.height; i++)
  {
    for(unsigned int j = 0; j < M.width; j++)
    {
        M.elements[i + j*M.width] = (rand() / (float)RAND_MAX);
    }
  }
  return M;
}	

