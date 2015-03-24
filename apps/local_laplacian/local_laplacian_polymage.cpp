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
extern "C" void  pipeline_laplacian(int  C, int  R, float  alpha, float  beta, void * img_colour_void_arg, void * laplacian_void_arg)
{
  short unsigned int * img_colour;
  img_colour = (short unsigned int *) (img_colour_void_arg);
  short unsigned int * laplacian;
  laplacian = (short unsigned int *) (laplacian_void_arg);
  float * img;
  img = (float *) (malloc((sizeof(float ) * ((4 + R) * (4 + C)))));
  float * remapLUT;
  remapLUT = (float *) (malloc((sizeof(float ) * 3584)));
  float * gPyramid_L0;
  gPyramid_L0 = (float *) (malloc((sizeof(float ) * ((8 * (4 + R)) * (4 + C)))));
  float * D_inGPyramid_L1;
  D_inGPyramid_L1 = (float *) (malloc((sizeof(float ) * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1)))));
  float * D_gPyramid_L1;
  D_gPyramid_L1 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 2) + 3) + 1)) * (((C / 2) + 3) + 1)))));
  float * D_inGPyramid_L2;
  D_inGPyramid_L2 = (float *) (malloc((sizeof(float ) * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1)))));
  float * D_gPyramid_L2;
  D_gPyramid_L2 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 4) + 3) + 1)) * (((C / 4) + 3) + 1)))));
  float * D_inGPyramid_L3;
  D_inGPyramid_L3 = (float *) (malloc((sizeof(float ) * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1)))));
  float * D_gPyramid_L3;
  D_gPyramid_L3 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 8) + 3) + 1)) * (((C / 8) + 3) + 1)))));
  float * Dx_inGPyramid_L4;
  Dx_inGPyramid_L4 = (float *) (malloc((sizeof(float ) * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1)))));
  float * D_inGPyramid_L4;
  D_inGPyramid_L4 = (float *) (malloc((sizeof(float ) * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1)))));
  float * D_gPyramid_L4;
  D_gPyramid_L4 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 16) + 3) + 1)) * (((C / 16) + 3) + 1)))));
  float * Dx_inGPyramid_L5;
  Dx_inGPyramid_L5 = (float *) (malloc((sizeof(float ) * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1)))));
  float * D_inGPyramid_L5;
  D_inGPyramid_L5 = (float *) (malloc((sizeof(float ) * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1)))));
  float * Dx_gPyramid_L5;
  Dx_gPyramid_L5 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 32) + 3) + 1)) * (((C / 16) + 3) + 1)))));
  float * D_gPyramid_L5;
  D_gPyramid_L5 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 32) + 3) + 1)) * (((C / 32) + 3) + 1)))));
  float * Dx_inGPyramid_L6;
  Dx_inGPyramid_L6 = (float *) (malloc((sizeof(float ) * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1)))));
  float * D_inGPyramid_L6;
  D_inGPyramid_L6 = (float *) (malloc((sizeof(float ) * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1)))));
  float * Dx_gPyramid_L6;
  Dx_gPyramid_L6 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 64) + 3) + 1)) * (((C / 32) + 3) + 1)))));
  float * Ux_lPyramid_L4;
  Ux_lPyramid_L4 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 16) + 3) + 1)) * (((C / 32) + 3) + 1)))));
  float * D_gPyramid_L6;
  D_gPyramid_L6 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 64) + 3) + 1)) * (((C / 64) + 3) + 1)))));
  float * Dx_inGPyramid_L7;
  Dx_inGPyramid_L7 = (float *) (malloc((sizeof(float ) * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1)))));
  float * D_inGPyramid_L7;
  D_inGPyramid_L7 = (float *) (malloc((sizeof(float ) * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1)))));
  float * Dx_gPyramid_L7;
  Dx_gPyramid_L7 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 128) + 3) + 1)) * (((C / 64) + 3) + 1)))));
  float * Ux_lPyramid_L5;
  Ux_lPyramid_L5 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 32) + 3) + 1)) * (((C / 64) + 3) + 1)))));
  float * D_gPyramid_L7;
  D_gPyramid_L7 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 128) + 3) + 1)) * (((C / 128) + 3) + 1)))));
  float * U_lPyramid_L5;
  U_lPyramid_L5 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 32) + 3) + 1)) * (((C / 32) + 3) + 1)))));
  float * Ux_lPyramid_L6;
  Ux_lPyramid_L6 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 64) + 3) + 1)) * (((C / 128) + 3) + 1)))));
  float * outLPyramid_L5;
  outLPyramid_L5 = (float *) (malloc((sizeof(float ) * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1)))));
  float * outLPyramid_L7;
  outLPyramid_L7 = (float *) (malloc((sizeof(float ) * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1)))));
  float * U_lPyramid_L6;
  U_lPyramid_L6 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 64) + 3) + 1)) * (((C / 64) + 3) + 1)))));
  float * Ux_outGPyramid_L6;
  Ux_outGPyramid_L6 = (float *) (malloc((sizeof(float ) * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1)))));
  float * outLPyramid_L6;
  outLPyramid_L6 = (float *) (malloc((sizeof(float ) * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1)))));
  float * outGPyramid_L6;
  outGPyramid_L6 = (float *) (malloc((sizeof(float ) * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1)))));
  float * Ux_outGPyramid_L5;
  Ux_outGPyramid_L5 = (float *) (malloc((sizeof(float ) * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1)))));
  float * outGPyramid_L5;
  outGPyramid_L5 = (float *) (malloc((sizeof(float ) * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1)))));
  float * Ux_outGPyramid_L4;
  Ux_outGPyramid_L4 = (float *) (malloc((sizeof(float ) * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1)))));
  float * Ux_outGPyramid_L3;
  Ux_outGPyramid_L3 = (float *) (malloc((sizeof(float ) * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1)))));
  float * outGPyramid_L3;
  outGPyramid_L3 = (float *) (malloc((sizeof(float ) * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1)))));
  float * outGPyramid_L2;
  outGPyramid_L2 = (float *) (malloc((sizeof(float ) * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1)))));
  float * outGPyramid_L1;
  outGPyramid_L1 = (float *) (malloc((sizeof(float ) * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1)))));
  float * result_ref_gray;
  result_ref_gray = (float *) (malloc((sizeof(float ) * ((4 + R) * (4 + C)))));
  for (int  _i0 = -1792; (_i0 <= 1791); _i0 = (_i0 + 1))
  {
    remapLUT[(_i0 - -1792)] = ((alpha * ((float ) (_i0) / 256.0f)) * std::exp(((-(((float ) (_i0) / 256.0f)) * ((float ) (_i0) / 256.0f)) / 2.0f)));
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 2563); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 0; (_i2 <= 1539); _i2 = (_i2 + 1))
    {
      img[((_i1 * (4 + C)) + _i2)] = ((((0.299f * img_colour[(((2 * ((R + 4) * (C + 4))) + (_i1 * (C + 4))) + _i2)]) + (0.587f * img_colour[(((1 * ((R + 4) * (C + 4))) + (_i1 * (C + 4))) + _i2)])) + (0.114f * img_colour[(((0 * ((R + 4) * (C + 4))) + (_i1 * (C + 4))) + _i2)])) / 65535.0f);
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 2563); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 1539); _i2 = (_i2 + 1))
      {
        int  _ct17193 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (1792.0f)));
        int  _ct17194 = 0;
        int  _ct17195 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (1792.0f))) > 0)? _ct17193: _ct17194);
        int  _ct17196 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (1792.0f)));
        int  _ct17197 = 0;
        int  _ct17198 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (1792.0f))) > 0)? _ct17196: _ct17197);
        int  _ct17199 = _ct17198;
        int  _ct17200 = 1792;
        int  _ct17201 = ((_ct17195 < 1792)? _ct17199: _ct17200);
        gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = (((beta * (img[((_i1 * (4 + C)) + _i2)] - (_i0 * 0.142857142857f))) + (_i0 * 0.142857142857f)) + remapLUT[((_ct17201 - (256 * _i0)) - -1792)]);
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 160); _T_i1 = (_T_i1 + 1))
  {
    float * Dx_gPyramid_L1;
    Dx_gPyramid_L1 = (float *) (malloc((sizeof(float ) * ((8 * 8) * 259))));
    for (int  _T_i2 = -1; (_T_i2 <= 6); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17202 = ((1281 < ((8 * _T_i1) + 7))? 1281: ((8 * _T_i1) + 7));
        int  _ct17203 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17203; (_i1 <= _ct17202); _i1 = (_i1 + 1))
        {
          int  _ct17204 = ((1537 < ((256 * _T_i2) + 258))? 1537: ((256 * _T_i2) + 258));
          int  _ct17205 = ((2 > (256 * _T_i2))? 2: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17205; (_i2 <= _ct17204); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L1[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + ((-256 * _T_i2) + _i2))] = ((((gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + ((-3 + (2 * _i1)) * (4 + C))) + _i2)] + (3.0f * gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + ((-2 + (2 * _i1)) * (4 + C))) + _i2)])) + (3.0f * gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + ((-1 + (2 * _i1)) * (4 + C))) + _i2)])) + gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + ((2 * _i1) * (4 + C))) + _i2)]) * 0.125f);
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17206 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17206); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L1[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17207 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17207); _i1 = (_i1 + 1))
        {
          int  _ct17208 = ((1539 < ((256 * _T_i2) + 258))? 1539: ((256 * _T_i2) + 258));
          #pragma ivdep
          for (int  _i2 = 1536; (_i2 <= _ct17208); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L1[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + ((-256 * _T_i2) + _i2))] = 0;
          }
        }
      }
      if ((_T_i1 == 160))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 1280; (_i1 <= 1283); _i1 = (_i1 + 1))
          {
            int  _ct17209 = ((1539 < ((256 * _T_i2) + 258))? 1539: ((256 * _T_i2) + 258));
            int  _ct17210 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17210; (_i2 <= _ct17209); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L1[(((_i0 * 2072) + ((_i1 - 1280) * 259)) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
            {
              int  _ct17211 = ((1539 < ((256 * _T_i2) + 258))? 1539: ((256 * _T_i2) + 258));
              int  _ct17212 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
              #pragma ivdep
              for (int  _i2 = _ct17212; (_i2 <= _ct17211); _i2 = (_i2 + 1))
              {
                Dx_gPyramid_L1[(((_i0 * 2072) + (_i1 * 259)) + ((-256 * _T_i2) + _i2))] = 0;
              }
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17213 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17213); _i1 = (_i1 + 1))
        {
          int  _ct17214 = ((771 < ((128 * _T_i2) + 129))? 771: ((128 * _T_i2) + 129));
          #pragma ivdep
          for (int  _i2 = 768; (_i2 <= _ct17214); _i2 = (_i2 + 1))
          {
            D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17215 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17215); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 160))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 1280; (_i1 <= 1283); _i1 = (_i1 + 1))
          {
            int  _ct17216 = ((771 < ((128 * _T_i2) + 129))? 771: ((128 * _T_i2) + 129));
            int  _ct17217 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17217; (_i2 <= _ct17216); _i2 = (_i2 + 1))
            {
              D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
            {
              int  _ct17218 = ((771 < ((128 * _T_i2) + 129))? 771: ((128 * _T_i2) + 129));
              int  _ct17219 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
              #pragma ivdep
              for (int  _i2 = _ct17219; (_i2 <= _ct17218); _i2 = (_i2 + 1))
              {
                D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
        }
      }
      if (((_T_i2 <= 5) && (_T_i2 >= 0)))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17220 = ((1281 < ((8 * _T_i1) + 7))? 1281: ((8 * _T_i1) + 7));
          int  _ct17221 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
          for (int  _i1 = _ct17221; (_i1 <= _ct17220); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = ((128 * _T_i2) + 2); (_i2 <= ((128 * _T_i2) + 129)); _i2 = (_i2 + 1))
            {
              D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L1[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (-3 + (2 * ((-128 * _T_i2) + _i2))))] + (3.0f * Dx_gPyramid_L1[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (-2 + (2 * ((-128 * _T_i2) + _i2))))])) + (3.0f * Dx_gPyramid_L1[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (-1 + (2 * ((-128 * _T_i2) + _i2))))])) + Dx_gPyramid_L1[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (2 * ((-128 * _T_i2) + _i2)))]) * 0.125f);
            }
          }
        }
      }
    }
    free(Dx_gPyramid_L1);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 160); _T_i1 = (_T_i1 + 1))
  {
    float * Dx_inGPyramid_L1;
    Dx_inGPyramid_L1 = (float *) (malloc((sizeof(float ) * 2072)));
    for (int  _T_i2 = -1; (_T_i2 <= 6); _T_i2 = (_T_i2 + 1))
    {
      int  _ct17222 = ((1281 < ((8 * _T_i1) + 7))? 1281: ((8 * _T_i1) + 7));
      int  _ct17223 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17223; (_i1 <= _ct17222); _i1 = (_i1 + 1))
      {
        int  _ct17224 = ((1537 < ((256 * _T_i2) + 258))? 1537: ((256 * _T_i2) + 258));
        int  _ct17225 = ((2 > (256 * _T_i2))? 2: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17225; (_i2 <= _ct17224); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L1[((((-8 * _T_i1) + _i1) * 259) + ((-256 * _T_i2) + _i2))] = ((((img[(((-3 + (2 * _i1)) * (4 + C)) + _i2)] + (3.0f * img[(((-2 + (2 * _i1)) * (4 + C)) + _i2)])) + (3.0f * img[(((-1 + (2 * _i1)) * (4 + C)) + _i2)])) + img[(((2 * _i1) * (4 + C)) + _i2)]) * 0.125f);
        }
      }
      int  _ct17226 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17226); _i1 = (_i1 + 1))
      {
        int  _ct17227 = ((1539 < ((256 * _T_i2) + 258))? 1539: ((256 * _T_i2) + 258));
        #pragma ivdep
        for (int  _i2 = 1536; (_i2 <= _ct17227); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L1[((((-8 * _T_i1) + _i1) * 259) + ((-256 * _T_i2) + _i2))] = 0;
        }
      }
      if ((_T_i2 <= 0))
      {
        int  _ct17228 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17228); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L1[((((-8 * _T_i1) + _i1) * 259) + ((-256 * _T_i2) + _i2))] = 0;
          }
        }
      }
      if ((_T_i1 == 160))
      {
        for (int  _i1 = 1280; (_i1 <= 1283); _i1 = (_i1 + 1))
        {
          int  _ct17229 = ((1539 < ((256 * _T_i2) + 258))? 1539: ((256 * _T_i2) + 258));
          int  _ct17230 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17230; (_i2 <= _ct17229); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L1[(((_i1 - 1280) * 259) + ((-256 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            int  _ct17231 = ((1539 < ((256 * _T_i2) + 258))? 1539: ((256 * _T_i2) + 258));
            int  _ct17232 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17232; (_i2 <= _ct17231); _i2 = (_i2 + 1))
            {
              Dx_inGPyramid_L1[((_i1 * 259) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      int  _ct17233 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17233); _i1 = (_i1 + 1))
      {
        int  _ct17234 = ((771 < ((128 * _T_i2) + 129))? 771: ((128 * _T_i2) + 129));
        #pragma ivdep
        for (int  _i2 = 768; (_i2 <= _ct17234); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_T_i2 <= 0))
      {
        int  _ct17235 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17235); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      if ((_T_i1 == 160))
      {
        for (int  _i1 = 1280; (_i1 <= 1283); _i1 = (_i1 + 1))
        {
          int  _ct17236 = ((771 < ((128 * _T_i2) + 129))? 771: ((128 * _T_i2) + 129));
          int  _ct17237 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17237; (_i2 <= _ct17236); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            int  _ct17238 = ((771 < ((128 * _T_i2) + 129))? 771: ((128 * _T_i2) + 129));
            int  _ct17239 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17239; (_i2 <= _ct17238); _i2 = (_i2 + 1))
            {
              D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
      }
      if (((_T_i2 <= 5) && (_T_i2 >= 0)))
      {
        int  _ct17240 = ((1281 < ((8 * _T_i1) + 7))? 1281: ((8 * _T_i1) + 7));
        int  _ct17241 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17241; (_i1 <= _ct17240); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = ((128 * _T_i2) + 2); (_i2 <= ((128 * _T_i2) + 129)); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L1[((((-8 * _T_i1) + _i1) * 259) + (-3 + (2 * ((-128 * _T_i2) + _i2))))] + (3.0f * Dx_inGPyramid_L1[((((-8 * _T_i1) + _i1) * 259) + (-2 + (2 * ((-128 * _T_i2) + _i2))))])) + (3.0f * Dx_inGPyramid_L1[((((-8 * _T_i1) + _i1) * 259) + (-1 + (2 * ((-128 * _T_i2) + _i2))))])) + Dx_inGPyramid_L1[((((-8 * _T_i1) + _i1) * 259) + (2 * ((-128 * _T_i2) + _i2)))]) * 0.125f);
          }
        }
      }
    }
    free(Dx_inGPyramid_L1);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 80); _T_i1 = (_T_i1 + 1))
  {
    float * Dx_gPyramid_L2;
    Dx_gPyramid_L2 = (float *) (malloc((sizeof(float ) * ((8 * 8) * 259))));
    for (int  _T_i2 = -1; (_T_i2 <= 3); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17242 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17242); _i1 = (_i1 + 1))
        {
          int  _ct17243 = ((387 < ((128 * _T_i2) + 129))? 387: ((128 * _T_i2) + 129));
          #pragma ivdep
          for (int  _i2 = 384; (_i2 <= _ct17243); _i2 = (_i2 + 1))
          {
            D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17244 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17244); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 80))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 640; (_i1 <= 643); _i1 = (_i1 + 1))
          {
            int  _ct17245 = ((387 < ((128 * _T_i2) + 129))? 387: ((128 * _T_i2) + 129));
            int  _ct17246 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17246; (_i2 <= _ct17245); _i2 = (_i2 + 1))
            {
              D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
            {
              int  _ct17247 = ((387 < ((128 * _T_i2) + 129))? 387: ((128 * _T_i2) + 129));
              int  _ct17248 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
              #pragma ivdep
              for (int  _i2 = _ct17248; (_i2 <= _ct17247); _i2 = (_i2 + 1))
              {
                D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17249 = ((641 < ((8 * _T_i1) + 7))? 641: ((8 * _T_i1) + 7));
        int  _ct17250 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17250; (_i1 <= _ct17249); _i1 = (_i1 + 1))
        {
          int  _ct17251 = ((769 < ((256 * _T_i2) + 258))? 769: ((256 * _T_i2) + 258));
          int  _ct17252 = ((2 > (256 * _T_i2))? 2: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17252; (_i2 <= _ct17251); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L2[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + ((-256 * _T_i2) + _i2))] = ((((D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + ((-3 + (2 * _i1)) * (((C / 2) + 3) + 1))) + _i2)] + (3.0f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + ((-2 + (2 * _i1)) * (((C / 2) + 3) + 1))) + _i2)])) + (3.0f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + ((-1 + (2 * _i1)) * (((C / 2) + 3) + 1))) + _i2)])) + D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + ((2 * _i1) * (((C / 2) + 3) + 1))) + _i2)]) * 0.125f);
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17253 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17253); _i1 = (_i1 + 1))
        {
          int  _ct17254 = ((771 < ((256 * _T_i2) + 258))? 771: ((256 * _T_i2) + 258));
          #pragma ivdep
          for (int  _i2 = 768; (_i2 <= _ct17254); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L2[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + ((-256 * _T_i2) + _i2))] = 0;
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17255 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17255); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L2[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 80))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 640; (_i1 <= 643); _i1 = (_i1 + 1))
          {
            int  _ct17256 = ((771 < ((256 * _T_i2) + 258))? 771: ((256 * _T_i2) + 258));
            int  _ct17257 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17257; (_i2 <= _ct17256); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L2[(((_i0 * 2072) + ((_i1 - 640) * 259)) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
            {
              int  _ct17258 = ((771 < ((256 * _T_i2) + 258))? 771: ((256 * _T_i2) + 258));
              int  _ct17259 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
              #pragma ivdep
              for (int  _i2 = _ct17259; (_i2 <= _ct17258); _i2 = (_i2 + 1))
              {
                Dx_gPyramid_L2[(((_i0 * 2072) + (_i1 * 259)) + ((-256 * _T_i2) + _i2))] = 0;
              }
            }
          }
        }
      }
      if (((_T_i2 <= 2) && (_T_i2 >= 0)))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17260 = ((641 < ((8 * _T_i1) + 7))? 641: ((8 * _T_i1) + 7));
          int  _ct17261 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
          for (int  _i1 = _ct17261; (_i1 <= _ct17260); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = ((128 * _T_i2) + 2); (_i2 <= ((128 * _T_i2) + 129)); _i2 = (_i2 + 1))
            {
              D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L2[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (-3 + (2 * ((-128 * _T_i2) + _i2))))] + (3.0f * Dx_gPyramid_L2[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (-2 + (2 * ((-128 * _T_i2) + _i2))))])) + (3.0f * Dx_gPyramid_L2[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (-1 + (2 * ((-128 * _T_i2) + _i2))))])) + Dx_gPyramid_L2[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (2 * ((-128 * _T_i2) + _i2)))]) * 0.125f);
            }
          }
        }
      }
    }
    free(Dx_gPyramid_L2);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 80); _T_i1 = (_T_i1 + 1))
  {
    float * Dx_inGPyramid_L2;
    Dx_inGPyramid_L2 = (float *) (malloc((sizeof(float ) * 2072)));
    for (int  _T_i2 = -1; (_T_i2 <= 3); _T_i2 = (_T_i2 + 1))
    {
      int  _ct17262 = ((641 < ((8 * _T_i1) + 7))? 641: ((8 * _T_i1) + 7));
      int  _ct17263 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17263; (_i1 <= _ct17262); _i1 = (_i1 + 1))
      {
        int  _ct17264 = ((769 < ((256 * _T_i2) + 258))? 769: ((256 * _T_i2) + 258));
        int  _ct17265 = ((2 > (256 * _T_i2))? 2: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17265; (_i2 <= _ct17264); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L2[((((-8 * _T_i1) + _i1) * 259) + ((-256 * _T_i2) + _i2))] = ((((D_inGPyramid_L1[(((-3 + (2 * _i1)) * (((C / 2) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L1[(((-2 + (2 * _i1)) * (((C / 2) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L1[(((-1 + (2 * _i1)) * (((C / 2) + 3) + 1)) + _i2)])) + D_inGPyramid_L1[(((2 * _i1) * (((C / 2) + 3) + 1)) + _i2)]) * 0.125f);
        }
      }
      if ((_T_i2 <= 0))
      {
        int  _ct17266 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17266); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L2[((((-8 * _T_i1) + _i1) * 259) + ((-256 * _T_i2) + _i2))] = 0;
          }
        }
      }
      int  _ct17267 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17267); _i1 = (_i1 + 1))
      {
        int  _ct17268 = ((771 < ((256 * _T_i2) + 258))? 771: ((256 * _T_i2) + 258));
        #pragma ivdep
        for (int  _i2 = 768; (_i2 <= _ct17268); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L2[((((-8 * _T_i1) + _i1) * 259) + ((-256 * _T_i2) + _i2))] = 0;
        }
      }
      if ((_T_i1 == 80))
      {
        for (int  _i1 = 640; (_i1 <= 643); _i1 = (_i1 + 1))
        {
          int  _ct17269 = ((771 < ((256 * _T_i2) + 258))? 771: ((256 * _T_i2) + 258));
          int  _ct17270 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17270; (_i2 <= _ct17269); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L2[(((_i1 - 640) * 259) + ((-256 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            int  _ct17271 = ((771 < ((256 * _T_i2) + 258))? 771: ((256 * _T_i2) + 258));
            int  _ct17272 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17272; (_i2 <= _ct17271); _i2 = (_i2 + 1))
            {
              Dx_inGPyramid_L2[((_i1 * 259) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      int  _ct17273 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17273); _i1 = (_i1 + 1))
      {
        int  _ct17274 = ((387 < ((128 * _T_i2) + 129))? 387: ((128 * _T_i2) + 129));
        #pragma ivdep
        for (int  _i2 = 384; (_i2 <= _ct17274); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_T_i2 <= 0))
      {
        int  _ct17275 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17275); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      if ((_T_i1 == 80))
      {
        for (int  _i1 = 640; (_i1 <= 643); _i1 = (_i1 + 1))
        {
          int  _ct17276 = ((387 < ((128 * _T_i2) + 129))? 387: ((128 * _T_i2) + 129));
          int  _ct17277 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17277; (_i2 <= _ct17276); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            int  _ct17278 = ((387 < ((128 * _T_i2) + 129))? 387: ((128 * _T_i2) + 129));
            int  _ct17279 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17279; (_i2 <= _ct17278); _i2 = (_i2 + 1))
            {
              D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
      }
      if (((_T_i2 <= 2) && (_T_i2 >= 0)))
      {
        int  _ct17280 = ((641 < ((8 * _T_i1) + 7))? 641: ((8 * _T_i1) + 7));
        int  _ct17281 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17281; (_i1 <= _ct17280); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = ((128 * _T_i2) + 2); (_i2 <= ((128 * _T_i2) + 129)); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L2[((((-8 * _T_i1) + _i1) * 259) + (-3 + (2 * ((-128 * _T_i2) + _i2))))] + (3.0f * Dx_inGPyramid_L2[((((-8 * _T_i1) + _i1) * 259) + (-2 + (2 * ((-128 * _T_i2) + _i2))))])) + (3.0f * Dx_inGPyramid_L2[((((-8 * _T_i1) + _i1) * 259) + (-1 + (2 * ((-128 * _T_i2) + _i2))))])) + Dx_inGPyramid_L2[((((-8 * _T_i1) + _i1) * 259) + (2 * ((-128 * _T_i2) + _i2)))]) * 0.125f);
          }
        }
      }
    }
    free(Dx_inGPyramid_L2);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 40); _T_i1 = (_T_i1 + 1))
  {
    float * Dx_gPyramid_L3;
    Dx_gPyramid_L3 = (float *) (malloc((sizeof(float ) * ((8 * 8) * 259))));
    for (int  _T_i2 = -1; (_T_i2 <= 1); _T_i2 = (_T_i2 + 1))
    {
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17282 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17282); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17283 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17283); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
            {
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 40))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 320; (_i1 <= 323); _i1 = (_i1 + 1))
          {
            int  _ct17284 = ((195 < ((128 * _T_i2) + 129))? 195: ((128 * _T_i2) + 129));
            int  _ct17285 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17285; (_i2 <= _ct17284); _i2 = (_i2 + 1))
            {
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
            {
              int  _ct17286 = ((195 < ((128 * _T_i2) + 129))? 195: ((128 * _T_i2) + 129));
              int  _ct17287 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
              #pragma ivdep
              for (int  _i2 = _ct17287; (_i2 <= _ct17286); _i2 = (_i2 + 1))
              {
                D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17288 = ((321 < ((8 * _T_i1) + 7))? 321: ((8 * _T_i1) + 7));
        int  _ct17289 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17289; (_i1 <= _ct17288); _i1 = (_i1 + 1))
        {
          int  _ct17290 = ((385 < ((256 * _T_i2) + 258))? 385: ((256 * _T_i2) + 258));
          int  _ct17291 = ((2 > (256 * _T_i2))? 2: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17291; (_i2 <= _ct17290); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L3[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + ((-256 * _T_i2) + _i2))] = ((((D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + ((-3 + (2 * _i1)) * (((C / 4) + 3) + 1))) + _i2)] + (3.0f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + ((-2 + (2 * _i1)) * (((C / 4) + 3) + 1))) + _i2)])) + (3.0f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + ((-1 + (2 * _i1)) * (((C / 4) + 3) + 1))) + _i2)])) + D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + ((2 * _i1) * (((C / 4) + 3) + 1))) + _i2)]) * 0.125f);
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17292 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17292); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L3[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17293 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17293); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 384; (_i2 <= 387); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L3[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (_i2 - 256))] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 40))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 320; (_i1 <= 323); _i1 = (_i1 + 1))
          {
            int  _ct17294 = ((387 < ((256 * _T_i2) + 258))? 387: ((256 * _T_i2) + 258));
            int  _ct17295 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17295; (_i2 <= _ct17294); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L3[(((_i0 * 2072) + ((_i1 - 320) * 259)) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
            {
              int  _ct17296 = ((387 < ((256 * _T_i2) + 258))? 387: ((256 * _T_i2) + 258));
              int  _ct17297 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
              #pragma ivdep
              for (int  _i2 = _ct17297; (_i2 <= _ct17296); _i2 = (_i2 + 1))
              {
                Dx_gPyramid_L3[(((_i0 * 2072) + (_i1 * 259)) + ((-256 * _T_i2) + _i2))] = 0;
              }
            }
          }
        }
      }
      if ((_T_i2 >= 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17298 = ((321 < ((8 * _T_i1) + 7))? 321: ((8 * _T_i1) + 7));
          int  _ct17299 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
          for (int  _i1 = _ct17299; (_i1 <= _ct17298); _i1 = (_i1 + 1))
          {
            int  _ct17300 = ((193 < ((128 * _T_i2) + 129))? 193: ((128 * _T_i2) + 129));
            #pragma ivdep
            for (int  _i2 = ((128 * _T_i2) + 2); (_i2 <= _ct17300); _i2 = (_i2 + 1))
            {
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L3[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (-3 + (2 * ((-128 * _T_i2) + _i2))))] + (3.0f * Dx_gPyramid_L3[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (-2 + (2 * ((-128 * _T_i2) + _i2))))])) + (3.0f * Dx_gPyramid_L3[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (-1 + (2 * ((-128 * _T_i2) + _i2))))])) + Dx_gPyramid_L3[(((_i0 * 2072) + (((-8 * _T_i1) + _i1) * 259)) + (2 * ((-128 * _T_i2) + _i2)))]) * 0.125f);
            }
          }
        }
      }
    }
    free(Dx_gPyramid_L3);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 40); _T_i1 = (_T_i1 + 1))
  {
    float * Dx_inGPyramid_L3;
    Dx_inGPyramid_L3 = (float *) (malloc((sizeof(float ) * 2072)));
    for (int  _T_i2 = -1; (_T_i2 <= 1); _T_i2 = (_T_i2 + 1))
    {
      if ((_T_i2 <= 0))
      {
        int  _ct17301 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17301); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        int  _ct17302 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17302); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      if ((_T_i1 == 40))
      {
        for (int  _i1 = 320; (_i1 <= 323); _i1 = (_i1 + 1))
        {
          int  _ct17303 = ((195 < ((128 * _T_i2) + 129))? 195: ((128 * _T_i2) + 129));
          int  _ct17304 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17304; (_i2 <= _ct17303); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            int  _ct17305 = ((195 < ((128 * _T_i2) + 129))? 195: ((128 * _T_i2) + 129));
            int  _ct17306 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17306; (_i2 <= _ct17305); _i2 = (_i2 + 1))
            {
              D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
      }
      int  _ct17307 = ((321 < ((8 * _T_i1) + 7))? 321: ((8 * _T_i1) + 7));
      int  _ct17308 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17308; (_i1 <= _ct17307); _i1 = (_i1 + 1))
      {
        int  _ct17309 = ((385 < ((256 * _T_i2) + 258))? 385: ((256 * _T_i2) + 258));
        int  _ct17310 = ((2 > (256 * _T_i2))? 2: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17310; (_i2 <= _ct17309); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L3[((((-8 * _T_i1) + _i1) * 259) + ((-256 * _T_i2) + _i2))] = ((((D_inGPyramid_L2[(((-3 + (2 * _i1)) * (((C / 4) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L2[(((-2 + (2 * _i1)) * (((C / 4) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L2[(((-1 + (2 * _i1)) * (((C / 4) + 3) + 1)) + _i2)])) + D_inGPyramid_L2[(((2 * _i1) * (((C / 4) + 3) + 1)) + _i2)]) * 0.125f);
        }
      }
      if ((_T_i2 <= 0))
      {
        int  _ct17311 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17311); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L3[((((-8 * _T_i1) + _i1) * 259) + ((-256 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        int  _ct17312 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17312); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 384; (_i2 <= 387); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L3[((((-8 * _T_i1) + _i1) * 259) + (_i2 - 256))] = 0;
          }
        }
      }
      if ((_T_i1 == 40))
      {
        for (int  _i1 = 320; (_i1 <= 323); _i1 = (_i1 + 1))
        {
          int  _ct17313 = ((387 < ((256 * _T_i2) + 258))? 387: ((256 * _T_i2) + 258));
          int  _ct17314 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17314; (_i2 <= _ct17313); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L3[(((_i1 - 320) * 259) + ((-256 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            int  _ct17315 = ((387 < ((256 * _T_i2) + 258))? 387: ((256 * _T_i2) + 258));
            int  _ct17316 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17316; (_i2 <= _ct17315); _i2 = (_i2 + 1))
            {
              Dx_inGPyramid_L3[((_i1 * 259) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i2 >= 0))
      {
        int  _ct17317 = ((321 < ((8 * _T_i1) + 7))? 321: ((8 * _T_i1) + 7));
        int  _ct17318 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17318; (_i1 <= _ct17317); _i1 = (_i1 + 1))
        {
          int  _ct17319 = ((193 < ((128 * _T_i2) + 129))? 193: ((128 * _T_i2) + 129));
          #pragma ivdep
          for (int  _i2 = ((128 * _T_i2) + 2); (_i2 <= _ct17319); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L3[((((-8 * _T_i1) + _i1) * 259) + (-3 + (2 * ((-128 * _T_i2) + _i2))))] + (3.0f * Dx_inGPyramid_L3[((((-8 * _T_i1) + _i1) * 259) + (-2 + (2 * ((-128 * _T_i2) + _i2))))])) + (3.0f * Dx_inGPyramid_L3[((((-8 * _T_i1) + _i1) * 259) + (-1 + (2 * ((-128 * _T_i2) + _i2))))])) + Dx_inGPyramid_L3[((((-8 * _T_i1) + _i1) * 259) + (2 * ((-128 * _T_i2) + _i2)))]) * 0.125f);
          }
        }
      }
    }
    free(Dx_inGPyramid_L3);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 20); _T_i1 = (_T_i1 + 1))
  {
    float * Dx_gPyramid_L4;
    Dx_gPyramid_L4 = (float *) (malloc((sizeof(float ) * ((8 * 8) * (((C / 8) + 3) + 1)))));
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17320 = ((163 < ((8 * _T_i1) + 7))? 163: ((8 * _T_i1) + 7));
      #pragma ivdep
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17320); _i1 = (_i1 + 1))
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17321 = ((163 < ((8 * _T_i1) + 7))? 163: ((8 * _T_i1) + 7));
      #pragma ivdep
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17321); _i1 = (_i1 + 1))
      {
        for (int  _i2 = 96; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
        }
      }
    }
    if ((_T_i1 == 20))
    {
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        #pragma ivdep
        for (int  _i1 = 160; (_i1 <= 163); _i1 = (_i1 + 1))
        {
          for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
    else
    {
      if ((_T_i1 == 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          #pragma ivdep
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
            {
              D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17322 = ((161 < ((8 * _T_i1) + 7))? 161: ((8 * _T_i1) + 7));
      int  _ct17323 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      #pragma ivdep
      for (int  _i1 = _ct17323; (_i1 <= _ct17322); _i1 = (_i1 + 1))
      {
        for (int  _i2 = 2; (_i2 <= 193); _i2 = (_i2 + 1))
        {
          Dx_gPyramid_L4[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + _i2)] = ((((D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + ((-3 + (2 * _i1)) * (((C / 8) + 3) + 1))) + _i2)] + (3.0f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + ((-2 + (2 * _i1)) * (((C / 8) + 3) + 1))) + _i2)])) + (3.0f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + ((-1 + (2 * _i1)) * (((C / 8) + 3) + 1))) + _i2)])) + D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + ((2 * _i1) * (((C / 8) + 3) + 1))) + _i2)]) * 0.125f);
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17324 = ((163 < ((8 * _T_i1) + 7))? 163: ((8 * _T_i1) + 7));
      #pragma ivdep
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17324); _i1 = (_i1 + 1))
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Dx_gPyramid_L4[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + _i2)] = 0;
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17325 = ((163 < ((8 * _T_i1) + 7))? 163: ((8 * _T_i1) + 7));
      #pragma ivdep
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17325); _i1 = (_i1 + 1))
      {
        for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          Dx_gPyramid_L4[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + _i2)] = 0;
        }
      }
    }
    if ((_T_i1 == 20))
    {
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        #pragma ivdep
        for (int  _i1 = 160; (_i1 <= 163); _i1 = (_i1 + 1))
        {
          for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L4[(((_i0 * (8 * (((C / 8) + 3) + 1))) + ((_i1 - 160) * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
    else
    {
      if ((_T_i1 == 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          #pragma ivdep
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L4[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17326 = ((161 < ((8 * _T_i1) + 7))? 161: ((8 * _T_i1) + 7));
      int  _ct17327 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      #pragma ivdep
      for (int  _i1 = _ct17327; (_i1 <= _ct17326); _i1 = (_i1 + 1))
      {
        for (int  _i2 = 2; (_i2 <= 97); _i2 = (_i2 + 1))
        {
          D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L4[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L4[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L4[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L4[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + (2 * _i2))]) * 0.125f);
        }
      }
    }
    free(Dx_gPyramid_L4);
  }
  for (int  _i1 = 0; (_i1 <= 163); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 2))
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        if ((_i1 >= 160))
        {
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 >= 162))
      {
        for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
        for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        for (int  _i2 = 2; (_i2 <= 193); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L3[(((-3 + (2 * _i1)) * (((C / 8) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L3[(((-2 + (2 * _i1)) * (((C / 8) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L3[(((-1 + (2 * _i1)) * (((C / 8) + 3) + 1)) + _i2)])) + D_inGPyramid_L3[(((2 * _i1) * (((C / 8) + 3) + 1)) + _i2)]) * 0.125f);
          if ((_i2 >= 192))
          {
            Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
          if ((_i1 >= 160))
          {
            Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
        for (int  _i2 = 194; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          if ((_i1 >= 160))
          {
            Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
    else
    {
      for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 192))
        {
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
        Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        if ((_i2 <= 1))
        {
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 82))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
          else
          {
            if ((_i2 >= 96))
            {
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            if ((_i2 <= 1))
            {
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
            Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            if ((_i2 >= 96))
            {
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
        else
        {
          if ((_i1 <= 79))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
          }
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 97); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = ((((D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + ((-3 + (2 * _i1)) * (((C / 16) + 3) + 1))) + _i2)] + (3.0f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + ((-2 + (2 * _i1)) * (((C / 16) + 3) + 1))) + _i2)])) + (3.0f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + ((-1 + (2 * _i1)) * (((C / 16) + 3) + 1))) + _i2)])) + D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + ((2 * _i1) * (((C / 16) + 3) + 1))) + _i2)]) * 0.125f);
            if ((_i1 >= 80))
            {
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i2 >= 96))
            {
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 79))
          {
            #pragma ivdep
            for (int  _i2 = 98; (_i2 <= 99); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 98; (_i2 <= 99); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 163); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 162))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
      {
        if ((_i2 <= 1))
        {
          D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
        D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 96))
        {
          D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      if ((_i1 <= 159))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
          for (int  _i2 = 96; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 >= 2))
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 97); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + (-3 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + (-2 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + (-1 + (2 * _i2)))])) + Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + (2 * _i2))]) * 0.125f);
          if ((_i1 >= 160))
          {
            D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
          if ((_i2 >= 96))
          {
            D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 159))
        {
          for (int  _i2 = 98; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 98; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 82))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
          D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 48))
          {
            D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
          {
            if ((_i2 <= 1))
            {
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
            else
            {
              if ((_i2 >= 48))
              {
                D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
              }
            }
            D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          if ((_i1 <= 79))
          {
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
          }
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 49); _i2 = (_i2 + 1))
          {
            if ((_i2 >= 48))
            {
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i1 >= 80))
            {
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
            D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + (2 * _i2))]) * 0.125f);
          }
          if ((_i1 <= 79))
          {
            for (int  _i2 = 50; (_i2 <= 51); _i2 = (_i2 + 1))
            {
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            for (int  _i2 = 50; (_i2 <= 51); _i2 = (_i2 + 1))
            {
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 82))
    {
      for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 96))
        {
          Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
        else
        {
          if ((_i2 <= 1))
          {
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
        Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
          else
          {
            if ((_i2 >= 96))
            {
              Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        if ((_i1 <= 79))
        {
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 97); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L4[(((-3 + (2 * _i1)) * (((C / 16) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L4[(((-2 + (2 * _i1)) * (((C / 16) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L4[(((-1 + (2 * _i1)) * (((C / 16) + 3) + 1)) + _i2)])) + D_inGPyramid_L4[(((2 * _i1) * (((C / 16) + 3) + 1)) + _i2)]) * 0.125f);
          if ((_i2 >= 96))
          {
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
          if ((_i1 >= 80))
          {
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 79))
        {
          for (int  _i2 = 98; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 98; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 42))
      {
        for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
          Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 48))
          {
            Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 39))
        {
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            if ((_i1 <= 1))
            {
              Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 1))
          {
            for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
            for (int  _i2 = 48; (_i2 <= 51); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
              Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 >= 2))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 49); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = ((((D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((-3 + (2 * _i1)) * (((C / 32) + 3) + 1))) + _i2)] + (3.0f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((-2 + (2 * _i1)) * (((C / 32) + 3) + 1))) + _i2)])) + (3.0f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((-1 + (2 * _i1)) * (((C / 32) + 3) + 1))) + _i2)])) + D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((2 * _i1) * (((C / 32) + 3) + 1))) + _i2)]) * 0.125f);
            if ((_i1 >= 40))
            {
              Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i2 >= 48))
            {
              Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 39))
          {
            for (int  _i2 = 50; (_i2 <= 51); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            for (int  _i2 = 50; (_i2 <= 51); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
              Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 2))
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        if ((_i1 >= 80))
        {
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 >= 82))
      {
        for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
        for (int  _i2 = 48; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 49); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + (-3 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + (-2 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + (-1 + (2 * _i2)))])) + Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + (2 * _i2))]) * 0.125f);
          if ((_i2 >= 48))
          {
            D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
          if ((_i1 >= 80))
          {
            D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
        }
        for (int  _i2 = 50; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          if ((_i1 >= 80))
          {
            D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
    else
    {
      for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 48))
        {
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
        D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        if ((_i2 <= 1))
        {
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 42))
      {
        for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 24))
          {
            D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
          D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 1))
        {
          for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
          {
            D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            if ((_i2 >= 24))
            {
              D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
            else
            {
              if ((_i2 <= 1))
              {
                D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
        }
        else
        {
          if ((_i1 <= 39))
          {
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
          }
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 25); _i2 = (_i2 + 1))
          {
            if ((_i2 >= 24))
            {
              D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
            D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + (2 * _i2))]) * 0.125f);
            if ((_i1 >= 40))
            {
              D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 39))
          {
            for (int  _i2 = 26; (_i2 <= 27); _i2 = (_i2 + 1))
            {
              D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            for (int  _i2 = 26; (_i2 <= 27); _i2 = (_i2 + 1))
            {
              D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 2))
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        if ((_i1 >= 40))
        {
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 >= 42))
      {
        for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
        for (int  _i2 = 48; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 49); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L5[(((-3 + (2 * _i1)) * (((C / 32) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L5[(((-2 + (2 * _i1)) * (((C / 32) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L5[(((-1 + (2 * _i1)) * (((C / 32) + 3) + 1)) + _i2)])) + D_inGPyramid_L5[(((2 * _i1) * (((C / 32) + 3) + 1)) + _i2)]) * 0.125f);
          if ((_i2 >= 48))
          {
            Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
          if ((_i1 >= 40))
          {
            Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
        }
        for (int  _i2 = 50; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          if ((_i1 >= 40))
          {
            Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
    else
    {
      for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 48))
        {
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
        Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        if ((_i2 <= 1))
        {
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 23); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 22))
      {
        for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
          Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 24))
          {
            Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 19))
        {
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            if ((_i1 <= 1))
            {
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 1))
          {
            for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
            for (int  _i2 = 24; (_i2 <= 27); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 >= 2))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 25); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = ((((D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + ((-3 + (2 * _i1)) * (((C / 64) + 3) + 1))) + _i2)] + (3.0f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + ((-2 + (2 * _i1)) * (((C / 64) + 3) + 1))) + _i2)])) + (3.0f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + ((-1 + (2 * _i1)) * (((C / 64) + 3) + 1))) + _i2)])) + D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + ((2 * _i1) * (((C / 64) + 3) + 1))) + _i2)]) * 0.125f);
            if ((_i1 >= 20))
            {
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i2 >= 24))
            {
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 19))
          {
            for (int  _i2 = 26; (_i2 <= 27); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            for (int  _i2 = 26; (_i2 <= 27); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 42))
    {
      for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
      {
        if ((_i2 <= 1))
        {
          D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
        D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 24))
        {
          D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      if ((_i1 <= 39))
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
          for (int  _i2 = 24; (_i2 <= 27); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 >= 2))
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 25); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (-3 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (-2 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (-1 + (2 * _i2)))])) + Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (2 * _i2))]) * 0.125f);
          if ((_i1 >= 40))
          {
            D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
          if ((_i2 >= 24))
          {
            D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 39))
        {
          for (int  _i2 = 26; (_i2 <= 27); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 26; (_i2 <= 27); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 23); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 20))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 15); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          }
          else
          {
            if ((_i2 >= 12))
            {
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            }
            if (((_i1 <= 21) && (_i2 <= 13)))
            {
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (2 * _i2))]) * 0.125f);
            }
          }
          D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
        }
      }
      else
      {
        if ((_i1 <= 1))
        {
          for (int  _i2 = 0; (_i2 <= 15); _i2 = (_i2 + 1))
          {
            D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            if ((_i2 >= 12))
            {
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            }
            else
            {
              if ((_i2 <= 1))
              {
                D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          }
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
          {
            D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (2 * _i2))]) * 0.125f);
          }
          #pragma ivdep
          for (int  _i2 = 12; (_i2 <= 15); _i2 = (_i2 + 1))
          {
            if ((_i2 <= 13))
            {
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (2 * _i2))]) * 0.125f);
            }
            D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 23); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 22))
    {
      for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
      {
        if ((_i2 <= 1))
        {
          Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
        Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 24))
        {
          Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      if ((_i1 <= 19))
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
          for (int  _i2 = 24; (_i2 <= 27); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
            Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 >= 2))
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 25); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L6[(((-3 + (2 * _i1)) * (((C / 64) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L6[(((-2 + (2 * _i1)) * (((C / 64) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L6[(((-1 + (2 * _i1)) * (((C / 64) + 3) + 1)) + _i2)])) + D_inGPyramid_L6[(((2 * _i1) * (((C / 64) + 3) + 1)) + _i2)]) * 0.125f);
          if ((_i1 >= 20))
          {
            Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
          if ((_i2 >= 24))
          {
            Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 19))
        {
          for (int  _i2 = 26; (_i2 <= 27); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 26; (_i2 <= 27); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
            Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 40))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 15); _i2 = (_i2 + 1))
        {
          if ((((_i1 == 40) && (_i2 <= 13)) && (_i2 >= 2)))
          {
            Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (40 * (((C / 128) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + ((40 / 2) * (((C / 128) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((40 / 2) + 1) * (((C / 128) + 3) + 1))) + _i2)]));
          }
          Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 12))
          {
            Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          }
          else
          {
            if ((_i2 <= 1))
            {
              Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((((_i1 == 41) && (_i2 <= 13)) && (_i2 >= 2)))
          {
            Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (41 * (((C / 128) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((41 / 2) + 2) * (((C / 128) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((41 / 2) + 1) * (((C / 128) + 3) + 1))) + _i2)]));
          }
        }
      }
      else
      {
        if ((_i1 <= 1))
        {
          for (int  _i2 = 0; (_i2 <= 15); _i2 = (_i2 + 1))
          {
            if ((_i2 >= 12))
            {
              Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            }
            Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            if ((_i2 <= 1))
            {
              Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          }
          if ((((_i1 + 1) % 2) == 0))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 128) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 128) + 3) + 1))) + _i2)]));
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + ((_i1 / 2) * (((C / 128) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 128) + 3) + 1))) + _i2)]));
            }
          }
          #pragma ivdep
          for (int  _i2 = 12; (_i2 <= 15); _i2 = (_i2 + 1))
          {
            if ((((_i1 % 2) == 0) && (_i2 <= 13)))
            {
              Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + ((_i1 / 2) * (((C / 128) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 128) + 3) + 1))) + _i2)]));
            }
            Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            if (((((_i1 - 1) % 2) == 0) && (_i2 <= 13)))
            {
              Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 128) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 128) + 3) + 1))) + _i2)]));
            }
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 23); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 22))
    {
      for (int  _i2 = 0; (_i2 <= 15); _i2 = (_i2 + 1))
      {
        if ((_i2 <= 1))
        {
          D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        }
        D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 12))
        {
          D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      if ((_i1 <= 19))
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          }
          for (int  _i2 = 12; (_i2 <= 15); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 >= 2))
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 13); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + (-3 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + (-2 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + (-1 + (2 * _i2)))])) + Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + (2 * _i2))]) * 0.125f);
          if ((_i1 >= 20))
          {
            D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          }
          if ((_i2 >= 12))
          {
            D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 19))
        {
          for (int  _i2 = 14; (_i2 <= 15); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 14; (_i2 <= 15); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 40))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
        {
          U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 24))
          {
            U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
          if ((((((_i2 % 2) == 0) && (_i2 <= 24)) && (_i1 <= 41)) && (_i2 >= 2)))
          {
            U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = (D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 25)) && (_i1 <= 41)) && (_i2 >= 3)))
            {
              U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = (D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              if ((_i2 <= 1))
              {
                U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
        }
      }
      else
      {
        if ((_i1 <= 1))
        {
          for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
          {
            if ((_i2 <= 1))
            {
              U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
            else
            {
              if ((_i2 >= 24))
              {
                U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
              }
            }
            U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
          {
            if ((((_i2 - 1) % 2) == 0))
            {
              U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = (D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = (D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
          }
          #pragma ivdep
          for (int  _i2 = 24; (_i2 <= 27); _i2 = (_i2 + 1))
          {
            if ((_i2 == 24))
            {
              U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + 24)] = (D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + 24)] - ((0.25f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + (24 / 2))]) + (0.75f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((24 / 2) + 1))])));
            }
            else
            {
              if ((_i2 == 25))
              {
                U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + 25)] = (D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + 25)] - ((0.25f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((25 / 2) + 2))]) + (0.75f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((25 / 2) + 1))])));
              }
            }
            U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 23); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 0; (_i2 <= 15); _i2 = (_i2 + 1))
    {
      int  _ct17328 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17329 = 0;
      int  _ct17330 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17328: _ct17329);
      int  _ct17331 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17332 = 0;
      int  _ct17333 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17331: _ct17332);
      int  _ct17334 = _ct17333;
      int  _ct17335 = 6;
      int  _ct17336 = ((_ct17330 < 6)? _ct17334: _ct17335);
      int  _ct17337 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17338 = 0;
      int  _ct17339 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17337: _ct17338);
      int  _ct17340 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17341 = 0;
      int  _ct17342 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17340: _ct17341);
      int  _ct17343 = _ct17342;
      int  _ct17344 = 6;
      int  _ct17345 = ((_ct17339 < 6)? _ct17343: _ct17344);
      int  _ct17346 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17347 = 0;
      int  _ct17348 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17346: _ct17347);
      int  _ct17349 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17350 = 0;
      int  _ct17351 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17349: _ct17350);
      int  _ct17352 = _ct17351;
      int  _ct17353 = 6;
      int  _ct17354 = ((_ct17348 < 6)? _ct17352: _ct17353);
      int  _ct17355 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17356 = 0;
      int  _ct17357 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17355: _ct17356);
      int  _ct17358 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17359 = 0;
      int  _ct17360 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17358: _ct17359);
      int  _ct17361 = _ct17360;
      int  _ct17362 = 6;
      int  _ct17363 = ((_ct17357 < 6)? _ct17361: _ct17362);
      outLPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = (((1.0f - ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17336)) * D_gPyramid_L7[(((_ct17345 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)]) + (((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17354) * D_gPyramid_L7[((((_ct17363 + 1) * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)]));
    }
  }
  for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
    {
      int  _ct17364 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17365 = 0;
      int  _ct17366 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17364: _ct17365);
      int  _ct17367 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17368 = 0;
      int  _ct17369 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17367: _ct17368);
      int  _ct17370 = _ct17369;
      int  _ct17371 = 6;
      int  _ct17372 = ((_ct17366 < 6)? _ct17370: _ct17371);
      int  _ct17373 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17374 = 0;
      int  _ct17375 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17373: _ct17374);
      int  _ct17376 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17377 = 0;
      int  _ct17378 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17376: _ct17377);
      int  _ct17379 = _ct17378;
      int  _ct17380 = 6;
      int  _ct17381 = ((_ct17375 < 6)? _ct17379: _ct17380);
      int  _ct17382 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17383 = 0;
      int  _ct17384 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17382: _ct17383);
      int  _ct17385 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17386 = 0;
      int  _ct17387 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17385: _ct17386);
      int  _ct17388 = _ct17387;
      int  _ct17389 = 6;
      int  _ct17390 = ((_ct17384 < 6)? _ct17388: _ct17389);
      int  _ct17391 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17392 = 0;
      int  _ct17393 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17391: _ct17392);
      int  _ct17394 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17395 = 0;
      int  _ct17396 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17394: _ct17395);
      int  _ct17397 = _ct17396;
      int  _ct17398 = 6;
      int  _ct17399 = ((_ct17393 < 6)? _ct17397: _ct17398);
      outLPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = (((1.0f - ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17372)) * U_lPyramid_L6[(((_ct17381 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)]) + (((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17390) * U_lPyramid_L6[((((_ct17399 + 1) * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)]));
    }
  }
  for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 40))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 15); _i2 = (_i2 + 1))
      {
        if ((_i2 <= 1))
        {
          Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        }
        Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 12))
        {
          Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        }
        if ((((_i1 == 40) && (_i2 <= 13)) && (_i2 >= 2)))
        {
          Ux_outGPyramid_L6[((40 * (((C / 128) + 3) + 1)) + _i2)] = ((0.25f * outLPyramid_L7[(((40 / 2) * (((C / 128) + 3) + 1)) + _i2)]) + (0.75f * outLPyramid_L7[((((40 / 2) + 1) * (((C / 128) + 3) + 1)) + _i2)]));
        }
        else
        {
          if ((((_i1 == 41) && (_i2 <= 13)) && (_i2 >= 2)))
          {
            Ux_outGPyramid_L6[((41 * (((C / 128) + 3) + 1)) + _i2)] = ((0.25f * outLPyramid_L7[((((41 / 2) + 2) * (((C / 128) + 3) + 1)) + _i2)]) + (0.75f * outLPyramid_L7[((((41 / 2) + 1) * (((C / 128) + 3) + 1)) + _i2)]));
          }
        }
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        for (int  _i2 = 0; (_i2 <= 15); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          }
          else
          {
            if ((_i2 >= 12))
            {
              Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
            }
          }
          Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        }
        if ((((_i1 + 1) % 2) == 0))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = ((0.25f * outLPyramid_L7[((((_i1 / 2) + 2) * (((C / 128) + 3) + 1)) + _i2)]) + (0.75f * outLPyramid_L7[((((_i1 / 2) + 1) * (((C / 128) + 3) + 1)) + _i2)]));
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = ((0.25f * outLPyramid_L7[(((_i1 / 2) * (((C / 128) + 3) + 1)) + _i2)]) + (0.75f * outLPyramid_L7[((((_i1 / 2) + 1) * (((C / 128) + 3) + 1)) + _i2)]));
          }
        }
        #pragma ivdep
        for (int  _i2 = 12; (_i2 <= 15); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          if ((((_i1 % 2) == 0) && (_i2 <= 13)))
          {
            Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = ((0.25f * outLPyramid_L7[(((_i1 / 2) * (((C / 128) + 3) + 1)) + _i2)]) + (0.75f * outLPyramid_L7[((((_i1 / 2) + 1) * (((C / 128) + 3) + 1)) + _i2)]));
          }
          else
          {
            if (((((_i1 - 1) % 2) == 0) && (_i2 <= 13)))
            {
              Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = ((0.25f * outLPyramid_L7[((((_i1 / 2) + 2) * (((C / 128) + 3) + 1)) + _i2)]) + (0.75f * outLPyramid_L7[((((_i1 / 2) + 1) * (((C / 128) + 3) + 1)) + _i2)]));
            }
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 80))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
        {
          if ((((_i1 == 80) && (_i2 <= 25)) && (_i2 >= 2)))
          {
            Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (80 * (((C / 64) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + ((80 / 2) * (((C / 64) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (((80 / 2) + 1) * (((C / 64) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((_i1 == 81) && (_i2 <= 25)) && (_i2 >= 2)))
            {
              Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (81 * (((C / 64) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (((81 / 2) + 2) * (((C / 64) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (((81 / 2) + 1) * (((C / 64) + 3) + 1))) + _i2)]));
            }
            else
            {
              if ((_i2 <= 1))
              {
                Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
          Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 24))
          {
            Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          if ((((_i1 + 1) % 2) == 0))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 64) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 64) + 3) + 1))) + _i2)]));
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + ((_i1 / 2) * (((C / 64) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 64) + 3) + 1))) + _i2)]));
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 24; (_i2 <= 27); _i2 = (_i2 + 1))
        {
          if (((((_i1 % 2) == 0) && (_i2 <= 25)) && (_i1 >= 2)))
          {
            Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + ((_i1 / 2) * (((C / 64) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 64) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((((_i1 + 1) % 2) == 0) && (_i2 <= 25)) && (_i1 >= 3)))
            {
              Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 64) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 64) + 3) + 1))) + _i2)]));
            }
          }
          Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 40))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
      {
        if ((((((_i2 % 2) == 0) && (_i2 <= 24)) && (_i1 <= 41)) && (_i2 >= 2)))
        {
          outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = (outLPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + ((_i2 / 2) + 1))])));
        }
        else
        {
          if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 25)) && (_i1 <= 41)) && (_i2 >= 3)))
          {
            outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = (outLPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if ((_i2 <= 1))
            {
              outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
        outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 24))
        {
          outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 <= 1))
      {
        for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
        {
          outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
        {
          if (((_i2 % 2) == 0))
          {
            outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = (outLPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = (outLPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
        }
      }
      #pragma ivdep
      for (int  _i2 = 24; (_i2 <= 27); _i2 = (_i2 + 1))
      {
        if (((_i2 == 24) && (_i1 >= 2)))
        {
          outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + 24)] = (outLPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + 24)] + ((0.25f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + (24 / 2))]) + (0.75f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + ((24 / 2) + 1))])));
        }
        else
        {
          if (((_i2 == 25) && (_i1 >= 2)))
          {
            outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + 25)] = (outLPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + 25)] + ((0.25f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + ((25 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + ((25 / 2) + 1))])));
          }
        }
        outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 80))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          if ((((((_i2 % 2) == 0) && (_i2 <= 48)) && (_i1 <= 81)) && (_i2 >= 2)))
          {
            U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = (D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 49)) && (_i1 <= 81)) && (_i2 >= 3)))
            {
              U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = (D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              if ((_i2 <= 1))
              {
                U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
          U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 48))
          {
            U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
          {
            U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
          {
            if (((_i2 % 2) == 0))
            {
              U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = (D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = (D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 48; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          if (((_i2 == 48) && (_i1 >= 2)))
          {
            U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + 48)] = (D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + 48)] - ((0.25f * Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (48 / 2))]) + (0.75f * Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + ((48 / 2) + 1))])));
          }
          else
          {
            if (((_i2 == 49) && (_i1 >= 2)))
            {
              U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + 49)] = (D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + 49)] - ((0.25f * Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + ((49 / 2) + 2))]) + (0.75f * Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + ((49 / 2) + 1))])));
            }
          }
          U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 2))
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        if ((_i1 >= 80))
        {
          Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 == 82))
      {
        for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L5[((82 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        if ((_i1 == 83))
        {
          for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L5[((83 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          if ((((_i1 + 1) % 2) == 0))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
            {
              Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L6[((((_i1 / 2) + 2) * (((C / 64) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L6[((((_i1 / 2) + 1) * (((C / 64) + 3) + 1)) + _i2)]));
              if ((_i1 == 81))
              {
                Ux_outGPyramid_L5[((81 * (((C / 64) + 3) + 1)) + _i2)] = 0;
              }
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
            {
              Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L6[(((_i1 / 2) * (((C / 64) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L6[((((_i1 / 2) + 1) * (((C / 64) + 3) + 1)) + _i2)]));
              if ((_i1 == 80))
              {
                Ux_outGPyramid_L5[((80 * (((C / 64) + 3) + 1)) + _i2)] = 0;
              }
            }
          }
        }
      }
      #pragma ivdep
      for (int  _i2 = 24; (_i2 <= 27); _i2 = (_i2 + 1))
      {
        if (((((_i1 % 2) == 0) && (_i1 <= 80)) && (_i2 <= 25)))
        {
          Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L6[(((_i1 / 2) * (((C / 64) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L6[((((_i1 / 2) + 1) * (((C / 64) + 3) + 1)) + _i2)]));
        }
        else
        {
          if ((((((_i1 - 1) % 2) == 0) && (_i1 <= 81)) && (_i2 <= 25)))
          {
            Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L6[((((_i1 / 2) + 2) * (((C / 64) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L6[((((_i1 / 2) + 1) * (((C / 64) + 3) + 1)) + _i2)]));
          }
        }
        Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        if ((_i1 >= 80))
        {
          Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        if ((_i2 <= 1))
        {
          Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
        else
        {
          if ((_i2 >= 24))
          {
            Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
    {
      int  _ct17400 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17401 = 0;
      int  _ct17402 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17400: _ct17401);
      int  _ct17403 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17404 = 0;
      int  _ct17405 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17403: _ct17404);
      int  _ct17406 = _ct17405;
      int  _ct17407 = 6;
      int  _ct17408 = ((_ct17402 < 6)? _ct17406: _ct17407);
      int  _ct17409 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17410 = 0;
      int  _ct17411 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17409: _ct17410);
      int  _ct17412 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17413 = 0;
      int  _ct17414 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17412: _ct17413);
      int  _ct17415 = _ct17414;
      int  _ct17416 = 6;
      int  _ct17417 = ((_ct17411 < 6)? _ct17415: _ct17416);
      int  _ct17418 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17419 = 0;
      int  _ct17420 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17418: _ct17419);
      int  _ct17421 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17422 = 0;
      int  _ct17423 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17421: _ct17422);
      int  _ct17424 = _ct17423;
      int  _ct17425 = 6;
      int  _ct17426 = ((_ct17420 < 6)? _ct17424: _ct17425);
      int  _ct17427 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17428 = 0;
      int  _ct17429 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17427: _ct17428);
      int  _ct17430 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct17431 = 0;
      int  _ct17432 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17430: _ct17431);
      int  _ct17433 = _ct17432;
      int  _ct17434 = 6;
      int  _ct17435 = ((_ct17429 < 6)? _ct17433: _ct17434);
      outLPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = (((1.0f - ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17408)) * U_lPyramid_L5[(((_ct17417 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)]) + (((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17426) * U_lPyramid_L5[((((_ct17435 + 1) * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)]));
    }
  }
  for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 80))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
      {
        if ((((((_i2 % 2) == 0) && (_i2 <= 48)) && (_i1 <= 81)) && (_i2 >= 2)))
        {
          outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = (outLPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + ((_i2 / 2) + 1))])));
        }
        else
        {
          if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 49)) && (_i1 <= 81)) && (_i2 >= 3)))
          {
            outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = (outLPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if ((_i2 <= 1))
            {
              outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
        outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 48))
        {
          outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 <= 1))
      {
        for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
        {
          outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
        {
          if (((_i2 % 2) == 0))
          {
            outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = (outLPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = (outLPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
        }
      }
      #pragma ivdep
      for (int  _i2 = 48; (_i2 <= 51); _i2 = (_i2 + 1))
      {
        if (((_i2 == 48) && (_i1 >= 2)))
        {
          outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + 48)] = (outLPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + 48)] + ((0.25f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + (48 / 2))]) + (0.75f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + ((48 / 2) + 1))])));
        }
        else
        {
          if (((_i2 == 49) && (_i1 >= 2)))
          {
            outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + 49)] = (outLPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + 49)] + ((0.25f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + ((49 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + ((49 / 2) + 1))])));
          }
        }
        outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 163); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 160))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
      {
        if ((((_i1 == 160) && (_i2 <= 49)) && (_i2 >= 2)))
        {
          Ux_outGPyramid_L4[((160 * (((C / 32) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L5[(((160 / 2) * (((C / 32) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L5[((((160 / 2) + 1) * (((C / 32) + 3) + 1)) + _i2)]));
        }
        else
        {
          if ((((_i1 == 161) && (_i2 <= 49)) && (_i2 >= 2)))
          {
            Ux_outGPyramid_L4[((161 * (((C / 32) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L5[((((161 / 2) + 2) * (((C / 32) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L5[((((161 / 2) + 1) * (((C / 32) + 3) + 1)) + _i2)]));
          }
          else
          {
            if ((_i2 <= 1))
            {
              Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
        Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 48))
        {
          Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 <= 1))
      {
        for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        if ((((_i1 + 1) % 2) == 0))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L5[((((_i1 / 2) + 2) * (((C / 32) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L5[((((_i1 / 2) + 1) * (((C / 32) + 3) + 1)) + _i2)]));
          }
        }
        else
        {
          for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L5[(((_i1 / 2) * (((C / 32) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L5[((((_i1 / 2) + 1) * (((C / 32) + 3) + 1)) + _i2)]));
          }
        }
      }
      #pragma ivdep
      for (int  _i2 = 48; (_i2 <= 51); _i2 = (_i2 + 1))
      {
        if (((((_i1 % 2) == 0) && (_i2 <= 49)) && (_i1 >= 2)))
        {
          Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L5[(((_i1 / 2) * (((C / 32) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L5[((((_i1 / 2) + 1) * (((C / 32) + 3) + 1)) + _i2)]));
        }
        else
        {
          if ((((((_i1 + 1) % 2) == 0) && (_i2 <= 49)) && (_i1 >= 3)))
          {
            Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L5[((((_i1 / 2) + 2) * (((C / 32) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L5[((((_i1 / 2) + 1) * (((C / 32) + 3) + 1)) + _i2)]));
          }
        }
        Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 163); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 160))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          if ((((_i1 == 160) && (_i2 <= 49)) && (_i2 >= 2)))
          {
            Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (160 * (((C / 32) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((160 / 2) * (((C / 32) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((160 / 2) + 1) * (((C / 32) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((_i1 == 161) && (_i2 <= 49)) && (_i2 >= 2)))
            {
              Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (161 * (((C / 32) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((161 / 2) + 2) * (((C / 32) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((161 / 2) + 1) * (((C / 32) + 3) + 1))) + _i2)]));
            }
            else
            {
              if ((_i2 <= 1))
              {
                Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
          Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 48))
          {
            Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          if ((((_i1 + 1) % 2) == 0))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 32) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 32) + 3) + 1))) + _i2)]));
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((_i1 / 2) * (((C / 32) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 32) + 3) + 1))) + _i2)]));
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 48; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          if (((((_i1 % 2) == 0) && (_i2 <= 49)) && (_i1 >= 2)))
          {
            Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((_i1 / 2) * (((C / 32) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 32) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((((_i1 + 1) % 2) == 0) && (_i2 <= 49)) && (_i1 >= 3)))
            {
              Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 32) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 32) + 3) + 1))) + _i2)]));
            }
          }
          Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = -2; (_T_i1 <= 40); _T_i1 = (_T_i1 + 1))
  {
    float * U_lPyramid_L4;
    U_lPyramid_L4 = (float *) (malloc((sizeof(float ) * ((8 * 10) * (((C / 16) + 3) + 1)))));
    float * outGPyramid_L4;
    outGPyramid_L4 = (float *) (malloc((sizeof(float ) * (10 * (((C / 16) + 3) + 1)))));
    float * outLPyramid_L4;
    outLPyramid_L4 = (float *) (malloc((sizeof(float ) * (10 * (((C / 16) + 3) + 1)))));
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17436 = ((161 < ((4 * _T_i1) + 9))? 161: ((4 * _T_i1) + 9));
      int  _ct17437 = ((2 > (4 * _T_i1))? 2: (4 * _T_i1));
      for (int  _i1 = _ct17437; (_i1 <= _ct17436); _i1 = (_i1 + 1))
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 96); _i2 = (_i2 + 2))
        {
          U_lPyramid_L4[(((_i0 * (10 * (((C / 16) + 3) + 1))) + (((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + _i2)] = (D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + ((_i2 / 2) + 1))])));
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17438 = ((161 < ((4 * _T_i1) + 9))? 161: ((4 * _T_i1) + 9));
      int  _ct17439 = ((2 > (4 * _T_i1))? 2: (4 * _T_i1));
      for (int  _i1 = _ct17439; (_i1 <= _ct17438); _i1 = (_i1 + 1))
      {
        #pragma ivdep
        for (int  _i2 = 3; (_i2 <= 97); _i2 = (_i2 + 2))
        {
          U_lPyramid_L4[(((_i0 * (10 * (((C / 16) + 3) + 1))) + (((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + _i2)] = (D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + ((_i2 / 2) + 1))])));
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17440 = ((163 < ((4 * _T_i1) + 9))? 163: ((4 * _T_i1) + 9));
      int  _ct17441 = ((0 > (4 * _T_i1))? 0: (4 * _T_i1));
      #pragma ivdep
      for (int  _i1 = _ct17441; (_i1 <= _ct17440); _i1 = (_i1 + 1))
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          U_lPyramid_L4[(((_i0 * (10 * (((C / 16) + 3) + 1))) + (((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + _i2)] = 0;
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17442 = ((163 < ((4 * _T_i1) + 9))? 163: ((4 * _T_i1) + 9));
      int  _ct17443 = ((0 > (4 * _T_i1))? 0: (4 * _T_i1));
      #pragma ivdep
      for (int  _i1 = _ct17443; (_i1 <= _ct17442); _i1 = (_i1 + 1))
      {
        for (int  _i2 = 96; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          U_lPyramid_L4[(((_i0 * (10 * (((C / 16) + 3) + 1))) + (((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + _i2)] = 0;
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17444 = ((163 < ((4 * _T_i1) + 9))? 163: ((4 * _T_i1) + 9));
      for (int  _i1 = 160; (_i1 <= _ct17444); _i1 = (_i1 + 1))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          U_lPyramid_L4[(((_i0 * (10 * (((C / 16) + 3) + 1))) + (((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + _i2)] = 0;
        }
      }
    }
    if ((_T_i1 <= 0))
    {
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            U_lPyramid_L4[(((_i0 * (10 * (((C / 16) + 3) + 1))) + (((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
    int  _ct17445 = ((323 < ((8 * _T_i1) + 19))? 323: ((8 * _T_i1) + 19));
    int  _ct17446 = ((0 > (8 * _T_i1))? 0: (8 * _T_i1));
    #pragma ivdep
    for (int  _i1 = _ct17446; (_i1 <= _ct17445); _i1 = (_i1 + 1))
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
      }
    }
    int  _ct17447 = ((323 < ((8 * _T_i1) + 19))? 323: ((8 * _T_i1) + 19));
    int  _ct17448 = ((0 > (8 * _T_i1))? 0: (8 * _T_i1));
    #pragma ivdep
    for (int  _i1 = _ct17448; (_i1 <= _ct17447); _i1 = (_i1 + 1))
    {
      for (int  _i2 = 96; (_i2 <= 99); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
      }
    }
    if ((_T_i1 >= 38))
    {
      for (int  _i1 = 320; (_i1 <= 323); _i1 = (_i1 + 1))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      if ((_T_i1 <= 0))
      {
        #pragma ivdep
        for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
        {
          for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
    int  _ct17449 = ((163 < ((4 * _T_i1) + 9))? 163: ((4 * _T_i1) + 9));
    int  _ct17450 = ((0 > (4 * _T_i1))? 0: (4 * _T_i1));
    #pragma ivdep
    for (int  _i1 = _ct17450; (_i1 <= _ct17449); _i1 = (_i1 + 1))
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        outGPyramid_L4[((((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1)) + _i2)] = 0;
      }
    }
    int  _ct17451 = ((163 < ((4 * _T_i1) + 9))? 163: ((4 * _T_i1) + 9));
    int  _ct17452 = ((0 > (4 * _T_i1))? 0: (4 * _T_i1));
    #pragma ivdep
    for (int  _i1 = _ct17452; (_i1 <= _ct17451); _i1 = (_i1 + 1))
    {
      for (int  _i2 = 96; (_i2 <= 99); _i2 = (_i2 + 1))
      {
        outGPyramid_L4[((((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1)) + _i2)] = 0;
      }
    }
    if ((_T_i1 <= 0))
    {
      #pragma ivdep
      for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
      {
        for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          outGPyramid_L4[((((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    int  _ct17453 = ((163 < ((4 * _T_i1) + 9))? 163: ((4 * _T_i1) + 9));
    #pragma ivdep
    for (int  _i1 = 160; (_i1 <= _ct17453); _i1 = (_i1 + 1))
    {
      for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
      {
        outGPyramid_L4[((((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1)) + _i2)] = 0;
      }
    }
    int  _ct17454 = ((163 < ((4 * _T_i1) + 7))? 163: ((4 * _T_i1) + 7));
    int  _ct17455 = ((0 > (4 * _T_i1))? 0: (4 * _T_i1));
    for (int  _i1 = _ct17455; (_i1 <= _ct17454); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
      {
        int  _ct17456 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17457 = 0;
        int  _ct17458 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17456: _ct17457);
        int  _ct17459 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17460 = 0;
        int  _ct17461 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17459: _ct17460);
        int  _ct17462 = _ct17461;
        int  _ct17463 = 6;
        int  _ct17464 = ((_ct17458 < 6)? _ct17462: _ct17463);
        int  _ct17465 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17466 = 0;
        int  _ct17467 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17465: _ct17466);
        int  _ct17468 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17469 = 0;
        int  _ct17470 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17468: _ct17469);
        int  _ct17471 = _ct17470;
        int  _ct17472 = 6;
        int  _ct17473 = ((_ct17467 < 6)? _ct17471: _ct17472);
        int  _ct17474 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17475 = 0;
        int  _ct17476 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17474: _ct17475);
        int  _ct17477 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17478 = 0;
        int  _ct17479 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17477: _ct17478);
        int  _ct17480 = _ct17479;
        int  _ct17481 = 6;
        int  _ct17482 = ((_ct17476 < 6)? _ct17480: _ct17481);
        int  _ct17483 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17484 = 0;
        int  _ct17485 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17483: _ct17484);
        int  _ct17486 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17487 = 0;
        int  _ct17488 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17486: _ct17487);
        int  _ct17489 = _ct17488;
        int  _ct17490 = 6;
        int  _ct17491 = ((_ct17485 < 6)? _ct17489: _ct17490);
        outLPyramid_L4[((((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1)) + _i2)] = (((1.0f - ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17464)) * U_lPyramid_L4[(((_ct17473 * (10 * (((C / 16) + 3) + 1))) + (((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + _i2)]) + (((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17482) * U_lPyramid_L4[((((_ct17491 + 1) * (10 * (((C / 16) + 3) + 1))) + (((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + _i2)]));
      }
    }
    int  _ct17492 = ((161 < ((4 * _T_i1) + 5))? 161: ((4 * _T_i1) + 5));
    int  _ct17493 = ((2 > (4 * _T_i1))? 2: (4 * _T_i1));
    for (int  _i1 = _ct17493; (_i1 <= _ct17492); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 2; (_i2 <= 96); _i2 = (_i2 + 2))
      {
        outGPyramid_L4[((((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1)) + _i2)] = (outLPyramid_L4[((((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + ((_i2 / 2) + 1))])));
      }
    }
    int  _ct17494 = ((161 < ((4 * _T_i1) + 5))? 161: ((4 * _T_i1) + 5));
    int  _ct17495 = ((2 > (4 * _T_i1))? 2: (4 * _T_i1));
    for (int  _i1 = _ct17495; (_i1 <= _ct17494); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 3; (_i2 <= 97); _i2 = (_i2 + 2))
      {
        outGPyramid_L4[((((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1)) + _i2)] = (outLPyramid_L4[((((-4 * _T_i1) + _i1) * (((C / 16) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + ((_i2 / 2) + 1))])));
      }
    }
    int  _ct17496 = ((320 < ((8 * _T_i1) + 6))? 320: ((8 * _T_i1) + 6));
    int  _ct17497 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
    for (int  _i1 = _ct17497; (_i1 <= _ct17496); _i1 = (_i1 + 2))
    {
      #pragma ivdep
      for (int  _i2 = 2; (_i2 <= 97); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L4[(((((-8 * _T_i1) + _i1) / 2) * (((C / 16) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L4[((((((-8 * _T_i1) + _i1) / 2) + 1) * (((C / 16) + 3) + 1)) + _i2)]));
      }
    }
    int  _ct17498 = ((321 < ((8 * _T_i1) + 7))? 321: ((8 * _T_i1) + 7));
    int  _ct17499 = ((3 > ((8 * _T_i1) + 1))? 3: ((8 * _T_i1) + 1));
    for (int  _i1 = _ct17499; (_i1 <= _ct17498); _i1 = (_i1 + 2))
    {
      #pragma ivdep
      for (int  _i2 = 2; (_i2 <= 97); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L4[((((((-8 * _T_i1) + _i1) / 2) + 2) * (((C / 16) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L4[((((((-8 * _T_i1) + _i1) / 2) + 1) * (((C / 16) + 3) + 1)) + _i2)]));
      }
    }
    free(U_lPyramid_L4);
    free(outGPyramid_L4);
    free(outLPyramid_L4);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 40); _T_i1 = (_T_i1 + 1))
  {
    float * Ux_lPyramid_L3;
    Ux_lPyramid_L3 = (float *) (malloc((sizeof(float ) * ((8 * 8) * (((C / 16) + 3) + 1)))));
    float * U_lPyramid_L3;
    U_lPyramid_L3 = (float *) (malloc((sizeof(float ) * ((8 * 8) * (((C / 8) + 3) + 1)))));
    float * outLPyramid_L3;
    outLPyramid_L3 = (float *) (malloc((sizeof(float ) * (8 * (((C / 8) + 3) + 1)))));
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17500 = ((320 < ((8 * _T_i1) + 6))? 320: ((8 * _T_i1) + 6));
      int  _ct17501 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17501; (_i1 <= _ct17500); _i1 = (_i1 + 2))
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 97); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L3[(((_i0 * (8 * (((C / 16) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + ((_i1 / 2) * (((C / 16) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 16) + 3) + 1))) + _i2)]));
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17502 = ((321 < ((8 * _T_i1) + 7))? 321: ((8 * _T_i1) + 7));
      int  _ct17503 = ((3 > ((8 * _T_i1) + 1))? 3: ((8 * _T_i1) + 1));
      for (int  _i1 = _ct17503; (_i1 <= _ct17502); _i1 = (_i1 + 2))
      {
      #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 97); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L3[(((_i0 * (8 * (((C / 16) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 16) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 16) + 3) + 1))) + _i2)]));
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17504 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
      #pragma ivdep
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17504); _i1 = (_i1 + 1))
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L3[(((_i0 * (8 * (((C / 16) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + _i2)] = 0;
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17505 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
      #pragma ivdep
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17505); _i1 = (_i1 + 1))
      {
        for (int  _i2 = 96; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L3[(((_i0 * (8 * (((C / 16) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + _i2)] = 0;
        }
      }
    }
    if ((_T_i1 == 40))
    {
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        for (int  _i1 = 320; (_i1 <= 323); _i1 = (_i1 + 1))
        {
        #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L3[(((_i0 * (8 * (((C / 16) + 3) + 1))) + ((_i1 - 320) * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
    else
    {
      if ((_T_i1 == 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
          #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L3[(((_i0 * (8 * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
    int  _ct17506 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
    #pragma ivdep
    for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17506); _i1 = (_i1 + 1))
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
      }
    }
    int  _ct17507 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
    #pragma ivdep
    for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17507); _i1 = (_i1 + 1))
    {
      for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
      {
        outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
      }
    }
    if ((_T_i1 == 40))
    {
      for (int  _i1 = 320; (_i1 <= 323); _i1 = (_i1 + 1))
      {
      #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      if ((_T_i1 == 0))
      {
        for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
          {
            outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17508 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17508); _i1 = (_i1 + 1))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          U_lPyramid_L3[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + _i2)] = 0;
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17509 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17509); _i1 = (_i1 + 1))
      {
        #pragma ivdep
        for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          U_lPyramid_L3[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + _i2)] = 0;
        }
      }
    }
    if ((_T_i1 == 40))
    {
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        for (int  _i1 = 320; (_i1 <= 323); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
          {
            U_lPyramid_L3[(((_i0 * (8 * (((C / 8) + 3) + 1))) + ((_i1 - 320) * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
    else
    {
      if ((_T_i1 == 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
          #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
            {
              U_lPyramid_L3[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17510 = ((321 < ((8 * _T_i1) + 7))? 321: ((8 * _T_i1) + 7));
      int  _ct17511 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17511; (_i1 <= _ct17510); _i1 = (_i1 + 1))
      {
      #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 192); _i2 = (_i2 + 2))
        {
          U_lPyramid_L3[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + _i2)] = (D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L3[(((_i0 * (8 * (((C / 16) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L3[(((_i0 * (8 * (((C / 16) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + ((_i2 / 2) + 1))])));
        }
      }
    }
    for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
    {
      int  _ct17512 = ((321 < ((8 * _T_i1) + 7))? 321: ((8 * _T_i1) + 7));
      int  _ct17513 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17513; (_i1 <= _ct17512); _i1 = (_i1 + 1))
      {
      #pragma ivdep
        for (int  _i2 = 3; (_i2 <= 193); _i2 = (_i2 + 2))
        {
          U_lPyramid_L3[(((_i0 * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + _i2)] = (D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L3[(((_i0 * (8 * (((C / 16) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L3[(((_i0 * (8 * (((C / 16) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 16) + 3) + 1))) + ((_i2 / 2) + 1))])));
        }
      }
    }
    int  _ct17514 = ((323 < ((8 * _T_i1) + 7))? 323: ((8 * _T_i1) + 7));
    for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17514); _i1 = (_i1 + 1))
    {
    #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
      {
        int  _ct17515 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17516 = 0;
        int  _ct17517 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17515: _ct17516);
        int  _ct17518 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17519 = 0;
        int  _ct17520 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17518: _ct17519);
        int  _ct17521 = _ct17520;
        int  _ct17522 = 6;
        int  _ct17523 = ((_ct17517 < 6)? _ct17521: _ct17522);
        int  _ct17524 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17525 = 0;
        int  _ct17526 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17524: _ct17525);
        int  _ct17527 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17528 = 0;
        int  _ct17529 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17527: _ct17528);
        int  _ct17530 = _ct17529;
        int  _ct17531 = 6;
        int  _ct17532 = ((_ct17526 < 6)? _ct17530: _ct17531);
        int  _ct17533 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17534 = 0;
        int  _ct17535 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17533: _ct17534);
        int  _ct17536 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17537 = 0;
        int  _ct17538 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17536: _ct17537);
        int  _ct17539 = _ct17538;
        int  _ct17540 = 6;
        int  _ct17541 = ((_ct17535 < 6)? _ct17539: _ct17540);
        int  _ct17542 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17543 = 0;
        int  _ct17544 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17542: _ct17543);
        int  _ct17545 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
        int  _ct17546 = 0;
        int  _ct17547 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17545: _ct17546);
        int  _ct17548 = _ct17547;
        int  _ct17549 = 6;
        int  _ct17550 = ((_ct17544 < 6)? _ct17548: _ct17549);
        outLPyramid_L3[((((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1)) + _i2)] = (((1.0f - ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17523)) * U_lPyramid_L3[(((_ct17532 * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + _i2)]) + (((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17541) * U_lPyramid_L3[((((_ct17550 + 1) * (8 * (((C / 8) + 3) + 1))) + (((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1))) + _i2)]));
      }
    }
    int  _ct17551 = ((321 < ((8 * _T_i1) + 7))? 321: ((8 * _T_i1) + 7));
    int  _ct17552 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
    for (int  _i1 = _ct17552; (_i1 <= _ct17551); _i1 = (_i1 + 1))
    {
    #pragma ivdep
      for (int  _i2 = 2; (_i2 <= 192); _i2 = (_i2 + 2))
      {
        outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = (outLPyramid_L3[((((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + ((_i2 / 2) + 1))])));
      }
    }
    int  _ct17553 = ((321 < ((8 * _T_i1) + 7))? 321: ((8 * _T_i1) + 7));
    int  _ct17554 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
    for (int  _i1 = _ct17554; (_i1 <= _ct17553); _i1 = (_i1 + 1))
    {
    #pragma ivdep
      for (int  _i2 = 3; (_i2 <= 193); _i2 = (_i2 + 2))
      {
        outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = (outLPyramid_L3[((((-8 * _T_i1) + _i1) * (((C / 8) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + ((_i2 / 2) + 1))])));
      }
    }
    free(Ux_lPyramid_L3);
    free(U_lPyramid_L3);
    free(outLPyramid_L3);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 80); _T_i1 = (_T_i1 + 1))
  {
    float * Ux_lPyramid_L2;
    Ux_lPyramid_L2 = (float *) (malloc((sizeof(float ) * ((8 * 8) * 131))));
    float * U_lPyramid_L2;
    U_lPyramid_L2 = (float *) (malloc((sizeof(float ) * ((8 * 8) * 262))));
    float * Ux_outGPyramid_L2;
    Ux_outGPyramid_L2 = (float *) (malloc((sizeof(float ) * 1048)));
    float * outLPyramid_L2;
    outLPyramid_L2 = (float *) (malloc((sizeof(float ) * 2096)));
    for (int  _T_i2 = -1; (_T_i2 <= 1); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17555 = ((640 < ((8 * _T_i1) + 6))? 640: ((8 * _T_i1) + 6));
        int  _ct17556 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17556; (_i1 <= _ct17555); _i1 = (_i1 + 2))
        {
          int  _ct17557 = ((193 < ((128 * _T_i2) + 130))? 193: ((128 * _T_i2) + 130));
          int  _ct17558 = ((2 > (128 * _T_i2))? 2: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17558; (_i2 <= _ct17557); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L2[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((-128 * _T_i2) + _i2))] = ((0.25f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + ((_i1 / 2) * (((C / 8) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 8) + 3) + 1))) + _i2)]));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17559 = ((641 < ((8 * _T_i1) + 7))? 641: ((8 * _T_i1) + 7));
        int  _ct17560 = ((3 > ((8 * _T_i1) + 1))? 3: ((8 * _T_i1) + 1));
        for (int  _i1 = _ct17560; (_i1 <= _ct17559); _i1 = (_i1 + 2))
        {
          int  _ct17561 = ((193 < ((128 * _T_i2) + 130))? 193: ((128 * _T_i2) + 130));
          int  _ct17562 = ((2 > (128 * _T_i2))? 2: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17562; (_i2 <= _ct17561); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L2[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((-128 * _T_i2) + _i2))] = ((0.25f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 8) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 8) + 3) + 1))) + _i2)]));
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17563 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17563); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L2[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17564 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17564); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L2[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + (_i2 - 128))] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 80))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 640; (_i1 <= 643); _i1 = (_i1 + 1))
          {
            int  _ct17565 = ((195 < ((128 * _T_i2) + 130))? 195: ((128 * _T_i2) + 130));
            int  _ct17566 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17566; (_i2 <= _ct17565); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L2[(((_i0 * 1048) + ((_i1 - 640) * 131)) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
            {
              int  _ct17567 = ((195 < ((128 * _T_i2) + 130))? 195: ((128 * _T_i2) + 130));
              int  _ct17568 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
              #pragma ivdep
              for (int  _i2 = _ct17568; (_i2 <= _ct17567); _i2 = (_i2 + 1))
              {
                Ux_lPyramid_L2[(((_i0 * 1048) + (_i1 * 131)) + ((-128 * _T_i2) + _i2))] = 0;
              }
            }
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17569 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17569); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              U_lPyramid_L2[(((_i0 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17570 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17570); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 384; (_i2 <= 387); _i2 = (_i2 + 1))
            {
              U_lPyramid_L2[(((_i0 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + (_i2 - 256))] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 80))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 640; (_i1 <= 643); _i1 = (_i1 + 1))
          {
            int  _ct17571 = ((387 < ((256 * _T_i2) + 261))? 387: ((256 * _T_i2) + 261));
            int  _ct17572 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17572; (_i2 <= _ct17571); _i2 = (_i2 + 1))
            {
              U_lPyramid_L2[(((_i0 * 2096) + ((_i1 - 640) * 262)) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
            {
              int  _ct17573 = ((387 < ((256 * _T_i2) + 261))? 387: ((256 * _T_i2) + 261));
              int  _ct17574 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
              #pragma ivdep
              for (int  _i2 = _ct17574; (_i2 <= _ct17573); _i2 = (_i2 + 1))
              {
                U_lPyramid_L2[(((_i0 * 2096) + (_i1 * 262)) + ((-256 * _T_i2) + _i2))] = 0;
              }
            }
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        int  _ct17575 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17575); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        int  _ct17576 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17576); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 384; (_i2 <= 387); _i2 = (_i2 + 1))
          {
            outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      if ((_T_i1 == 80))
      {
        for (int  _i1 = 640; (_i1 <= 643); _i1 = (_i1 + 1))
        {
          int  _ct17577 = ((387 < ((256 * _T_i2) + 261))? 387: ((256 * _T_i2) + 261));
          int  _ct17578 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17578; (_i2 <= _ct17577); _i2 = (_i2 + 1))
          {
            outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            int  _ct17579 = ((387 < ((256 * _T_i2) + 261))? 387: ((256 * _T_i2) + 261));
            int  _ct17580 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17580; (_i2 <= _ct17579); _i2 = (_i2 + 1))
            {
              outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
      }
      int  _ct17581 = ((640 < ((8 * _T_i1) + 6))? 640: ((8 * _T_i1) + 6));
      int  _ct17582 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17582; (_i1 <= _ct17581); _i1 = (_i1 + 2))
      {
        int  _ct17583 = ((193 < ((128 * _T_i2) + 130))? 193: ((128 * _T_i2) + 130));
        int  _ct17584 = ((2 > (128 * _T_i2))? 2: (128 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17584; (_i2 <= _ct17583); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L2[((((-8 * _T_i1) + _i1) * 131) + ((-128 * _T_i2) + _i2))] = ((0.25f * outGPyramid_L3[(((_i1 / 2) * (((C / 8) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L3[((((_i1 / 2) + 1) * (((C / 8) + 3) + 1)) + _i2)]));
        }
      }
      int  _ct17585 = ((641 < ((8 * _T_i1) + 7))? 641: ((8 * _T_i1) + 7));
      int  _ct17586 = ((3 > ((8 * _T_i1) + 1))? 3: ((8 * _T_i1) + 1));
      for (int  _i1 = _ct17586; (_i1 <= _ct17585); _i1 = (_i1 + 2))
      {
        int  _ct17587 = ((193 < ((128 * _T_i2) + 130))? 193: ((128 * _T_i2) + 130));
        int  _ct17588 = ((2 > (128 * _T_i2))? 2: (128 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17588; (_i2 <= _ct17587); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L2[((((-8 * _T_i1) + _i1) * 131) + ((-128 * _T_i2) + _i2))] = ((0.25f * outGPyramid_L3[((((_i1 / 2) + 2) * (((C / 8) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L3[((((_i1 / 2) + 1) * (((C / 8) + 3) + 1)) + _i2)]));
        }
      }
      if ((_T_i2 <= 0))
      {
        int  _ct17589 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17589); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L2[((((-8 * _T_i1) + _i1) * 131) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        int  _ct17590 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17590); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L2[((((-8 * _T_i1) + _i1) * 131) + (_i2 - 128))] = 0;
          }
        }
      }
      if ((_T_i1 == 80))
      {
        for (int  _i1 = 640; (_i1 <= 643); _i1 = (_i1 + 1))
        {
          int  _ct17591 = ((195 < ((128 * _T_i2) + 130))? 195: ((128 * _T_i2) + 130));
          int  _ct17592 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17592; (_i2 <= _ct17591); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L2[(((_i1 - 640) * 131) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            int  _ct17593 = ((195 < ((128 * _T_i2) + 130))? 195: ((128 * _T_i2) + 130));
            int  _ct17594 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17594; (_i2 <= _ct17593); _i2 = (_i2 + 1))
            {
              Ux_outGPyramid_L2[((_i1 * 131) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17595 = ((641 < ((8 * _T_i1) + 7))? 641: ((8 * _T_i1) + 7));
        int  _ct17596 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17596; (_i1 <= _ct17595); _i1 = (_i1 + 1))
        {
          int  _ct17597 = ((384 < ((256 * _T_i2) + 258))? 384: ((256 * _T_i2) + 258));
          int  _ct17598 = ((2 > (256 * _T_i2))? 2: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17598; (_i2 <= _ct17597); _i2 = (_i2 + 2))
          {
            U_lPyramid_L2[(((_i0 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))] = (D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L2[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + (((-256 * _T_i2) + _i2) / 2))]) + (0.75f * Ux_lPyramid_L2[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((((-256 * _T_i2) + _i2) / 2) + 1))])));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17599 = ((641 < ((8 * _T_i1) + 7))? 641: ((8 * _T_i1) + 7));
        int  _ct17600 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17600; (_i1 <= _ct17599); _i1 = (_i1 + 1))
        {
          int  _ct17601 = ((385 < ((256 * _T_i2) + 259))? 385: ((256 * _T_i2) + 259));
          int  _ct17602 = ((3 > ((256 * _T_i2) + 1))? 3: ((256 * _T_i2) + 1));
          #pragma ivdep
          for (int  _i2 = _ct17602; (_i2 <= _ct17601); _i2 = (_i2 + 2))
          {
            U_lPyramid_L2[(((_i0 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))] = (D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L2[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((((-256 * _T_i2) + _i2) / 2) + 2))]) + (0.75f * Ux_lPyramid_L2[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((((-256 * _T_i2) + _i2) / 2) + 1))])));
          }
        }
      }
      int  _ct17603 = ((643 < ((8 * _T_i1) + 7))? 643: ((8 * _T_i1) + 7));
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17603); _i1 = (_i1 + 1))
      {
        int  _ct17604 = ((387 < ((256 * _T_i2) + 257))? 387: ((256 * _T_i2) + 257));
        int  _ct17605 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17605; (_i2 <= _ct17604); _i2 = (_i2 + 1))
        {
          int  _ct17606 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17607 = 0;
          int  _ct17608 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17606: _ct17607);
          int  _ct17609 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17610 = 0;
          int  _ct17611 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17609: _ct17610);
          int  _ct17612 = _ct17611;
          int  _ct17613 = 6;
          int  _ct17614 = ((_ct17608 < 6)? _ct17612: _ct17613);
          int  _ct17615 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17616 = 0;
          int  _ct17617 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17615: _ct17616);
          int  _ct17618 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17619 = 0;
          int  _ct17620 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17618: _ct17619);
          int  _ct17621 = _ct17620;
          int  _ct17622 = 6;
          int  _ct17623 = ((_ct17617 < 6)? _ct17621: _ct17622);
          int  _ct17624 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17625 = 0;
          int  _ct17626 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17624: _ct17625);
          int  _ct17627 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17628 = 0;
          int  _ct17629 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17627: _ct17628);
          int  _ct17630 = _ct17629;
          int  _ct17631 = 6;
          int  _ct17632 = ((_ct17626 < 6)? _ct17630: _ct17631);
          int  _ct17633 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17634 = 0;
          int  _ct17635 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17633: _ct17634);
          int  _ct17636 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17637 = 0;
          int  _ct17638 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17636: _ct17637);
          int  _ct17639 = _ct17638;
          int  _ct17640 = 6;
          int  _ct17641 = ((_ct17635 < 6)? _ct17639: _ct17640);
          outLPyramid_L2[((((-8 * _T_i1) + _i1) * 262) + ((-256 * _T_i2) + _i2))] = (((1.0f - ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17614)) * U_lPyramid_L2[(((_ct17623 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))]) + (((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17632) * U_lPyramid_L2[((((_ct17641 + 1) * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))]));
        }
      }
      int  _ct17642 = ((641 < ((8 * _T_i1) + 7))? 641: ((8 * _T_i1) + 7));
      int  _ct17643 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17643; (_i1 <= _ct17642); _i1 = (_i1 + 1))
      {
        int  _ct17644 = ((384 < ((256 * _T_i2) + 254))? 384: ((256 * _T_i2) + 254));
        int  _ct17645 = ((2 > (256 * _T_i2))? 2: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17645; (_i2 <= _ct17644); _i2 = (_i2 + 2))
        {
          outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = (outLPyramid_L2[((((-8 * _T_i1) + _i1) * 262) + ((-256 * _T_i2) + _i2))] + ((0.25f * Ux_outGPyramid_L2[((((-8 * _T_i1) + _i1) * 131) + (((-256 * _T_i2) + _i2) / 2))]) + (0.75f * Ux_outGPyramid_L2[((((-8 * _T_i1) + _i1) * 131) + ((((-256 * _T_i2) + _i2) / 2) + 1))])));
        }
      }
      int  _ct17646 = ((641 < ((8 * _T_i1) + 7))? 641: ((8 * _T_i1) + 7));
      int  _ct17647 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17647; (_i1 <= _ct17646); _i1 = (_i1 + 1))
      {
        int  _ct17648 = ((385 < ((256 * _T_i2) + 255))? 385: ((256 * _T_i2) + 255));
        int  _ct17649 = ((3 > ((256 * _T_i2) + 1))? 3: ((256 * _T_i2) + 1));
        #pragma ivdep
        for (int  _i2 = _ct17649; (_i2 <= _ct17648); _i2 = (_i2 + 2))
        {
          outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = (outLPyramid_L2[((((-8 * _T_i1) + _i1) * 262) + ((-256 * _T_i2) + _i2))] + ((0.25f * Ux_outGPyramid_L2[((((-8 * _T_i1) + _i1) * 131) + ((((-256 * _T_i2) + _i2) / 2) + 2))]) + (0.75f * Ux_outGPyramid_L2[((((-8 * _T_i1) + _i1) * 131) + ((((-256 * _T_i2) + _i2) / 2) + 1))])));
        }
      }
    }
    free(Ux_lPyramid_L2);
    free(U_lPyramid_L2);
    free(Ux_outGPyramid_L2);
    free(outLPyramid_L2);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 160); _T_i1 = (_T_i1 + 1))
  {
    float * Ux_lPyramid_L1;
    Ux_lPyramid_L1 = (float *) (malloc((sizeof(float ) * ((8 * 8) * 131))));
    float * U_lPyramid_L1;
    U_lPyramid_L1 = (float *) (malloc((sizeof(float ) * ((8 * 8) * 262))));
    float * Ux_outGPyramid_L1;
    Ux_outGPyramid_L1 = (float *) (malloc((sizeof(float ) * 1048)));
    float * outLPyramid_L1;
    outLPyramid_L1 = (float *) (malloc((sizeof(float ) * 2096)));
    for (int  _T_i2 = -1; (_T_i2 <= 3); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17650 = ((1280 < ((8 * _T_i1) + 6))? 1280: ((8 * _T_i1) + 6));
        int  _ct17651 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17651; (_i1 <= _ct17650); _i1 = (_i1 + 2))
        {
          int  _ct17652 = ((385 < ((128 * _T_i2) + 130))? 385: ((128 * _T_i2) + 130));
          int  _ct17653 = ((2 > (128 * _T_i2))? 2: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17653; (_i2 <= _ct17652); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L1[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((-128 * _T_i2) + _i2))] = ((0.25f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + ((_i1 / 2) * (((C / 4) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 4) + 3) + 1))) + _i2)]));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17654 = ((1281 < ((8 * _T_i1) + 7))? 1281: ((8 * _T_i1) + 7));
        int  _ct17655 = ((3 > ((8 * _T_i1) + 1))? 3: ((8 * _T_i1) + 1));
        for (int  _i1 = _ct17655; (_i1 <= _ct17654); _i1 = (_i1 + 2))
        {
          int  _ct17656 = ((385 < ((128 * _T_i2) + 130))? 385: ((128 * _T_i2) + 130));
          int  _ct17657 = ((2 > (128 * _T_i2))? 2: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17657; (_i2 <= _ct17656); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L1[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((-128 * _T_i2) + _i2))] = ((0.25f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 4) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 4) + 3) + 1))) + _i2)]));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17658 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17658); _i1 = (_i1 + 1))
        {
          int  _ct17659 = ((387 < ((128 * _T_i2) + 130))? 387: ((128 * _T_i2) + 130));
          #pragma ivdep
          for (int  _i2 = 384; (_i2 <= _ct17659); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L1[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17660 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17660); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L1[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 160))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 1280; (_i1 <= 1283); _i1 = (_i1 + 1))
          {
            int  _ct17661 = ((387 < ((128 * _T_i2) + 130))? 387: ((128 * _T_i2) + 130));
            int  _ct17662 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17662; (_i2 <= _ct17661); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L1[(((_i0 * 1048) + ((_i1 - 1280) * 131)) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
            {
              int  _ct17663 = ((387 < ((128 * _T_i2) + 130))? 387: ((128 * _T_i2) + 130));
              int  _ct17664 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
              #pragma ivdep
              for (int  _i2 = _ct17664; (_i2 <= _ct17663); _i2 = (_i2 + 1))
              {
                Ux_lPyramid_L1[(((_i0 * 1048) + (_i1 * 131)) + ((-128 * _T_i2) + _i2))] = 0;
              }
            }
          }
        }
      }
      if ((_T_i2 >= 2))
      {
        int  _ct17665 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17665); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 768; (_i2 <= 771); _i2 = (_i2 + 1))
          {
            outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          int  _ct17666 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17666); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 160))
      {
        for (int  _i1 = 1280; (_i1 <= 1283); _i1 = (_i1 + 1))
        {
          int  _ct17667 = ((771 < ((256 * _T_i2) + 261))? 771: ((256 * _T_i2) + 261));
          int  _ct17668 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17668; (_i2 <= _ct17667); _i2 = (_i2 + 1))
          {
            outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            int  _ct17669 = ((771 < ((256 * _T_i2) + 261))? 771: ((256 * _T_i2) + 261));
            int  _ct17670 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17670; (_i2 <= _ct17669); _i2 = (_i2 + 1))
            {
              outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
      }
      if ((_T_i2 >= 2))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17671 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17671); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 768; (_i2 <= 771); _i2 = (_i2 + 1))
            {
              U_lPyramid_L1[(((_i0 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            int  _ct17672 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
            for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17672); _i1 = (_i1 + 1))
            {
              #pragma ivdep
              for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
              {
                U_lPyramid_L1[(((_i0 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))] = 0;
              }
            }
          }
        }
      }
      if ((_T_i1 == 160))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 1280; (_i1 <= 1283); _i1 = (_i1 + 1))
          {
            int  _ct17673 = ((771 < ((256 * _T_i2) + 261))? 771: ((256 * _T_i2) + 261));
            int  _ct17674 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17674; (_i2 <= _ct17673); _i2 = (_i2 + 1))
            {
              U_lPyramid_L1[(((_i0 * 2096) + ((_i1 - 1280) * 262)) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
            {
              int  _ct17675 = ((771 < ((256 * _T_i2) + 261))? 771: ((256 * _T_i2) + 261));
              int  _ct17676 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
              #pragma ivdep
              for (int  _i2 = _ct17676; (_i2 <= _ct17675); _i2 = (_i2 + 1))
              {
                U_lPyramid_L1[(((_i0 * 2096) + (_i1 * 262)) + ((-256 * _T_i2) + _i2))] = 0;
              }
            }
          }
        }
      }
      int  _ct17677 = ((1280 < ((8 * _T_i1) + 6))? 1280: ((8 * _T_i1) + 6));
      int  _ct17678 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17678; (_i1 <= _ct17677); _i1 = (_i1 + 2))
      {
        int  _ct17679 = ((385 < ((128 * _T_i2) + 130))? 385: ((128 * _T_i2) + 130));
        int  _ct17680 = ((2 > (128 * _T_i2))? 2: (128 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17680; (_i2 <= _ct17679); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L1[((((-8 * _T_i1) + _i1) * 131) + ((-128 * _T_i2) + _i2))] = ((0.25f * outGPyramid_L2[(((_i1 / 2) * (((C / 4) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L2[((((_i1 / 2) + 1) * (((C / 4) + 3) + 1)) + _i2)]));
        }
      }
      int  _ct17681 = ((1281 < ((8 * _T_i1) + 7))? 1281: ((8 * _T_i1) + 7));
      int  _ct17682 = ((3 > ((8 * _T_i1) + 1))? 3: ((8 * _T_i1) + 1));
      for (int  _i1 = _ct17682; (_i1 <= _ct17681); _i1 = (_i1 + 2))
      {
        int  _ct17683 = ((385 < ((128 * _T_i2) + 130))? 385: ((128 * _T_i2) + 130));
        int  _ct17684 = ((2 > (128 * _T_i2))? 2: (128 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17684; (_i2 <= _ct17683); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L1[((((-8 * _T_i1) + _i1) * 131) + ((-128 * _T_i2) + _i2))] = ((0.25f * outGPyramid_L2[((((_i1 / 2) + 2) * (((C / 4) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L2[((((_i1 / 2) + 1) * (((C / 4) + 3) + 1)) + _i2)]));
        }
      }
      int  _ct17685 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17685); _i1 = (_i1 + 1))
      {
        int  _ct17686 = ((387 < ((128 * _T_i2) + 130))? 387: ((128 * _T_i2) + 130));
        #pragma ivdep
        for (int  _i2 = 384; (_i2 <= _ct17686); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L1[((((-8 * _T_i1) + _i1) * 131) + ((-128 * _T_i2) + _i2))] = 0;
        }
      }
      if ((_T_i2 <= 0))
      {
        int  _ct17687 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17687); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L1[((((-8 * _T_i1) + _i1) * 131) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      if ((_T_i1 == 160))
      {
        for (int  _i1 = 1280; (_i1 <= 1283); _i1 = (_i1 + 1))
        {
          int  _ct17688 = ((387 < ((128 * _T_i2) + 130))? 387: ((128 * _T_i2) + 130));
          int  _ct17689 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17689; (_i2 <= _ct17688); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L1[(((_i1 - 1280) * 131) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            int  _ct17690 = ((387 < ((128 * _T_i2) + 130))? 387: ((128 * _T_i2) + 130));
            int  _ct17691 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17691; (_i2 <= _ct17690); _i2 = (_i2 + 1))
            {
              Ux_outGPyramid_L1[((_i1 * 131) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17692 = ((1281 < ((8 * _T_i1) + 7))? 1281: ((8 * _T_i1) + 7));
        int  _ct17693 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17693; (_i1 <= _ct17692); _i1 = (_i1 + 1))
        {
          int  _ct17694 = ((768 < ((256 * _T_i2) + 258))? 768: ((256 * _T_i2) + 258));
          int  _ct17695 = ((2 > (256 * _T_i2))? 2: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17695; (_i2 <= _ct17694); _i2 = (_i2 + 2))
          {
            U_lPyramid_L1[(((_i0 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))] = (D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L1[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + (((-256 * _T_i2) + _i2) / 2))]) + (0.75f * Ux_lPyramid_L1[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((((-256 * _T_i2) + _i2) / 2) + 1))])));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17696 = ((1281 < ((8 * _T_i1) + 7))? 1281: ((8 * _T_i1) + 7));
        int  _ct17697 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17697; (_i1 <= _ct17696); _i1 = (_i1 + 1))
        {
          int  _ct17698 = ((769 < ((256 * _T_i2) + 259))? 769: ((256 * _T_i2) + 259));
          int  _ct17699 = ((3 > ((256 * _T_i2) + 1))? 3: ((256 * _T_i2) + 1));
          #pragma ivdep
          for (int  _i2 = _ct17699; (_i2 <= _ct17698); _i2 = (_i2 + 2))
          {
            U_lPyramid_L1[(((_i0 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))] = (D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L1[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((((-256 * _T_i2) + _i2) / 2) + 2))]) + (0.75f * Ux_lPyramid_L1[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((((-256 * _T_i2) + _i2) / 2) + 1))])));
          }
        }
      }
      int  _ct17700 = ((1283 < ((8 * _T_i1) + 7))? 1283: ((8 * _T_i1) + 7));
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17700); _i1 = (_i1 + 1))
      {
        int  _ct17701 = ((771 < ((256 * _T_i2) + 257))? 771: ((256 * _T_i2) + 257));
        int  _ct17702 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17702; (_i2 <= _ct17701); _i2 = (_i2 + 1))
        {
          int  _ct17703 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17704 = 0;
          int  _ct17705 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17703: _ct17704);
          int  _ct17706 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17707 = 0;
          int  _ct17708 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17706: _ct17707);
          int  _ct17709 = _ct17708;
          int  _ct17710 = 6;
          int  _ct17711 = ((_ct17705 < 6)? _ct17709: _ct17710);
          int  _ct17712 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17713 = 0;
          int  _ct17714 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17712: _ct17713);
          int  _ct17715 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17716 = 0;
          int  _ct17717 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17715: _ct17716);
          int  _ct17718 = _ct17717;
          int  _ct17719 = 6;
          int  _ct17720 = ((_ct17714 < 6)? _ct17718: _ct17719);
          int  _ct17721 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17722 = 0;
          int  _ct17723 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17721: _ct17722);
          int  _ct17724 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17725 = 0;
          int  _ct17726 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17724: _ct17725);
          int  _ct17727 = _ct17726;
          int  _ct17728 = 6;
          int  _ct17729 = ((_ct17723 < 6)? _ct17727: _ct17728);
          int  _ct17730 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17731 = 0;
          int  _ct17732 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17730: _ct17731);
          int  _ct17733 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
          int  _ct17734 = 0;
          int  _ct17735 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct17733: _ct17734);
          int  _ct17736 = _ct17735;
          int  _ct17737 = 6;
          int  _ct17738 = ((_ct17732 < 6)? _ct17736: _ct17737);
          outLPyramid_L1[((((-8 * _T_i1) + _i1) * 262) + ((-256 * _T_i2) + _i2))] = (((1.0f - ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17711)) * U_lPyramid_L1[(((_ct17720 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))]) + (((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17729) * U_lPyramid_L1[((((_ct17738 + 1) * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))]));
        }
      }
      int  _ct17739 = ((1281 < ((8 * _T_i1) + 7))? 1281: ((8 * _T_i1) + 7));
      int  _ct17740 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17740; (_i1 <= _ct17739); _i1 = (_i1 + 1))
      {
        int  _ct17741 = ((768 < ((256 * _T_i2) + 254))? 768: ((256 * _T_i2) + 254));
        int  _ct17742 = ((2 > (256 * _T_i2))? 2: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17742; (_i2 <= _ct17741); _i2 = (_i2 + 2))
        {
          outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = (outLPyramid_L1[((((-8 * _T_i1) + _i1) * 262) + ((-256 * _T_i2) + _i2))] + ((0.25f * Ux_outGPyramid_L1[((((-8 * _T_i1) + _i1) * 131) + (((-256 * _T_i2) + _i2) / 2))]) + (0.75f * Ux_outGPyramid_L1[((((-8 * _T_i1) + _i1) * 131) + ((((-256 * _T_i2) + _i2) / 2) + 1))])));
        }
      }
      int  _ct17743 = ((1281 < ((8 * _T_i1) + 7))? 1281: ((8 * _T_i1) + 7));
      int  _ct17744 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17744; (_i1 <= _ct17743); _i1 = (_i1 + 1))
      {
        int  _ct17745 = ((769 < ((256 * _T_i2) + 255))? 769: ((256 * _T_i2) + 255));
        int  _ct17746 = ((3 > ((256 * _T_i2) + 1))? 3: ((256 * _T_i2) + 1));
        #pragma ivdep
        for (int  _i2 = _ct17746; (_i2 <= _ct17745); _i2 = (_i2 + 2))
        {
          outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = (outLPyramid_L1[((((-8 * _T_i1) + _i1) * 262) + ((-256 * _T_i2) + _i2))] + ((0.25f * Ux_outGPyramid_L1[((((-8 * _T_i1) + _i1) * 131) + ((((-256 * _T_i2) + _i2) / 2) + 2))]) + (0.75f * Ux_outGPyramid_L1[((((-8 * _T_i1) + _i1) * 131) + ((((-256 * _T_i2) + _i2) / 2) + 1))])));
        }
      }
    }
    free(Ux_lPyramid_L1);
    free(U_lPyramid_L1);
    free(Ux_outGPyramid_L1);
    free(outLPyramid_L1);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= 320); _T_i1 = (_T_i1 + 1))
  {
    float * Ux_lPyramid_L0;
    Ux_lPyramid_L0 = (float *) (malloc((sizeof(float ) * ((8 * 8) * 131))));
    float * U_lPyramid_L0;
    U_lPyramid_L0 = (float *) (malloc((sizeof(float ) * ((8 * 8) * 262))));
    float * Ux_result_ref_gray;
    Ux_result_ref_gray = (float *) (malloc((sizeof(float ) * 1048)));
    float * outLPyramid_L0;
    outLPyramid_L0 = (float *) (malloc((sizeof(float ) * 2096)));
    for (int  _T_i2 = -1; (_T_i2 <= 6); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17747 = ((2560 < ((8 * _T_i1) + 6))? 2560: ((8 * _T_i1) + 6));
        int  _ct17748 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17748; (_i1 <= _ct17747); _i1 = (_i1 + 2))
        {
          int  _ct17749 = ((769 < ((128 * _T_i2) + 130))? 769: ((128 * _T_i2) + 130));
          int  _ct17750 = ((2 > (128 * _T_i2))? 2: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17750; (_i2 <= _ct17749); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L0[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((-128 * _T_i2) + _i2))] = ((0.25f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + ((_i1 / 2) * (((C / 2) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 2) + 3) + 1))) + _i2)]));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17751 = ((2561 < ((8 * _T_i1) + 7))? 2561: ((8 * _T_i1) + 7));
        int  _ct17752 = ((3 > ((8 * _T_i1) + 1))? 3: ((8 * _T_i1) + 1));
        for (int  _i1 = _ct17752; (_i1 <= _ct17751); _i1 = (_i1 + 2))
        {
          int  _ct17753 = ((769 < ((128 * _T_i2) + 130))? 769: ((128 * _T_i2) + 130));
          int  _ct17754 = ((2 > (128 * _T_i2))? 2: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17754; (_i2 <= _ct17753); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L0[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((-128 * _T_i2) + _i2))] = ((0.25f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 2) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 2) + 3) + 1))) + _i2)]));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17755 = ((2563 < ((8 * _T_i1) + 7))? 2563: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17755); _i1 = (_i1 + 1))
        {
          int  _ct17756 = ((771 < ((128 * _T_i2) + 130))? 771: ((128 * _T_i2) + 130));
          #pragma ivdep
          for (int  _i2 = 768; (_i2 <= _ct17756); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L0[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      if ((_T_i2 <= 0))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17757 = ((2563 < ((8 * _T_i1) + 7))? 2563: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17757); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L0[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 320))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 2560; (_i1 <= 2563); _i1 = (_i1 + 1))
          {
            int  _ct17758 = ((771 < ((128 * _T_i2) + 130))? 771: ((128 * _T_i2) + 130));
            int  _ct17759 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17759; (_i2 <= _ct17758); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L0[(((_i0 * 1048) + ((_i1 - 2560) * 131)) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
            {
              int  _ct17760 = ((771 < ((128 * _T_i2) + 130))? 771: ((128 * _T_i2) + 130));
              int  _ct17761 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
              #pragma ivdep
              for (int  _i2 = _ct17761; (_i2 <= _ct17760); _i2 = (_i2 + 1))
              {
                Ux_lPyramid_L0[(((_i0 * 1048) + (_i1 * 131)) + ((-128 * _T_i2) + _i2))] = 0;
              }
            }
          }
        }
      }
      if ((_T_i2 >= 5))
      {
        int  _ct17762 = ((2563 < ((8 * _T_i1) + 7))? 2563: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17762); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 1536; (_i2 <= 1539); _i2 = (_i2 + 1))
          {
            result_ref_gray[((_i1 * (4 + C)) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          int  _ct17763 = ((2563 < ((8 * _T_i1) + 7))? 2563: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17763); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              result_ref_gray[((_i1 * (4 + C)) + _i2)] = 0;
            }
          }
        }
      }
      if ((_T_i1 == 320))
      {
        for (int  _i1 = 2560; (_i1 <= 2563); _i1 = (_i1 + 1))
        {
          int  _ct17764 = ((1539 < ((256 * _T_i2) + 261))? 1539: ((256 * _T_i2) + 261));
          int  _ct17765 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17765; (_i2 <= _ct17764); _i2 = (_i2 + 1))
          {
            result_ref_gray[((_i1 * (4 + C)) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            int  _ct17766 = ((1539 < ((256 * _T_i2) + 261))? 1539: ((256 * _T_i2) + 261));
            int  _ct17767 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17767; (_i2 <= _ct17766); _i2 = (_i2 + 1))
            {
              result_ref_gray[((_i1 * (4 + C)) + _i2)] = 0;
            }
          }
        }
      }
      if ((_T_i2 >= 5))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          int  _ct17768 = ((2563 < ((8 * _T_i1) + 7))? 2563: ((8 * _T_i1) + 7));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17768); _i1 = (_i1 + 1))
          {
            #pragma ivdep
            for (int  _i2 = 1536; (_i2 <= 1539); _i2 = (_i2 + 1))
            {
              U_lPyramid_L0[(((_i0 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i2 <= 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            int  _ct17769 = ((2563 < ((8 * _T_i1) + 7))? 2563: ((8 * _T_i1) + 7));
            for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17769); _i1 = (_i1 + 1))
            {
              #pragma ivdep
              for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
              {
                U_lPyramid_L0[(((_i0 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))] = 0;
              }
            }
          }
        }
      }
      if ((_T_i1 == 320))
      {
        for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
        {
          for (int  _i1 = 2560; (_i1 <= 2563); _i1 = (_i1 + 1))
          {
            int  _ct17770 = ((1539 < ((256 * _T_i2) + 261))? 1539: ((256 * _T_i2) + 261));
            int  _ct17771 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17771; (_i2 <= _ct17770); _i2 = (_i2 + 1))
            {
              U_lPyramid_L0[(((_i0 * 2096) + ((_i1 - 2560) * 262)) + ((-256 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
          {
            for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
            {
              int  _ct17772 = ((1539 < ((256 * _T_i2) + 261))? 1539: ((256 * _T_i2) + 261));
              int  _ct17773 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
              #pragma ivdep
              for (int  _i2 = _ct17773; (_i2 <= _ct17772); _i2 = (_i2 + 1))
              {
                U_lPyramid_L0[(((_i0 * 2096) + (_i1 * 262)) + ((-256 * _T_i2) + _i2))] = 0;
              }
            }
          }
        }
      }
      int  _ct17774 = ((2560 < ((8 * _T_i1) + 6))? 2560: ((8 * _T_i1) + 6));
      int  _ct17775 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17775; (_i1 <= _ct17774); _i1 = (_i1 + 2))
      {
        int  _ct17776 = ((769 < ((128 * _T_i2) + 130))? 769: ((128 * _T_i2) + 130));
        int  _ct17777 = ((2 > (128 * _T_i2))? 2: (128 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17777; (_i2 <= _ct17776); _i2 = (_i2 + 1))
        {
          Ux_result_ref_gray[((((-8 * _T_i1) + _i1) * 131) + ((-128 * _T_i2) + _i2))] = ((0.25f * outGPyramid_L1[(((_i1 / 2) * (((C / 2) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L1[((((_i1 / 2) + 1) * (((C / 2) + 3) + 1)) + _i2)]));
        }
      }
      int  _ct17778 = ((2561 < ((8 * _T_i1) + 7))? 2561: ((8 * _T_i1) + 7));
      int  _ct17779 = ((3 > ((8 * _T_i1) + 1))? 3: ((8 * _T_i1) + 1));
      for (int  _i1 = _ct17779; (_i1 <= _ct17778); _i1 = (_i1 + 2))
      {
        int  _ct17780 = ((769 < ((128 * _T_i2) + 130))? 769: ((128 * _T_i2) + 130));
        int  _ct17781 = ((2 > (128 * _T_i2))? 2: (128 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17781; (_i2 <= _ct17780); _i2 = (_i2 + 1))
        {
          Ux_result_ref_gray[((((-8 * _T_i1) + _i1) * 131) + ((-128 * _T_i2) + _i2))] = ((0.25f * outGPyramid_L1[((((_i1 / 2) + 2) * (((C / 2) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L1[((((_i1 / 2) + 1) * (((C / 2) + 3) + 1)) + _i2)]));
        }
      }
      int  _ct17782 = ((2563 < ((8 * _T_i1) + 7))? 2563: ((8 * _T_i1) + 7));
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17782); _i1 = (_i1 + 1))
      {
        int  _ct17783 = ((771 < ((128 * _T_i2) + 130))? 771: ((128 * _T_i2) + 130));
        #pragma ivdep
        for (int  _i2 = 768; (_i2 <= _ct17783); _i2 = (_i2 + 1))
        {
          Ux_result_ref_gray[((((-8 * _T_i1) + _i1) * 131) + ((-128 * _T_i2) + _i2))] = 0;
        }
      }
      if ((_T_i2 <= 0))
      {
        int  _ct17784 = ((2563 < ((8 * _T_i1) + 7))? 2563: ((8 * _T_i1) + 7));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17784); _i1 = (_i1 + 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Ux_result_ref_gray[((((-8 * _T_i1) + _i1) * 131) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      if ((_T_i1 == 320))
      {
        for (int  _i1 = 2560; (_i1 <= 2563); _i1 = (_i1 + 1))
        {
          int  _ct17785 = ((771 < ((128 * _T_i2) + 130))? 771: ((128 * _T_i2) + 130));
          int  _ct17786 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17786; (_i2 <= _ct17785); _i2 = (_i2 + 1))
          {
            Ux_result_ref_gray[(((_i1 - 2560) * 131) + ((-128 * _T_i2) + _i2))] = 0;
          }
        }
      }
      else
      {
        if ((_T_i1 == 0))
        {
          for (int  _i1 = 0; (_i1 <= 1); _i1 = (_i1 + 1))
          {
            int  _ct17787 = ((771 < ((128 * _T_i2) + 130))? 771: ((128 * _T_i2) + 130));
            int  _ct17788 = ((0 > (128 * _T_i2))? 0: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct17788; (_i2 <= _ct17787); _i2 = (_i2 + 1))
            {
              Ux_result_ref_gray[((_i1 * 131) + ((-128 * _T_i2) + _i2))] = 0;
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17789 = ((2561 < ((8 * _T_i1) + 7))? 2561: ((8 * _T_i1) + 7));
        int  _ct17790 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17790; (_i1 <= _ct17789); _i1 = (_i1 + 1))
        {
          int  _ct17791 = ((1536 < ((256 * _T_i2) + 258))? 1536: ((256 * _T_i2) + 258));
          int  _ct17792 = ((2 > (256 * _T_i2))? 2: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct17792; (_i2 <= _ct17791); _i2 = (_i2 + 2))
          {
            U_lPyramid_L0[(((_i0 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))] = (gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] - ((0.25f * Ux_lPyramid_L0[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + (((-256 * _T_i2) + _i2) / 2))]) + (0.75f * Ux_lPyramid_L0[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((((-256 * _T_i2) + _i2) / 2) + 1))])));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
      {
        int  _ct17793 = ((2561 < ((8 * _T_i1) + 7))? 2561: ((8 * _T_i1) + 7));
        int  _ct17794 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
        for (int  _i1 = _ct17794; (_i1 <= _ct17793); _i1 = (_i1 + 1))
        {
          int  _ct17795 = ((1537 < ((256 * _T_i2) + 259))? 1537: ((256 * _T_i2) + 259));
          int  _ct17796 = ((3 > ((256 * _T_i2) + 1))? 3: ((256 * _T_i2) + 1));
          #pragma ivdep
          for (int  _i2 = _ct17796; (_i2 <= _ct17795); _i2 = (_i2 + 2))
          {
            U_lPyramid_L0[(((_i0 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))] = (gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] - ((0.25f * Ux_lPyramid_L0[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((((-256 * _T_i2) + _i2) / 2) + 2))]) + (0.75f * Ux_lPyramid_L0[(((_i0 * 1048) + (((-8 * _T_i1) + _i1) * 131)) + ((((-256 * _T_i2) + _i2) / 2) + 1))])));
          }
        }
      }
      int  _ct17797 = ((2563 < ((8 * _T_i1) + 7))? 2563: ((8 * _T_i1) + 7));
      for (int  _i1 = (8 * _T_i1); (_i1 <= _ct17797); _i1 = (_i1 + 1))
      {
        int  _ct17798 = ((1539 < ((256 * _T_i2) + 257))? 1539: ((256 * _T_i2) + 257));
        int  _ct17799 = ((0 > (256 * _T_i2))? 0: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17799; (_i2 <= _ct17798); _i2 = (_i2 + 1))
        {
          int  _ct17800 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
          int  _ct17801 = 0;
          int  _ct17802 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct17800: _ct17801);
          int  _ct17803 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
          int  _ct17804 = 0;
          int  _ct17805 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct17803: _ct17804);
          int  _ct17806 = _ct17805;
          int  _ct17807 = 6;
          int  _ct17808 = ((_ct17802 < 6)? _ct17806: _ct17807);
          int  _ct17809 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
          int  _ct17810 = 0;
          int  _ct17811 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct17809: _ct17810);
          int  _ct17812 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
          int  _ct17813 = 0;
          int  _ct17814 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct17812: _ct17813);
          int  _ct17815 = _ct17814;
          int  _ct17816 = 6;
          int  _ct17817 = ((_ct17811 < 6)? _ct17815: _ct17816);
          int  _ct17818 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
          int  _ct17819 = 0;
          int  _ct17820 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct17818: _ct17819);
          int  _ct17821 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
          int  _ct17822 = 0;
          int  _ct17823 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct17821: _ct17822);
          int  _ct17824 = _ct17823;
          int  _ct17825 = 6;
          int  _ct17826 = ((_ct17820 < 6)? _ct17824: _ct17825);
          int  _ct17827 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
          int  _ct17828 = 0;
          int  _ct17829 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct17827: _ct17828);
          int  _ct17830 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
          int  _ct17831 = 0;
          int  _ct17832 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct17830: _ct17831);
          int  _ct17833 = _ct17832;
          int  _ct17834 = 6;
          int  _ct17835 = ((_ct17829 < 6)? _ct17833: _ct17834);
          outLPyramid_L0[((((-8 * _T_i1) + _i1) * 262) + ((-256 * _T_i2) + _i2))] = (((1.0f - ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)) - _ct17808)) * U_lPyramid_L0[(((_ct17817 * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))]) + (((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)) - _ct17826) * U_lPyramid_L0[((((_ct17835 + 1) * 2096) + (((-8 * _T_i1) + _i1) * 262)) + ((-256 * _T_i2) + _i2))]));
        }
      }
      int  _ct17836 = ((2561 < ((8 * _T_i1) + 7))? 2561: ((8 * _T_i1) + 7));
      int  _ct17837 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17837; (_i1 <= _ct17836); _i1 = (_i1 + 1))
      {
        int  _ct17838 = ((1536 < ((256 * _T_i2) + 254))? 1536: ((256 * _T_i2) + 254));
        int  _ct17839 = ((2 > (256 * _T_i2))? 2: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct17839; (_i2 <= _ct17838); _i2 = (_i2 + 2))
        {
          result_ref_gray[((_i1 * (4 + C)) + _i2)] = (outLPyramid_L0[((((-8 * _T_i1) + _i1) * 262) + ((-256 * _T_i2) + _i2))] + ((0.25f * Ux_result_ref_gray[((((-8 * _T_i1) + _i1) * 131) + (((-256 * _T_i2) + _i2) / 2))]) + (0.75f * Ux_result_ref_gray[((((-8 * _T_i1) + _i1) * 131) + ((((-256 * _T_i2) + _i2) / 2) + 1))])));
        }
      }
      int  _ct17840 = ((2561 < ((8 * _T_i1) + 7))? 2561: ((8 * _T_i1) + 7));
      int  _ct17841 = ((2 > (8 * _T_i1))? 2: (8 * _T_i1));
      for (int  _i1 = _ct17841; (_i1 <= _ct17840); _i1 = (_i1 + 1))
      {
        int  _ct17842 = ((1537 < ((256 * _T_i2) + 255))? 1537: ((256 * _T_i2) + 255));
        int  _ct17843 = ((3 > ((256 * _T_i2) + 1))? 3: ((256 * _T_i2) + 1));
        #pragma ivdep
        for (int  _i2 = _ct17843; (_i2 <= _ct17842); _i2 = (_i2 + 2))
        {
          result_ref_gray[((_i1 * (4 + C)) + _i2)] = (outLPyramid_L0[((((-8 * _T_i1) + _i1) * 262) + ((-256 * _T_i2) + _i2))] + ((0.25f * Ux_result_ref_gray[((((-8 * _T_i1) + _i1) * 131) + ((((-256 * _T_i2) + _i2) / 2) + 2))]) + (0.75f * Ux_result_ref_gray[((((-8 * _T_i1) + _i1) * 131) + ((((-256 * _T_i2) + _i2) / 2) + 1))])));
        }
      }
    }
    free(Ux_lPyramid_L0);
    free(U_lPyramid_L0);
    free(Ux_result_ref_gray);
    free(outLPyramid_L0);
  }
  for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 2559); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 1535); _i2 = (_i2 + 1))
      {
        float  _ct17844 = ((result_ref_gray[(((2 + _i1) * (4 + C)) + (2 + _i2))] * ((img_colour[(((_i0 * ((R + 4) * (C + 4))) + ((2 + _i1) * (C + 4))) + (2 + _i2))] / 65535.0f) + 0.01f)) / (img[(((2 + _i1) * (4 + C)) + (2 + _i2))] + 0.01f));
        float  _ct17845 = 0.0f;
        float  _ct17846 = ((((result_ref_gray[(((2 + _i1) * (4 + C)) + (2 + _i2))] * ((img_colour[(((_i0 * ((R + 4) * (C + 4))) + ((2 + _i1) * (C + 4))) + (2 + _i2))] / 65535.0f) + 0.01f)) / (img[(((2 + _i1) * (4 + C)) + (2 + _i2))] + 0.01f)) > 0.0f)? _ct17844: _ct17845);
        float  _ct17847 = ((result_ref_gray[(((2 + _i1) * (4 + C)) + (2 + _i2))] * ((img_colour[(((_i0 * ((R + 4) * (C + 4))) + ((2 + _i1) * (C + 4))) + (2 + _i2))] / 65535.0f) + 0.01f)) / (img[(((2 + _i1) * (4 + C)) + (2 + _i2))] + 0.01f));
        float  _ct17848 = 0.0f;
        float  _ct17849 = ((((result_ref_gray[(((2 + _i1) * (4 + C)) + (2 + _i2))] * ((img_colour[(((_i0 * ((R + 4) * (C + 4))) + ((2 + _i1) * (C + 4))) + (2 + _i2))] / 65535.0f) + 0.01f)) / (img[(((2 + _i1) * (4 + C)) + (2 + _i2))] + 0.01f)) > 0.0f)? _ct17847: _ct17848);
        float  _ct17850 = _ct17849;
        float  _ct17851 = 1.0f;
        float  _ct17852 = ((_ct17846 < 1.0f)? _ct17850: _ct17851);
        laplacian[(((_i0 * (R * C)) + (_i1 * C)) + _i2)] = (short unsigned int ) ((_ct17852 * 65535.0f));
      }
    }
  }
  free(img);
  free(remapLUT);
  free(gPyramid_L0);
  free(D_inGPyramid_L1);
  free(D_gPyramid_L1);
  free(D_inGPyramid_L2);
  free(D_gPyramid_L2);
  free(D_inGPyramid_L3);
  free(D_gPyramid_L3);
  free(Dx_inGPyramid_L4);
  free(D_inGPyramid_L4);
  free(D_gPyramid_L4);
  free(Dx_inGPyramid_L5);
  free(D_inGPyramid_L5);
  free(Dx_gPyramid_L5);
  free(D_gPyramid_L5);
  free(Dx_inGPyramid_L6);
  free(D_inGPyramid_L6);
  free(Dx_gPyramid_L6);
  free(Ux_lPyramid_L4);
  free(D_gPyramid_L6);
  free(Dx_inGPyramid_L7);
  free(D_inGPyramid_L7);
  free(Dx_gPyramid_L7);
  free(Ux_lPyramid_L5);
  free(D_gPyramid_L7);
  free(U_lPyramid_L5);
  free(Ux_lPyramid_L6);
  free(outLPyramid_L5);
  free(outLPyramid_L7);
  free(U_lPyramid_L6);
  free(Ux_outGPyramid_L6);
  free(outLPyramid_L6);
  free(outGPyramid_L6);
  free(Ux_outGPyramid_L5);
  free(outGPyramid_L5);
  free(Ux_outGPyramid_L4);
  free(Ux_outGPyramid_L3);
  free(outGPyramid_L3);
  free(outGPyramid_L2);
  free(outGPyramid_L1);
  free(result_ref_gray);
}
