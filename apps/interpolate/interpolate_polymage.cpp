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
extern "C" void  pipeline_interpolate(int  C, int  R, void * img_void_arg, void * interpolate_void_arg)
{
  float * img;
  img = (float *) (img_void_arg);
  float * interpolate;
  interpolate = (float *) (interpolate_void_arg);
  float * downsampled_L0;
  downsampled_L0 = (float *) (malloc((sizeof(float ) * ((4 * (2 + R)) * (2 + C)))));
  float * D_1_downsampled;
  D_1_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 2) + 1) + 1)) * (((C / 2) + 1) + 1)))));
  float * D_2_downsampled;
  D_2_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 4) + 1) + 1)) * (((C / 4) + 1) + 1)))));
  float * D_3_downsampled;
  D_3_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 8) + 1) + 1)) * (((C / 8) + 1) + 1)))));
  float * D_4_downsampled;
  D_4_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 16) + 1) + 1)) * (((C / 16) + 1) + 1)))));
  float * Dx_5_downsampled;
  Dx_5_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 32) + 1) + 1)) * (((C / 16) + 1) + 1)))));
  float * D_5_downsampled;
  D_5_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 32) + 1) + 1)) * (((C / 32) + 1) + 1)))));
  float * Dx_6_downsampled;
  Dx_6_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 64) + 1) + 1)) * (((C / 32) + 1) + 1)))));
  float * D_6_downsampled;
  D_6_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 64) + 1) + 1)) * (((C / 64) + 1) + 1)))));
  float * Dx_7_downsampled;
  Dx_7_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 128) + 1) + 1)) * (((C / 64) + 1) + 1)))));
  float * D_7_downsampled;
  D_7_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 128) + 1) + 1)) * (((C / 128) + 1) + 1)))));
  float * Dx_8_downsampled;
  Dx_8_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 256) + 1) + 1)) * (((C / 128) + 1) + 1)))));
  float * D_8_downsampled;
  D_8_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 256) + 1) + 1)) * (((C / 256) + 1) + 1)))));
  float * Dx_9_downsampled;
  Dx_9_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 512) + 1) + 1)) * (((C / 256) + 1) + 1)))));
  float * D_9_downsampled;
  D_9_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 512) + 1) + 1)) * (((C / 512) + 1) + 1)))));
  float * Ux_interpolated_L8;
  Ux_interpolated_L8 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 256) + 1) + 1)) * (((C / 512) + 1) + 1)))));
  float * interpolated_L8;
  interpolated_L8 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 256) + 1) + 1)) * (((C / 256) + 1) + 1)))));
  float * Ux_interpolated_L7;
  Ux_interpolated_L7 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 128) + 1) + 1)) * (((C / 256) + 1) + 1)))));
  float * interpolated_L7;
  interpolated_L7 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 128) + 1) + 1)) * (((C / 128) + 1) + 1)))));
  float * Ux_interpolated_L6;
  Ux_interpolated_L6 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 64) + 1) + 1)) * (((C / 128) + 1) + 1)))));
  float * interpolated_L6;
  interpolated_L6 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 64) + 1) + 1)) * (((C / 64) + 1) + 1)))));
  float * Ux_interpolated_L5;
  Ux_interpolated_L5 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 32) + 1) + 1)) * (((C / 64) + 1) + 1)))));
  float * interpolated_L5;
  interpolated_L5 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 32) + 1) + 1)) * (((C / 32) + 1) + 1)))));
  float * Ux_interpolated_L4;
  Ux_interpolated_L4 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 16) + 1) + 1)) * (((C / 32) + 1) + 1)))));
  float * interpolated_L4;
  interpolated_L4 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 16) + 1) + 1)) * (((C / 16) + 1) + 1)))));
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 2561); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 1537); _i2 = (_i2 + 1))
      {
        downsampled_L0[(((_i0 * ((2 + R) * (2 + C))) + (_i1 * (2 + C))) + _i2)] = (img[(((_i0 * ((R + 2) * (C + 2))) + (_i1 * (C + 2))) + _i2)] * img[(((3 * ((R + 2) * (C + 2))) + (_i1 * (C + 2))) + _i2)]);
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 40); _T_i1 = (_T_i1 + 1))
  {
    float * Dx_1_downsampled;
    Dx_1_downsampled = (float *) (malloc((sizeof(float ) * ((4 * 32) * 130))));
    for (int  _T_i2 = -1; (_T_i2 <= 12); _T_i2 = (_T_i2 + 1))
    {
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10007 = ((1281 < ((32 * _T_i1) + 31))? 1281: ((32 * _T_i1) + 31));
          for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10007); _i1 = (_i1 + 1))
          {
            D_1_downsampled[((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1)))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 == 12))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10008 = ((1281 < ((32 * _T_i1) + 31))? 1281: ((32 * _T_i1) + 31));
            for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10008); _i1 = (_i1 + 1))
            {
              D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + 769)] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 40))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10009 = ((769 < ((64 * _T_i2) + 64))? 769: ((64 * _T_i2) + 64));
          int  _ct10010 = ((0 > (64 * _T_i2))? 0: (64 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10010; (_i2 <= _ct10009); _i2 = (_i2 + 1))
          {
            D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (1281 * (((C / 2) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10011 = ((769 < ((64 * _T_i2) + 64))? 769: ((64 * _T_i2) + 64));
            int  _ct10012 = ((0 > (64 * _T_i2))? 0: (64 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10012; (_i2 <= _ct10011); _i2 = (_i2 + 1))
            {
              D_1_downsampled[((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct10013 = ((1280 < ((32 * _T_i1) + 31))? 1280: ((32 * _T_i1) + 31));
        int  _ct10014 = ((1 > (32 * _T_i1))? 1: (32 * _T_i1));
        for (int  _i1 = _ct10014; (_i1 <= _ct10013); _i1 = (_i1 + 1))
        {
          int  _ct10015 = ((1536 < ((128 * _T_i2) + 129))? 1536: ((128 * _T_i2) + 129));
          int  _ct10016 = ((1 > (128 * _T_i2))? 1: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10016; (_i2 <= _ct10015); _i2 = (_i2 + 1))
          {
            Dx_1_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + ((-128 * _T_i2) + _i2))] = (((downsampled_L0[(((_i0 * ((2 + R) * (2 + C))) + ((-2 + (2 * _i1)) * (2 + C))) + _i2)] + (2.0f * downsampled_L0[(((_i0 * ((2 + R) * (2 + C))) + ((-1 + (2 * _i1)) * (2 + C))) + _i2)])) + downsampled_L0[(((_i0 * ((2 + R) * (2 + C))) + ((2 * _i1) * (2 + C))) + _i2)]) * 0.25f);
          }
        }
      }
      if ((_T_i2 >= 11))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10017 = ((1281 < ((32 * _T_i1) + 31))? 1281: ((32 * _T_i1) + 31));
          for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10017); _i1 = (_i1 + 1))
          {
            Dx_1_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + ((-128 * _T_i2) + 1537))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10018 = ((1281 < ((32 * _T_i1) + 31))? 1281: ((32 * _T_i1) + 31));
            for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10018); _i1 = (_i1 + 1))
            {
              Dx_1_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (-128 * _T_i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 40))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10019 = ((1537 < ((128 * _T_i2) + 129))? 1537: ((128 * _T_i2) + 129));
          int  _ct10020 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10020; (_i2 <= _ct10019); _i2 = (_i2 + 1))
          {
            Dx_1_downsampled[(((_i0 * 4160) + 130) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10021 = ((1537 < ((128 * _T_i2) + 129))? 1537: ((128 * _T_i2) + 129));
            int  _ct10022 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10022; (_i2 <= _ct10021); _i2 = (_i2 + 1))
            {
              Dx_1_downsampled[((_i0 * 4160) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if (((_T_i2 <= 11) && (_T_i2 >= 0)))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10023 = ((1280 < ((32 * _T_i1) + 31))? 1280: ((32 * _T_i1) + 31));
          int  _ct10024 = ((1 > (32 * _T_i1))? 1: (32 * _T_i1));
          for (int  _i1 = _ct10024; (_i1 <= _ct10023); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = ((64 * _T_i2) + 1); (_i2 <= ((64 * _T_i2) + 64)); _i2 = (_i2 + 1))
            {
              D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + _i2)] = (((Dx_1_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (-2 + (2 * ((-64 * _T_i2) + _i2))))] + (2.0f * Dx_1_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (-1 + (2 * ((-64 * _T_i2) + _i2))))])) + Dx_1_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (2 * ((-64 * _T_i2) + _i2)))]) * 0.25f);
            }
          }
        }
      }
    }
    free(Dx_1_downsampled);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 20); _T_i1 = (_T_i1 + 1))
  {
    float * Dx_2_downsampled;
    Dx_2_downsampled = (float *) (malloc((sizeof(float ) * ((4 * 32) * 130))));
    for (int  _T_i2 = -1; (_T_i2 <= 6); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct10025 = ((640 < ((32 * _T_i1) + 31))? 640: ((32 * _T_i1) + 31));
        int  _ct10026 = ((1 > (32 * _T_i1))? 1: (32 * _T_i1));
        for (int  _i1 = _ct10026; (_i1 <= _ct10025); _i1 = (_i1 + 1))
        {
          int  _ct10027 = ((768 < ((128 * _T_i2) + 129))? 768: ((128 * _T_i2) + 129));
          int  _ct10028 = ((1 > (128 * _T_i2))? 1: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10028; (_i2 <= _ct10027); _i2 = (_i2 + 1))
          {
            Dx_2_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + ((-128 * _T_i2) + _i2))] = (((D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + ((-2 + (2 * _i1)) * (((C / 2) + 1) + 1))) + _i2)] + (2.0f * D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + ((-1 + (2 * _i1)) * (((C / 2) + 1) + 1))) + _i2)])) + D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + ((2 * _i1) * (((C / 2) + 1) + 1))) + _i2)]) * 0.25f);
          }
        }
      }
      if ((_T_i2 >= 5))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10029 = ((641 < ((32 * _T_i1) + 31))? 641: ((32 * _T_i1) + 31));
          for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10029); _i1 = (_i1 + 1))
          {
            Dx_2_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + ((-128 * _T_i2) + 769))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10030 = ((641 < ((32 * _T_i1) + 31))? 641: ((32 * _T_i1) + 31));
            for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10030); _i1 = (_i1 + 1))
            {
              Dx_2_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (-128 * _T_i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 20))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10031 = ((769 < ((128 * _T_i2) + 129))? 769: ((128 * _T_i2) + 129));
          int  _ct10032 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10032; (_i2 <= _ct10031); _i2 = (_i2 + 1))
          {
            Dx_2_downsampled[(((_i0 * 4160) + 130) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10033 = ((769 < ((128 * _T_i2) + 129))? 769: ((128 * _T_i2) + 129));
            int  _ct10034 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10034; (_i2 <= _ct10033); _i2 = (_i2 + 1))
            {
              Dx_2_downsampled[((_i0 * 4160) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10035 = ((641 < ((32 * _T_i1) + 31))? 641: ((32 * _T_i1) + 31));
          for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10035); _i1 = (_i1 + 1))
          {
            D_2_downsampled[((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1)))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 == 6))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10036 = ((641 < ((32 * _T_i1) + 31))? 641: ((32 * _T_i1) + 31));
            for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10036); _i1 = (_i1 + 1))
            {
              D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + 385)] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 20))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10037 = ((385 < ((64 * _T_i2) + 64))? 385: ((64 * _T_i2) + 64));
          int  _ct10038 = ((0 > (64 * _T_i2))? 0: (64 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10038; (_i2 <= _ct10037); _i2 = (_i2 + 1))
          {
            D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (641 * (((C / 4) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10039 = ((385 < ((64 * _T_i2) + 64))? 385: ((64 * _T_i2) + 64));
            int  _ct10040 = ((0 > (64 * _T_i2))? 0: (64 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10040; (_i2 <= _ct10039); _i2 = (_i2 + 1))
            {
              D_2_downsampled[((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      if (((_T_i2 <= 5) && (_T_i2 >= 0)))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10041 = ((640 < ((32 * _T_i1) + 31))? 640: ((32 * _T_i1) + 31));
          int  _ct10042 = ((1 > (32 * _T_i1))? 1: (32 * _T_i1));
          for (int  _i1 = _ct10042; (_i1 <= _ct10041); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = ((64 * _T_i2) + 1); (_i2 <= ((64 * _T_i2) + 64)); _i2 = (_i2 + 1))
            {
              D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + _i2)] = (((Dx_2_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (-2 + (2 * ((-64 * _T_i2) + _i2))))] + (2.0f * Dx_2_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (-1 + (2 * ((-64 * _T_i2) + _i2))))])) + Dx_2_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (2 * ((-64 * _T_i2) + _i2)))]) * 0.25f);
            }
          }
        }
      }
    }
    free(Dx_2_downsampled);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 10); _T_i1 = (_T_i1 + 1))
  {
    float * Dx_3_downsampled;
    Dx_3_downsampled = (float *) (malloc((sizeof(float ) * ((4 * 32) * 130))));
    for (int  _T_i2 = -1; (_T_i2 <= 3); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct10043 = ((320 < ((32 * _T_i1) + 31))? 320: ((32 * _T_i1) + 31));
        int  _ct10044 = ((1 > (32 * _T_i1))? 1: (32 * _T_i1));
        for (int  _i1 = _ct10044; (_i1 <= _ct10043); _i1 = (_i1 + 1))
        {
          int  _ct10045 = ((384 < ((128 * _T_i2) + 129))? 384: ((128 * _T_i2) + 129));
          int  _ct10046 = ((1 > (128 * _T_i2))? 1: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10046; (_i2 <= _ct10045); _i2 = (_i2 + 1))
          {
            Dx_3_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + ((-128 * _T_i2) + _i2))] = (((D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + ((-2 + (2 * _i1)) * (((C / 4) + 1) + 1))) + _i2)] + (2.0f * D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + ((-1 + (2 * _i1)) * (((C / 4) + 1) + 1))) + _i2)])) + D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + ((2 * _i1) * (((C / 4) + 1) + 1))) + _i2)]) * 0.25f);
          }
        }
      }
      if ((_T_i2 >= 2))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10047 = ((321 < ((32 * _T_i1) + 31))? 321: ((32 * _T_i1) + 31));
          for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10047); _i1 = (_i1 + 1))
          {
            Dx_3_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + ((-128 * _T_i2) + 385))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10048 = ((321 < ((32 * _T_i1) + 31))? 321: ((32 * _T_i1) + 31));
            for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10048); _i1 = (_i1 + 1))
            {
              Dx_3_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (-128 * _T_i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 10))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10049 = ((385 < ((128 * _T_i2) + 129))? 385: ((128 * _T_i2) + 129));
          int  _ct10050 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10050; (_i2 <= _ct10049); _i2 = (_i2 + 1))
          {
            Dx_3_downsampled[(((_i0 * 4160) + 130) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10051 = ((385 < ((128 * _T_i2) + 129))? 385: ((128 * _T_i2) + 129));
            int  _ct10052 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10052; (_i2 <= _ct10051); _i2 = (_i2 + 1))
            {
              Dx_3_downsampled[((_i0 * 4160) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10053 = ((321 < ((32 * _T_i1) + 31))? 321: ((32 * _T_i1) + 31));
          for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10053); _i1 = (_i1 + 1))
          {
            D_3_downsampled[((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1)))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 == 3))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10054 = ((321 < ((32 * _T_i1) + 31))? 321: ((32 * _T_i1) + 31));
            for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10054); _i1 = (_i1 + 1))
            {
              D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + 193)] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 10))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10055 = ((193 < ((64 * _T_i2) + 64))? 193: ((64 * _T_i2) + 64));
          int  _ct10056 = ((0 > (64 * _T_i2))? 0: (64 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10056; (_i2 <= _ct10055); _i2 = (_i2 + 1))
          {
            D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (321 * (((C / 8) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10057 = ((193 < ((64 * _T_i2) + 64))? 193: ((64 * _T_i2) + 64));
            int  _ct10058 = ((0 > (64 * _T_i2))? 0: (64 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10058; (_i2 <= _ct10057); _i2 = (_i2 + 1))
            {
              D_3_downsampled[((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      if (((_T_i2 <= 2) && (_T_i2 >= 0)))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10059 = ((320 < ((32 * _T_i1) + 31))? 320: ((32 * _T_i1) + 31));
          int  _ct10060 = ((1 > (32 * _T_i1))? 1: (32 * _T_i1));
          for (int  _i1 = _ct10060; (_i1 <= _ct10059); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = ((64 * _T_i2) + 1); (_i2 <= ((64 * _T_i2) + 64)); _i2 = (_i2 + 1))
            {
              D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + _i2)] = (((Dx_3_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (-2 + (2 * ((-64 * _T_i2) + _i2))))] + (2.0f * Dx_3_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (-1 + (2 * ((-64 * _T_i2) + _i2))))])) + Dx_3_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (2 * ((-64 * _T_i2) + _i2)))]) * 0.25f);
            }
          }
        }
      }
    }
    free(Dx_3_downsampled);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 5); _T_i1 = (_T_i1 + 1))
  {
    float * Dx_4_downsampled;
    Dx_4_downsampled = (float *) (malloc((sizeof(float ) * ((4 * 32) * 130))));
    for (int  _T_i2 = -1; (_T_i2 <= 1); _T_i2 = (_T_i2 + 1))
    {
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10061 = ((161 < ((32 * _T_i1) + 31))? 161: ((32 * _T_i1) + 31));
          for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10061); _i1 = (_i1 + 1))
          {
            D_4_downsampled[((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1)))] = 0;
          }
        }
      }
      else
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10062 = ((161 < ((32 * _T_i1) + 31))? 161: ((32 * _T_i1) + 31));
          for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10062); _i1 = (_i1 + 1))
          {
            D_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + 97)] = 0;
          }
        }
      }
      if ((_T_i1 == 5))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10063 = ((97 < ((64 * _T_i2) + 64))? 97: ((64 * _T_i2) + 64));
          int  _ct10064 = ((0 > (64 * _T_i2))? 0: (64 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10064; (_i2 <= _ct10063); _i2 = (_i2 + 1))
          {
            D_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (161 * (((C / 16) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10065 = ((97 < ((64 * _T_i2) + 64))? 97: ((64 * _T_i2) + 64));
            int  _ct10066 = ((0 > (64 * _T_i2))? 0: (64 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10066; (_i2 <= _ct10065); _i2 = (_i2 + 1))
            {
              D_4_downsampled[((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct10067 = ((160 < ((32 * _T_i1) + 31))? 160: ((32 * _T_i1) + 31));
        int  _ct10068 = ((1 > (32 * _T_i1))? 1: (32 * _T_i1));
        for (int  _i1 = _ct10068; (_i1 <= _ct10067); _i1 = (_i1 + 1))
        {
          int  _ct10069 = ((192 < ((128 * _T_i2) + 129))? 192: ((128 * _T_i2) + 129));
          int  _ct10070 = ((1 > (128 * _T_i2))? 1: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10070; (_i2 <= _ct10069); _i2 = (_i2 + 1))
          {
            Dx_4_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + ((-128 * _T_i2) + _i2))] = (((D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + ((-2 + (2 * _i1)) * (((C / 8) + 1) + 1))) + _i2)] + (2.0f * D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + ((-1 + (2 * _i1)) * (((C / 8) + 1) + 1))) + _i2)])) + D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + ((2 * _i1) * (((C / 8) + 1) + 1))) + _i2)]) * 0.25f);
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10071 = ((161 < ((32 * _T_i1) + 31))? 161: ((32 * _T_i1) + 31));
          for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10071); _i1 = (_i1 + 1))
          {
            Dx_4_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (-128 * _T_i2))] = 0;
          }
        }
      }
      else
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10072 = ((161 < ((32 * _T_i1) + 31))? 161: ((32 * _T_i1) + 31));
          for (int  _i1 = (32 * _T_i1); (_i1 <= _ct10072); _i1 = (_i1 + 1))
          {
            Dx_4_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + 65)] = 0;
          }
        }
      }
      if ((_T_i1 == 5))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10073 = ((193 < ((128 * _T_i2) + 129))? 193: ((128 * _T_i2) + 129));
          int  _ct10074 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10074; (_i2 <= _ct10073); _i2 = (_i2 + 1))
          {
            Dx_4_downsampled[(((_i0 * 4160) + 130) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10075 = ((193 < ((128 * _T_i2) + 129))? 193: ((128 * _T_i2) + 129));
            int  _ct10076 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10076; (_i2 <= _ct10075); _i2 = (_i2 + 1))
            {
              Dx_4_downsampled[((_i0 * 4160) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i2 >= 0))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10077 = ((160 < ((32 * _T_i1) + 31))? 160: ((32 * _T_i1) + 31));
          int  _ct10078 = ((1 > (32 * _T_i1))? 1: (32 * _T_i1));
          for (int  _i1 = _ct10078; (_i1 <= _ct10077); _i1 = (_i1 + 1))
          {
            int  _ct10079 = ((96 < ((64 * _T_i2) + 64))? 96: ((64 * _T_i2) + 64));
            #pragma ivdep
            for (int  _i2 = ((64 * _T_i2) + 1); (_i2 <= _ct10079); _i2 = (_i2 + 1))
            {
              D_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + _i2)] = (((Dx_4_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (-2 + (2 * ((-64 * _T_i2) + _i2))))] + (2.0f * Dx_4_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (-1 + (2 * ((-64 * _T_i2) + _i2))))])) + Dx_4_downsampled[(((_i0 * 4160) + (((-32 * _T_i1) + _i1) * 130)) + (2 * ((-64 * _T_i2) + _i2)))]) * 0.25f);
            }
          }
        }
      }
    }
    free(Dx_4_downsampled);
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 81); _i1 = (_i1 + 1))
    {
      Dx_5_downsampled[((_i0 * ((((R / 32) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1)))] = 0;
      if (((_i1 <= 80) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 96); _i2 = (_i2 + 1))
        {
          Dx_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + _i2)] = (((D_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + ((-2 + (2 * _i1)) * (((C / 16) + 1) + 1))) + _i2)] + (2.0f * D_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + ((-1 + (2 * _i1)) * (((C / 16) + 1) + 1))) + _i2)])) + D_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + ((2 * _i1) * (((C / 16) + 1) + 1))) + _i2)]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 81))
        {
          for (int  _i2 = 0; (_i2 <= 97); _i2 = (_i2 + 1))
          {
            Dx_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 16) + 1) + 1))) + (81 * (((C / 16) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 97); _i2 = (_i2 + 1))
          {
            Dx_5_downsampled[((_i0 * ((((R / 32) + 1) + 1) * (((C / 16) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Dx_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + 97)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 81); _i1 = (_i1 + 1))
    {
      D_5_downsampled[((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1)))] = 0;
      if (((_i1 <= 80) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 48); _i2 = (_i2 + 1))
        {
          D_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + _i2)] = (((Dx_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + (-2 + (2 * _i2)))] + (2.0f * Dx_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + (-1 + (2 * _i2)))])) + Dx_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + (2 * _i2))]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 81))
        {
          for (int  _i2 = 0; (_i2 <= 49); _i2 = (_i2 + 1))
          {
            D_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + (81 * (((C / 32) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 49); _i2 = (_i2 + 1))
          {
            D_5_downsampled[((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      D_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + 49)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 41); _i1 = (_i1 + 1))
    {
      Dx_6_downsampled[((_i0 * ((((R / 64) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1)))] = 0;
      if (((_i1 <= 40) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 48); _i2 = (_i2 + 1))
        {
          Dx_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + _i2)] = (((D_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + ((-2 + (2 * _i1)) * (((C / 32) + 1) + 1))) + _i2)] + (2.0f * D_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + ((-1 + (2 * _i1)) * (((C / 32) + 1) + 1))) + _i2)])) + D_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + ((2 * _i1) * (((C / 32) + 1) + 1))) + _i2)]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 41))
        {
          for (int  _i2 = 0; (_i2 <= 49); _i2 = (_i2 + 1))
          {
            Dx_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 32) + 1) + 1))) + (41 * (((C / 32) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 49); _i2 = (_i2 + 1))
          {
            Dx_6_downsampled[((_i0 * ((((R / 64) + 1) + 1) * (((C / 32) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Dx_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + 49)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 41); _i1 = (_i1 + 1))
    {
      D_6_downsampled[((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1)))] = 0;
      if (((_i1 <= 40) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 24); _i2 = (_i2 + 1))
        {
          D_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + _i2)] = (((Dx_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + (-2 + (2 * _i2)))] + (2.0f * Dx_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + (-1 + (2 * _i2)))])) + Dx_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + (2 * _i2))]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 41))
        {
          for (int  _i2 = 0; (_i2 <= 25); _i2 = (_i2 + 1))
          {
            D_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + (41 * (((C / 64) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 25); _i2 = (_i2 + 1))
          {
            D_6_downsampled[((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      D_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + 25)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 21); _i1 = (_i1 + 1))
    {
      Dx_7_downsampled[((_i0 * ((((R / 128) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1)))] = 0;
      if (((_i1 <= 20) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 24); _i2 = (_i2 + 1))
        {
          Dx_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + _i2)] = (((D_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + ((-2 + (2 * _i1)) * (((C / 64) + 1) + 1))) + _i2)] + (2.0f * D_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + ((-1 + (2 * _i1)) * (((C / 64) + 1) + 1))) + _i2)])) + D_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + ((2 * _i1) * (((C / 64) + 1) + 1))) + _i2)]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 21))
        {
          for (int  _i2 = 0; (_i2 <= 25); _i2 = (_i2 + 1))
          {
            Dx_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 64) + 1) + 1))) + (21 * (((C / 64) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 25); _i2 = (_i2 + 1))
          {
            Dx_7_downsampled[((_i0 * ((((R / 128) + 1) + 1) * (((C / 64) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Dx_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + 25)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 21); _i1 = (_i1 + 1))
    {
      D_7_downsampled[((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1)))] = 0;
      if (((_i1 <= 20) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 12); _i2 = (_i2 + 1))
        {
          D_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + _i2)] = (((Dx_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + (-2 + (2 * _i2)))] + (2.0f * Dx_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + (-1 + (2 * _i2)))])) + Dx_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + (2 * _i2))]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 21))
        {
          for (int  _i2 = 0; (_i2 <= 13); _i2 = (_i2 + 1))
          {
            D_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + (21 * (((C / 128) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 13); _i2 = (_i2 + 1))
          {
            D_7_downsampled[((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      D_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + 13)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 11); _i1 = (_i1 + 1))
    {
      Dx_8_downsampled[((_i0 * ((((R / 256) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1)))] = 0;
      if (((_i1 <= 10) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 12); _i2 = (_i2 + 1))
        {
          Dx_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + _i2)] = (((D_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + ((-2 + (2 * _i1)) * (((C / 128) + 1) + 1))) + _i2)] + (2.0f * D_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + ((-1 + (2 * _i1)) * (((C / 128) + 1) + 1))) + _i2)])) + D_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + ((2 * _i1) * (((C / 128) + 1) + 1))) + _i2)]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 11))
        {
          for (int  _i2 = 0; (_i2 <= 13); _i2 = (_i2 + 1))
          {
            Dx_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 128) + 1) + 1))) + (11 * (((C / 128) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 13); _i2 = (_i2 + 1))
          {
            Dx_8_downsampled[((_i0 * ((((R / 256) + 1) + 1) * (((C / 128) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Dx_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + 13)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 11); _i1 = (_i1 + 1))
    {
      D_8_downsampled[((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1)))] = 0;
      if (((_i1 <= 10) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 6); _i2 = (_i2 + 1))
        {
          D_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + _i2)] = (((Dx_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + (-2 + (2 * _i2)))] + (2.0f * Dx_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + (-1 + (2 * _i2)))])) + Dx_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + (2 * _i2))]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 11))
        {
          for (int  _i2 = 0; (_i2 <= 7); _i2 = (_i2 + 1))
          {
            D_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + (11 * (((C / 256) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 7); _i2 = (_i2 + 1))
          {
            D_8_downsampled[((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      D_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + 7)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 6); _i1 = (_i1 + 1))
    {
      Dx_9_downsampled[((_i0 * ((((R / 512) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1)))] = 0;
      if (((_i1 <= 5) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 6); _i2 = (_i2 + 1))
        {
          Dx_9_downsampled[(((_i0 * ((((R / 512) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + _i2)] = (((D_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + ((-2 + (2 * _i1)) * (((C / 256) + 1) + 1))) + _i2)] + (2.0f * D_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + ((-1 + (2 * _i1)) * (((C / 256) + 1) + 1))) + _i2)])) + D_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + ((2 * _i1) * (((C / 256) + 1) + 1))) + _i2)]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 6))
        {
          for (int  _i2 = 0; (_i2 <= 7); _i2 = (_i2 + 1))
          {
            Dx_9_downsampled[(((_i0 * ((((R / 512) + 1) + 1) * (((C / 256) + 1) + 1))) + (6 * (((C / 256) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 7); _i2 = (_i2 + 1))
          {
            Dx_9_downsampled[((_i0 * ((((R / 512) + 1) + 1) * (((C / 256) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Dx_9_downsampled[(((_i0 * ((((R / 512) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + 7)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 6); _i1 = (_i1 + 1))
    {
      D_9_downsampled[((_i0 * ((((R / 512) + 1) + 1) * (((C / 512) + 1) + 1))) + (_i1 * (((C / 512) + 1) + 1)))] = 0;
      if (((_i1 <= 5) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 3); _i2 = (_i2 + 1))
        {
          D_9_downsampled[(((_i0 * ((((R / 512) + 1) + 1) * (((C / 512) + 1) + 1))) + (_i1 * (((C / 512) + 1) + 1))) + _i2)] = (((Dx_9_downsampled[(((_i0 * ((((R / 512) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + (-2 + (2 * _i2)))] + (2.0f * Dx_9_downsampled[(((_i0 * ((((R / 512) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + (-1 + (2 * _i2)))])) + Dx_9_downsampled[(((_i0 * ((((R / 512) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + (2 * _i2))]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 6))
        {
          for (int  _i2 = 0; (_i2 <= 4); _i2 = (_i2 + 1))
          {
            D_9_downsampled[(((_i0 * ((((R / 512) + 1) + 1) * (((C / 512) + 1) + 1))) + (6 * (((C / 512) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 4); _i2 = (_i2 + 1))
          {
            D_9_downsampled[((_i0 * ((((R / 512) + 1) + 1) * (((C / 512) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      D_9_downsampled[(((_i0 * ((((R / 512) + 1) + 1) * (((C / 512) + 1) + 1))) + (_i1 * (((C / 512) + 1) + 1))) + 4)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 11); _i1 = (_i1 + 1))
    {
      Ux_interpolated_L8[((_i0 * ((((R / 256) + 1) + 1) * (((C / 512) + 1) + 1))) + (_i1 * (((C / 512) + 1) + 1)))] = 0;
      if (((_i1 <= 10) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 3); _i2 = (_i2 + 1))
        {
          Ux_interpolated_L8[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 512) + 1) + 1))) + (_i1 * (((C / 512) + 1) + 1))) + _i2)] = ((D_9_downsampled[(((_i0 * ((((R / 512) + 1) + 1) * (((C / 512) + 1) + 1))) + (((_i1 + 1) / 2) * (((C / 512) + 1) + 1))) + _i2)] + D_9_downsampled[(((_i0 * ((((R / 512) + 1) + 1) * (((C / 512) + 1) + 1))) + (((_i1 + 2) / 2) * (((C / 512) + 1) + 1))) + _i2)]) / 2.0f);
        }
      }
      else
      {
        if ((_i1 == 11))
        {
          for (int  _i2 = 0; (_i2 <= 4); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L8[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 512) + 1) + 1))) + (11 * (((C / 512) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 4); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L8[((_i0 * ((((R / 256) + 1) + 1) * (((C / 512) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Ux_interpolated_L8[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 512) + 1) + 1))) + (_i1 * (((C / 512) + 1) + 1))) + 4)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 11); _i1 = (_i1 + 1))
    {
      interpolated_L8[((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1)))] = 0;
      if (((_i1 <= 10) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 6); _i2 = (_i2 + 1))
        {
          interpolated_L8[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + _i2)] = (D_8_downsampled[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + _i2)] + ((1.0f - D_8_downsampled[(((3 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + _i2)]) * ((Ux_interpolated_L8[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 512) + 1) + 1))) + (_i1 * (((C / 512) + 1) + 1))) + ((_i2 + 1) / 2))] + Ux_interpolated_L8[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 512) + 1) + 1))) + (_i1 * (((C / 512) + 1) + 1))) + ((_i2 + 2) / 2))]) / 2.0f)));
        }
      }
      else
      {
        if ((_i1 == 11))
        {
          for (int  _i2 = 0; (_i2 <= 7); _i2 = (_i2 + 1))
          {
            interpolated_L8[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + (11 * (((C / 256) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 7); _i2 = (_i2 + 1))
          {
            interpolated_L8[((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      interpolated_L8[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + 7)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 21); _i1 = (_i1 + 1))
    {
      Ux_interpolated_L7[((_i0 * ((((R / 128) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1)))] = 0;
      if (((_i1 <= 20) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 6); _i2 = (_i2 + 1))
        {
          Ux_interpolated_L7[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + _i2)] = ((interpolated_L8[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + (((_i1 + 1) / 2) * (((C / 256) + 1) + 1))) + _i2)] + interpolated_L8[(((_i0 * ((((R / 256) + 1) + 1) * (((C / 256) + 1) + 1))) + (((_i1 + 2) / 2) * (((C / 256) + 1) + 1))) + _i2)]) / 2.0f);
        }
      }
      else
      {
        if ((_i1 == 21))
        {
          for (int  _i2 = 0; (_i2 <= 7); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L7[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 256) + 1) + 1))) + (21 * (((C / 256) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 7); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L7[((_i0 * ((((R / 128) + 1) + 1) * (((C / 256) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Ux_interpolated_L7[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + 7)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 21); _i1 = (_i1 + 1))
    {
      interpolated_L7[((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1)))] = 0;
      if (((_i1 <= 20) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 12); _i2 = (_i2 + 1))
        {
          interpolated_L7[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + _i2)] = (D_7_downsampled[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + _i2)] + ((1.0f - D_7_downsampled[(((3 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + _i2)]) * ((Ux_interpolated_L7[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + ((_i2 + 1) / 2))] + Ux_interpolated_L7[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 256) + 1) + 1))) + (_i1 * (((C / 256) + 1) + 1))) + ((_i2 + 2) / 2))]) / 2.0f)));
        }
      }
      else
      {
        if ((_i1 == 21))
        {
          for (int  _i2 = 0; (_i2 <= 13); _i2 = (_i2 + 1))
          {
            interpolated_L7[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + (21 * (((C / 128) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 13); _i2 = (_i2 + 1))
          {
            interpolated_L7[((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      interpolated_L7[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + 13)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 41); _i1 = (_i1 + 1))
    {
      Ux_interpolated_L6[((_i0 * ((((R / 64) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1)))] = 0;
      if (((_i1 <= 40) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 12); _i2 = (_i2 + 1))
        {
          Ux_interpolated_L6[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + _i2)] = ((interpolated_L7[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + (((_i1 + 1) / 2) * (((C / 128) + 1) + 1))) + _i2)] + interpolated_L7[(((_i0 * ((((R / 128) + 1) + 1) * (((C / 128) + 1) + 1))) + (((_i1 + 2) / 2) * (((C / 128) + 1) + 1))) + _i2)]) / 2.0f);
        }
      }
      else
      {
        if ((_i1 == 41))
        {
          for (int  _i2 = 0; (_i2 <= 13); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L6[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 128) + 1) + 1))) + (41 * (((C / 128) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 13); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L6[((_i0 * ((((R / 64) + 1) + 1) * (((C / 128) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Ux_interpolated_L6[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + 13)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 41); _i1 = (_i1 + 1))
    {
      interpolated_L6[((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1)))] = 0;
      if (((_i1 <= 40) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 24); _i2 = (_i2 + 1))
        {
          interpolated_L6[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + _i2)] = (D_6_downsampled[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + _i2)] + ((1.0f - D_6_downsampled[(((3 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + _i2)]) * ((Ux_interpolated_L6[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + ((_i2 + 1) / 2))] + Ux_interpolated_L6[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 128) + 1) + 1))) + (_i1 * (((C / 128) + 1) + 1))) + ((_i2 + 2) / 2))]) / 2.0f)));
        }
      }
      else
      {
        if ((_i1 == 41))
        {
          for (int  _i2 = 0; (_i2 <= 25); _i2 = (_i2 + 1))
          {
            interpolated_L6[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + (41 * (((C / 64) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 25); _i2 = (_i2 + 1))
          {
            interpolated_L6[((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      interpolated_L6[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + 25)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 81); _i1 = (_i1 + 1))
    {
      Ux_interpolated_L5[((_i0 * ((((R / 32) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1)))] = 0;
      if (((_i1 <= 80) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 24); _i2 = (_i2 + 1))
        {
          Ux_interpolated_L5[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + _i2)] = ((interpolated_L6[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + (((_i1 + 1) / 2) * (((C / 64) + 1) + 1))) + _i2)] + interpolated_L6[(((_i0 * ((((R / 64) + 1) + 1) * (((C / 64) + 1) + 1))) + (((_i1 + 2) / 2) * (((C / 64) + 1) + 1))) + _i2)]) / 2.0f);
        }
      }
      else
      {
        if ((_i1 == 81))
        {
          for (int  _i2 = 0; (_i2 <= 25); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L5[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 64) + 1) + 1))) + (81 * (((C / 64) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 25); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L5[((_i0 * ((((R / 32) + 1) + 1) * (((C / 64) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Ux_interpolated_L5[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + 25)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 81); _i1 = (_i1 + 1))
    {
      interpolated_L5[((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1)))] = 0;
      if (((_i1 <= 80) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 48); _i2 = (_i2 + 1))
        {
          interpolated_L5[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + _i2)] = (D_5_downsampled[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + _i2)] + ((1.0f - D_5_downsampled[(((3 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + _i2)]) * ((Ux_interpolated_L5[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + ((_i2 + 1) / 2))] + Ux_interpolated_L5[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 64) + 1) + 1))) + (_i1 * (((C / 64) + 1) + 1))) + ((_i2 + 2) / 2))]) / 2.0f)));
        }
      }
      else
      {
        if ((_i1 == 81))
        {
          for (int  _i2 = 0; (_i2 <= 49); _i2 = (_i2 + 1))
          {
            interpolated_L5[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + (81 * (((C / 32) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 49); _i2 = (_i2 + 1))
          {
            interpolated_L5[((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      interpolated_L5[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + 49)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 161); _i1 = (_i1 + 1))
    {
      Ux_interpolated_L4[((_i0 * ((((R / 16) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1)))] = 0;
      if (((_i1 <= 160) && (_i1 >= 1)))
      {
        for (int  _i2 = 1; (_i2 <= 48); _i2 = (_i2 + 1))
        {
          Ux_interpolated_L4[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + _i2)] = ((interpolated_L5[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + (((_i1 + 1) / 2) * (((C / 32) + 1) + 1))) + _i2)] + interpolated_L5[(((_i0 * ((((R / 32) + 1) + 1) * (((C / 32) + 1) + 1))) + (((_i1 + 2) / 2) * (((C / 32) + 1) + 1))) + _i2)]) / 2.0f);
        }
      }
      else
      {
        if ((_i1 == 161))
        {
          for (int  _i2 = 0; (_i2 <= 49); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L4[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 32) + 1) + 1))) + (161 * (((C / 32) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 49); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L4[((_i0 * ((((R / 16) + 1) + 1) * (((C / 32) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Ux_interpolated_L4[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + 49)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 161); _i1 = (_i1 + 1))
    {
      interpolated_L4[((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1)))] = 0;
      if (((_i1 <= 160) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 96); _i2 = (_i2 + 1))
        {
          interpolated_L4[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + _i2)] = (D_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + _i2)] + ((1.0f - D_4_downsampled[(((3 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + _i2)]) * ((Ux_interpolated_L4[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + ((_i2 + 1) / 2))] + Ux_interpolated_L4[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 32) + 1) + 1))) + (_i1 * (((C / 32) + 1) + 1))) + ((_i2 + 2) / 2))]) / 2.0f)));
        }
      }
      else
      {
        if ((_i1 == 161))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 97); _i2 = (_i2 + 1))
          {
            interpolated_L4[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (161 * (((C / 16) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 97); _i2 = (_i2 + 1))
          {
            interpolated_L4[((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      interpolated_L4[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + 97)] = 0;
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = -1; (_T_i1 <= 80); _T_i1 = (_T_i1 + 1))
  {
    float * Ux_interpolated_L3;
    Ux_interpolated_L3 = (float *) (malloc((sizeof(float ) * ((4 * 7) * 10))));
    float * interpolated_L2;
    interpolated_L2 = (float *) (malloc((sizeof(float ) * ((4 * 14) * 40))));
    float * Ux_interpolated_L2;
    Ux_interpolated_L2 = (float *) (malloc((sizeof(float ) * ((4 * 14) * 20))));
    float * interpolated_L1;
    interpolated_L1 = (float *) (malloc((sizeof(float ) * ((4 * 28) * 80))));
    float * interpolated_L0;
    interpolated_L0 = (float *) (malloc((sizeof(float ) * ((4 * 56) * 160))));
    float * interpolated_L3;
    interpolated_L3 = (float *) (malloc((sizeof(float ) * ((4 * 7) * 20))));
    float * Ux_interpolated_L0;
    Ux_interpolated_L0 = (float *) (malloc((sizeof(float ) * ((4 * 56) * 80))));
    float * Ux_interpolated_L1;
    Ux_interpolated_L1 = (float *) (malloc((sizeof(float ) * ((4 * 28) * 40))));
    for (int  _T_i2 = -1; (_T_i2 <= 12); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct10080 = ((320 < ((4 * _T_i1) + 6))? 320: ((4 * _T_i1) + 6));
        int  _ct10081 = ((1 > (4 * _T_i1))? 1: (4 * _T_i1));
        for (int  _i1 = _ct10081; (_i1 <= _ct10080); _i1 = (_i1 + 1))
        {
          int  _ct10082 = ((96 < ((8 * _T_i2) + 9))? 96: ((8 * _T_i2) + 9));
          int  _ct10083 = ((1 > (8 * _T_i2))? 1: (8 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10083; (_i2 <= _ct10082); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L3[(((_i0 * 70) + (((-4 * _T_i1) + _i1) * 10)) + ((-8 * _T_i2) + _i2))] = ((interpolated_L4[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (((_i1 + 1) / 2) * (((C / 16) + 1) + 1))) + _i2)] + interpolated_L4[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (((_i1 + 2) / 2) * (((C / 16) + 1) + 1))) + _i2)]) / 2.0f);
          }
        }
      }
      if ((_T_i2 >= 11))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10084 = ((321 < ((4 * _T_i1) + 6))? 321: ((4 * _T_i1) + 6));
          int  _ct10085 = ((0 > (4 * _T_i1))? 0: (4 * _T_i1));
          for (int  _i1 = _ct10085; (_i1 <= _ct10084); _i1 = (_i1 + 1))
          {
            Ux_interpolated_L3[(((_i0 * 70) + (((-4 * _T_i1) + _i1) * 10)) + ((-8 * _T_i2) + 97))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10086 = ((321 < ((4 * _T_i1) + 6))? 321: ((4 * _T_i1) + 6));
            int  _ct10087 = ((0 > (4 * _T_i1))? 0: (4 * _T_i1));
            for (int  _i1 = _ct10087; (_i1 <= _ct10086); _i1 = (_i1 + 1))
            {
              Ux_interpolated_L3[(((_i0 * 70) + (((-4 * _T_i1) + _i1) * 10)) + (-8 * _T_i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 >= 79))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10088 = ((97 < ((8 * _T_i2) + 9))? 97: ((8 * _T_i2) + 9));
          int  _ct10089 = ((0 > (8 * _T_i2))? 0: (8 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10089; (_i2 <= _ct10088); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L3[(((_i0 * 70) + (((-4 * _T_i1) + 321) * 10)) + ((-8 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10090 = ((97 < ((8 * _T_i2) + 9))? 97: ((8 * _T_i2) + 9));
            int  _ct10091 = ((0 > (8 * _T_i2))? 0: (8 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10091; (_i2 <= _ct10090); _i2 = (_i2 + 1))
            {
              Ux_interpolated_L3[(((_i0 * 70) + ((-4 * _T_i1) * 10)) + ((-8 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i2 >= 11))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10092 = ((641 < ((8 * _T_i1) + 13))? 641: ((8 * _T_i1) + 13));
          int  _ct10093 = ((0 > (8 * _T_i1))? 0: (8 * _T_i1));
          for (int  _i1 = _ct10093; (_i1 <= _ct10092); _i1 = (_i1 + 1))
          {
            interpolated_L2[(((_i0 * 560) + (((-8 * _T_i1) + _i1) * 40)) + ((-32 * _T_i2) + 385))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10094 = ((641 < ((8 * _T_i1) + 13))? 641: ((8 * _T_i1) + 13));
            int  _ct10095 = ((0 > (8 * _T_i1))? 0: (8 * _T_i1));
            for (int  _i1 = _ct10095; (_i1 <= _ct10094); _i1 = (_i1 + 1))
            {
              interpolated_L2[(((_i0 * 560) + (((-8 * _T_i1) + _i1) * 40)) + (-32 * _T_i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 >= 79))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10096 = ((385 < ((32 * _T_i2) + 39))? 385: ((32 * _T_i2) + 39));
          int  _ct10097 = ((0 > (32 * _T_i2))? 0: (32 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10097; (_i2 <= _ct10096); _i2 = (_i2 + 1))
          {
            interpolated_L2[(((_i0 * 560) + (((-8 * _T_i1) + 641) * 40)) + ((-32 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10098 = ((385 < ((32 * _T_i2) + 39))? 385: ((32 * _T_i2) + 39));
            int  _ct10099 = ((0 > (32 * _T_i2))? 0: (32 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10099; (_i2 <= _ct10098); _i2 = (_i2 + 1))
            {
              interpolated_L2[(((_i0 * 560) + ((-8 * _T_i1) * 40)) + ((-32 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i2 >= 11))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10100 = ((641 < ((8 * _T_i1) + 13))? 641: ((8 * _T_i1) + 13));
          int  _ct10101 = ((0 > (8 * _T_i1))? 0: (8 * _T_i1));
          for (int  _i1 = _ct10101; (_i1 <= _ct10100); _i1 = (_i1 + 1))
          {
            Ux_interpolated_L2[(((_i0 * 280) + (((-8 * _T_i1) + _i1) * 20)) + ((-16 * _T_i2) + 193))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10102 = ((641 < ((8 * _T_i1) + 13))? 641: ((8 * _T_i1) + 13));
            int  _ct10103 = ((0 > (8 * _T_i1))? 0: (8 * _T_i1));
            for (int  _i1 = _ct10103; (_i1 <= _ct10102); _i1 = (_i1 + 1))
            {
              Ux_interpolated_L2[(((_i0 * 280) + (((-8 * _T_i1) + _i1) * 20)) + (-16 * _T_i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 >= 79))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10104 = ((193 < ((16 * _T_i2) + 19))? 193: ((16 * _T_i2) + 19));
          int  _ct10105 = ((0 > (16 * _T_i2))? 0: (16 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10105; (_i2 <= _ct10104); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L2[(((_i0 * 280) + (((-8 * _T_i1) + 641) * 20)) + ((-16 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10106 = ((193 < ((16 * _T_i2) + 19))? 193: ((16 * _T_i2) + 19));
            int  _ct10107 = ((0 > (16 * _T_i2))? 0: (16 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10107; (_i2 <= _ct10106); _i2 = (_i2 + 1))
            {
              Ux_interpolated_L2[(((_i0 * 280) + ((-8 * _T_i1) * 20)) + ((-16 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i2 >= 11))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10108 = ((1281 < ((16 * _T_i1) + 27))? 1281: ((16 * _T_i1) + 27));
          int  _ct10109 = ((0 > (16 * _T_i1))? 0: (16 * _T_i1));
          for (int  _i1 = _ct10109; (_i1 <= _ct10108); _i1 = (_i1 + 1))
          {
            interpolated_L1[(((_i0 * 2240) + (((-16 * _T_i1) + _i1) * 80)) + ((-64 * _T_i2) + 769))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10110 = ((1281 < ((16 * _T_i1) + 27))? 1281: ((16 * _T_i1) + 27));
            int  _ct10111 = ((0 > (16 * _T_i1))? 0: (16 * _T_i1));
            for (int  _i1 = _ct10111; (_i1 <= _ct10110); _i1 = (_i1 + 1))
            {
              interpolated_L1[(((_i0 * 2240) + (((-16 * _T_i1) + _i1) * 80)) + (-64 * _T_i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 >= 79))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10112 = ((769 < ((64 * _T_i2) + 79))? 769: ((64 * _T_i2) + 79));
          int  _ct10113 = ((0 > (64 * _T_i2))? 0: (64 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10113; (_i2 <= _ct10112); _i2 = (_i2 + 1))
          {
            interpolated_L1[(((_i0 * 2240) + (((-16 * _T_i1) + 1281) * 80)) + ((-64 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10114 = ((769 < ((64 * _T_i2) + 79))? 769: ((64 * _T_i2) + 79));
            int  _ct10115 = ((0 > (64 * _T_i2))? 0: (64 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10115; (_i2 <= _ct10114); _i2 = (_i2 + 1))
            {
              interpolated_L1[(((_i0 * 2240) + ((-16 * _T_i1) * 80)) + ((-64 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i2 >= 11))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10116 = ((2561 < ((32 * _T_i1) + 55))? 2561: ((32 * _T_i1) + 55));
          int  _ct10117 = ((0 > (32 * _T_i1))? 0: (32 * _T_i1));
          for (int  _i1 = _ct10117; (_i1 <= _ct10116); _i1 = (_i1 + 1))
          {
            interpolated_L0[(((_i0 * 8960) + (((-32 * _T_i1) + _i1) * 160)) + ((-128 * _T_i2) + 1537))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10118 = ((2561 < ((32 * _T_i1) + 55))? 2561: ((32 * _T_i1) + 55));
            int  _ct10119 = ((0 > (32 * _T_i1))? 0: (32 * _T_i1));
            for (int  _i1 = _ct10119; (_i1 <= _ct10118); _i1 = (_i1 + 1))
            {
              interpolated_L0[(((_i0 * 8960) + (((-32 * _T_i1) + _i1) * 160)) + (-128 * _T_i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 >= 79))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10120 = ((1537 < ((128 * _T_i2) + 159))? 1537: ((128 * _T_i2) + 159));
          int  _ct10121 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10121; (_i2 <= _ct10120); _i2 = (_i2 + 1))
          {
            interpolated_L0[(((_i0 * 8960) + (((-32 * _T_i1) + 2561) * 160)) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10122 = ((1537 < ((128 * _T_i2) + 159))? 1537: ((128 * _T_i2) + 159));
            int  _ct10123 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10123; (_i2 <= _ct10122); _i2 = (_i2 + 1))
            {
              interpolated_L0[(((_i0 * 8960) + ((-32 * _T_i1) * 160)) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i2 >= 11))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10124 = ((321 < ((4 * _T_i1) + 6))? 321: ((4 * _T_i1) + 6));
          int  _ct10125 = ((0 > (4 * _T_i1))? 0: (4 * _T_i1));
          for (int  _i1 = _ct10125; (_i1 <= _ct10124); _i1 = (_i1 + 1))
          {
            interpolated_L3[(((_i0 * 140) + (((-4 * _T_i1) + _i1) * 20)) + ((-16 * _T_i2) + 193))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10126 = ((321 < ((4 * _T_i1) + 6))? 321: ((4 * _T_i1) + 6));
            int  _ct10127 = ((0 > (4 * _T_i1))? 0: (4 * _T_i1));
            for (int  _i1 = _ct10127; (_i1 <= _ct10126); _i1 = (_i1 + 1))
            {
              interpolated_L3[(((_i0 * 140) + (((-4 * _T_i1) + _i1) * 20)) + (-16 * _T_i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 >= 79))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10128 = ((193 < ((16 * _T_i2) + 19))? 193: ((16 * _T_i2) + 19));
          int  _ct10129 = ((0 > (16 * _T_i2))? 0: (16 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10129; (_i2 <= _ct10128); _i2 = (_i2 + 1))
          {
            interpolated_L3[(((_i0 * 140) + (((-4 * _T_i1) + 321) * 20)) + ((-16 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10130 = ((193 < ((16 * _T_i2) + 19))? 193: ((16 * _T_i2) + 19));
            int  _ct10131 = ((0 > (16 * _T_i2))? 0: (16 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10131; (_i2 <= _ct10130); _i2 = (_i2 + 1))
            {
              interpolated_L3[(((_i0 * 140) + ((-4 * _T_i1) * 20)) + ((-16 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i2 >= 11))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10132 = ((2561 < ((32 * _T_i1) + 55))? 2561: ((32 * _T_i1) + 55));
          int  _ct10133 = ((0 > (32 * _T_i1))? 0: (32 * _T_i1));
          for (int  _i1 = _ct10133; (_i1 <= _ct10132); _i1 = (_i1 + 1))
          {
            Ux_interpolated_L0[(((_i0 * 4480) + (((-32 * _T_i1) + _i1) * 80)) + ((-64 * _T_i2) + 769))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10134 = ((2561 < ((32 * _T_i1) + 55))? 2561: ((32 * _T_i1) + 55));
            int  _ct10135 = ((0 > (32 * _T_i1))? 0: (32 * _T_i1));
            for (int  _i1 = _ct10135; (_i1 <= _ct10134); _i1 = (_i1 + 1))
            {
              Ux_interpolated_L0[(((_i0 * 4480) + (((-32 * _T_i1) + _i1) * 80)) + (-64 * _T_i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 >= 79))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10136 = ((769 < ((64 * _T_i2) + 79))? 769: ((64 * _T_i2) + 79));
          int  _ct10137 = ((0 > (64 * _T_i2))? 0: (64 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10137; (_i2 <= _ct10136); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L0[(((_i0 * 4480) + (((-32 * _T_i1) + 2561) * 80)) + ((-64 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10138 = ((769 < ((64 * _T_i2) + 79))? 769: ((64 * _T_i2) + 79));
            int  _ct10139 = ((0 > (64 * _T_i2))? 0: (64 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10139; (_i2 <= _ct10138); _i2 = (_i2 + 1))
            {
              Ux_interpolated_L0[(((_i0 * 4480) + ((-32 * _T_i1) * 80)) + ((-64 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i2 >= 11))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10140 = ((1281 < ((16 * _T_i1) + 27))? 1281: ((16 * _T_i1) + 27));
          int  _ct10141 = ((0 > (16 * _T_i1))? 0: (16 * _T_i1));
          for (int  _i1 = _ct10141; (_i1 <= _ct10140); _i1 = (_i1 + 1))
          {
            Ux_interpolated_L1[(((_i0 * 1120) + (((-16 * _T_i1) + _i1) * 40)) + ((-32 * _T_i2) + 385))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10142 = ((1281 < ((16 * _T_i1) + 27))? 1281: ((16 * _T_i1) + 27));
            int  _ct10143 = ((0 > (16 * _T_i1))? 0: (16 * _T_i1));
            for (int  _i1 = _ct10143; (_i1 <= _ct10142); _i1 = (_i1 + 1))
            {
              Ux_interpolated_L1[(((_i0 * 1120) + (((-16 * _T_i1) + _i1) * 40)) + (-32 * _T_i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 >= 79))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct10144 = ((385 < ((32 * _T_i2) + 39))? 385: ((32 * _T_i2) + 39));
          int  _ct10145 = ((0 > (32 * _T_i2))? 0: (32 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10145; (_i2 <= _ct10144); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L1[(((_i0 * 1120) + (((-16 * _T_i1) + 1281) * 40)) + ((-32 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
          {
            int  _ct10146 = ((385 < ((32 * _T_i2) + 39))? 385: ((32 * _T_i2) + 39));
            int  _ct10147 = ((0 > (32 * _T_i2))? 0: (32 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct10147; (_i2 <= _ct10146); _i2 = (_i2 + 1))
            {
              Ux_interpolated_L1[(((_i0 * 1120) + ((-16 * _T_i1) * 40)) + ((-32 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct10148 = ((320 < ((4 * _T_i1) + 6))? 320: ((4 * _T_i1) + 6));
        int  _ct10149 = ((1 > (4 * _T_i1))? 1: (4 * _T_i1));
        for (int  _i1 = _ct10149; (_i1 <= _ct10148); _i1 = (_i1 + 1))
        {
          int  _ct10150 = ((192 < ((16 * _T_i2) + 19))? 192: ((16 * _T_i2) + 19));
          int  _ct10151 = ((1 > (16 * _T_i2))? 1: (16 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10151; (_i2 <= _ct10150); _i2 = (_i2 + 1))
          {
            interpolated_L3[(((_i0 * 140) + (((-4 * _T_i1) + _i1) * 20)) + ((-16 * _T_i2) + _i2))] = (D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + _i2)] + ((1.0f - D_3_downsampled[(((3 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + _i2)]) * ((Ux_interpolated_L3[(((_i0 * 70) + (((-4 * _T_i1) + _i1) * 10)) + ((1 + ((-16 * _T_i2) + _i2)) / 2))] + Ux_interpolated_L3[(((_i0 * 70) + (((-4 * _T_i1) + _i1) * 10)) + ((2 + ((-16 * _T_i2) + _i2)) / 2))]) / 2.0f)));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct10152 = ((640 < ((8 * _T_i1) + 12))? 640: ((8 * _T_i1) + 12));
        int  _ct10153 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
        for (int  _i1 = _ct10153; (_i1 <= _ct10152); _i1 = (_i1 + 1))
        {
          int  _ct10154 = ((192 < ((16 * _T_i2) + 18))? 192: ((16 * _T_i2) + 18));
          int  _ct10155 = ((1 > (16 * _T_i2))? 1: (16 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10155; (_i2 <= _ct10154); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L2[(((_i0 * 280) + (((-8 * _T_i1) + _i1) * 20)) + ((-16 * _T_i2) + _i2))] = ((interpolated_L3[(((_i0 * 140) + (((1 + ((-8 * _T_i1) + _i1)) / 2) * 20)) + ((-16 * _T_i2) + _i2))] + interpolated_L3[(((_i0 * 140) + (((2 + ((-8 * _T_i1) + _i1)) / 2) * 20)) + ((-16 * _T_i2) + _i2))]) / 2.0f);
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct10156 = ((640 < ((8 * _T_i1) + 11))? 640: ((8 * _T_i1) + 11));
        int  _ct10157 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
        for (int  _i1 = _ct10157; (_i1 <= _ct10156); _i1 = (_i1 + 1))
        {
          int  _ct10158 = ((384 < ((32 * _T_i2) + 36))? 384: ((32 * _T_i2) + 36));
          int  _ct10159 = ((1 > (32 * _T_i2))? 1: (32 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10159; (_i2 <= _ct10158); _i2 = (_i2 + 1))
          {
            interpolated_L2[(((_i0 * 560) + (((-8 * _T_i1) + _i1) * 40)) + ((-32 * _T_i2) + _i2))] = (D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + _i2)] + ((1.0f - D_2_downsampled[(((3 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + _i2)]) * ((Ux_interpolated_L2[(((_i0 * 280) + (((-8 * _T_i1) + _i1) * 20)) + ((1 + ((-32 * _T_i2) + _i2)) / 2))] + Ux_interpolated_L2[(((_i0 * 280) + (((-8 * _T_i1) + _i1) * 20)) + ((2 + ((-32 * _T_i2) + _i2)) / 2))]) / 2.0f)));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct10160 = ((1280 < ((16 * _T_i1) + 21))? 1280: ((16 * _T_i1) + 21));
        int  _ct10161 = ((1 > (16 * _T_i1))? 1: (16 * _T_i1));
        for (int  _i1 = _ct10161; (_i1 <= _ct10160); _i1 = (_i1 + 1))
        {
          int  _ct10162 = ((384 < ((32 * _T_i2) + 35))? 384: ((32 * _T_i2) + 35));
          int  _ct10163 = ((1 > (32 * _T_i2))? 1: (32 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10163; (_i2 <= _ct10162); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L1[(((_i0 * 1120) + (((-16 * _T_i1) + _i1) * 40)) + ((-32 * _T_i2) + _i2))] = ((interpolated_L2[(((_i0 * 560) + (((1 + ((-16 * _T_i1) + _i1)) / 2) * 40)) + ((-32 * _T_i2) + _i2))] + interpolated_L2[(((_i0 * 560) + (((2 + ((-16 * _T_i1) + _i1)) / 2) * 40)) + ((-32 * _T_i2) + _i2))]) / 2.0f);
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct10164 = ((1280 < ((16 * _T_i1) + 20))? 1280: ((16 * _T_i1) + 20));
        int  _ct10165 = ((1 > (16 * _T_i1))? 1: (16 * _T_i1));
        for (int  _i1 = _ct10165; (_i1 <= _ct10164); _i1 = (_i1 + 1))
        {
          int  _ct10166 = ((768 < ((64 * _T_i2) + 69))? 768: ((64 * _T_i2) + 69));
          int  _ct10167 = ((1 > (64 * _T_i2))? 1: (64 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10167; (_i2 <= _ct10166); _i2 = (_i2 + 1))
          {
            interpolated_L1[(((_i0 * 2240) + (((-16 * _T_i1) + _i1) * 80)) + ((-64 * _T_i2) + _i2))] = (D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + _i2)] + ((1.0f - D_1_downsampled[(((3 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + _i2)]) * ((Ux_interpolated_L1[(((_i0 * 1120) + (((-16 * _T_i1) + _i1) * 40)) + ((1 + ((-64 * _T_i2) + _i2)) / 2))] + Ux_interpolated_L1[(((_i0 * 1120) + (((-16 * _T_i1) + _i1) * 40)) + ((2 + ((-64 * _T_i2) + _i2)) / 2))]) / 2.0f)));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct10168 = ((2560 < ((32 * _T_i1) + 37))? 2560: ((32 * _T_i1) + 37));
        int  _ct10169 = ((1 > (32 * _T_i1))? 1: (32 * _T_i1));
        for (int  _i1 = _ct10169; (_i1 <= _ct10168); _i1 = (_i1 + 1))
        {
          int  _ct10170 = ((768 < ((64 * _T_i2) + 67))? 768: ((64 * _T_i2) + 67));
          int  _ct10171 = ((1 > (64 * _T_i2))? 1: (64 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10171; (_i2 <= _ct10170); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L0[(((_i0 * 4480) + (((-32 * _T_i1) + _i1) * 80)) + ((-64 * _T_i2) + _i2))] = ((interpolated_L1[(((_i0 * 2240) + (((1 + ((-32 * _T_i1) + _i1)) / 2) * 80)) + ((-64 * _T_i2) + _i2))] + interpolated_L1[(((_i0 * 2240) + (((2 + ((-32 * _T_i1) + _i1)) / 2) * 80)) + ((-64 * _T_i2) + _i2))]) / 2.0f);
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct10172 = ((2560 < ((32 * _T_i1) + 34))? 2560: ((32 * _T_i1) + 34));
        int  _ct10173 = ((1 > (32 * _T_i1))? 1: (32 * _T_i1));
        for (int  _i1 = _ct10173; (_i1 <= _ct10172); _i1 = (_i1 + 1))
        {
          int  _ct10174 = ((1536 < ((128 * _T_i2) + 131))? 1536: ((128 * _T_i2) + 131));
          int  _ct10175 = ((1 > (128 * _T_i2))? 1: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct10175; (_i2 <= _ct10174); _i2 = (_i2 + 1))
          {
            interpolated_L0[(((_i0 * 8960) + (((-32 * _T_i1) + _i1) * 160)) + ((-128 * _T_i2) + _i2))] = (downsampled_L0[(((_i0 * ((2 + R) * (2 + C))) + (_i1 * (2 + C))) + _i2)] + ((1.0f - downsampled_L0[(((3 * ((2 + R) * (2 + C))) + (_i1 * (2 + C))) + _i2)]) * ((Ux_interpolated_L0[(((_i0 * 4480) + (((-32 * _T_i1) + _i1) * 80)) + ((1 + ((-128 * _T_i2) + _i2)) / 2))] + Ux_interpolated_L0[(((_i0 * 4480) + (((-32 * _T_i1) + _i1) * 80)) + ((2 + ((-128 * _T_i2) + _i2)) / 2))]) / 2.0f)));
          }
        }
      }
      if (((((_T_i1 <= 79) && (_T_i1 >= 0)) && (_T_i2 <= 11)) && (_T_i2 >= 0)))
      {
        for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
        {
          for (int  _i1 = (32 * _T_i1); (_i1 <= ((32 * _T_i1) + 31)); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = (128 * _T_i2); (_i2 <= ((128 * _T_i2) + 127)); _i2 = (_i2 + 1))
            {
              interpolate[(((_i0 * (R * C)) + (_i1 * C)) + _i2)] = (interpolated_L0[(((_i0 * 8960) + ((1 + ((-32 * _T_i1) + _i1)) * 160)) + (1 + ((-128 * _T_i2) + _i2)))] / interpolated_L0[(((3 * 8960) + ((1 + ((-32 * _T_i1) + _i1)) * 160)) + (1 + ((-128 * _T_i2) + _i2)))]);
            }
          }
        }
      }
    }
    free(Ux_interpolated_L3);
    free(interpolated_L2);
    free(Ux_interpolated_L2);
    free(interpolated_L1);
    free(interpolated_L0);
    free(interpolated_L3);
    free(Ux_interpolated_L0);
    free(Ux_interpolated_L1);
  }
  free(downsampled_L0);
  free(D_1_downsampled);
  free(D_2_downsampled);
  free(D_3_downsampled);
  free(D_4_downsampled);
  free(Dx_5_downsampled);
  free(D_5_downsampled);
  free(Dx_6_downsampled);
  free(D_6_downsampled);
  free(Dx_7_downsampled);
  free(D_7_downsampled);
  free(Dx_8_downsampled);
  free(D_8_downsampled);
  free(Dx_9_downsampled);
  free(D_9_downsampled);
  free(Ux_interpolated_L8);
  free(interpolated_L8);
  free(Ux_interpolated_L7);
  free(interpolated_L7);
  free(Ux_interpolated_L6);
  free(interpolated_L6);
  free(Ux_interpolated_L5);
  free(interpolated_L5);
  free(Ux_interpolated_L4);
  free(interpolated_L4);
}
