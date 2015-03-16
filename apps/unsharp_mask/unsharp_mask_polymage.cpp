/*Copyright (c) 2015-, Ravi Teja Mullapudi, Vinay Vasista, CSA Indian 
  Institue of Science
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
  Institue of Science ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
  BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
  PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Ravi Teja Mullapudi, Vinay
  Vasista, CSA Indian Institue of Science BE LIABLE FOR ANY DIRECT, INDIRECT,
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
extern "C" void  pipeline_mask(int  C, int  R, float  threshold, float  weight, void * img_void_arg, void * mask_void_arg)
{
  float * img;
  img = (float *) (img_void_arg);
  float * mask;
  mask = (float *) (mask_void_arg);
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= ((R + 1) / 8)); _T_i1 = (_T_i1 + 1))
  {
    float  blurx[3][8][518];
    float  blury[3][8][518];
    float  sharpen[3][8][518];
    for (int  _T_i2 = -1; (_T_i2 <= ((C + 3) / 512)); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
      {
        int  _ct1083 = (((R + 1) < ((8 * _T_i1) + 7))? (R + 1): ((8 * _T_i1) + 7));
        int  _ct1084 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct1084; (_i1 <= _ct1083); _i1 = (_i1 + 1))
        {
          int  _ct1085 = (((C + 3) < ((512 * _T_i2) + 517))? (C + 3): ((512 * _T_i2) + 517));
          int  _ct1086 = ((0 > (512 * _T_i2))? 0: (512 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct1086; (_i2 <= _ct1085); _i2 = (_i2 + 1))
          {
            blurx[_i0][((-8 * _T_i1) + _i1)][((-512 * _T_i2) + _i2)] = (((((img[(((_i0 * ((R + 4) * (C + 4))) + ((-2 + _i1) * (C + 4))) + _i2)] * 0.0625f) + (img[(((_i0 * ((R + 4) * (C + 4))) + ((-1 + _i1) * (C + 4))) + _i2)] * 0.25f)) + (img[(((_i0 * ((R + 4) * (C + 4))) + (_i1 * (C + 4))) + _i2)] * 0.375f)) + (img[(((_i0 * ((R + 4) * (C + 4))) + ((1 + _i1) * (C + 4))) + _i2)] * 0.25f)) + (img[(((_i0 * ((R + 4) * (C + 4))) + ((2 + _i1) * (C + 4))) + _i2)] * 0.0625f));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
      {
        int  _ct1087 = (((R + 1) < ((8 * _T_i1) + 7))? (R + 1): ((8 * _T_i1) + 7));
        int  _ct1088 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct1088; (_i1 <= _ct1087); _i1 = (_i1 + 1))
        {
          int  _ct1089 = (((C + 1) < ((512 * _T_i2) + 516))? (C + 1): ((512 * _T_i2) + 516));
          int  _ct1090 = ((2 > ((512 * _T_i2) + 1))? 2: ((512 * _T_i2) + 1));
          #pragma ivdep
          for (int  _i2 = _ct1090; (_i2 <= _ct1089); _i2 = (_i2 + 1))
          {
            blury[_i0][((-8 * _T_i1) + _i1)][((-512 * _T_i2) + _i2)] = (((((blurx[_i0][((-8 * _T_i1) + _i1)][(-2 + ((-512 * _T_i2) + _i2))] * 0.0625f) + (blurx[_i0][((-8 * _T_i1) + _i1)][(-1 + ((-512 * _T_i2) + _i2))] * 0.25f)) + (blurx[_i0][((-8 * _T_i1) + _i1)][((-512 * _T_i2) + _i2)] * 0.375f)) + (blurx[_i0][((-8 * _T_i1) + _i1)][(1 + ((-512 * _T_i2) + _i2))] * 0.25f)) + (blurx[_i0][((-8 * _T_i1) + _i1)][(2 + ((-512 * _T_i2) + _i2))] * 0.0625f));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
      {
        int  _ct1091 = (((R + 1) < ((8 * _T_i1) + 7))? (R + 1): ((8 * _T_i1) + 7));
        int  _ct1092 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct1092; (_i1 <= _ct1091); _i1 = (_i1 + 1))
        {
          int  _ct1093 = (((C + 1) < ((512 * _T_i2) + 515))? (C + 1): ((512 * _T_i2) + 515));
          int  _ct1094 = ((2 > ((512 * _T_i2) + 2))? 2: ((512 * _T_i2) + 2));
          #pragma ivdep
          for (int  _i2 = _ct1094; (_i2 <= _ct1093); _i2 = (_i2 + 1))
          {
            sharpen[_i0][((-8 * _T_i1) + _i1)][((-512 * _T_i2) + _i2)] = ((img[(((_i0 * ((R + 4) * (C + 4))) + (_i1 * (C + 4))) + _i2)] * (1 + weight)) + (blury[_i0][((-8 * _T_i1) + _i1)][((-512 * _T_i2) + _i2)] * -(weight)));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
      {
        int  _ct1095 = (((R + 1) < ((8 * _T_i1) + 7))? (R + 1): ((8 * _T_i1) + 7));
        int  _ct1096 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct1096; (_i1 <= _ct1095); _i1 = (_i1 + 1))
        {
          int  _ct1097 = (((C + 1) < ((512 * _T_i2) + 514))? (C + 1): ((512 * _T_i2) + 514));
          int  _ct1098 = ((2 > ((512 * _T_i2) + 3))? 2: ((512 * _T_i2) + 3));
          #pragma ivdep
          for (int  _i2 = _ct1098; (_i2 <= _ct1097); _i2 = (_i2 + 1))
          {
            float  _ct1099 = img[(((_i0 * ((R + 4) * (C + 4))) + (_i1 * (C + 4))) + _i2)];
            float  _ct1100 = sharpen[_i0][((-8 * _T_i1) + _i1)][((-512 * _T_i2) + _i2)];
            float  _ct1101 = ((std::abs((img[(((_i0 * ((R + 4) * (C + 4))) + (_i1 * (C + 4))) + _i2)] - blury[_i0][((-8 * _T_i1) + _i1)][((-512 * _T_i2) + _i2)])) < threshold)? _ct1099: _ct1100);
            mask[(((_i0 * (R * C)) + ((_i1 - 2) * C)) + (_i2 - 2))] = _ct1101;
          }
        }
      }
    }
  }
}
