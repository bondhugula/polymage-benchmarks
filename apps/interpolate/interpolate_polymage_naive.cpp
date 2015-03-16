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
  float * Dx_1_downsampled;
  Dx_1_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 2) + 1) + 1)) * (2 + C)))));
  float * D_1_downsampled;
  D_1_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 2) + 1) + 1)) * (((C / 2) + 1) + 1)))));
  float * Dx_2_downsampled;
  Dx_2_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 4) + 1) + 1)) * (((C / 2) + 1) + 1)))));
  float * D_2_downsampled;
  D_2_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 4) + 1) + 1)) * (((C / 4) + 1) + 1)))));
  float * Dx_3_downsampled;
  Dx_3_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 8) + 1) + 1)) * (((C / 4) + 1) + 1)))));
  float * D_3_downsampled;
  D_3_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 8) + 1) + 1)) * (((C / 8) + 1) + 1)))));
  float * Dx_4_downsampled;
  Dx_4_downsampled = (float *) (malloc((sizeof(float ) * ((4 * (((R / 16) + 1) + 1)) * (((C / 8) + 1) + 1)))));
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
  float * Ux_interpolated_L3;
  Ux_interpolated_L3 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 8) + 1) + 1)) * (((C / 16) + 1) + 1)))));
  float * interpolated_L3;
  interpolated_L3 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 8) + 1) + 1)) * (((C / 8) + 1) + 1)))));
  float * Ux_interpolated_L2;
  Ux_interpolated_L2 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 4) + 1) + 1)) * (((C / 8) + 1) + 1)))));
  float * interpolated_L2;
  interpolated_L2 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 4) + 1) + 1)) * (((C / 4) + 1) + 1)))));
  float * Ux_interpolated_L1;
  Ux_interpolated_L1 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 2) + 1) + 1)) * (((C / 4) + 1) + 1)))));
  float * interpolated_L1;
  interpolated_L1 = (float *) (malloc((sizeof(float ) * ((4 * (((R / 2) + 1) + 1)) * (((C / 2) + 1) + 1)))));
  float * Ux_interpolated_L0;
  Ux_interpolated_L0 = (float *) (malloc((sizeof(float ) * ((4 * (2 + R)) * (((C / 2) + 1) + 1)))));
  float * interpolated_L0;
  interpolated_L0 = (float *) (malloc((sizeof(float ) * ((4 * (2 + R)) * (2 + C)))));
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
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 1281); _i1 = (_i1 + 1))
    {
      Dx_1_downsampled[((_i0 * ((((R / 2) + 1) + 1) * (2 + C))) + (_i1 * (2 + C)))] = 0;
      if (((_i1 <= 1280) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 1536); _i2 = (_i2 + 1))
        {
          Dx_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (2 + C))) + (_i1 * (2 + C))) + _i2)] = (((downsampled_L0[(((_i0 * ((2 + R) * (2 + C))) + ((-2 + (2 * _i1)) * (2 + C))) + _i2)] + (2.0f * downsampled_L0[(((_i0 * ((2 + R) * (2 + C))) + ((-1 + (2 * _i1)) * (2 + C))) + _i2)])) + downsampled_L0[(((_i0 * ((2 + R) * (2 + C))) + ((2 * _i1) * (2 + C))) + _i2)]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 1281))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1537); _i2 = (_i2 + 1))
          {
            Dx_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (2 + C))) + (1281 * (2 + C))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1537); _i2 = (_i2 + 1))
          {
            Dx_1_downsampled[((_i0 * ((((R / 2) + 1) + 1) * (2 + C))) + _i2)] = 0;
          }
        }
      }
      Dx_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (2 + C))) + (_i1 * (2 + C))) + 1537)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 1281); _i1 = (_i1 + 1))
    {
      D_1_downsampled[((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1)))] = 0;
      if (((_i1 <= 1280) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 768); _i2 = (_i2 + 1))
        {
          D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + _i2)] = (((Dx_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (2 + C))) + (_i1 * (2 + C))) + (-2 + (2 * _i2)))] + (2.0f * Dx_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (2 + C))) + (_i1 * (2 + C))) + (-1 + (2 * _i2)))])) + Dx_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (2 + C))) + (_i1 * (2 + C))) + (2 * _i2))]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 1281))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 769); _i2 = (_i2 + 1))
          {
            D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (1281 * (((C / 2) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 769); _i2 = (_i2 + 1))
          {
            D_1_downsampled[((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + 769)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 641); _i1 = (_i1 + 1))
    {
      Dx_2_downsampled[((_i0 * ((((R / 4) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1)))] = 0;
      if (((_i1 <= 640) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 768); _i2 = (_i2 + 1))
        {
          Dx_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + _i2)] = (((D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + ((-2 + (2 * _i1)) * (((C / 2) + 1) + 1))) + _i2)] + (2.0f * D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + ((-1 + (2 * _i1)) * (((C / 2) + 1) + 1))) + _i2)])) + D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + ((2 * _i1) * (((C / 2) + 1) + 1))) + _i2)]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 641))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 769); _i2 = (_i2 + 1))
          {
            Dx_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 2) + 1) + 1))) + (641 * (((C / 2) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 769); _i2 = (_i2 + 1))
          {
            Dx_2_downsampled[((_i0 * ((((R / 4) + 1) + 1) * (((C / 2) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Dx_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + 769)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 641); _i1 = (_i1 + 1))
    {
      D_2_downsampled[((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1)))] = 0;
      if (((_i1 <= 640) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 384); _i2 = (_i2 + 1))
        {
          D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + _i2)] = (((Dx_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + (-2 + (2 * _i2)))] + (2.0f * Dx_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + (-1 + (2 * _i2)))])) + Dx_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + (2 * _i2))]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 641))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 385); _i2 = (_i2 + 1))
          {
            D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (641 * (((C / 4) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 385); _i2 = (_i2 + 1))
          {
            D_2_downsampled[((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + 385)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 321); _i1 = (_i1 + 1))
    {
      Dx_3_downsampled[((_i0 * ((((R / 8) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1)))] = 0;
      if (((_i1 <= 320) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 384); _i2 = (_i2 + 1))
        {
          Dx_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + _i2)] = (((D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + ((-2 + (2 * _i1)) * (((C / 4) + 1) + 1))) + _i2)] + (2.0f * D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + ((-1 + (2 * _i1)) * (((C / 4) + 1) + 1))) + _i2)])) + D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + ((2 * _i1) * (((C / 4) + 1) + 1))) + _i2)]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 321))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 385); _i2 = (_i2 + 1))
          {
            Dx_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 4) + 1) + 1))) + (321 * (((C / 4) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 385); _i2 = (_i2 + 1))
          {
            Dx_3_downsampled[((_i0 * ((((R / 8) + 1) + 1) * (((C / 4) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Dx_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + 385)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 321); _i1 = (_i1 + 1))
    {
      D_3_downsampled[((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1)))] = 0;
      if (((_i1 <= 320) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 192); _i2 = (_i2 + 1))
        {
          D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + _i2)] = (((Dx_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + (-2 + (2 * _i2)))] + (2.0f * Dx_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + (-1 + (2 * _i2)))])) + Dx_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + (2 * _i2))]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 321))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 193); _i2 = (_i2 + 1))
          {
            D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (321 * (((C / 8) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 193); _i2 = (_i2 + 1))
          {
            D_3_downsampled[((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + 193)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 161); _i1 = (_i1 + 1))
    {
      Dx_4_downsampled[((_i0 * ((((R / 16) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1)))] = 0;
      if (((_i1 <= 160) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 192); _i2 = (_i2 + 1))
        {
          Dx_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + _i2)] = (((D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + ((-2 + (2 * _i1)) * (((C / 8) + 1) + 1))) + _i2)] + (2.0f * D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + ((-1 + (2 * _i1)) * (((C / 8) + 1) + 1))) + _i2)])) + D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + ((2 * _i1) * (((C / 8) + 1) + 1))) + _i2)]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 161))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 193); _i2 = (_i2 + 1))
          {
            Dx_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 8) + 1) + 1))) + (161 * (((C / 8) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 193); _i2 = (_i2 + 1))
          {
            Dx_4_downsampled[((_i0 * ((((R / 16) + 1) + 1) * (((C / 8) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Dx_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + 193)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 161); _i1 = (_i1 + 1))
    {
      D_4_downsampled[((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1)))] = 0;
      if (((_i1 <= 160) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 96); _i2 = (_i2 + 1))
        {
          D_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + _i2)] = (((Dx_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + (-2 + (2 * _i2)))] + (2.0f * Dx_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + (-1 + (2 * _i2)))])) + Dx_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + (2 * _i2))]) * 0.25f);
        }
      }
      else
      {
        if ((_i1 == 161))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 97); _i2 = (_i2 + 1))
          {
            D_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (161 * (((C / 16) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 97); _i2 = (_i2 + 1))
          {
            D_4_downsampled[((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      D_4_downsampled[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + 97)] = 0;
    }
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
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 321); _i1 = (_i1 + 1))
    {
      Ux_interpolated_L3[((_i0 * ((((R / 8) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1)))] = 0;
      if (((_i1 <= 320) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 96); _i2 = (_i2 + 1))
        {
          Ux_interpolated_L3[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + _i2)] = ((interpolated_L4[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (((_i1 + 1) / 2) * (((C / 16) + 1) + 1))) + _i2)] + interpolated_L4[(((_i0 * ((((R / 16) + 1) + 1) * (((C / 16) + 1) + 1))) + (((_i1 + 2) / 2) * (((C / 16) + 1) + 1))) + _i2)]) / 2.0f);
        }
      }
      else
      {
        if ((_i1 == 321))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 97); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L3[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 16) + 1) + 1))) + (321 * (((C / 16) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 97); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L3[((_i0 * ((((R / 8) + 1) + 1) * (((C / 16) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Ux_interpolated_L3[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + 97)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 321); _i1 = (_i1 + 1))
    {
      interpolated_L3[((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1)))] = 0;
      if (((_i1 <= 320) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 192); _i2 = (_i2 + 1))
        {
          interpolated_L3[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + _i2)] = (D_3_downsampled[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + _i2)] + ((1.0f - D_3_downsampled[(((3 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + _i2)]) * ((Ux_interpolated_L3[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + ((_i2 + 1) / 2))] + Ux_interpolated_L3[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 16) + 1) + 1))) + (_i1 * (((C / 16) + 1) + 1))) + ((_i2 + 2) / 2))]) / 2.0f)));
        }
      }
      else
      {
        if ((_i1 == 321))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 193); _i2 = (_i2 + 1))
          {
            interpolated_L3[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (321 * (((C / 8) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 193); _i2 = (_i2 + 1))
          {
            interpolated_L3[((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      interpolated_L3[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + 193)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 641); _i1 = (_i1 + 1))
    {
      Ux_interpolated_L2[((_i0 * ((((R / 4) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1)))] = 0;
      if (((_i1 <= 640) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 192); _i2 = (_i2 + 1))
        {
          Ux_interpolated_L2[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + _i2)] = ((interpolated_L3[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (((_i1 + 1) / 2) * (((C / 8) + 1) + 1))) + _i2)] + interpolated_L3[(((_i0 * ((((R / 8) + 1) + 1) * (((C / 8) + 1) + 1))) + (((_i1 + 2) / 2) * (((C / 8) + 1) + 1))) + _i2)]) / 2.0f);
        }
      }
      else
      {
        if ((_i1 == 641))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 193); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L2[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 8) + 1) + 1))) + (641 * (((C / 8) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 193); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L2[((_i0 * ((((R / 4) + 1) + 1) * (((C / 8) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Ux_interpolated_L2[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + 193)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 641); _i1 = (_i1 + 1))
    {
      interpolated_L2[((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1)))] = 0;
      if (((_i1 <= 640) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 384); _i2 = (_i2 + 1))
        {
          interpolated_L2[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + _i2)] = (D_2_downsampled[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + _i2)] + ((1.0f - D_2_downsampled[(((3 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + _i2)]) * ((Ux_interpolated_L2[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + ((_i2 + 1) / 2))] + Ux_interpolated_L2[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 8) + 1) + 1))) + (_i1 * (((C / 8) + 1) + 1))) + ((_i2 + 2) / 2))]) / 2.0f)));
        }
      }
      else
      {
        if ((_i1 == 641))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 385); _i2 = (_i2 + 1))
          {
            interpolated_L2[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (641 * (((C / 4) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 385); _i2 = (_i2 + 1))
          {
            interpolated_L2[((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      interpolated_L2[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + 385)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 1281); _i1 = (_i1 + 1))
    {
      Ux_interpolated_L1[((_i0 * ((((R / 2) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1)))] = 0;
      if (((_i1 <= 1280) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 384); _i2 = (_i2 + 1))
        {
          Ux_interpolated_L1[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + _i2)] = ((interpolated_L2[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (((_i1 + 1) / 2) * (((C / 4) + 1) + 1))) + _i2)] + interpolated_L2[(((_i0 * ((((R / 4) + 1) + 1) * (((C / 4) + 1) + 1))) + (((_i1 + 2) / 2) * (((C / 4) + 1) + 1))) + _i2)]) / 2.0f);
        }
      }
      else
      {
        if ((_i1 == 1281))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 385); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L1[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 4) + 1) + 1))) + (1281 * (((C / 4) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 385); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L1[((_i0 * ((((R / 2) + 1) + 1) * (((C / 4) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Ux_interpolated_L1[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + 385)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 1281); _i1 = (_i1 + 1))
    {
      interpolated_L1[((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1)))] = 0;
      if (((_i1 <= 1280) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 768); _i2 = (_i2 + 1))
        {
          interpolated_L1[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + _i2)] = (D_1_downsampled[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + _i2)] + ((1.0f - D_1_downsampled[(((3 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + _i2)]) * ((Ux_interpolated_L1[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + ((_i2 + 1) / 2))] + Ux_interpolated_L1[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 4) + 1) + 1))) + (_i1 * (((C / 4) + 1) + 1))) + ((_i2 + 2) / 2))]) / 2.0f)));
        }
      }
      else
      {
        if ((_i1 == 1281))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 769); _i2 = (_i2 + 1))
          {
            interpolated_L1[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (1281 * (((C / 2) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 769); _i2 = (_i2 + 1))
          {
            interpolated_L1[((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      interpolated_L1[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + 769)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 2561); _i1 = (_i1 + 1))
    {
      Ux_interpolated_L0[((_i0 * ((2 + R) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1)))] = 0;
      if (((_i1 <= 2560) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 768); _i2 = (_i2 + 1))
        {
          Ux_interpolated_L0[(((_i0 * ((2 + R) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + _i2)] = ((interpolated_L1[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (((_i1 + 1) / 2) * (((C / 2) + 1) + 1))) + _i2)] + interpolated_L1[(((_i0 * ((((R / 2) + 1) + 1) * (((C / 2) + 1) + 1))) + (((_i1 + 2) / 2) * (((C / 2) + 1) + 1))) + _i2)]) / 2.0f);
        }
      }
      else
      {
        if ((_i1 == 2561))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 769); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L0[(((_i0 * ((2 + R) * (((C / 2) + 1) + 1))) + (2561 * (((C / 2) + 1) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 769); _i2 = (_i2 + 1))
          {
            Ux_interpolated_L0[((_i0 * ((2 + R) * (((C / 2) + 1) + 1))) + _i2)] = 0;
          }
        }
      }
      Ux_interpolated_L0[(((_i0 * ((2 + R) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + 769)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 2561); _i1 = (_i1 + 1))
    {
      interpolated_L0[((_i0 * ((2 + R) * (2 + C))) + (_i1 * (2 + C)))] = 0;
      if (((_i1 <= 2560) && (_i1 >= 1)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 <= 1536); _i2 = (_i2 + 1))
        {
          interpolated_L0[(((_i0 * ((2 + R) * (2 + C))) + (_i1 * (2 + C))) + _i2)] = (downsampled_L0[(((_i0 * ((2 + R) * (2 + C))) + (_i1 * (2 + C))) + _i2)] + ((1.0f - downsampled_L0[(((3 * ((2 + R) * (2 + C))) + (_i1 * (2 + C))) + _i2)]) * ((Ux_interpolated_L0[(((_i0 * ((2 + R) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + ((_i2 + 1) / 2))] + Ux_interpolated_L0[(((_i0 * ((2 + R) * (((C / 2) + 1) + 1))) + (_i1 * (((C / 2) + 1) + 1))) + ((_i2 + 2) / 2))]) / 2.0f)));
        }
      }
      else
      {
        if ((_i1 == 2561))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1537); _i2 = (_i2 + 1))
          {
            interpolated_L0[(((_i0 * ((2 + R) * (2 + C))) + (2561 * (2 + C))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1537); _i2 = (_i2 + 1))
          {
            interpolated_L0[((_i0 * ((2 + R) * (2 + C))) + _i2)] = 0;
          }
        }
      }
      interpolated_L0[(((_i0 * ((2 + R) * (2 + C))) + (_i1 * (2 + C))) + 1537)] = 0;
    }
  }
  for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 2559); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 1535); _i2 = (_i2 + 1))
      {
        interpolate[(((_i0 * (R * C)) + (_i1 * C)) + _i2)] = (interpolated_L0[(((_i0 * ((2 + R) * (2 + C))) + ((1 + _i1) * (2 + C))) + (1 + _i2))] / interpolated_L0[(((3 * ((2 + R) * (2 + C))) + ((1 + _i1) * (2 + C))) + (1 + _i2))]);
      }
    }
  }
  free(downsampled_L0);
  free(Dx_1_downsampled);
  free(D_1_downsampled);
  free(Dx_2_downsampled);
  free(D_2_downsampled);
  free(Dx_3_downsampled);
  free(D_3_downsampled);
  free(Dx_4_downsampled);
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
  free(Ux_interpolated_L3);
  free(interpolated_L3);
  free(Ux_interpolated_L2);
  free(interpolated_L2);
  free(Ux_interpolated_L1);
  free(interpolated_L1);
  free(Ux_interpolated_L0);
  free(interpolated_L0);
}
