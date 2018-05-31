#include <stdlib.h>
#include <algorithm>
#define TILE_SIZE 32
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

void matmul(float* C, const float* A, const float* B, unsigned int hA, 
    unsigned int wA, unsigned int wB)
{
int tileSize = TILE_SIZE;
  for (unsigned int i = 0; i < hA; i += tileSize)
    for (unsigned int j = 0; j < wB; j += tileSize) {
      for (unsigned int k = 0; k < wA; k += tileSize) {
        unsigned int edge1 = std::min(i + tileSize, hA);
        for (unsigned int x = i; x < edge1; x++){
            unsigned int edge2 = std::min(j + tileSize, wB);
            for (unsigned int y = j; y < edge2; y++){
                unsigned int edge3 = std::min(k + tileSize, wA);
                double sum = 0;
                for (unsigned int z = k; z < edge3; z++){
                    double a = A[x * wA + z];
                    double b = B[z + y * wA];
                    sum += a * b;
                }
                C[x * wA + y] += sum;
            }
        }
      }
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

