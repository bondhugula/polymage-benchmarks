/*Copyright (c) 2015-, Ravi Teja Mullapudi, Vinay Vasista, CSA Indian 
  Institute of Science
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
  3. Neither the name of the Indian Institute of Science nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY Ravi Teja Mullapudi, Vinay Vasista, CSA Indian
  Institute of Science ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
  BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
  PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Ravi Teja Mullapudi, Vinay
  Vasista, CSA Indian Institute of Science BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <cmath>
#include <string.h>
#define isl_min(x,y) ((x) < (y) ? (x) : (y))
#define isl_max(x,y) ((x) > (y) ? (x) : (y))
#define isl_floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
extern "C" void  pipeline_harris(int  C, int  R, void * img_void_arg, void * harris_void_arg)
{
  float * img;
  img = (float *) (img_void_arg);
  float * harris;
  harris = (float *) (harris_void_arg);
  float * Ix;
  Ix = (float *) (malloc((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Iy;
  Iy = (float *) (malloc((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Ixx;
  Ixx = (float *) (malloc((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Ixy;
  Ixy = (float *) (malloc((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Iyy;
  Iyy = (float *) (malloc((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Sxx;
  Sxx = (float *) (malloc((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Sxy;
  Sxy = (float *) (malloc((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * Syy;
  Syy = (float *) (malloc((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * det;
  det = (float *) (malloc((sizeof(float ) * ((2 + R) * (2 + C)))));
  float * trace;
  trace = (float *) (malloc((sizeof(float ) * ((2 + R) * (2 + C)))));
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 1; (_i0 <= R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 1; (_i1 <= C); _i1 = (_i1 + 1))
    {
      Iy[((_i0 * (2 + C)) + _i1)] = ((((((img[(((-1 + _i0) * (C + 2)) + (-1 + _i1))] * -0.0833333333333f) + (img[(((-1 + _i0) * (C + 2)) + (1 + _i1))] * 0.0833333333333f)) + (img[((_i0 * (C + 2)) + (-1 + _i1))] * -0.166666666667f)) + (img[((_i0 * (C + 2)) + (1 + _i1))] * 0.166666666667f)) + (img[(((1 + _i0) * (C + 2)) + (-1 + _i1))] * -0.0833333333333f)) + (img[(((1 + _i0) * (C + 2)) + (1 + _i1))] * 0.0833333333333f));
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 1; (_i0 <= R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 1; (_i1 <= C); _i1 = (_i1 + 1))
    {
      Ix[((_i0 * (2 + C)) + _i1)] = ((((((img[(((-1 + _i0) * (C + 2)) + (-1 + _i1))] * -0.0833333333333f) + (img[(((1 + _i0) * (C + 2)) + (-1 + _i1))] * 0.0833333333333f)) + (img[(((-1 + _i0) * (C + 2)) + _i1)] * -0.166666666667f)) + (img[(((1 + _i0) * (C + 2)) + _i1)] * 0.166666666667f)) + (img[(((-1 + _i0) * (C + 2)) + (1 + _i1))] * -0.0833333333333f)) + (img[(((1 + _i0) * (C + 2)) + (1 + _i1))] * 0.0833333333333f));
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 1; (_i0 <= R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 1; (_i1 <= C); _i1 = (_i1 + 1))
    {
      Iyy[((_i0 * (2 + C)) + _i1)] = (Iy[((_i0 * (2 + C)) + _i1)] * Iy[((_i0 * (2 + C)) + _i1)]);
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 1; (_i0 <= R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 1; (_i1 <= C); _i1 = (_i1 + 1))
    {
      Ixy[((_i0 * (2 + C)) + _i1)] = (Ix[((_i0 * (2 + C)) + _i1)] * Iy[((_i0 * (2 + C)) + _i1)]);
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 1; (_i0 <= R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 1; (_i1 <= C); _i1 = (_i1 + 1))
    {
      Ixx[((_i0 * (2 + C)) + _i1)] = (Ix[((_i0 * (2 + C)) + _i1)] * Ix[((_i0 * (2 + C)) + _i1)]);
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 2; (_i0 < R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 2; (_i1 < C); _i1 = (_i1 + 1))
    {
      Syy[((_i0 * (2 + C)) + _i1)] = ((((((((Iyy[(((-1 + _i0) * (2 + C)) + (-1 + _i1))] + Iyy[(((-1 + _i0) * (2 + C)) + _i1)]) + Iyy[(((-1 + _i0) * (2 + C)) + (1 + _i1))]) + Iyy[((_i0 * (2 + C)) + (-1 + _i1))]) + Iyy[((_i0 * (2 + C)) + _i1)]) + Iyy[((_i0 * (2 + C)) + (1 + _i1))]) + Iyy[(((1 + _i0) * (2 + C)) + (-1 + _i1))]) + Iyy[(((1 + _i0) * (2 + C)) + _i1)]) + Iyy[(((1 + _i0) * (2 + C)) + (1 + _i1))]);
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 2; (_i0 < R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 2; (_i1 < C); _i1 = (_i1 + 1))
    {
      Sxy[((_i0 * (2 + C)) + _i1)] = ((((((((Ixy[(((-1 + _i0) * (2 + C)) + (-1 + _i1))] + Ixy[(((-1 + _i0) * (2 + C)) + _i1)]) + Ixy[(((-1 + _i0) * (2 + C)) + (1 + _i1))]) + Ixy[((_i0 * (2 + C)) + (-1 + _i1))]) + Ixy[((_i0 * (2 + C)) + _i1)]) + Ixy[((_i0 * (2 + C)) + (1 + _i1))]) + Ixy[(((1 + _i0) * (2 + C)) + (-1 + _i1))]) + Ixy[(((1 + _i0) * (2 + C)) + _i1)]) + Ixy[(((1 + _i0) * (2 + C)) + (1 + _i1))]);
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 2; (_i0 < R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 2; (_i1 < C); _i1 = (_i1 + 1))
    {
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
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 2; (_i0 < R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 2; (_i1 < C); _i1 = (_i1 + 1))
    {
      det[((_i0 * (2 + C)) + _i1)] = ((Sxx[((_i0 * (2 + C)) + _i1)] * Syy[((_i0 * (2 + C)) + _i1)]) - (Sxy[((_i0 * (2 + C)) + _i1)] * Sxy[((_i0 * (2 + C)) + _i1)]));
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i0 = 2; (_i0 < R); _i0 = (_i0 + 1))
  {
    #pragma ivdep
    for (int  _i1 = 2; (_i1 < C); _i1 = (_i1 + 1))
    {
      harris[((_i0 * (2 + C)) + _i1)] = (det[((_i0 * (2 + C)) + _i1)] - ((0.04f * trace[((_i0 * (2 + C)) + _i1)]) * trace[((_i0 * (2 + C)) + _i1)]));
    }
  }
  free(Ix);
  free(Iy);
  free(Ixx);
  free(Ixy);
  free(Iyy);
  free(Sxx);
  free(Sxy);
  free(Syy);
  free(det);
  free(trace);
}
