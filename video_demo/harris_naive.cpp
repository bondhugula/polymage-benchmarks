#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <cmath>
#include <string.h>
#include "simple_pool_allocator.h"
#define isl_min(x,y) ((x) < (y) ? (x) : (y))
#define isl_max(x,y) ((x) > (y) ? (x) : (y))
#define isl_floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
extern "C" void  pipeline_harris_naive(int  C, int  R, void * img_void_arg, void * harris_void_arg)
{
  unsigned char * img;
  img = (unsigned char *) (img_void_arg);
  float * harris;
  harris = (float *) (harris_void_arg);
  float * gray;
  gray = (float *) (pool_allocate((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Ix;
  Ix = (float *) (pool_allocate((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Iy;
  Iy = (float *) (pool_allocate((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Ixx;
  Ixx = (float *) (pool_allocate((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Ixy;
  Ixy = (float *) (pool_allocate((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Iyy;
  Iyy = (float *) (pool_allocate((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Sxx;
  Sxx = (float *) (pool_allocate((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Sxy;
  Sxy = (float *) (pool_allocate((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Syy;
  Syy = (float *) (pool_allocate((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * det;
  det = (float *) (pool_allocate((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * trace;
  trace = (float *) (pool_allocate((sizeof(float ) * ((2 + R) * (2 + C)))));
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 0; (_i0 <= (R + 1)); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 0; (_i1 <= (C + 1)); _i1 = (_i1 + 1))
    {
      gray[((_i0 * (2 + C)) + _i1)] = ((((img[((_i0 * ((C + 2) * 3)) + (_i1 * 3))] * 0.114f) + (img[(((_i0 * ((C + 2) * 3)) + (_i1 * 3)) + 1)] * 0.587f)) + (img[(((_i0 * ((C + 2) * 3)) + (_i1 * 3)) + 2)] * 0.299f)) / 255.0f);
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 1; (_i0 <= R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 1; (_i1 <= C); _i1 = (_i1 + 1))
    {
      Ix[((_i0 * (2 + C)) + _i1)] = ((((((gray[(((-1 + _i0) * (2 + C)) + (-1 + _i1))] * -0.0833333333333f) + (gray[(((1 + _i0) * (2 + C)) + (-1 + _i1))] * 0.0833333333333f)) + (gray[(((-1 + _i0) * (2 + C)) + _i1)] * -0.166666666667f)) + (gray[(((1 + _i0) * (2 + C)) + _i1)] * 0.166666666667f)) + (gray[(((-1 + _i0) * (2 + C)) + (1 + _i1))] * -0.0833333333333f)) + (gray[(((1 + _i0) * (2 + C)) + (1 + _i1))] * 0.0833333333333f));
      Iy[((_i0 * (2 + C)) + _i1)] = ((((((gray[(((-1 + _i0) * (2 + C)) + (-1 + _i1))] * -0.0833333333333f) + (gray[(((-1 + _i0) * (2 + C)) + (1 + _i1))] * 0.0833333333333f)) + (gray[((_i0 * (2 + C)) + (-1 + _i1))] * -0.166666666667f)) + (gray[((_i0 * (2 + C)) + (1 + _i1))] * 0.166666666667f)) + (gray[(((1 + _i0) * (2 + C)) + (-1 + _i1))] * -0.0833333333333f)) + (gray[(((1 + _i0) * (2 + C)) + (1 + _i1))] * 0.0833333333333f));
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 1; (_i0 <= R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 1; (_i1 <= C); _i1 = (_i1 + 1))
    {
      Ixx[((_i0 * (2 + C)) + _i1)] = (Ix[((_i0 * (2 + C)) + _i1)] * Ix[((_i0 * (2 + C)) + _i1)]);
      Iyy[((_i0 * (2 + C)) + _i1)] = (Iy[((_i0 * (2 + C)) + _i1)] * Iy[((_i0 * (2 + C)) + _i1)]);
      Ixy[((_i0 * (2 + C)) + _i1)] = (Ix[((_i0 * (2 + C)) + _i1)] * Iy[((_i0 * (2 + C)) + _i1)]);
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 2; (_i0 < R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 2; (_i1 < C); _i1 = (_i1 + 1))
    {
      Syy[((_i0 * (2 + C)) + _i1)] = ((((((((Iyy[(((-1 + _i0) * (2 + C)) + (-1 + _i1))] + Iyy[(((-1 + _i0) * (2 + C)) + _i1)]) + Iyy[(((-1 + _i0) * (2 + C)) + (1 + _i1))]) + Iyy[((_i0 * (2 + C)) + (-1 + _i1))]) + Iyy[((_i0 * (2 + C)) + _i1)]) + Iyy[((_i0 * (2 + C)) + (1 + _i1))]) + Iyy[(((1 + _i0) * (2 + C)) + (-1 + _i1))]) + Iyy[(((1 + _i0) * (2 + C)) + _i1)]) + Iyy[(((1 + _i0) * (2 + C)) + (1 + _i1))]);
      Sxy[((_i0 * (2 + C)) + _i1)] = ((((((((Ixy[(((-1 + _i0) * (2 + C)) + (-1 + _i1))] + Ixy[(((-1 + _i0) * (2 + C)) + _i1)]) + Ixy[(((-1 + _i0) * (2 + C)) + (1 + _i1))]) + Ixy[((_i0 * (2 + C)) + (-1 + _i1))]) + Ixy[((_i0 * (2 + C)) + _i1)]) + Ixy[((_i0 * (2 + C)) + (1 + _i1))]) + Ixy[(((1 + _i0) * (2 + C)) + (-1 + _i1))]) + Ixy[(((1 + _i0) * (2 + C)) + _i1)]) + Ixy[(((1 + _i0) * (2 + C)) + (1 + _i1))]);
      Sxx[((_i0 * (2 + C)) + _i1)] = ((((((((Ixx[(((-1 + _i0) * (2 + C)) + (-1 + _i1))] + Ixx[(((-1 + _i0) * (2 + C)) + _i1)]) + Ixx[(((-1 + _i0) * (2 + C)) + (1 + _i1))]) + Ixx[((_i0 * (2 + C)) + (-1 + _i1))]) + Ixx[((_i0 * (2 + C)) + _i1)]) + Ixx[((_i0 * (2 + C)) + (1 + _i1))]) + Ixx[(((1 + _i0) * (2 + C)) + (-1 + _i1))]) + Ixx[(((1 + _i0) * (2 + C)) + _i1)]) + Ixx[(((1 + _i0) * (2 + C)) + (1 + _i1))]);
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 2; (_i0 < R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 2; (_i1 < C); _i1 = (_i1 + 1))
    {
      trace[((_i0 * (2 + C)) + _i1)] = (Sxx[((_i0 * (2 + C)) + _i1)] + Syy[((_i0 * (2 + C)) + _i1)]);
      det[((_i0 * (2 + C)) + _i1)] = ((Sxx[((_i0 * (2 + C)) + _i1)] * Syy[((_i0 * (2 + C)) + _i1)]) - (Sxy[((_i0 * (2 + C)) + _i1)] * Sxy[((_i0 * (2 + C)) + _i1)]));
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 2; (_i0 < R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 2; (_i1 < C); _i1 = (_i1 + 1))
    {
      harris[((_i0 * (2 + C)) + _i1)] = (((det[((_i0 * (2 + C)) + _i1)] - ((0.04f * trace[((_i0 * (2 + C)) + _i1)]) * trace[((_i0 * (2 + C)) + _i1)])) * 65536.0f) * 256.0f);
    }
  }
  pool_deallocate(gray);
  pool_deallocate(Ix);
  pool_deallocate(Iy);
  pool_deallocate(Ixx);
  pool_deallocate(Ixy);
  pool_deallocate(Iyy);
  pool_deallocate(Sxx);
  pool_deallocate(Sxy);
  pool_deallocate(Syy);
  pool_deallocate(det);
  pool_deallocate(trace);
}
