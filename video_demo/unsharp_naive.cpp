/*
  Copyright (c) 2015 Indian Institute of Science
  All rights reserved.

  Written and provided by:
  Ravi Teja Mullapudi, Vinay Vasista, Uday Bondhugula
  Dept of Computer Science and Automation
  Indian Institute of Science
  Bangalore 560012
  India

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

  THIS MATERIAL IS PROVIDED BY Ravi Teja Mullapudi, Vinay Vasista, and Uday
  Bondhugula, Indian Institute of Science ''AS IS'' AND ANY EXPRESS OR IMPLIED
  WARRANTIES, INCLUDING,
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
#include "simple_pool_allocator.h"
#define isl_min(x,y) ((x) < (y) ? (x) : (y))
#define isl_max(x,y) ((x) > (y) ? (x) : (y))
#define isl_floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
extern "C" void  pipeline_mask_naive(int  C, int  R, float  threshold, float  weight, void * img_void_arg, void * mask_void_arg)
{
  unsigned char * img_flip;
  img_flip = (unsigned char *) (img_void_arg);
  float * mask_flip;
  mask_flip = (float *) (mask_void_arg);
  float * blurx;
  blurx = (float *) (pool_allocate((sizeof(float ) * ((3 * R) * (4 + C)))));
  float * blury;
  blury = (float *) (pool_allocate((sizeof(float ) * ((3 * R) * C))));
  float * sharpen;
  sharpen = (float *) (pool_allocate((sizeof(float ) * ((3 * R) * C))));

  float * img = (float *)pool_allocate(sizeof(float) * 3 * (R+4) * (C+4));
  #pragma omp parallel for schedule(static)
  for(int i = 0; i < R+4; i++)
      for(int j = 0; j< C+4; j++)
          for(int c = 0; c < 3; c++)
              img[c*(R+4)*(C+4) + i*(C+4) + j] = ((float)img_flip[i*(C+4)*3 + j*3 + c]) / 255.0f;

  for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
  {
  #pragma omp parallel for schedule(static)
    for (int  _i1 = 2; (_i1 <= (R + 1)); _i1 = (_i1 + 1))
    {
          #pragma ivdep
      for (int  _i2 = 0; (_i2 <= (C + 3)); _i2 = (_i2 + 1))
      {
        blurx[(((_i0 * (R * (4 + C))) + ((_i1 - 2) * (4 + C))) + _i2)] = (((((img[(((_i0 * ((R + 4) * (C + 4))) + ((-2 + _i1) * (C + 4))) + _i2)] * 0.0625f) + (img[(((_i0 * ((R + 4) * (C + 4))) + ((-1 + _i1) * (C + 4))) + _i2)] * 0.25f)) + (img[(((_i0 * ((R + 4) * (C + 4))) + (_i1 * (C + 4))) + _i2)] * 0.375f)) + (img[(((_i0 * ((R + 4) * (C + 4))) + ((1 + _i1) * (C + 4))) + _i2)] * 0.25f)) + (img[(((_i0 * ((R + 4) * (C + 4))) + ((2 + _i1) * (C + 4))) + _i2)] * 0.0625f));
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
  {
  #pragma omp parallel for schedule(static)
    for (int  _i1 = 2; (_i1 <= (R + 1)); _i1 = (_i1 + 1))
    {
          #pragma ivdep
      for (int  _i2 = 2; (_i2 <= (C + 1)); _i2 = (_i2 + 1))
      {
        blury[(((_i0 * (R * C)) + ((_i1 - 2) * C)) + (_i2 - 2))] = (((((blurx[(((_i0 * (R * (4 + C))) + ((-2 + _i1) * (4 + C))) + (-2 + _i2))] * 0.0625f) + (blurx[(((_i0 * (R * (4 + C))) + ((-2 + _i1) * (4 + C))) + (-1 + _i2))] * 0.25f)) + (blurx[(((_i0 * (R * (4 + C))) + ((-2 + _i1) * (4 + C))) + _i2)] * 0.375f)) + (blurx[(((_i0 * (R * (4 + C))) + ((-2 + _i1) * (4 + C))) + (1 + _i2))] * 0.25f)) + (blurx[(((_i0 * (R * (4 + C))) + ((-2 + _i1) * (4 + C))) + (2 + _i2))] * 0.0625f));
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
  {
  #pragma omp parallel for schedule(static)
    for (int  _i1 = 2; (_i1 <= (R + 1)); _i1 = (_i1 + 1))
    {
          #pragma ivdep
      for (int  _i2 = 2; (_i2 <= (C + 1)); _i2 = (_i2 + 1))
      {
        sharpen[(((_i0 * (R * C)) + ((_i1 - 2) * C)) + (_i2 - 2))] = ((img[(((_i0 * ((R + 4) * (C + 4))) + (_i1 * (C + 4))) + _i2)] * (1 + weight)) + (blury[(((_i0 * (R * C)) + ((-2 + _i1) * C)) + (-2 + _i2))] * -(weight)));
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
  {
  #pragma omp parallel for schedule(static)
    for (int  _i1 = 2; (_i1 <= (R + 1)); _i1 = (_i1 + 1))
    {
          #pragma ivdep
      for (int  _i2 = 2; (_i2 <= (C + 1)); _i2 = (_i2 + 1))
      {
        float  _ct0 = img[(((_i0 * ((R + 4) * (C + 4))) + (_i1 * (C + 4))) + _i2)];
        float  _ct1 = sharpen[(((_i0 * (R * C)) + ((-2 + _i1) * C)) + (-2 + _i2))];
        float  _ct2 = ((std::abs((img[(((_i0 * ((R + 4) * (C + 4))) + (_i1 * (C + 4))) + _i2)] - blury[(((_i0 * (R * C)) + ((-2 + _i1) * C)) + (-2 + _i2))])) < threshold)? _ct0: _ct1);
        mask_flip[((((_i1-2) * (3 * C)) + ((_i2 - 2) * 3)) + (_i0))] = _ct2;
      }
    }
  }
  pool_deallocate(img);
  pool_deallocate(blurx);
  pool_deallocate(blury);
  pool_deallocate(sharpen);
}
