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
  float * Dx_inGPyramid_L1;
  Dx_inGPyramid_L1 = (float *) (malloc((sizeof(float ) * ((((R / 2) + 3) + 1) * (4 + C)))));
  float * gPyramid_L0;
  gPyramid_L0 = (float *) (malloc((sizeof(float ) * ((8 * (4 + R)) * (4 + C)))));
  float * D_inGPyramid_L1;
  D_inGPyramid_L1 = (float *) (malloc((sizeof(float ) * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1)))));
  float * Dx_gPyramid_L1;
  Dx_gPyramid_L1 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 2) + 3) + 1)) * (4 + C)))));
  float * D_gPyramid_L1;
  D_gPyramid_L1 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 2) + 3) + 1)) * (((C / 2) + 3) + 1)))));
  float * Dx_inGPyramid_L2;
  Dx_inGPyramid_L2 = (float *) (malloc((sizeof(float ) * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1)))));
  float * D_inGPyramid_L2;
  D_inGPyramid_L2 = (float *) (malloc((sizeof(float ) * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1)))));
  float * Dx_gPyramid_L2;
  Dx_gPyramid_L2 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 4) + 3) + 1)) * (((C / 2) + 3) + 1)))));
  float * Ux_lPyramid_L0;
  Ux_lPyramid_L0 = (float *) (malloc((sizeof(float ) * ((8 * (4 + R)) * (((C / 2) + 3) + 1)))));
  float * D_gPyramid_L2;
  D_gPyramid_L2 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 4) + 3) + 1)) * (((C / 4) + 3) + 1)))));
  float * Dx_inGPyramid_L3;
  Dx_inGPyramid_L3 = (float *) (malloc((sizeof(float ) * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1)))));
  float * U_lPyramid_L0;
  U_lPyramid_L0 = (float *) (malloc((sizeof(float ) * ((8 * (4 + R)) * (4 + C)))));
  float * D_inGPyramid_L3;
  D_inGPyramid_L3 = (float *) (malloc((sizeof(float ) * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1)))));
  float * Dx_gPyramid_L3;
  Dx_gPyramid_L3 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 8) + 3) + 1)) * (((C / 4) + 3) + 1)))));
  float * Ux_lPyramid_L1;
  Ux_lPyramid_L1 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 2) + 3) + 1)) * (((C / 4) + 3) + 1)))));
  float * outLPyramid_L0;
  outLPyramid_L0 = (float *) (malloc((sizeof(float ) * ((4 + R) * (4 + C)))));
  float * D_gPyramid_L3;
  D_gPyramid_L3 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 8) + 3) + 1)) * (((C / 8) + 3) + 1)))));
  float * Dx_inGPyramid_L4;
  Dx_inGPyramid_L4 = (float *) (malloc((sizeof(float ) * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1)))));
  float * U_lPyramid_L1;
  U_lPyramid_L1 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 2) + 3) + 1)) * (((C / 2) + 3) + 1)))));
  float * D_inGPyramid_L4;
  D_inGPyramid_L4 = (float *) (malloc((sizeof(float ) * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1)))));
  float * Dx_gPyramid_L4;
  Dx_gPyramid_L4 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 16) + 3) + 1)) * (((C / 8) + 3) + 1)))));
  float * Ux_lPyramid_L2;
  Ux_lPyramid_L2 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 4) + 3) + 1)) * (((C / 8) + 3) + 1)))));
  float * outLPyramid_L1;
  outLPyramid_L1 = (float *) (malloc((sizeof(float ) * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1)))));
  float * D_gPyramid_L4;
  D_gPyramid_L4 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 16) + 3) + 1)) * (((C / 16) + 3) + 1)))));
  float * Dx_inGPyramid_L5;
  Dx_inGPyramid_L5 = (float *) (malloc((sizeof(float ) * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1)))));
  float * U_lPyramid_L2;
  U_lPyramid_L2 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 4) + 3) + 1)) * (((C / 4) + 3) + 1)))));
  float * D_inGPyramid_L5;
  D_inGPyramid_L5 = (float *) (malloc((sizeof(float ) * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1)))));
  float * Dx_gPyramid_L5;
  Dx_gPyramid_L5 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 32) + 3) + 1)) * (((C / 16) + 3) + 1)))));
  float * Ux_lPyramid_L3;
  Ux_lPyramid_L3 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 8) + 3) + 1)) * (((C / 16) + 3) + 1)))));
  float * outLPyramid_L2;
  outLPyramid_L2 = (float *) (malloc((sizeof(float ) * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1)))));
  float * D_gPyramid_L5;
  D_gPyramid_L5 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 32) + 3) + 1)) * (((C / 32) + 3) + 1)))));
  float * Dx_inGPyramid_L6;
  Dx_inGPyramid_L6 = (float *) (malloc((sizeof(float ) * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1)))));
  float * U_lPyramid_L3;
  U_lPyramid_L3 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 8) + 3) + 1)) * (((C / 8) + 3) + 1)))));
  float * D_inGPyramid_L6;
  D_inGPyramid_L6 = (float *) (malloc((sizeof(float ) * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1)))));
  float * Dx_gPyramid_L6;
  Dx_gPyramid_L6 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 64) + 3) + 1)) * (((C / 32) + 3) + 1)))));
  float * Ux_lPyramid_L4;
  Ux_lPyramid_L4 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 16) + 3) + 1)) * (((C / 32) + 3) + 1)))));
  float * outLPyramid_L3;
  outLPyramid_L3 = (float *) (malloc((sizeof(float ) * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1)))));
  float * D_gPyramid_L6;
  D_gPyramid_L6 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 64) + 3) + 1)) * (((C / 64) + 3) + 1)))));
  float * Dx_inGPyramid_L7;
  Dx_inGPyramid_L7 = (float *) (malloc((sizeof(float ) * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1)))));
  float * U_lPyramid_L4;
  U_lPyramid_L4 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 16) + 3) + 1)) * (((C / 16) + 3) + 1)))));
  float * D_inGPyramid_L7;
  D_inGPyramid_L7 = (float *) (malloc((sizeof(float ) * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1)))));
  float * Dx_gPyramid_L7;
  Dx_gPyramid_L7 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 128) + 3) + 1)) * (((C / 64) + 3) + 1)))));
  float * Ux_lPyramid_L5;
  Ux_lPyramid_L5 = (float *) (malloc((sizeof(float ) * ((8 * (((R / 32) + 3) + 1)) * (((C / 64) + 3) + 1)))));
  float * outLPyramid_L4;
  outLPyramid_L4 = (float *) (malloc((sizeof(float ) * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1)))));
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
  float * outGPyramid_L4;
  outGPyramid_L4 = (float *) (malloc((sizeof(float ) * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1)))));
  float * Ux_outGPyramid_L3;
  Ux_outGPyramid_L3 = (float *) (malloc((sizeof(float ) * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1)))));
  float * outGPyramid_L3;
  outGPyramid_L3 = (float *) (malloc((sizeof(float ) * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1)))));
  float * Ux_outGPyramid_L2;
  Ux_outGPyramid_L2 = (float *) (malloc((sizeof(float ) * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1)))));
  float * outGPyramid_L2;
  outGPyramid_L2 = (float *) (malloc((sizeof(float ) * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1)))));
  float * Ux_outGPyramid_L1;
  Ux_outGPyramid_L1 = (float *) (malloc((sizeof(float ) * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1)))));
  float * outGPyramid_L1;
  outGPyramid_L1 = (float *) (malloc((sizeof(float ) * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1)))));
  float * Ux_result_ref_gray;
  Ux_result_ref_gray = (float *) (malloc((sizeof(float ) * ((4 + R) * (((C / 2) + 3) + 1)))));
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
        int  _ct0 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (1792.0f)));
        int  _ct1 = 0;
        int  _ct2 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (1792.0f))) > 0)? _ct0: _ct1);
        int  _ct3 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (1792.0f)));
        int  _ct4 = 0;
        int  _ct5 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (1792.0f))) > 0)? _ct3: _ct4);
        int  _ct6 = _ct5;
        int  _ct7 = 1792;
        int  _ct8 = ((_ct2 < 1792)? _ct6: _ct7);
        gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = (((beta * (img[((_i1 * (4 + C)) + _i2)] - (_i0 * 0.142857142857f))) + (_i0 * 0.142857142857f)) + remapLUT[((_ct8 - (256 * _i0)) - -1792)]);
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 1283); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 1282))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1539); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
          }
          Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
          if ((_i2 >= 1536))
          {
            Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 1279))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
            if ((_i1 <= 1))
            {
              Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 1))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 1535); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
            }
            #pragma ivdep
            for (int  _i2 = 1536; (_i2 <= 1539); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
              Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
            }
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
            Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
          }
        }
        if ((_i1 >= 2))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 1537); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = ((((gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + ((-3 + (2 * _i1)) * (4 + C))) + _i2)] + (3.0f * gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + ((-2 + (2 * _i1)) * (4 + C))) + _i2)])) + (3.0f * gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + ((-1 + (2 * _i1)) * (4 + C))) + _i2)])) + gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + ((2 * _i1) * (4 + C))) + _i2)]) * 0.125f);
            if ((_i1 >= 1280))
            {
              Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
            }
            if ((_i2 >= 1536))
            {
              Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 1279))
          {
            #pragma ivdep
            for (int  _i2 = 1538; (_i2 <= 1539); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 1538; (_i2 <= 1539); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
              Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
            }
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 1283); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 1282))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
          D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 768))
          {
            D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
          {
            if ((_i2 <= 1))
            {
              D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
            else
            {
              if ((_i2 >= 768))
              {
                D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
              }
            }
            D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          if ((_i1 <= 1279))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
          }
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 769); _i2 = (_i2 + 1))
          {
            if ((_i2 >= 768))
            {
              D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i1 >= 1280))
            {
              D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
            D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (4 + C))) + (_i1 * (4 + C))) + (2 * _i2))]) * 0.125f);
          }
          if ((_i1 <= 1279))
          {
            #pragma ivdep
            for (int  _i2 = 770; (_i2 <= 771); _i2 = (_i2 + 1))
            {
              D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 770; (_i2 <= 771); _i2 = (_i2 + 1))
            {
              D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 1283); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 1282))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 1539); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 1536))
        {
          Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
        }
        Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
        if ((_i2 <= 1))
        {
          Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
        }
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1539); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
          if ((_i2 >= 1536))
          {
            Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
          }
          else
          {
            if ((_i2 <= 1))
            {
              Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        if ((_i1 <= 1279))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
            Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
          }
        }
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 1537); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 1536))
          {
            Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
          }
          Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = ((((img[(((-3 + (2 * _i1)) * (4 + C)) + _i2)] + (3.0f * img[(((-2 + (2 * _i1)) * (4 + C)) + _i2)])) + (3.0f * img[(((-1 + (2 * _i1)) * (4 + C)) + _i2)])) + img[(((2 * _i1) * (4 + C)) + _i2)]) * 0.125f);
          if ((_i1 >= 1280))
          {
            Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1279))
        {
          #pragma ivdep
          for (int  _i2 = 1538; (_i2 <= 1539); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 1538; (_i2 <= 1539); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
            Dx_inGPyramid_L1[((_i1 * (4 + C)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 643); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 642))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 768))
          {
            Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
          Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            if ((_i2 >= 768))
            {
              Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
            else
            {
              if ((_i2 <= 1))
              {
                Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
        }
        else
        {
          if ((_i1 <= 639))
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
              Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
          }
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 769); _i2 = (_i2 + 1))
          {
            if ((_i2 >= 768))
            {
              Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
            Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = ((((D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + ((-3 + (2 * _i1)) * (((C / 2) + 3) + 1))) + _i2)] + (3.0f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + ((-2 + (2 * _i1)) * (((C / 2) + 3) + 1))) + _i2)])) + (3.0f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + ((-1 + (2 * _i1)) * (((C / 2) + 3) + 1))) + _i2)])) + D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + ((2 * _i1) * (((C / 2) + 3) + 1))) + _i2)]) * 0.125f);
            if ((_i1 >= 640))
            {
              Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 639))
          {
            #pragma ivdep
            for (int  _i2 = 770; (_i2 <= 771); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 770; (_i2 <= 771); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
              Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 1283); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 1282))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 768))
        {
          D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        }
        else
        {
          if ((_i2 <= 1))
          {
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
        D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 768))
          {
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
          D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 1279))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 769); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 768))
          {
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
          D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L1[((_i1 * (4 + C)) + (-3 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L1[((_i1 * (4 + C)) + (-2 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L1[((_i1 * (4 + C)) + (-1 + (2 * _i2)))])) + Dx_inGPyramid_L1[((_i1 * (4 + C)) + (2 * _i2))]) * 0.125f);
          if ((_i1 >= 1280))
          {
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1279))
        {
          #pragma ivdep
          for (int  _i2 = 770; (_i2 <= 771); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 770; (_i2 <= 771); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 643); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 642))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
          D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 384))
          {
            D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 639))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            if ((_i1 <= 1))
            {
              D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 1))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 383); _i2 = (_i2 + 1))
            {
              D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
            #pragma ivdep
            for (int  _i2 = 384; (_i2 <= 387); _i2 = (_i2 + 1))
            {
              D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 >= 2))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 385); _i2 = (_i2 + 1))
          {
            if ((_i1 >= 640))
            {
              D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
            D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + (2 * _i2))]) * 0.125f);
            if ((_i2 >= 384))
            {
              D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 639))
          {
            #pragma ivdep
            for (int  _i2 = 386; (_i2 <= 387); _i2 = (_i2 + 1))
            {
              D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 386; (_i2 <= 387); _i2 = (_i2 + 1))
            {
              D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 643); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 642))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 768))
        {
          Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        }
        Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        if ((_i2 <= 1))
        {
          Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          if ((_i2 >= 768))
          {
            Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
          else
          {
            if ((_i2 <= 1))
            {
              Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        if ((_i1 <= 639))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
            Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 769); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 768))
          {
            Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
          Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L1[(((-3 + (2 * _i1)) * (((C / 2) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L1[(((-2 + (2 * _i1)) * (((C / 2) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L1[(((-1 + (2 * _i1)) * (((C / 2) + 3) + 1)) + _i2)])) + D_inGPyramid_L1[(((2 * _i1) * (((C / 2) + 3) + 1)) + _i2)]) * 0.125f);
          if ((_i1 >= 640))
          {
            Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 639))
        {
          #pragma ivdep
          for (int  _i2 = 770; (_i2 <= 771); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 770; (_i2 <= 771); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
            Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 323); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 322))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
          Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 384))
          {
            Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 319))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            if ((_i1 <= 1))
            {
              Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 1))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 383); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
            #pragma ivdep
            for (int  _i2 = 384; (_i2 <= 387); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
              Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 >= 2))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 385); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = ((((D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + ((-3 + (2 * _i1)) * (((C / 4) + 3) + 1))) + _i2)] + (3.0f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + ((-2 + (2 * _i1)) * (((C / 4) + 3) + 1))) + _i2)])) + (3.0f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + ((-1 + (2 * _i1)) * (((C / 4) + 3) + 1))) + _i2)])) + D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + ((2 * _i1) * (((C / 4) + 3) + 1))) + _i2)]) * 0.125f);
            if ((_i1 >= 320))
            {
              Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i2 >= 384))
            {
              Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 319))
          {
            #pragma ivdep
            for (int  _i2 = 386; (_i2 <= 387); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 386; (_i2 <= 387); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
              Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 643); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 642))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 384))
        {
          D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
        }
        else
        {
          if ((_i2 <= 1))
          {
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
        D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 384))
          {
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
          D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 639))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 385); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 384))
          {
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
          D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + (-3 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + (-2 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + (-1 + (2 * _i2)))])) + Dx_inGPyramid_L2[((_i1 * (((C / 2) + 3) + 1)) + (2 * _i2))]) * 0.125f);
          if ((_i1 >= 640))
          {
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 639))
        {
          #pragma ivdep
          for (int  _i2 = 386; (_i2 <= 387); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 386; (_i2 <= 387); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 323); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 322))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
          D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 192))
          {
            D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 319))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            if ((_i1 <= 1))
            {
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 1))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
            {
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
            #pragma ivdep
            for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
            {
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 >= 2))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 193); _i2 = (_i2 + 1))
          {
            D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + (2 * _i2))]) * 0.125f);
            if ((_i1 >= 320))
            {
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i2 >= 192))
            {
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 319))
          {
            #pragma ivdep
            for (int  _i2 = 194; (_i2 <= 195); _i2 = (_i2 + 1))
            {
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 194; (_i2 <= 195); _i2 = (_i2 + 1))
            {
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 323); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 322))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 384))
        {
          Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
        }
        else
        {
          if ((_i2 <= 1))
          {
            Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
        Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 384))
          {
            Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
          Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 319))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
            Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 385); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 384))
          {
            Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
          Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L2[(((-3 + (2 * _i1)) * (((C / 4) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L2[(((-2 + (2 * _i1)) * (((C / 4) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L2[(((-1 + (2 * _i1)) * (((C / 4) + 3) + 1)) + _i2)])) + D_inGPyramid_L2[(((2 * _i1) * (((C / 4) + 3) + 1)) + _i2)]) * 0.125f);
          if ((_i1 >= 320))
          {
            Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 319))
        {
          #pragma ivdep
          for (int  _i2 = 386; (_i2 <= 387); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 386; (_i2 <= 387); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
            Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 163); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 2))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          if ((_i1 >= 160))
          {
            Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 >= 162))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
          #pragma ivdep
          for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 193); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = ((((D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + ((-3 + (2 * _i1)) * (((C / 8) + 3) + 1))) + _i2)] + (3.0f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + ((-2 + (2 * _i1)) * (((C / 8) + 3) + 1))) + _i2)])) + (3.0f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + ((-1 + (2 * _i1)) * (((C / 8) + 3) + 1))) + _i2)])) + D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + ((2 * _i1) * (((C / 8) + 3) + 1))) + _i2)]) * 0.125f);
            if ((_i2 >= 192))
            {
              Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i1 >= 160))
            {
              Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
          }
          #pragma ivdep
          for (int  _i2 = 194; (_i2 <= 195); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            if ((_i1 >= 160))
            {
              Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 192))
          {
            Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
          Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 323); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 322))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 192))
        {
          D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
        D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        if ((_i2 <= 1))
        {
          D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          if ((_i2 >= 192))
          {
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
          else
          {
            if ((_i2 <= 1))
            {
              D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        if ((_i1 <= 319))
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 193); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 192))
          {
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
          D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + (-3 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + (-2 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + (-1 + (2 * _i2)))])) + Dx_inGPyramid_L3[((_i1 * (((C / 4) + 3) + 1)) + (2 * _i2))]) * 0.125f);
          if ((_i1 >= 320))
          {
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 319))
        {
          #pragma ivdep
          for (int  _i2 = 194; (_i2 <= 195); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 194; (_i2 <= 195); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 163); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 2))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          if ((_i1 >= 160))
          {
            D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 >= 162))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
          {
            D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
          #pragma ivdep
          for (int  _i2 = 96; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 97); _i2 = (_i2 + 1))
          {
            D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + (2 * _i2))]) * 0.125f);
            if ((_i2 >= 96))
            {
              D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i1 >= 160))
            {
              D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
          }
          #pragma ivdep
          for (int  _i2 = 98; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            if ((_i1 >= 160))
            {
              D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
          D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 96))
          {
            D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 163); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 160))
    {
      for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
      {
        if ((((_i2 <= 193) && (_i1 <= 161)) && (_i2 >= 2)))
        {
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L3[(((-3 + (2 * _i1)) * (((C / 8) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L3[(((-2 + (2 * _i1)) * (((C / 8) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L3[(((-1 + (2 * _i1)) * (((C / 8) + 3) + 1)) + _i2)])) + D_inGPyramid_L3[(((2 * _i1) * (((C / 8) + 3) + 1)) + _i2)]) * 0.125f);
        }
        Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        if ((_i2 <= 1))
        {
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
        else
        {
          if ((_i2 >= 192))
          {
            Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          if ((_i2 >= 192))
          {
            Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
        for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L3[(((-3 + (2 * _i1)) * (((C / 8) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L3[(((-2 + (2 * _i1)) * (((C / 8) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L3[(((-1 + (2 * _i1)) * (((C / 8) + 3) + 1)) + _i2)])) + D_inGPyramid_L3[(((2 * _i1) * (((C / 8) + 3) + 1)) + _i2)]) * 0.125f);
        }
        for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
          if ((_i2 <= 193))
          {
            Dx_inGPyramid_L4[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L3[(((-3 + (2 * _i1)) * (((C / 8) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L3[(((-2 + (2 * _i1)) * (((C / 8) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L3[(((-1 + (2 * _i1)) * (((C / 8) + 3) + 1)) + _i2)])) + D_inGPyramid_L3[(((2 * _i1) * (((C / 8) + 3) + 1)) + _i2)]) * 0.125f);
          }
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
          Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
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
            else
            {
              if ((_i2 >= 96))
              {
                Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
              }
            }
            Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
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
            if ((_i1 >= 80))
            {
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i2 >= 96))
            {
              Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
            }
            Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = ((((D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + ((-3 + (2 * _i1)) * (((C / 16) + 3) + 1))) + _i2)] + (3.0f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + ((-2 + (2 * _i1)) * (((C / 16) + 3) + 1))) + _i2)])) + (3.0f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + ((-1 + (2 * _i1)) * (((C / 16) + 3) + 1))) + _i2)])) + D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + ((2 * _i1) * (((C / 16) + 3) + 1))) + _i2)]) * 0.125f);
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
        if ((_i1 <= 79))
        {
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            if ((_i1 <= 1))
            {
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 1))
          {
            for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
            {
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
            for (int  _i2 = 48; (_i2 <= 51); _i2 = (_i2 + 1))
            {
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
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
        if ((_i1 >= 2))
        {
          for (int  _i2 = 2; (_i2 <= 49); _i2 = (_i2 + 1))
          {
            D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + (2 * _i2))]) * 0.125f);
            if ((_i1 >= 80))
            {
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i2 >= 48))
            {
              D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
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
        if ((_i2 <= 1))
        {
          Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
        Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 96))
        {
          Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
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
          if ((_i1 <= 1))
          {
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
          for (int  _i2 = 96; (_i2 <= 99); _i2 = (_i2 + 1))
          {
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
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
      if ((_i1 >= 2))
      {
        for (int  _i2 = 2; (_i2 <= 97); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L4[(((-3 + (2 * _i1)) * (((C / 16) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L4[(((-2 + (2 * _i1)) * (((C / 16) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L4[(((-1 + (2 * _i1)) * (((C / 16) + 3) + 1)) + _i2)])) + D_inGPyramid_L4[(((2 * _i1) * (((C / 16) + 3) + 1)) + _i2)]) * 0.125f);
          if ((_i1 >= 80))
          {
            Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
          }
          if ((_i2 >= 96))
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
      if ((_i1 >= 2))
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if ((_i1 >= 40))
          {
            Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 >= 42))
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
        else
        {
          for (int  _i2 = 2; (_i2 <= 49); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = ((((D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((-3 + (2 * _i1)) * (((C / 32) + 3) + 1))) + _i2)] + (3.0f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((-2 + (2 * _i1)) * (((C / 32) + 3) + 1))) + _i2)])) + (3.0f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((-1 + (2 * _i1)) * (((C / 32) + 3) + 1))) + _i2)])) + D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((2 * _i1) * (((C / 32) + 3) + 1))) + _i2)]) * 0.125f);
            if ((_i2 >= 48))
            {
              Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i1 >= 40))
            {
              Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            }
          }
          for (int  _i2 = 50; (_i2 <= 51); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
            if ((_i1 >= 40))
            {
              Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
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
            Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
          Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 82))
    {
      for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
      {
        if ((_i2 <= 1))
        {
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
        D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 48))
        {
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      if ((_i1 <= 79))
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
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
      }
      else
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 >= 2))
      {
        for (int  _i2 = 2; (_i2 <= 49); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + (-3 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + (-2 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + (-1 + (2 * _i2)))])) + Dx_inGPyramid_L5[((_i1 * (((C / 16) + 3) + 1)) + (2 * _i2))]) * 0.125f);
          if ((_i1 >= 80))
          {
            D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
          if ((_i2 >= 48))
          {
            D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((_i1 <= 79))
        {
          for (int  _i2 = 50; (_i2 <= 51); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 50; (_i2 <= 51); _i2 = (_i2 + 1))
          {
            D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
            D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 2))
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          if ((_i1 >= 40))
          {
            D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 >= 42))
        {
          for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
          {
            D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
          for (int  _i2 = 24; (_i2 <= 27); _i2 = (_i2 + 1))
          {
            D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 2; (_i2 <= 25); _i2 = (_i2 + 1))
          {
            D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + (2 * _i2))]) * 0.125f);
            if ((_i2 >= 24))
            {
              D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i1 >= 40))
            {
              D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
          }
          for (int  _i2 = 26; (_i2 <= 27); _i2 = (_i2 + 1))
          {
            D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            if ((_i1 >= 40))
            {
              D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
      }
      else
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
    }
  }
  for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 40))
    {
      for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
      {
        if ((((_i2 <= 49) && (_i1 <= 41)) && (_i2 >= 2)))
        {
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L5[(((-3 + (2 * _i1)) * (((C / 32) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L5[(((-2 + (2 * _i1)) * (((C / 32) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L5[(((-1 + (2 * _i1)) * (((C / 32) + 3) + 1)) + _i2)])) + D_inGPyramid_L5[(((2 * _i1) * (((C / 32) + 3) + 1)) + _i2)]) * 0.125f);
        }
        if ((_i2 >= 48))
        {
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
        else
        {
          if ((_i2 <= 1))
          {
            Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
        }
        Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
      }
    }
    else
    {
      if ((_i1 <= 1))
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
      else
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
        for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L5[(((-3 + (2 * _i1)) * (((C / 32) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L5[(((-2 + (2 * _i1)) * (((C / 32) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L5[(((-1 + (2 * _i1)) * (((C / 32) + 3) + 1)) + _i2)])) + D_inGPyramid_L5[(((2 * _i1) * (((C / 32) + 3) + 1)) + _i2)]) * 0.125f);
        }
        for (int  _i2 = 48; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          if ((_i2 <= 49))
          {
            Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((((D_inGPyramid_L5[(((-3 + (2 * _i1)) * (((C / 32) + 3) + 1)) + _i2)] + (3.0f * D_inGPyramid_L5[(((-2 + (2 * _i1)) * (((C / 32) + 3) + 1)) + _i2)])) + (3.0f * D_inGPyramid_L5[(((-1 + (2 * _i1)) * (((C / 32) + 3) + 1)) + _i2)])) + D_inGPyramid_L5[(((2 * _i1) * (((C / 32) + 3) + 1)) + _i2)]) * 0.125f);
          }
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
        if ((_i1 <= 1))
        {
          for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
          {
            if ((_i2 <= 1))
            {
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
            else
            {
              if ((_i2 >= 24))
              {
                Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
              }
            }
            Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          if ((_i1 <= 19))
          {
            for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
            {
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
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
          for (int  _i2 = 2; (_i2 <= 25); _i2 = (_i2 + 1))
          {
            if ((_i2 >= 24))
            {
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i1 >= 20))
            {
              Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
            }
            Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = ((((D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + ((-3 + (2 * _i1)) * (((C / 64) + 3) + 1))) + _i2)] + (3.0f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + ((-2 + (2 * _i1)) * (((C / 64) + 3) + 1))) + _i2)])) + (3.0f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + ((-1 + (2 * _i1)) * (((C / 64) + 3) + 1))) + _i2)])) + D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + ((2 * _i1) * (((C / 64) + 3) + 1))) + _i2)]) * 0.125f);
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
    if ((_i1 >= 40))
    {
      for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
      {
        if ((((_i2 <= 25) && (_i1 <= 41)) && (_i2 >= 2)))
        {
          D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (-3 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (-2 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (-1 + (2 * _i2)))])) + Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (2 * _i2))]) * 0.125f);
        }
        D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        if ((_i2 <= 1))
        {
          D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
        else
        {
          if ((_i2 >= 24))
          {
            D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
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
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
        for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (-3 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (-2 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (-1 + (2 * _i2)))])) + Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (2 * _i2))]) * 0.125f);
        }
        for (int  _i2 = 24; (_i2 <= 27); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          if ((_i2 <= 25))
          {
            D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (-3 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (-2 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (-1 + (2 * _i2)))])) + Dx_inGPyramid_L6[((_i1 * (((C / 32) + 3) + 1)) + (2 * _i2))]) * 0.125f);
          }
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
        for (int  _i2 = 0; (_i2 <= 15); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          }
          D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 12))
          {
            D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        if ((_i1 <= 19))
        {
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            if ((_i1 <= 1))
            {
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 1))
          {
            for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
            {
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            }
            for (int  _i2 = 12; (_i2 <= 15); _i2 = (_i2 + 1))
            {
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            }
          }
        }
        else
        {
          for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
          {
            D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 >= 2))
        {
          for (int  _i2 = 2; (_i2 <= 13); _i2 = (_i2 + 1))
          {
            D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = ((((Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (-3 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (-2 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (-1 + (2 * _i2)))])) + Dx_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + (2 * _i2))]) * 0.125f);
            if ((_i1 >= 20))
            {
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            }
            if ((_i2 >= 12))
            {
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            }
          }
          if ((_i1 <= 19))
          {
            for (int  _i2 = 14; (_i2 <= 15); _i2 = (_i2 + 1))
            {
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            for (int  _i2 = 14; (_i2 <= 15); _i2 = (_i2 + 1))
            {
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
              D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
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
      if ((_i1 >= 2))
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          if ((_i1 >= 40))
          {
            Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 == 42))
        {
          for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (42 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          if ((_i1 == 43))
          {
            for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (43 * (((C / 128) + 3) + 1))) + _i2)] = 0;
            }
          }
          else
          {
            if ((((_i1 + 1) % 2) == 0))
            {
              for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
              {
                Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 128) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 128) + 3) + 1))) + _i2)]));
                if ((_i1 == 41))
                {
                  Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (41 * (((C / 128) + 3) + 1))) + _i2)] = 0;
                }
              }
            }
            else
            {
              for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
              {
                Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + ((_i1 / 2) * (((C / 128) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 128) + 3) + 1))) + _i2)]));
                if ((_i1 == 40))
                {
                  Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (40 * (((C / 128) + 3) + 1))) + _i2)] = 0;
                }
              }
            }
          }
        }
        for (int  _i2 = 12; (_i2 <= 15); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          if (((((_i1 % 2) == 0) && (_i1 <= 40)) && (_i2 <= 13)))
          {
            Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + ((_i1 / 2) * (((C / 128) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 128) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((((_i1 - 1) % 2) == 0) && (_i1 <= 41)) && (_i2 <= 13)))
            {
              Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 128) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L7[(((_i0 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 128) + 3) + 1))) + _i2)]));
            }
          }
          if ((_i1 >= 40))
          {
            Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
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
    }
  }
  for (int  _i1 = 0; (_i1 <= 23); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 2))
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        if ((_i1 >= 20))
        {
          D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 >= 22))
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
      else
      {
        for (int  _i2 = 2; (_i2 <= 13); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = ((((Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + (-3 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + (-2 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + (-1 + (2 * _i2)))])) + Dx_inGPyramid_L7[((_i1 * (((C / 64) + 3) + 1)) + (2 * _i2))]) * 0.125f);
          if ((_i2 >= 12))
          {
            D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          }
          if ((_i1 >= 20))
          {
            D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          }
        }
        for (int  _i2 = 14; (_i2 <= 15); _i2 = (_i2 + 1))
        {
          D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          if ((_i1 >= 20))
          {
            D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
    }
    else
    {
      for (int  _i2 = 0; (_i2 <= 15); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 12))
        {
          D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        }
        D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        if ((_i2 <= 1))
        {
          D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
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
        for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
        {
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
          U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 24))
          {
            U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
          {
            U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
          {
            if (((_i2 % 2) == 0))
            {
              U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = (D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = (D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
          }
        }
        for (int  _i2 = 24; (_i2 <= 27); _i2 = (_i2 + 1))
        {
          if (((_i2 == 24) && (_i1 >= 2)))
          {
            U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + 24)] = (D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + 24)] - ((0.25f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + (24 / 2))]) + (0.75f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((24 / 2) + 1))])));
          }
          else
          {
            if (((_i2 == 25) && (_i1 >= 2)))
            {
              U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + 25)] = (D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + 25)] - ((0.25f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((25 / 2) + 2))]) + (0.75f * Ux_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + ((25 / 2) + 1))])));
            }
          }
          U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 23); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 0; (_i2 <= 15); _i2 = (_i2 + 1))
    {
      int  _ct9 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct10 = 0;
      int  _ct11 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct9: _ct10);
      int  _ct12 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct13 = 0;
      int  _ct14 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct12: _ct13);
      int  _ct15 = _ct14;
      int  _ct16 = 6;
      int  _ct17 = ((_ct11 < 6)? _ct15: _ct16);
      int  _ct18 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct19 = 0;
      int  _ct20 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct18: _ct19);
      int  _ct21 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct22 = 0;
      int  _ct23 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct21: _ct22);
      int  _ct24 = _ct23;
      int  _ct25 = 6;
      int  _ct26 = ((_ct20 < 6)? _ct24: _ct25);
      int  _ct27 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct28 = 0;
      int  _ct29 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct27: _ct28);
      int  _ct30 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct31 = 0;
      int  _ct32 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct30: _ct31);
      int  _ct33 = _ct32;
      int  _ct34 = 6;
      int  _ct35 = ((_ct29 < 6)? _ct33: _ct34);
      int  _ct36 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct37 = 0;
      int  _ct38 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct36: _ct37);
      int  _ct39 = (int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct40 = 0;
      int  _ct41 = (((int ) ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct39: _ct40);
      int  _ct42 = _ct41;
      int  _ct43 = 6;
      int  _ct44 = ((_ct38 < 6)? _ct42: _ct43);
      outLPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = (((1.0f - ((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)) - _ct17)) * D_gPyramid_L7[(((_ct26 * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)]) + (((D_inGPyramid_L7[((_i1 * (((C / 128) + 3) + 1)) + _i2)] * (float ) (7)) - _ct35) * D_gPyramid_L7[((((_ct44 + 1) * ((((R / 128) + 3) + 1) * (((C / 128) + 3) + 1))) + (_i1 * (((C / 128) + 3) + 1))) + _i2)]));
    }
  }
  for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
    {
      int  _ct45 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct46 = 0;
      int  _ct47 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct45: _ct46);
      int  _ct48 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct49 = 0;
      int  _ct50 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct48: _ct49);
      int  _ct51 = _ct50;
      int  _ct52 = 6;
      int  _ct53 = ((_ct47 < 6)? _ct51: _ct52);
      int  _ct54 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct55 = 0;
      int  _ct56 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct54: _ct55);
      int  _ct57 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct58 = 0;
      int  _ct59 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct57: _ct58);
      int  _ct60 = _ct59;
      int  _ct61 = 6;
      int  _ct62 = ((_ct56 < 6)? _ct60: _ct61);
      int  _ct63 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct64 = 0;
      int  _ct65 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct63: _ct64);
      int  _ct66 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct67 = 0;
      int  _ct68 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct66: _ct67);
      int  _ct69 = _ct68;
      int  _ct70 = 6;
      int  _ct71 = ((_ct65 < 6)? _ct69: _ct70);
      int  _ct72 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct73 = 0;
      int  _ct74 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct72: _ct73);
      int  _ct75 = (int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct76 = 0;
      int  _ct77 = (((int ) ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct75: _ct76);
      int  _ct78 = _ct77;
      int  _ct79 = 6;
      int  _ct80 = ((_ct74 < 6)? _ct78: _ct79);
      outLPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = (((1.0f - ((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)) - _ct53)) * U_lPyramid_L6[(((_ct62 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)]) + (((D_inGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] * (float ) (7)) - _ct71) * U_lPyramid_L6[((((_ct80 + 1) * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)]));
    }
  }
  for (int  _i1 = 0; (_i1 <= 43); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 2))
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        if ((_i1 >= 40))
        {
          Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        }
        Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
      }
      if ((_i1 == 42))
      {
        for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L6[((42 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        if ((_i1 == 43))
        {
          for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L6[((43 * (((C / 128) + 3) + 1)) + _i2)] = 0;
          }
        }
        else
        {
          if ((((_i1 + 1) % 2) == 0))
          {
            for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
            {
              if ((_i1 == 41))
              {
                Ux_outGPyramid_L6[((41 * (((C / 128) + 3) + 1)) + _i2)] = 0;
              }
              Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = ((0.25f * outLPyramid_L7[((((_i1 / 2) + 2) * (((C / 128) + 3) + 1)) + _i2)]) + (0.75f * outLPyramid_L7[((((_i1 / 2) + 1) * (((C / 128) + 3) + 1)) + _i2)]));
            }
          }
          else
          {
            for (int  _i2 = 2; (_i2 <= 11); _i2 = (_i2 + 1))
            {
              if ((_i1 == 40))
              {
                Ux_outGPyramid_L6[((40 * (((C / 128) + 3) + 1)) + _i2)] = 0;
              }
              Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = ((0.25f * outLPyramid_L7[(((_i1 / 2) * (((C / 128) + 3) + 1)) + _i2)]) + (0.75f * outLPyramid_L7[((((_i1 / 2) + 1) * (((C / 128) + 3) + 1)) + _i2)]));
            }
          }
        }
      }
      for (int  _i2 = 12; (_i2 <= 15); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        if (((((_i1 % 2) == 0) && (_i1 <= 40)) && (_i2 <= 13)))
        {
          Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = ((0.25f * outLPyramid_L7[(((_i1 / 2) * (((C / 128) + 3) + 1)) + _i2)]) + (0.75f * outLPyramid_L7[((((_i1 / 2) + 1) * (((C / 128) + 3) + 1)) + _i2)]));
        }
        if ((_i1 >= 40))
        {
          Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
        }
        if ((((((_i1 - 1) % 2) == 0) && (_i1 <= 41)) && (_i2 <= 13)))
        {
          Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = ((0.25f * outLPyramid_L7[((((_i1 / 2) + 2) * (((C / 128) + 3) + 1)) + _i2)]) + (0.75f * outLPyramid_L7[((((_i1 / 2) + 1) * (((C / 128) + 3) + 1)) + _i2)]));
        }
      }
    }
    else
    {
      for (int  _i2 = 0; (_i2 <= 15); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + _i2)] = 0;
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
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 80))
      {
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
            for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 64) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 64) + 3) + 1))) + _i2)]));
            }
          }
          else
          {
            for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 64) + 3) + 1))) + (_i1 * (((C / 64) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + ((_i1 / 2) * (((C / 64) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L6[(((_i0 * ((((R / 64) + 3) + 1) * (((C / 64) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 64) + 3) + 1))) + _i2)]));
            }
          }
        }
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
      if ((_i1 <= 1))
      {
        for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
        {
          outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
          else
          {
            if ((_i2 >= 24))
            {
              outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
        for (int  _i2 = 2; (_i2 <= 25); _i2 = (_i2 + 1))
        {
          if (((_i2 % 2) == 0))
          {
            outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = (outLPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = (outLPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L6[((_i1 * (((C / 128) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          if ((_i2 >= 24))
          {
            outGPyramid_L6[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
          }
        }
        for (int  _i2 = 26; (_i2 <= 27); _i2 = (_i2 + 1))
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
    if ((_i1 >= 80))
    {
      for (int  _i2 = 0; (_i2 <= 27); _i2 = (_i2 + 1))
      {
        if ((((_i1 == 80) && (_i2 <= 25)) && (_i2 >= 2)))
        {
          Ux_outGPyramid_L5[((80 * (((C / 64) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L6[(((80 / 2) * (((C / 64) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L6[((((80 / 2) + 1) * (((C / 64) + 3) + 1)) + _i2)]));
        }
        else
        {
          if ((((_i1 == 81) && (_i2 <= 25)) && (_i2 >= 2)))
          {
            Ux_outGPyramid_L5[((81 * (((C / 64) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L6[((((81 / 2) + 2) * (((C / 64) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L6[((((81 / 2) + 1) * (((C / 64) + 3) + 1)) + _i2)]));
          }
          else
          {
            if ((_i2 <= 1))
            {
              Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
        Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 24))
        {
          Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 <= 1))
      {
        for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        if ((((_i1 + 1) % 2) == 0))
        {
          for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L6[((((_i1 / 2) + 2) * (((C / 64) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L6[((((_i1 / 2) + 1) * (((C / 64) + 3) + 1)) + _i2)]));
          }
        }
        else
        {
          for (int  _i2 = 2; (_i2 <= 23); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L6[(((_i1 / 2) * (((C / 64) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L6[((((_i1 / 2) + 1) * (((C / 64) + 3) + 1)) + _i2)]));
          }
        }
      }
      for (int  _i2 = 24; (_i2 <= 27); _i2 = (_i2 + 1))
      {
        if (((((_i1 % 2) == 0) && (_i2 <= 25)) && (_i1 >= 2)))
        {
          Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L6[(((_i1 / 2) * (((C / 64) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L6[((((_i1 / 2) + 1) * (((C / 64) + 3) + 1)) + _i2)]));
        }
        else
        {
          if ((((((_i1 + 1) % 2) == 0) && (_i2 <= 25)) && (_i1 >= 3)))
          {
            Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L6[((((_i1 / 2) + 2) * (((C / 64) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L6[((((_i1 / 2) + 1) * (((C / 64) + 3) + 1)) + _i2)]));
          }
        }
        Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
    {
      int  _ct81 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct82 = 0;
      int  _ct83 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct81: _ct82);
      int  _ct84 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct85 = 0;
      int  _ct86 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct84: _ct85);
      int  _ct87 = _ct86;
      int  _ct88 = 6;
      int  _ct89 = ((_ct83 < 6)? _ct87: _ct88);
      int  _ct90 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct91 = 0;
      int  _ct92 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct90: _ct91);
      int  _ct93 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct94 = 0;
      int  _ct95 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct93: _ct94);
      int  _ct96 = _ct95;
      int  _ct97 = 6;
      int  _ct98 = ((_ct92 < 6)? _ct96: _ct97);
      int  _ct99 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct100 = 0;
      int  _ct101 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct99: _ct100);
      int  _ct102 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct103 = 0;
      int  _ct104 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct102: _ct103);
      int  _ct105 = _ct104;
      int  _ct106 = 6;
      int  _ct107 = ((_ct101 < 6)? _ct105: _ct106);
      int  _ct108 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct109 = 0;
      int  _ct110 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct108: _ct109);
      int  _ct111 = (int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct112 = 0;
      int  _ct113 = (((int ) ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct111: _ct112);
      int  _ct114 = _ct113;
      int  _ct115 = 6;
      int  _ct116 = ((_ct110 < 6)? _ct114: _ct115);
      outLPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = (((1.0f - ((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)) - _ct89)) * U_lPyramid_L5[(((_ct98 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)]) + (((D_inGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] * (float ) (7)) - _ct107) * U_lPyramid_L5[((((_ct116 + 1) * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)]));
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 163); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 2))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if ((_i1 >= 160))
          {
            Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 == 162))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (162 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          if ((_i1 == 163))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (163 * (((C / 32) + 3) + 1))) + _i2)] = 0;
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
                if ((_i1 == 161))
                {
                  Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (161 * (((C / 32) + 3) + 1))) + _i2)] = 0;
                }
              }
            }
            else
            {
              #pragma ivdep
              for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
              {
                Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((_i1 / 2) * (((C / 32) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 32) + 3) + 1))) + _i2)]));
                if ((_i1 == 160))
                {
                  Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (160 * (((C / 32) + 3) + 1))) + _i2)] = 0;
                }
              }
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 48; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if (((((_i1 % 2) == 0) && (_i1 <= 160)) && (_i2 <= 49)))
          {
            Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + ((_i1 / 2) * (((C / 32) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 32) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((((_i1 - 1) % 2) == 0) && (_i1 <= 161)) && (_i2 <= 49)))
            {
              Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 32) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L5[(((_i0 * ((((R / 32) + 3) + 1) * (((C / 32) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 32) + 3) + 1))) + _i2)]));
            }
          }
          if ((_i1 >= 160))
          {
            Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 48))
          {
            Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
          Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 83); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 80))
    {
      for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 48))
        {
          outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
        else
        {
          if ((_i2 <= 1))
          {
            outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
        }
        outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
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
        }
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 48))
          {
            outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          }
          outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          if ((_i2 <= 1))
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
        }
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
        for (int  _i2 = 48; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          if ((_i2 == 48))
          {
            outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + 48)] = (outLPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + 48)] + ((0.25f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + (48 / 2))]) + (0.75f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + ((48 / 2) + 1))])));
          }
          else
          {
            if ((_i2 == 49))
            {
              outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + 49)] = (outLPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + 49)] + ((0.25f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + ((49 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L5[((_i1 * (((C / 64) + 3) + 1)) + ((49 / 2) + 1))])));
            }
          }
          outGPyramid_L5[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
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
        for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          if ((((((_i2 % 2) == 0) && (_i2 <= 96)) && (_i1 <= 161)) && (_i2 >= 2)))
          {
            U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = (D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 97)) && (_i1 <= 161)) && (_i2 >= 3)))
            {
              U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = (D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              if ((_i2 <= 1))
              {
                U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
          U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 96))
          {
            U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
          {
            U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
          {
            if (((_i2 % 2) == 0))
            {
              U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = (D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = (D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 96; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          if (((_i2 == 96) && (_i1 >= 2)))
          {
            U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + 96)] = (D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + 96)] - ((0.25f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + (96 / 2))]) + (0.75f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + ((96 / 2) + 1))])));
          }
          else
          {
            if (((_i2 == 97) && (_i1 >= 2)))
            {
              U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + 97)] = (D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + 97)] - ((0.25f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + ((97 / 2) + 2))]) + (0.75f * Ux_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 32) + 3) + 1))) + (_i1 * (((C / 32) + 3) + 1))) + ((97 / 2) + 1))])));
            }
          }
          U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 163); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 160))
    {
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
        if ((_i2 >= 48))
        {
          Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
        }
        Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        for (int  _i2 = 0; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
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
        }
        if (((_i1 % 2) == 0))
        {
          for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L5[(((_i1 / 2) * (((C / 32) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L5[((((_i1 / 2) + 1) * (((C / 32) + 3) + 1)) + _i2)]));
          }
        }
        else
        {
          for (int  _i2 = 2; (_i2 <= 47); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L5[((((_i1 / 2) + 2) * (((C / 32) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L5[((((_i1 / 2) + 1) * (((C / 32) + 3) + 1)) + _i2)]));
          }
        }
        for (int  _i2 = 48; (_i2 <= 51); _i2 = (_i2 + 1))
        {
          if (((((_i1 - 1) % 2) == 0) && (_i2 <= 49)))
          {
            Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L5[((((_i1 / 2) + 2) * (((C / 32) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L5[((((_i1 / 2) + 1) * (((C / 32) + 3) + 1)) + _i2)]));
          }
          Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = 0;
          if ((((_i1 % 2) == 0) && (_i2 <= 49)))
          {
            Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L5[(((_i1 / 2) * (((C / 32) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L5[((((_i1 / 2) + 1) * (((C / 32) + 3) + 1)) + _i2)]));
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 163); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
    {
      int  _ct117 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct118 = 0;
      int  _ct119 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct117: _ct118);
      int  _ct120 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct121 = 0;
      int  _ct122 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct120: _ct121);
      int  _ct123 = _ct122;
      int  _ct124 = 6;
      int  _ct125 = ((_ct119 < 6)? _ct123: _ct124);
      int  _ct126 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct127 = 0;
      int  _ct128 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct126: _ct127);
      int  _ct129 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct130 = 0;
      int  _ct131 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct129: _ct130);
      int  _ct132 = _ct131;
      int  _ct133 = 6;
      int  _ct134 = ((_ct128 < 6)? _ct132: _ct133);
      int  _ct135 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct136 = 0;
      int  _ct137 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct135: _ct136);
      int  _ct138 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct139 = 0;
      int  _ct140 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct138: _ct139);
      int  _ct141 = _ct140;
      int  _ct142 = 6;
      int  _ct143 = ((_ct137 < 6)? _ct141: _ct142);
      int  _ct144 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct145 = 0;
      int  _ct146 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct144: _ct145);
      int  _ct147 = (int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct148 = 0;
      int  _ct149 = (((int ) ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct147: _ct148);
      int  _ct150 = _ct149;
      int  _ct151 = 6;
      int  _ct152 = ((_ct146 < 6)? _ct150: _ct151);
      outLPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = (((1.0f - ((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)) - _ct125)) * U_lPyramid_L4[(((_ct134 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)]) + (((D_inGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] * (float ) (7)) - _ct143) * U_lPyramid_L4[((((_ct152 + 1) * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)]));
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 323); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 320))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          if ((((_i1 == 320) && (_i2 <= 97)) && (_i2 >= 2)))
          {
            Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (320 * (((C / 16) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + ((320 / 2) * (((C / 16) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (((320 / 2) + 1) * (((C / 16) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((_i1 == 321) && (_i2 <= 97)) && (_i2 >= 2)))
            {
              Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (321 * (((C / 16) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (((321 / 2) + 2) * (((C / 16) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (((321 / 2) + 1) * (((C / 16) + 3) + 1))) + _i2)]));
            }
            else
            {
              if ((_i2 <= 1))
              {
                Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
          Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 96))
          {
            Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          if ((((_i1 + 1) % 2) == 0))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 16) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 16) + 3) + 1))) + _i2)]));
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + ((_i1 / 2) * (((C / 16) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 16) + 3) + 1))) + _i2)]));
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 96; (_i2 <= 99); _i2 = (_i2 + 1))
        {
          if (((((_i1 % 2) == 0) && (_i2 <= 97)) && (_i1 >= 2)))
          {
            Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + ((_i1 / 2) * (((C / 16) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 16) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((((_i1 + 1) % 2) == 0) && (_i2 <= 97)) && (_i1 >= 3)))
            {
              Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 16) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L4[(((_i0 * ((((R / 16) + 3) + 1) * (((C / 16) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 16) + 3) + 1))) + _i2)]));
            }
          }
          Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 163); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 160))
    {
      for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
      {
        if ((((((_i2 % 2) == 0) && (_i2 <= 96)) && (_i1 <= 161)) && (_i2 >= 2)))
        {
          outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = (outLPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + ((_i2 / 2) + 1))])));
        }
        else
        {
          if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 97)) && (_i1 <= 161)) && (_i2 >= 3)))
          {
            outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = (outLPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if ((_i2 <= 1))
            {
              outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
        outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 96))
        {
          outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 <= 1))
      {
        for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
        {
          outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
        {
          if (((_i2 % 2) == 0))
          {
            outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = (outLPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = (outLPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
        }
      }
      for (int  _i2 = 96; (_i2 <= 99); _i2 = (_i2 + 1))
      {
        if (((_i2 == 96) && (_i1 >= 2)))
        {
          outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + 96)] = (outLPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + 96)] + ((0.25f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + (96 / 2))]) + (0.75f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + ((96 / 2) + 1))])));
        }
        else
        {
          if (((_i2 == 97) && (_i1 >= 2)))
          {
            outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + 97)] = (outLPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + 97)] + ((0.25f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + ((97 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L4[((_i1 * (((C / 32) + 3) + 1)) + ((97 / 2) + 1))])));
          }
        }
        outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          outGPyramid_L4[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 323); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 320))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          if ((((((_i2 % 2) == 0) && (_i2 <= 192)) && (_i1 <= 321)) && (_i2 >= 2)))
          {
            U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = (D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 193)) && (_i1 <= 321)) && (_i2 >= 3)))
            {
              U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = (D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              if ((_i2 <= 1))
              {
                U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
          U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 192))
          {
            U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
          {
            U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
          {
            if (((_i2 % 2) == 0))
            {
              U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = (D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = (D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          if (((_i2 == 192) && (_i1 >= 2)))
          {
            U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + 192)] = (D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + 192)] - ((0.25f * Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + (192 / 2))]) + (0.75f * Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + ((192 / 2) + 1))])));
          }
          else
          {
            if (((_i2 == 193) && (_i1 >= 2)))
            {
              U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + 193)] = (D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + 193)] - ((0.25f * Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + ((193 / 2) + 2))]) + (0.75f * Ux_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 16) + 3) + 1))) + (_i1 * (((C / 16) + 3) + 1))) + ((193 / 2) + 1))])));
            }
          }
          U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  for (int  _i1 = 0; (_i1 <= 323); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 320))
    {
      for (int  _i2 = 0; (_i2 <= 99); _i2 = (_i2 + 1))
      {
        if ((((_i1 == 320) && (_i2 <= 97)) && (_i2 >= 2)))
        {
          Ux_outGPyramid_L3[((320 * (((C / 16) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L4[(((320 / 2) * (((C / 16) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L4[((((320 / 2) + 1) * (((C / 16) + 3) + 1)) + _i2)]));
        }
        else
        {
          if ((((_i1 == 321) && (_i2 <= 97)) && (_i2 >= 2)))
          {
            Ux_outGPyramid_L3[((321 * (((C / 16) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L4[((((321 / 2) + 2) * (((C / 16) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L4[((((321 / 2) + 1) * (((C / 16) + 3) + 1)) + _i2)]));
          }
          else
          {
            if ((_i2 <= 1))
            {
              Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
        Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 96))
        {
          Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 <= 1))
      {
        for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        if ((((_i1 + 1) % 2) == 0))
        {
          for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L4[((((_i1 / 2) + 2) * (((C / 16) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L4[((((_i1 / 2) + 1) * (((C / 16) + 3) + 1)) + _i2)]));
          }
        }
        else
        {
          for (int  _i2 = 2; (_i2 <= 95); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L4[(((_i1 / 2) * (((C / 16) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L4[((((_i1 / 2) + 1) * (((C / 16) + 3) + 1)) + _i2)]));
          }
        }
      }
      for (int  _i2 = 96; (_i2 <= 99); _i2 = (_i2 + 1))
      {
        if (((((_i1 % 2) == 0) && (_i2 <= 97)) && (_i1 >= 2)))
        {
          Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L4[(((_i1 / 2) * (((C / 16) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L4[((((_i1 / 2) + 1) * (((C / 16) + 3) + 1)) + _i2)]));
        }
        else
        {
          if ((((((_i1 + 1) % 2) == 0) && (_i2 <= 97)) && (_i1 >= 3)))
          {
            Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L4[((((_i1 / 2) + 2) * (((C / 16) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L4[((((_i1 / 2) + 1) * (((C / 16) + 3) + 1)) + _i2)]));
          }
        }
        Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 323); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
    {
      int  _ct153 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct154 = 0;
      int  _ct155 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct153: _ct154);
      int  _ct156 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct157 = 0;
      int  _ct158 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct156: _ct157);
      int  _ct159 = _ct158;
      int  _ct160 = 6;
      int  _ct161 = ((_ct155 < 6)? _ct159: _ct160);
      int  _ct162 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct163 = 0;
      int  _ct164 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct162: _ct163);
      int  _ct165 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct166 = 0;
      int  _ct167 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct165: _ct166);
      int  _ct168 = _ct167;
      int  _ct169 = 6;
      int  _ct170 = ((_ct164 < 6)? _ct168: _ct169);
      int  _ct171 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct172 = 0;
      int  _ct173 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct171: _ct172);
      int  _ct174 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct175 = 0;
      int  _ct176 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct174: _ct175);
      int  _ct177 = _ct176;
      int  _ct178 = 6;
      int  _ct179 = ((_ct173 < 6)? _ct177: _ct178);
      int  _ct180 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct181 = 0;
      int  _ct182 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct180: _ct181);
      int  _ct183 = (int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct184 = 0;
      int  _ct185 = (((int ) ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct183: _ct184);
      int  _ct186 = _ct185;
      int  _ct187 = 6;
      int  _ct188 = ((_ct182 < 6)? _ct186: _ct187);
      outLPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = (((1.0f - ((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)) - _ct161)) * U_lPyramid_L3[(((_ct170 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)]) + (((D_inGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] * (float ) (7)) - _ct179) * U_lPyramid_L3[((((_ct188 + 1) * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)]));
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 643); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 640))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          if ((((_i1 == 640) && (_i2 <= 193)) && (_i2 >= 2)))
          {
            Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (640 * (((C / 8) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + ((640 / 2) * (((C / 8) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (((640 / 2) + 1) * (((C / 8) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((_i1 == 641) && (_i2 <= 193)) && (_i2 >= 2)))
            {
              Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (641 * (((C / 8) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (((641 / 2) + 2) * (((C / 8) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (((641 / 2) + 1) * (((C / 8) + 3) + 1))) + _i2)]));
            }
            else
            {
              if ((_i2 <= 1))
              {
                Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
          Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 192))
          {
            Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          if ((((_i1 + 1) % 2) == 0))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 8) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 8) + 3) + 1))) + _i2)]));
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + ((_i1 / 2) * (((C / 8) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 8) + 3) + 1))) + _i2)]));
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
        {
          if (((((_i1 % 2) == 0) && (_i2 <= 193)) && (_i1 >= 2)))
          {
            Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + ((_i1 / 2) * (((C / 8) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 8) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((((_i1 + 1) % 2) == 0) && (_i2 <= 193)) && (_i1 >= 3)))
            {
              Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 8) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L3[(((_i0 * ((((R / 8) + 3) + 1) * (((C / 8) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 8) + 3) + 1))) + _i2)]));
            }
          }
          Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 323); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 320))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
      {
        if ((((((_i2 % 2) == 0) && (_i2 <= 192)) && (_i1 <= 321)) && (_i2 >= 2)))
        {
          outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = (outLPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + ((_i2 / 2) + 1))])));
        }
        else
        {
          if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 193)) && (_i1 <= 321)) && (_i2 >= 3)))
          {
            outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = (outLPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if ((_i2 <= 1))
            {
              outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
        outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 192))
        {
          outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
        {
          outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
        {
          if (((_i2 % 2) == 0))
          {
            outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = (outLPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = (outLPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
        }
      }
      #pragma ivdep
      for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
      {
        if (((_i2 == 192) && (_i1 >= 2)))
        {
          outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + 192)] = (outLPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + 192)] + ((0.25f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + (192 / 2))]) + (0.75f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + ((192 / 2) + 1))])));
        }
        else
        {
          if (((_i2 == 193) && (_i1 >= 2)))
          {
            outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + 193)] = (outLPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + 193)] + ((0.25f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + ((193 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L3[((_i1 * (((C / 16) + 3) + 1)) + ((193 / 2) + 1))])));
          }
        }
        outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          outGPyramid_L3[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 643); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 640))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
          U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          if ((((((_i2 % 2) == 0) && (_i2 <= 384)) && (_i1 <= 641)) && (_i2 >= 2)))
          {
            U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = (D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 385)) && (_i1 <= 641)) && (_i2 >= 3)))
            {
              U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = (D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
          }
          if ((_i2 >= 384))
          {
            U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 383); _i2 = (_i2 + 1))
          {
            U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 383); _i2 = (_i2 + 1))
          {
            if (((_i2 % 2) == 0))
            {
              U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = (D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = (D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 384; (_i2 <= 387); _i2 = (_i2 + 1))
        {
          if (((_i2 == 384) && (_i1 >= 2)))
          {
            U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + 384)] = (D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + 384)] - ((0.25f * Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + (384 / 2))]) + (0.75f * Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + ((384 / 2) + 1))])));
          }
          else
          {
            if (((_i2 == 385) && (_i1 >= 2)))
            {
              U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + 385)] = (D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + 385)] - ((0.25f * Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + ((385 / 2) + 2))]) + (0.75f * Ux_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 8) + 3) + 1))) + (_i1 * (((C / 8) + 3) + 1))) + ((385 / 2) + 1))])));
            }
          }
          U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 643); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 640))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 195); _i2 = (_i2 + 1))
      {
        if ((((_i1 == 640) && (_i2 <= 193)) && (_i2 >= 2)))
        {
          Ux_outGPyramid_L2[((640 * (((C / 8) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L3[(((640 / 2) * (((C / 8) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L3[((((640 / 2) + 1) * (((C / 8) + 3) + 1)) + _i2)]));
        }
        else
        {
          if ((((_i1 == 641) && (_i2 <= 193)) && (_i2 >= 2)))
          {
            Ux_outGPyramid_L2[((641 * (((C / 8) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L3[((((641 / 2) + 2) * (((C / 8) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L3[((((641 / 2) + 1) * (((C / 8) + 3) + 1)) + _i2)]));
          }
          else
          {
            if ((_i2 <= 1))
            {
              Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
        Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 192))
        {
          Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        if ((((_i1 + 1) % 2) == 0))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L3[((((_i1 / 2) + 2) * (((C / 8) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L3[((((_i1 / 2) + 1) * (((C / 8) + 3) + 1)) + _i2)]));
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 191); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L3[(((_i1 / 2) * (((C / 8) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L3[((((_i1 / 2) + 1) * (((C / 8) + 3) + 1)) + _i2)]));
          }
        }
      }
      #pragma ivdep
      for (int  _i2 = 192; (_i2 <= 195); _i2 = (_i2 + 1))
      {
        if (((((_i1 % 2) == 0) && (_i2 <= 193)) && (_i1 >= 2)))
        {
          Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L3[(((_i1 / 2) * (((C / 8) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L3[((((_i1 / 2) + 1) * (((C / 8) + 3) + 1)) + _i2)]));
        }
        else
        {
          if ((((((_i1 + 1) % 2) == 0) && (_i2 <= 193)) && (_i1 >= 3)))
          {
            Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L3[((((_i1 / 2) + 2) * (((C / 8) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L3[((((_i1 / 2) + 1) * (((C / 8) + 3) + 1)) + _i2)]));
          }
        }
        Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 643); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
    {
      int  _ct189 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct190 = 0;
      int  _ct191 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct189: _ct190);
      int  _ct192 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct193 = 0;
      int  _ct194 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct192: _ct193);
      int  _ct195 = _ct194;
      int  _ct196 = 6;
      int  _ct197 = ((_ct191 < 6)? _ct195: _ct196);
      int  _ct198 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct199 = 0;
      int  _ct200 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct198: _ct199);
      int  _ct201 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct202 = 0;
      int  _ct203 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct201: _ct202);
      int  _ct204 = _ct203;
      int  _ct205 = 6;
      int  _ct206 = ((_ct200 < 6)? _ct204: _ct205);
      int  _ct207 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct208 = 0;
      int  _ct209 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct207: _ct208);
      int  _ct210 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct211 = 0;
      int  _ct212 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct210: _ct211);
      int  _ct213 = _ct212;
      int  _ct214 = 6;
      int  _ct215 = ((_ct209 < 6)? _ct213: _ct214);
      int  _ct216 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct217 = 0;
      int  _ct218 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct216: _ct217);
      int  _ct219 = (int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct220 = 0;
      int  _ct221 = (((int ) ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct219: _ct220);
      int  _ct222 = _ct221;
      int  _ct223 = 6;
      int  _ct224 = ((_ct218 < 6)? _ct222: _ct223);
      outLPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = (((1.0f - ((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)) - _ct197)) * U_lPyramid_L2[(((_ct206 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)]) + (((D_inGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] * (float ) (7)) - _ct215) * U_lPyramid_L2[((((_ct224 + 1) * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)]));
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 1283); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 1280))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
        {
          if ((((_i1 == 1280) && (_i2 <= 385)) && (_i2 >= 2)))
          {
            Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (1280 * (((C / 4) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + ((1280 / 2) * (((C / 4) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (((1280 / 2) + 1) * (((C / 4) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((_i1 == 1281) && (_i2 <= 385)) && (_i2 >= 2)))
            {
              Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (1281 * (((C / 4) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (((1281 / 2) + 2) * (((C / 4) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (((1281 / 2) + 1) * (((C / 4) + 3) + 1))) + _i2)]));
            }
            else
            {
              if ((_i2 <= 1))
              {
                Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
          Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 384))
          {
            Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 383); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          if ((((_i1 + 1) % 2) == 0))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 383); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 4) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 4) + 3) + 1))) + _i2)]));
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 383); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + ((_i1 / 2) * (((C / 4) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 4) + 3) + 1))) + _i2)]));
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 384; (_i2 <= 387); _i2 = (_i2 + 1))
        {
          if (((((_i1 % 2) == 0) && (_i2 <= 385)) && (_i1 >= 2)))
          {
            Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + ((_i1 / 2) * (((C / 4) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 4) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((((_i1 + 1) % 2) == 0) && (_i2 <= 385)) && (_i1 >= 3)))
            {
              Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 4) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L2[(((_i0 * ((((R / 4) + 3) + 1) * (((C / 4) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 4) + 3) + 1))) + _i2)]));
            }
          }
          Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 643); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 640))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
      {
        outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
        if ((_i2 <= 1))
        {
          outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
        }
        else
        {
          if ((_i2 >= 384))
          {
            outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
          if (((((_i2 % 2) == 0) && (_i1 <= 641)) && (_i2 <= 384)))
          {
            outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = (outLPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if ((((((_i2 + 1) % 2) == 0) && (_i1 <= 641)) && (_i2 <= 385)))
            {
              outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = (outLPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + ((_i2 / 2) + 1))])));
            }
          }
        }
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
        {
          outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          if ((_i2 >= 384))
          {
            outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
          else
          {
            if ((_i2 <= 1))
            {
              outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
        }
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 383); _i2 = (_i2 + 1))
        {
          if (((_i2 % 2) == 0))
          {
            outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = (outLPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = (outLPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
        }
        #pragma ivdep
        for (int  _i2 = 384; (_i2 <= 387); _i2 = (_i2 + 1))
        {
          outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          if ((_i2 == 384))
          {
            outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + 384)] = (outLPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + 384)] + ((0.25f * Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + (384 / 2))]) + (0.75f * Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + ((384 / 2) + 1))])));
          }
          else
          {
            if ((_i2 == 385))
            {
              outGPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + 385)] = (outLPyramid_L2[((_i1 * (((C / 4) + 3) + 1)) + 385)] + ((0.25f * Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + ((385 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L2[((_i1 * (((C / 8) + 3) + 1)) + ((385 / 2) + 1))])));
            }
          }
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 1283); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 1280))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
        {
          if ((_i2 <= 1))
          {
            U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
          U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 768))
          {
            U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
          if ((((((_i2 % 2) == 0) && (_i2 <= 768)) && (_i1 <= 1281)) && (_i2 >= 2)))
          {
            U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = (D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 769)) && (_i1 <= 1281)) && (_i2 >= 3)))
            {
              U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = (D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 767); _i2 = (_i2 + 1))
          {
            U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 767); _i2 = (_i2 + 1))
          {
            if (((_i2 % 2) == 0))
            {
              U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = (D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = (D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] - ((0.25f * Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 768; (_i2 <= 771); _i2 = (_i2 + 1))
        {
          U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
          else
          {
            if ((_i2 == 768))
            {
              U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + 768)] = (D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + 768)] - ((0.25f * Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + (768 / 2))]) + (0.75f * Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + ((768 / 2) + 1))])));
            }
            else
            {
              if ((_i2 == 769))
              {
                U_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + 769)] = (D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + 769)] - ((0.25f * Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + ((769 / 2) + 2))]) + (0.75f * Ux_lPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 4) + 3) + 1))) + (_i1 * (((C / 4) + 3) + 1))) + ((769 / 2) + 1))])));
              }
            }
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 1283); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 1280))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
      {
        if ((_i2 >= 384))
        {
          Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
        }
        else
        {
          if ((_i2 <= 1))
          {
            Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
        Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
        if ((((_i1 == 1280) && (_i2 <= 385)) && (_i2 >= 2)))
        {
          Ux_outGPyramid_L1[((1280 * (((C / 4) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L2[(((1280 / 2) * (((C / 4) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L2[((((1280 / 2) + 1) * (((C / 4) + 3) + 1)) + _i2)]));
        }
        else
        {
          if ((((_i1 == 1281) && (_i2 <= 385)) && (_i2 >= 2)))
          {
            Ux_outGPyramid_L1[((1281 * (((C / 4) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L2[((((1281 / 2) + 2) * (((C / 4) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L2[((((1281 / 2) + 1) * (((C / 4) + 3) + 1)) + _i2)]));
          }
        }
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 387); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 384))
          {
            Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
          Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
        }
        if ((((_i1 + 1) % 2) == 0))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 383); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L2[((((_i1 / 2) + 2) * (((C / 4) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L2[((((_i1 / 2) + 1) * (((C / 4) + 3) + 1)) + _i2)]));
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 383); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L2[(((_i1 / 2) * (((C / 4) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L2[((((_i1 / 2) + 1) * (((C / 4) + 3) + 1)) + _i2)]));
          }
        }
        #pragma ivdep
        for (int  _i2 = 384; (_i2 <= 387); _i2 = (_i2 + 1))
        {
          if ((((_i1 % 2) == 0) && (_i2 <= 385)))
          {
            Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L2[(((_i1 / 2) * (((C / 4) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L2[((((_i1 / 2) + 1) * (((C / 4) + 3) + 1)) + _i2)]));
          }
          else
          {
            if (((((_i1 - 1) % 2) == 0) && (_i2 <= 385)))
            {
              Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L2[((((_i1 / 2) + 2) * (((C / 4) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L2[((((_i1 / 2) + 1) * (((C / 4) + 3) + 1)) + _i2)]));
            }
          }
          Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 1283); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
    {
      int  _ct225 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct226 = 0;
      int  _ct227 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct225: _ct226);
      int  _ct228 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct229 = 0;
      int  _ct230 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct228: _ct229);
      int  _ct231 = _ct230;
      int  _ct232 = 6;
      int  _ct233 = ((_ct227 < 6)? _ct231: _ct232);
      int  _ct234 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct235 = 0;
      int  _ct236 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct234: _ct235);
      int  _ct237 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct238 = 0;
      int  _ct239 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct237: _ct238);
      int  _ct240 = _ct239;
      int  _ct241 = 6;
      int  _ct242 = ((_ct236 < 6)? _ct240: _ct241);
      int  _ct243 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct244 = 0;
      int  _ct245 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct243: _ct244);
      int  _ct246 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct247 = 0;
      int  _ct248 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct246: _ct247);
      int  _ct249 = _ct248;
      int  _ct250 = 6;
      int  _ct251 = ((_ct245 < 6)? _ct249: _ct250);
      int  _ct252 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct253 = 0;
      int  _ct254 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct252: _ct253);
      int  _ct255 = (int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)));
      int  _ct256 = 0;
      int  _ct257 = (((int ) ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7))) > 0)? _ct255: _ct256);
      int  _ct258 = _ct257;
      int  _ct259 = 6;
      int  _ct260 = ((_ct254 < 6)? _ct258: _ct259);
      outLPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = (((1.0f - ((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)) - _ct233)) * U_lPyramid_L1[(((_ct242 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)]) + (((D_inGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] * (float ) (7)) - _ct251) * U_lPyramid_L1[((((_ct260 + 1) * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)]));
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 2563); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 2560))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
        {
          if ((((_i1 == 2560) && (_i2 <= 769)) && (_i2 >= 2)))
          {
            Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (2560 * (((C / 2) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + ((2560 / 2) * (((C / 2) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (((2560 / 2) + 1) * (((C / 2) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((_i1 == 2561) && (_i2 <= 769)) && (_i2 >= 2)))
            {
              Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (2561 * (((C / 2) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (((2561 / 2) + 2) * (((C / 2) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (((2561 / 2) + 1) * (((C / 2) + 3) + 1))) + _i2)]));
            }
            else
            {
              if ((_i2 <= 1))
              {
                Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
              }
            }
          }
          Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          if ((_i2 >= 768))
          {
            Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 767); _i2 = (_i2 + 1))
          {
            Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
        }
        else
        {
          if ((((_i1 + 1) % 2) == 0))
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 767); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 2) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 2) + 3) + 1))) + _i2)]));
            }
          }
          else
          {
            #pragma ivdep
            for (int  _i2 = 2; (_i2 <= 767); _i2 = (_i2 + 1))
            {
              Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + ((_i1 / 2) * (((C / 2) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 2) + 3) + 1))) + _i2)]));
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 768; (_i2 <= 771); _i2 = (_i2 + 1))
        {
          if (((((_i1 % 2) == 0) && (_i2 <= 769)) && (_i1 >= 2)))
          {
            Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + ((_i1 / 2) * (((C / 2) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 2) + 3) + 1))) + _i2)]));
          }
          else
          {
            if ((((((_i1 + 1) % 2) == 0) && (_i2 <= 769)) && (_i1 >= 3)))
            {
              Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = ((0.25f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (((_i1 / 2) + 2) * (((C / 2) + 3) + 1))) + _i2)]) + (0.75f * D_gPyramid_L1[(((_i0 * ((((R / 2) + 3) + 1) * (((C / 2) + 3) + 1))) + (((_i1 / 2) + 1) * (((C / 2) + 3) + 1))) + _i2)]));
            }
          }
          Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + _i2)] = 0;
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 1283); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 1280))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
      {
        if ((((((_i2 % 2) == 0) && (_i2 <= 768)) && (_i1 <= 1281)) && (_i2 >= 2)))
        {
          outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = (outLPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + ((_i2 / 2) + 1))])));
        }
        else
        {
          if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 769)) && (_i1 <= 1281)) && (_i2 >= 3)))
          {
            outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = (outLPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if ((_i2 <= 1))
            {
              outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
            }
          }
        }
        outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        if ((_i2 >= 768))
        {
          outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
    else
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        }
      }
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 767); _i2 = (_i2 + 1))
        {
          outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 767); _i2 = (_i2 + 1))
        {
          if (((_i2 % 2) == 0))
          {
            outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = (outLPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = (outLPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] + ((0.25f * Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
        }
      }
      #pragma ivdep
      for (int  _i2 = 768; (_i2 <= 771); _i2 = (_i2 + 1))
      {
        if (((_i2 == 768) && (_i1 >= 2)))
        {
          outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + 768)] = (outLPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + 768)] + ((0.25f * Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + (768 / 2))]) + (0.75f * Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + ((768 / 2) + 1))])));
        }
        else
        {
          if (((_i2 == 769) && (_i1 >= 2)))
          {
            outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + 769)] = (outLPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + 769)] + ((0.25f * Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + ((769 / 2) + 2))]) + (0.75f * Ux_outGPyramid_L1[((_i1 * (((C / 4) + 3) + 1)) + ((769 / 2) + 1))])));
          }
        }
        outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          outGPyramid_L1[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        }
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 7); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 <= 2563); _i1 = (_i1 + 1))
    {
      if ((_i1 >= 2560))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1539); _i2 = (_i2 + 1))
        {
          if ((((((_i2 % 2) == 0) && (_i2 <= 1536)) && (_i1 <= 2561)) && (_i2 >= 2)))
          {
            U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = (gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] - ((0.25f * Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 1537)) && (_i1 <= 2561)) && (_i2 >= 3)))
            {
              U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = (gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] - ((0.25f * Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              if ((_i2 <= 1))
              {
                U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
              }
            }
          }
          U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
          if ((_i2 >= 1536))
          {
            U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
          }
        }
        if ((_i1 <= 1))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 1535); _i2 = (_i2 + 1))
          {
            U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 1535); _i2 = (_i2 + 1))
          {
            if (((_i2 % 2) == 0))
            {
              U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = (gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] - ((0.25f * Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + (_i2 / 2))]) + (0.75f * Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
            else
            {
              U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = (gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] - ((0.25f * Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + ((_i2 / 2) + 2))]) + (0.75f * Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + ((_i2 / 2) + 1))])));
            }
          }
        }
        #pragma ivdep
        for (int  _i2 = 1536; (_i2 <= 1539); _i2 = (_i2 + 1))
        {
          if (((_i2 == 1536) && (_i1 >= 2)))
          {
            U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + 1536)] = (gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + 1536)] - ((0.25f * Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + (1536 / 2))]) + (0.75f * Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + ((1536 / 2) + 1))])));
          }
          else
          {
            if (((_i2 == 1537) && (_i1 >= 2)))
            {
              U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + 1537)] = (gPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + 1537)] - ((0.25f * Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + ((1537 / 2) + 2))]) + (0.75f * Ux_lPyramid_L0[(((_i0 * ((4 + R) * (((C / 2) + 3) + 1))) + (_i1 * (((C / 2) + 3) + 1))) + ((1537 / 2) + 1))])));
            }
          }
          U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
          if ((_i1 <= 1))
          {
            U_lPyramid_L0[(((_i0 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)] = 0;
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 2563); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 2560))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
      {
        Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        if ((((_i1 == 2561) && (_i2 <= 769)) && (_i2 >= 2)))
        {
          Ux_result_ref_gray[((2561 * (((C / 2) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L1[((((2561 / 2) + 2) * (((C / 2) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L1[((((2561 / 2) + 1) * (((C / 2) + 3) + 1)) + _i2)]));
        }
        if ((_i2 >= 768))
        {
          Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        }
        else
        {
          if ((_i2 <= 1))
          {
            Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
        if ((((_i1 == 2560) && (_i2 <= 769)) && (_i2 >= 2)))
        {
          Ux_result_ref_gray[((2560 * (((C / 2) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L1[(((2560 / 2) * (((C / 2) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L1[((((2560 / 2) + 1) * (((C / 2) + 3) + 1)) + _i2)]));
        }
      }
    }
    else
    {
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 771); _i2 = (_i2 + 1))
        {
          if ((_i2 >= 768))
          {
            Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
          Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          if ((_i2 <= 1))
          {
            Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          }
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
        {
          Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
        }
        if (((_i1 % 2) == 0))
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 767); _i2 = (_i2 + 1))
          {
            Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L1[(((_i1 / 2) * (((C / 2) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L1[((((_i1 / 2) + 1) * (((C / 2) + 3) + 1)) + _i2)]));
          }
        }
        else
        {
          #pragma ivdep
          for (int  _i2 = 2; (_i2 <= 767); _i2 = (_i2 + 1))
          {
            Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L1[((((_i1 / 2) + 2) * (((C / 2) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L1[((((_i1 / 2) + 1) * (((C / 2) + 3) + 1)) + _i2)]));
          }
        }
        #pragma ivdep
        for (int  _i2 = 768; (_i2 <= 771); _i2 = (_i2 + 1))
        {
          if (((((_i1 - 1) % 2) == 0) && (_i2 <= 769)))
          {
            Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L1[((((_i1 / 2) + 2) * (((C / 2) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L1[((((_i1 / 2) + 1) * (((C / 2) + 3) + 1)) + _i2)]));
          }
          Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = 0;
          if ((((_i1 % 2) == 0) && (_i2 <= 769)))
          {
            Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + _i2)] = ((0.25f * outGPyramid_L1[(((_i1 / 2) * (((C / 2) + 3) + 1)) + _i2)]) + (0.75f * outGPyramid_L1[((((_i1 / 2) + 1) * (((C / 2) + 3) + 1)) + _i2)]));
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 2563); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 0; (_i2 <= 1539); _i2 = (_i2 + 1))
    {
      int  _ct261 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
      int  _ct262 = 0;
      int  _ct263 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct261: _ct262);
      int  _ct264 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
      int  _ct265 = 0;
      int  _ct266 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct264: _ct265);
      int  _ct267 = _ct266;
      int  _ct268 = 6;
      int  _ct269 = ((_ct263 < 6)? _ct267: _ct268);
      int  _ct270 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
      int  _ct271 = 0;
      int  _ct272 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct270: _ct271);
      int  _ct273 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
      int  _ct274 = 0;
      int  _ct275 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct273: _ct274);
      int  _ct276 = _ct275;
      int  _ct277 = 6;
      int  _ct278 = ((_ct272 < 6)? _ct276: _ct277);
      int  _ct279 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
      int  _ct280 = 0;
      int  _ct281 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct279: _ct280);
      int  _ct282 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
      int  _ct283 = 0;
      int  _ct284 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct282: _ct283);
      int  _ct285 = _ct284;
      int  _ct286 = 6;
      int  _ct287 = ((_ct281 < 6)? _ct285: _ct286);
      int  _ct288 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
      int  _ct289 = 0;
      int  _ct290 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct288: _ct289);
      int  _ct291 = (int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)));
      int  _ct292 = 0;
      int  _ct293 = (((int ) ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7))) > 0)? _ct291: _ct292);
      int  _ct294 = _ct293;
      int  _ct295 = 6;
      int  _ct296 = ((_ct290 < 6)? _ct294: _ct295);
      outLPyramid_L0[((_i1 * (4 + C)) + _i2)] = (((1.0f - ((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)) - _ct269)) * U_lPyramid_L0[(((_ct278 * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)]) + (((img[((_i1 * (4 + C)) + _i2)] * (float ) (7)) - _ct287) * U_lPyramid_L0[((((_ct296 + 1) * ((4 + R) * (4 + C))) + (_i1 * (4 + C))) + _i2)]));
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 <= 2563); _i1 = (_i1 + 1))
  {
    if ((_i1 >= 2560))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 1539); _i2 = (_i2 + 1))
      {
        if ((((((_i2 % 2) == 0) && (_i2 <= 1536)) && (_i1 <= 2561)) && (_i2 >= 2)))
        {
          result_ref_gray[((_i1 * (4 + C)) + _i2)] = (outLPyramid_L0[((_i1 * (4 + C)) + _i2)] + ((0.25f * Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + ((_i2 / 2) + 1))])));
        }
        else
        {
          if (((((((_i2 + 1) % 2) == 0) && (_i2 <= 1537)) && (_i1 <= 2561)) && (_i2 >= 3)))
          {
            result_ref_gray[((_i1 * (4 + C)) + _i2)] = (outLPyramid_L0[((_i1 * (4 + C)) + _i2)] + ((0.25f * Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            if ((_i2 <= 1))
            {
              result_ref_gray[((_i1 * (4 + C)) + _i2)] = 0;
            }
          }
        }
        result_ref_gray[((_i1 * (4 + C)) + _i2)] = 0;
        if ((_i2 >= 1536))
        {
          result_ref_gray[((_i1 * (4 + C)) + _i2)] = 0;
        }
      }
    }
    else
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 <= 1); _i2 = (_i2 + 1))
      {
        result_ref_gray[((_i1 * (4 + C)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          result_ref_gray[((_i1 * (4 + C)) + _i2)] = 0;
        }
      }
      if ((_i1 <= 1))
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 1535); _i2 = (_i2 + 1))
        {
          result_ref_gray[((_i1 * (4 + C)) + _i2)] = 0;
        }
      }
      else
      {
        #pragma ivdep
        for (int  _i2 = 2; (_i2 <= 1535); _i2 = (_i2 + 1))
        {
          if (((_i2 % 2) == 0))
          {
            result_ref_gray[((_i1 * (4 + C)) + _i2)] = (outLPyramid_L0[((_i1 * (4 + C)) + _i2)] + ((0.25f * Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + (_i2 / 2))]) + (0.75f * Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
          else
          {
            result_ref_gray[((_i1 * (4 + C)) + _i2)] = (outLPyramid_L0[((_i1 * (4 + C)) + _i2)] + ((0.25f * Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + ((_i2 / 2) + 2))]) + (0.75f * Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + ((_i2 / 2) + 1))])));
          }
        }
      }
      #pragma ivdep
      for (int  _i2 = 1536; (_i2 <= 1539); _i2 = (_i2 + 1))
      {
        if (((_i2 == 1536) && (_i1 >= 2)))
        {
          result_ref_gray[((_i1 * (4 + C)) + 1536)] = (outLPyramid_L0[((_i1 * (4 + C)) + 1536)] + ((0.25f * Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + (1536 / 2))]) + (0.75f * Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + ((1536 / 2) + 1))])));
        }
        else
        {
          if (((_i2 == 1537) && (_i1 >= 2)))
          {
            result_ref_gray[((_i1 * (4 + C)) + 1537)] = (outLPyramid_L0[((_i1 * (4 + C)) + 1537)] + ((0.25f * Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + ((1537 / 2) + 2))]) + (0.75f * Ux_result_ref_gray[((_i1 * (((C / 2) + 3) + 1)) + ((1537 / 2) + 1))])));
          }
        }
        result_ref_gray[((_i1 * (4 + C)) + _i2)] = 0;
        if ((_i1 <= 1))
        {
          result_ref_gray[((_i1 * (4 + C)) + _i2)] = 0;
        }
      }
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
        float  _ct297 = ((result_ref_gray[(((2 + _i1) * (4 + C)) + (2 + _i2))] * ((img_colour[(((_i0 * ((R + 4) * (C + 4))) + ((2 + _i1) * (C + 4))) + (2 + _i2))] / 65535.0f) + 0.01f)) / (img[(((2 + _i1) * (4 + C)) + (2 + _i2))] + 0.01f));
        float  _ct298 = 0.0f;
        float  _ct299 = ((((result_ref_gray[(((2 + _i1) * (4 + C)) + (2 + _i2))] * ((img_colour[(((_i0 * ((R + 4) * (C + 4))) + ((2 + _i1) * (C + 4))) + (2 + _i2))] / 65535.0f) + 0.01f)) / (img[(((2 + _i1) * (4 + C)) + (2 + _i2))] + 0.01f)) > 0.0f)? _ct297: _ct298);
        float  _ct300 = ((result_ref_gray[(((2 + _i1) * (4 + C)) + (2 + _i2))] * ((img_colour[(((_i0 * ((R + 4) * (C + 4))) + ((2 + _i1) * (C + 4))) + (2 + _i2))] / 65535.0f) + 0.01f)) / (img[(((2 + _i1) * (4 + C)) + (2 + _i2))] + 0.01f));
        float  _ct301 = 0.0f;
        float  _ct302 = ((((result_ref_gray[(((2 + _i1) * (4 + C)) + (2 + _i2))] * ((img_colour[(((_i0 * ((R + 4) * (C + 4))) + ((2 + _i1) * (C + 4))) + (2 + _i2))] / 65535.0f) + 0.01f)) / (img[(((2 + _i1) * (4 + C)) + (2 + _i2))] + 0.01f)) > 0.0f)? _ct300: _ct301);
        float  _ct303 = _ct302;
        float  _ct304 = 1.0f;
        float  _ct305 = ((_ct299 < 1.0f)? _ct303: _ct304);
        laplacian[(((_i0 * (R * C)) + (_i1 * C)) + _i2)] = (short unsigned int ) ((_ct305 * 65535.0f));
      }
    }
  }
  free(img);
  free(remapLUT);
  free(Dx_inGPyramid_L1);
  free(gPyramid_L0);
  free(D_inGPyramid_L1);
  free(Dx_gPyramid_L1);
  free(D_gPyramid_L1);
  free(Dx_inGPyramid_L2);
  free(D_inGPyramid_L2);
  free(Dx_gPyramid_L2);
  free(Ux_lPyramid_L0);
  free(D_gPyramid_L2);
  free(Dx_inGPyramid_L3);
  free(U_lPyramid_L0);
  free(D_inGPyramid_L3);
  free(Dx_gPyramid_L3);
  free(Ux_lPyramid_L1);
  free(outLPyramid_L0);
  free(D_gPyramid_L3);
  free(Dx_inGPyramid_L4);
  free(U_lPyramid_L1);
  free(D_inGPyramid_L4);
  free(Dx_gPyramid_L4);
  free(Ux_lPyramid_L2);
  free(outLPyramid_L1);
  free(D_gPyramid_L4);
  free(Dx_inGPyramid_L5);
  free(U_lPyramid_L2);
  free(D_inGPyramid_L5);
  free(Dx_gPyramid_L5);
  free(Ux_lPyramid_L3);
  free(outLPyramid_L2);
  free(D_gPyramid_L5);
  free(Dx_inGPyramid_L6);
  free(U_lPyramid_L3);
  free(D_inGPyramid_L6);
  free(Dx_gPyramid_L6);
  free(Ux_lPyramid_L4);
  free(outLPyramid_L3);
  free(D_gPyramid_L6);
  free(Dx_inGPyramid_L7);
  free(U_lPyramid_L4);
  free(D_inGPyramid_L7);
  free(Dx_gPyramid_L7);
  free(Ux_lPyramid_L5);
  free(outLPyramid_L4);
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
  free(outGPyramid_L4);
  free(Ux_outGPyramid_L3);
  free(outGPyramid_L3);
  free(Ux_outGPyramid_L2);
  free(outGPyramid_L2);
  free(Ux_outGPyramid_L1);
  free(outGPyramid_L1);
  free(Ux_result_ref_gray);
  free(result_ref_gray);
}
