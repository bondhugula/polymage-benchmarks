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
extern "C" void  pipeline_process(int  C, int  R, float  colour_temp, float  contrast, float  gamma, void * img_void_arg, void * matrix_3200_void_arg, void * matrix_7000_void_arg, void * process_void_arg)
{
  short int * img;
  img = (short int *) (img_void_arg);
  float * matrix_3200;
  matrix_3200 = (float *) (matrix_3200_void_arg);
  float * matrix_7000;
  matrix_7000 = (float *) (matrix_7000_void_arg);
  unsigned char * process;
  process = (unsigned char *) (process_void_arg);
  unsigned char * curveLUT;
  curveLUT = (unsigned char *) (malloc((sizeof(unsigned char ) * 65536)));
  short int * denoised;
  denoised = (short int *) (malloc((sizeof(short int ) * ((-38 + R) * (-54 + C)))));
  int * matrix;
  matrix = (int *) (malloc((sizeof(int ) * (3 * 4))));
  short int * deinterleaved;
  deinterleaved = (short int *) (malloc((sizeof(short int ) * ((4 * ((((((R - 24) - 12) / 2) + 2) - 4) + 1)) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)))));
  short int * b_b;
  b_b = (short int *) (malloc((sizeof(short int ) * (((((((R - 24) - 12) / 2) + 2) - 4) + 1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)))));
  short int * g_gb;
  g_gb = (short int *) (malloc((sizeof(short int ) * (((((((R - 24) - 12) / 2) + 2) - 4) + 1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)))));
  short int * g_gr;
  g_gr = (short int *) (malloc((sizeof(short int ) * (((((((R - 24) - 12) / 2) + 2) - 4) + 1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)))));
  short int * r_r;
  r_r = (short int *) (malloc((sizeof(short int ) * (((((((R - 24) - 12) / 2) + 2) - 4) + 1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)))));
  short int * g_b;
  g_b = (short int *) (malloc((sizeof(short int ) * (((((((R - 24) - 12) / 2) + 1) - 5) + 1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)))));
  short int * g_r;
  g_r = (short int *) (malloc((sizeof(short int ) * (((((((R - 24) - 12) / 2) + 1) - 5) + 1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)))));
  short int * b_gb;
  b_gb = (short int *) (malloc((sizeof(short int ) * ((((((R - 24) - 12) / 2) - 6) + 1) * (((((C - 32) - 16) / 2) - 8) + 1)))));
  short int * b_gr;
  b_gr = (short int *) (malloc((sizeof(short int ) * ((((((R - 24) - 12) / 2) - 6) + 1) * (((((C - 32) - 16) / 2) - 8) + 1)))));
  short int * b_r;
  b_r = (short int *) (malloc((sizeof(short int ) * ((((((R - 24) - 12) / 2) - 6) + 1) * (((((C - 32) - 16) / 2) - 8) + 1)))));
  short int * greenX1;
  greenX1 = (short int *) (malloc((sizeof(short int ) * ((((((R - 24) - 12) / 2) - 6) + 1) * (-64 + C)))));
  short int * greenX2;
  greenX2 = (short int *) (malloc((sizeof(short int ) * ((((((R - 24) - 12) / 2) - 6) + 1) * (-64 + C)))));
  short int * r_b;
  r_b = (short int *) (malloc((sizeof(short int ) * ((((((R - 24) - 12) / 2) - 6) + 1) * (((((C - 32) - 16) / 2) - 8) + 1)))));
  short int * r_gb;
  r_gb = (short int *) (malloc((sizeof(short int ) * ((((((R - 24) - 12) / 2) - 6) + 1) * (((((C - 32) - 16) / 2) - 8) + 1)))));
  short int * r_gr;
  r_gr = (short int *) (malloc((sizeof(short int ) * ((((((R - 24) - 12) / 2) - 6) + 1) * (((((C - 32) - 16) / 2) - 8) + 1)))));
  short int * blueX1;
  blueX1 = (short int *) (malloc((sizeof(short int ) * ((((((R - 24) - 12) / 2) - 6) + 1) * (-64 + C)))));
  short int * blueX2;
  blueX2 = (short int *) (malloc((sizeof(short int ) * ((((((R - 24) - 12) / 2) - 6) + 1) * (-64 + C)))));
  short int * green;
  green = (short int *) (malloc((sizeof(short int ) * ((-48 + R) * (-64 + C)))));
  short int * redX1;
  redX1 = (short int *) (malloc((sizeof(short int ) * ((((((R - 24) - 12) / 2) - 6) + 1) * (-64 + C)))));
  short int * redX2;
  redX2 = (short int *) (malloc((sizeof(short int ) * ((((((R - 24) - 12) / 2) - 6) + 1) * (-64 + C)))));
  short int * blue;
  blue = (short int *) (malloc((sizeof(short int ) * ((-48 + R) * (-64 + C)))));
  short int * red;
  red = (short int *) (malloc((sizeof(short int ) * ((-48 + R) * (-64 + C)))));
  short int * corrected;
  corrected = (short int *) (malloc((sizeof(short int ) * ((3 * (-48 + R)) * (-64 + C)))));
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 8; (_i1 <= 1937); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 12; (_i2 <= 2549); _i2 = (_i2 + 1))
    {
      short int  _ct0 = img[(((-2 + _i1) * C) + _i2)];
      short int  _ct1 = img[(((2 + _i1) * C) + _i2)];
      short int  _ct2 = ((img[(((-2 + _i1) * C) + _i2)] < img[(((2 + _i1) * C) + _i2)])? _ct0: _ct1);
      short int  _ct3 = img[((_i1 * C) + (-2 + _i2))];
      short int  _ct4 = img[((_i1 * C) + (2 + _i2))];
      short int  _ct5 = ((img[((_i1 * C) + (-2 + _i2))] < img[((_i1 * C) + (2 + _i2))])? _ct3: _ct4);
      short int  _ct6 = img[(((-2 + _i1) * C) + _i2)];
      short int  _ct7 = img[(((2 + _i1) * C) + _i2)];
      short int  _ct8 = ((img[(((-2 + _i1) * C) + _i2)] < img[(((2 + _i1) * C) + _i2)])? _ct6: _ct7);
      short int  _ct9 = img[((_i1 * C) + (-2 + _i2))];
      short int  _ct10 = img[((_i1 * C) + (2 + _i2))];
      short int  _ct11 = ((img[((_i1 * C) + (-2 + _i2))] < img[((_i1 * C) + (2 + _i2))])? _ct9: _ct10);
      short int  _ct12 = _ct8;
      short int  _ct13 = _ct11;
      short int  _ct14 = ((_ct2 < _ct5)? _ct12: _ct13);
      short int  _ct15 = img[(((-2 + _i1) * C) + _i2)];
      short int  _ct16 = img[(((2 + _i1) * C) + _i2)];
      short int  _ct17 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct15: _ct16);
      short int  _ct18 = img[((_i1 * C) + (-2 + _i2))];
      short int  _ct19 = img[((_i1 * C) + (2 + _i2))];
      short int  _ct20 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct18: _ct19);
      short int  _ct21 = img[(((-2 + _i1) * C) + _i2)];
      short int  _ct22 = img[(((2 + _i1) * C) + _i2)];
      short int  _ct23 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct21: _ct22);
      short int  _ct24 = img[((_i1 * C) + (-2 + _i2))];
      short int  _ct25 = img[((_i1 * C) + (2 + _i2))];
      short int  _ct26 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct24: _ct25);
      short int  _ct27 = _ct23;
      short int  _ct28 = _ct26;
      short int  _ct29 = ((_ct17 > _ct20)? _ct27: _ct28);
      short int  _ct30 = img[(((-2 + _i1) * C) + _i2)];
      short int  _ct31 = img[(((2 + _i1) * C) + _i2)];
      short int  _ct32 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct30: _ct31);
      short int  _ct33 = img[((_i1 * C) + (-2 + _i2))];
      short int  _ct34 = img[((_i1 * C) + (2 + _i2))];
      short int  _ct35 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct33: _ct34);
      short int  _ct36 = img[(((-2 + _i1) * C) + _i2)];
      short int  _ct37 = img[(((2 + _i1) * C) + _i2)];
      short int  _ct38 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct36: _ct37);
      short int  _ct39 = img[((_i1 * C) + (-2 + _i2))];
      short int  _ct40 = img[((_i1 * C) + (2 + _i2))];
      short int  _ct41 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct39: _ct40);
      short int  _ct42 = _ct38;
      short int  _ct43 = _ct41;
      short int  _ct44 = ((_ct32 > _ct35)? _ct42: _ct43);
      short int  _ct45 = _ct44;
      short int  _ct46 = img[((_i1 * C) + _i2)];
      short int  _ct47 = ((_ct29 < img[((_i1 * C) + _i2)])? _ct45: _ct46);
      short int  _ct48 = img[(((-2 + _i1) * C) + _i2)];
      short int  _ct49 = img[(((2 + _i1) * C) + _i2)];
      short int  _ct50 = ((img[(((-2 + _i1) * C) + _i2)] < img[(((2 + _i1) * C) + _i2)])? _ct48: _ct49);
      short int  _ct51 = img[((_i1 * C) + (-2 + _i2))];
      short int  _ct52 = img[((_i1 * C) + (2 + _i2))];
      short int  _ct53 = ((img[((_i1 * C) + (-2 + _i2))] < img[((_i1 * C) + (2 + _i2))])? _ct51: _ct52);
      short int  _ct54 = img[(((-2 + _i1) * C) + _i2)];
      short int  _ct55 = img[(((2 + _i1) * C) + _i2)];
      short int  _ct56 = ((img[(((-2 + _i1) * C) + _i2)] < img[(((2 + _i1) * C) + _i2)])? _ct54: _ct55);
      short int  _ct57 = img[((_i1 * C) + (-2 + _i2))];
      short int  _ct58 = img[((_i1 * C) + (2 + _i2))];
      short int  _ct59 = ((img[((_i1 * C) + (-2 + _i2))] < img[((_i1 * C) + (2 + _i2))])? _ct57: _ct58);
      short int  _ct60 = _ct56;
      short int  _ct61 = _ct59;
      short int  _ct62 = ((_ct50 < _ct53)? _ct60: _ct61);
      short int  _ct63 = img[(((-2 + _i1) * C) + _i2)];
      short int  _ct64 = img[(((2 + _i1) * C) + _i2)];
      short int  _ct65 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct63: _ct64);
      short int  _ct66 = img[((_i1 * C) + (-2 + _i2))];
      short int  _ct67 = img[((_i1 * C) + (2 + _i2))];
      short int  _ct68 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct66: _ct67);
      short int  _ct69 = img[(((-2 + _i1) * C) + _i2)];
      short int  _ct70 = img[(((2 + _i1) * C) + _i2)];
      short int  _ct71 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct69: _ct70);
      short int  _ct72 = img[((_i1 * C) + (-2 + _i2))];
      short int  _ct73 = img[((_i1 * C) + (2 + _i2))];
      short int  _ct74 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct72: _ct73);
      short int  _ct75 = _ct71;
      short int  _ct76 = _ct74;
      short int  _ct77 = ((_ct65 > _ct68)? _ct75: _ct76);
      short int  _ct78 = img[(((-2 + _i1) * C) + _i2)];
      short int  _ct79 = img[(((2 + _i1) * C) + _i2)];
      short int  _ct80 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct78: _ct79);
      short int  _ct81 = img[((_i1 * C) + (-2 + _i2))];
      short int  _ct82 = img[((_i1 * C) + (2 + _i2))];
      short int  _ct83 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct81: _ct82);
      short int  _ct84 = img[(((-2 + _i1) * C) + _i2)];
      short int  _ct85 = img[(((2 + _i1) * C) + _i2)];
      short int  _ct86 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct84: _ct85);
      short int  _ct87 = img[((_i1 * C) + (-2 + _i2))];
      short int  _ct88 = img[((_i1 * C) + (2 + _i2))];
      short int  _ct89 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct87: _ct88);
      short int  _ct90 = _ct86;
      short int  _ct91 = _ct89;
      short int  _ct92 = ((_ct80 > _ct83)? _ct90: _ct91);
      short int  _ct93 = _ct92;
      short int  _ct94 = img[((_i1 * C) + _i2)];
      short int  _ct95 = ((_ct77 < img[((_i1 * C) + _i2)])? _ct93: _ct94);
      short int  _ct96 = _ct62;
      short int  _ct97 = _ct95;
      short int  _ct98 = ((_ct14 > _ct47)? _ct96: _ct97);
      denoised[(((_i1 - 8) * (-54 + C)) + (_i2 - 12))] = _ct98;
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 4; (_i1 <= 968); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 6; (_i2 <= 1274); _i2 = (_i2 + 1))
    {
      deinterleaved[((0 + ((_i1 - 4) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + (_i2 - 6))] = denoised[(((-8 + (2 * _i1)) * (-54 + C)) + (-12 + (2 * _i2)))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 4; (_i1 <= 968); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 6; (_i2 <= 1274); _i2 = (_i2 + 1))
    {
      deinterleaved[(((((((((R - 24) - 12) / 2) + 2) - 4) + 1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + ((_i1 - 4) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + (_i2 - 6))] = denoised[(((-8 + (2 * _i1)) * (-54 + C)) + (-11 + (2 * _i2)))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 4; (_i1 <= 968); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 6; (_i2 <= 1274); _i2 = (_i2 + 1))
    {
      deinterleaved[(((2 * (((((((R - 24) - 12) / 2) + 2) - 4) + 1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + ((_i1 - 4) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + (_i2 - 6))] = denoised[(((-7 + (2 * _i1)) * (-54 + C)) + (-12 + (2 * _i2)))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 4; (_i1 <= 968); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 6; (_i2 <= 1274); _i2 = (_i2 + 1))
    {
      deinterleaved[(((3 * (((((((R - 24) - 12) / 2) + 2) - 4) + 1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + ((_i1 - 4) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + (_i2 - 6))] = denoised[(((-7 + (2 * _i1)) * (-54 + C)) + (-11 + (2 * _i2)))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 4; (_i1 <= 968); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 6; (_i2 <= 1274); _i2 = (_i2 + 1))
    {
      g_gr[(((_i1 - 4) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (_i2 - 6))] = deinterleaved[(((0 * (((((((R - 24) - 12) / 2) + 2) - 4) + 1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + ((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + (-6 + _i2))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 4; (_i1 <= 968); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 6; (_i2 <= 1274); _i2 = (_i2 + 1))
    {
      g_gb[(((_i1 - 4) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (_i2 - 6))] = deinterleaved[(((3 * (((((((R - 24) - 12) / 2) + 2) - 4) + 1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + ((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + (-6 + _i2))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 5; (_i1 <= 967); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 7; (_i2 <= 1273); _i2 = (_i2 + 1))
    {
      short int  _ct99 = (g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))] - g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]);
      short int  _ct100 = (g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))]);
      short int  _ct101 = ((g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))] > g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))])? _ct99: _ct100);
      short int  _ct102 = (g_gb[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]);
      short int  _ct103 = (g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - g_gb[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]);
      short int  _ct104 = ((g_gb[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] > g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))])? _ct102: _ct103);
      int  _ct105 = ((g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))] + g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]) / 2);
      int  _ct106 = ((g_gb[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] + g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]) / 2);
      int  _ct107 = ((_ct101 < _ct104)? _ct105: _ct106);
      g_r[(((_i1 - 5) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (_i2 - 7))] = _ct107;
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 5; (_i1 <= 967); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 7; (_i2 <= 1273); _i2 = (_i2 + 1))
    {
      short int  _ct108 = (g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))] - g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]);
      short int  _ct109 = (g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))]);
      short int  _ct110 = ((g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))] > g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))])? _ct108: _ct109);
      short int  _ct111 = (g_gr[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]);
      short int  _ct112 = (g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - g_gr[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]);
      short int  _ct113 = ((g_gr[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] > g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))])? _ct111: _ct112);
      int  _ct114 = ((g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))] + g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]) / 2);
      int  _ct115 = ((g_gr[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] + g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]) / 2);
      int  _ct116 = ((_ct110 < _ct113)? _ct114: _ct115);
      g_b[(((_i1 - 5) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (_i2 - 7))] = _ct116;
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 4; (_i1 <= 968); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 6; (_i2 <= 1274); _i2 = (_i2 + 1))
    {
      r_r[(((_i1 - 4) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (_i2 - 6))] = deinterleaved[(((1 * (((((((R - 24) - 12) / 2) + 2) - 4) + 1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + ((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + (-6 + _i2))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 4; (_i1 <= 968); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 6; (_i2 <= 1274); _i2 = (_i2 + 1))
    {
      b_b[(((_i1 - 4) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (_i2 - 6))] = deinterleaved[(((2 * (((((((R - 24) - 12) / 2) + 2) - 4) + 1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + ((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1))) + (-6 + _i2))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 6; (_i1 <= 966); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 8; (_i2 <= 1272); _i2 = (_i2 + 1))
    {
      r_gr[(((_i1 - 6) * (((((C - 32) - 16) / 2) - 8) + 1)) + (_i2 - 8))] = ((g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - ((g_r[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))] + g_r[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-8 + _i2))]) / 2)) + ((r_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))] + r_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]) / 2));
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 6; (_i1 <= 966); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 8; (_i2 <= 1272); _i2 = (_i2 + 1))
    {
      r_gb[(((_i1 - 6) * (((((C - 32) - 16) / 2) - 8) + 1)) + (_i2 - 8))] = ((g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - ((g_r[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))] + g_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))]) / 2)) + ((r_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] + r_r[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]) / 2));
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 6; (_i1 <= 966); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 8; (_i2 <= 1272); _i2 = (_i2 + 1))
    {
      short int  _ct117 = (r_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - r_r[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))]);
      short int  _ct118 = (r_r[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))] - r_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]);
      short int  _ct119 = ((r_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] > r_r[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))])? _ct117: _ct118);
      short int  _ct120 = (r_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))] - r_r[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]);
      short int  _ct121 = (r_r[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - r_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))]);
      short int  _ct122 = ((r_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))] > r_r[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))])? _ct120: _ct121);
      int  _ct123 = ((g_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))] - ((g_r[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))] + g_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-8 + _i2))]) / 2)) + ((r_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] + r_r[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))]) / 2));
      int  _ct124 = ((g_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))] - ((g_r[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-8 + _i2))] + g_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))]) / 2)) + ((r_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-7 + _i2))] + r_r[(((-3 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]) / 2));
      int  _ct125 = ((_ct119 < _ct122)? _ct123: _ct124);
      r_b[(((_i1 - 6) * (((((C - 32) - 16) / 2) - 8) + 1)) + (_i2 - 8))] = _ct125;
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 6; (_i1 <= 966); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 8; (_i2 <= 1272); _i2 = (_i2 + 1))
    {
      short int  _ct126 = (b_b[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - b_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))]);
      short int  _ct127 = (b_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))] - b_b[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]);
      short int  _ct128 = ((b_b[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] > b_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))])? _ct126: _ct127);
      short int  _ct129 = (b_b[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))] - b_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]);
      short int  _ct130 = (b_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - b_b[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))]);
      short int  _ct131 = ((b_b[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))] > b_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))])? _ct129: _ct130);
      int  _ct132 = ((g_r[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))] - ((g_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))] + g_b[(((-6 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-6 + _i2))]) / 2)) + ((b_b[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] + b_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))]) / 2));
      int  _ct133 = ((g_r[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))] - ((g_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-6 + _i2))] + g_b[(((-6 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))]) / 2)) + ((b_b[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))] + b_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]) / 2));
      int  _ct134 = ((_ct128 < _ct131)? _ct132: _ct133);
      b_r[(((_i1 - 6) * (((((C - 32) - 16) / 2) - 8) + 1)) + (_i2 - 8))] = _ct134;
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 6; (_i1 <= 966); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 8; (_i2 <= 1272); _i2 = (_i2 + 1))
    {
      b_gr[(((_i1 - 6) * (((((C - 32) - 16) / 2) - 8) + 1)) + (_i2 - 8))] = ((g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - ((g_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))] + g_b[(((-6 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))]) / 2)) + ((b_b[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] + b_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))]) / 2));
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 6; (_i1 <= 966); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 8; (_i2 <= 1272); _i2 = (_i2 + 1))
    {
      b_gb[(((_i1 - 6) * (((((C - 32) - 16) / 2) - 8) + 1)) + (_i2 - 8))] = ((g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] - ((g_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-7 + _i2))] + g_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (-6 + _i2))]) / 2)) + ((b_b[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-6 + _i2))] + b_b[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (-5 + _i2))]) / 2));
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 6; (_i1 <= 966); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2542); _i2 = (_i2 + 2))
    {
      redX2[(((_i1 - 6) * (-64 + C)) + (_i2 - 16))] = r_b[(((-6 + _i1) * (((((C - 32) - 16) / 2) - 8) + 1)) + ((_i2 / 2) - 8))];
      redX2[(((_i1 - 6) * (-64 + C)) + ((_i2 + 1) - 16))] = r_gb[(((-6 + _i1) * (((((C - 32) - 16) / 2) - 8) + 1)) + (((_i2 + 1) / 2) - 8))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 6; (_i1 <= 966); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2542); _i2 = (_i2 + 2))
    {
      redX1[(((_i1 - 6) * (-64 + C)) + (_i2 - 16))] = r_gr[(((-6 + _i1) * (((((C - 32) - 16) / 2) - 8) + 1)) + ((_i2 / 2) - 8))];
      redX1[(((_i1 - 6) * (-64 + C)) + ((_i2 + 1) - 16))] = r_r[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (((_i2 + 1) / 2) - 6))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 6; (_i1 <= 966); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2542); _i2 = (_i2 + 2))
    {
      blueX2[(((_i1 - 6) * (-64 + C)) + (_i2 - 16))] = b_b[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + ((_i2 / 2) - 6))];
      blueX2[(((_i1 - 6) * (-64 + C)) + ((_i2 + 1) - 16))] = b_gb[(((-6 + _i1) * (((((C - 32) - 16) / 2) - 8) + 1)) + (((_i2 + 1) / 2) - 8))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 6; (_i1 <= 966); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2542); _i2 = (_i2 + 2))
    {
      blueX1[(((_i1 - 6) * (-64 + C)) + (_i2 - 16))] = b_gr[(((-6 + _i1) * (((((C - 32) - 16) / 2) - 8) + 1)) + ((_i2 / 2) - 8))];
      blueX1[(((_i1 - 6) * (-64 + C)) + ((_i2 + 1) - 16))] = b_r[(((-6 + _i1) * (((((C - 32) - 16) / 2) - 8) + 1)) + (((_i2 + 1) / 2) - 8))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 6; (_i1 <= 966); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2542); _i2 = (_i2 + 2))
    {
      greenX2[(((_i1 - 6) * (-64 + C)) + (_i2 - 16))] = g_b[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + ((_i2 / 2) - 7))];
      greenX2[(((_i1 - 6) * (-64 + C)) + ((_i2 + 1) - 16))] = g_gb[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + (((_i2 + 1) / 2) - 6))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 6; (_i1 <= 966); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2542); _i2 = (_i2 + 2))
    {
      greenX1[(((_i1 - 6) * (-64 + C)) + (_i2 - 16))] = g_gr[(((-4 + _i1) * ((((((C - 32) - 16) / 2) + 2) - 6) + 1)) + ((_i2 / 2) - 6))];
      greenX1[(((_i1 - 6) * (-64 + C)) + ((_i2 + 1) - 16))] = g_r[(((-5 + _i1) * ((((((C - 32) - 16) / 2) + 1) - 7) + 1)) + (((_i2 + 1) / 2) - 7))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 12; (_i1 <= 1930); _i1 = (_i1 + 2))
  {
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2543); _i2 = (_i2 + 1))
    {
      red[(((_i1 - 12) * (-64 + C)) + (_i2 - 16))] = redX1[((((_i1 / 2) - 6) * (-64 + C)) + (-16 + _i2))];
    }
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2543); _i2 = (_i2 + 1))
    {
      red[((((_i1 + 1) - 12) * (-64 + C)) + (_i2 - 16))] = redX2[(((((_i1 + 1) / 2) - 6) * (-64 + C)) + (-16 + _i2))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 12; (_i1 <= 1930); _i1 = (_i1 + 2))
  {
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2543); _i2 = (_i2 + 1))
    {
      blue[(((_i1 - 12) * (-64 + C)) + (_i2 - 16))] = blueX1[((((_i1 / 2) - 6) * (-64 + C)) + (-16 + _i2))];
    }
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2543); _i2 = (_i2 + 1))
    {
      blue[((((_i1 + 1) - 12) * (-64 + C)) + (_i2 - 16))] = blueX2[(((((_i1 + 1) / 2) - 6) * (-64 + C)) + (-16 + _i2))];
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 12; (_i1 <= 1930); _i1 = (_i1 + 2))
  {
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2543); _i2 = (_i2 + 1))
    {
      green[(((_i1 - 12) * (-64 + C)) + (_i2 - 16))] = greenX1[((((_i1 / 2) - 6) * (-64 + C)) + (-16 + _i2))];
    }
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2543); _i2 = (_i2 + 1))
    {
      green[((((_i1 + 1) - 12) * (-64 + C)) + (_i2 - 16))] = greenX2[(((((_i1 + 1) / 2) - 6) * (-64 + C)) + (-16 + _i2))];
    }
  }
  for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 3); _i1 = (_i1 + 1))
    {
      matrix[((_i0 * 4) + _i1)] = (int ) ((((matrix_3200[((_i0 * 4) + _i1)] * (((1.0f / colour_temp) - 0.0003125f) / -0.000169642857143f)) + (matrix_7000[((_i0 * 4) + _i1)] * (1 - (((1.0f / colour_temp) - 0.0003125f) / -0.000169642857143f)))) * 256.0f));
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 12; (_i1 <= 1931); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2543); _i2 = (_i2 + 1))
    {
      corrected[((0 + ((_i1 - 12) * (-64 + C))) + (_i2 - 16))] = ((((matrix[((2 * 4) + 3)] + (matrix[(2 * 4)] * red[(((-12 + _i1) * (-64 + C)) + (-16 + _i2))])) + (matrix[((2 * 4) + 1)] * green[(((-12 + _i1) * (-64 + C)) + (-16 + _i2))])) + (matrix[((2 * 4) + 2)] * blue[(((-12 + _i1) * (-64 + C)) + (-16 + _i2))])) / 256);
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 12; (_i1 <= 1931); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2543); _i2 = (_i2 + 1))
    {
      corrected[((((-48 + R) * (-64 + C)) + ((_i1 - 12) * (-64 + C))) + (_i2 - 16))] = ((((matrix[((1 * 4) + 3)] + (matrix[(1 * 4)] * red[(((-12 + _i1) * (-64 + C)) + (-16 + _i2))])) + (matrix[((1 * 4) + 1)] * green[(((-12 + _i1) * (-64 + C)) + (-16 + _i2))])) + (matrix[((1 * 4) + 2)] * blue[(((-12 + _i1) * (-64 + C)) + (-16 + _i2))])) / 256);
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 12; (_i1 <= 1931); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 16; (_i2 <= 2543); _i2 = (_i2 + 1))
    {
      corrected[(((2 * ((-48 + R) * (-64 + C))) + ((_i1 - 12) * (-64 + C))) + (_i2 - 16))] = ((((matrix[((0 * 4) + 3)] + (matrix[(0 * 4)] * red[(((-12 + _i1) * (-64 + C)) + (-16 + _i2))])) + (matrix[((0 * 4) + 1)] * green[(((-12 + _i1) * (-64 + C)) + (-16 + _i2))])) + (matrix[((0 * 4) + 2)] * blue[(((-12 + _i1) * (-64 + C)) + (-16 + _i2))])) / 256);
    }
  }
  #pragma omp parallel for schedule(static)
  #pragma ivdep
  for (int  _i0 = -32768; (_i0 <= 32767); _i0 = (_i0 + 1))
  {
    float  _ct135 = (1.0f - ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))))));
    float  _ct136 = ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))));
    float  _ct137 = ((powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)) > 0.5f)? _ct135: _ct136);
    float  _ct138 = (1.0f - ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))))));
    float  _ct139 = ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))));
    float  _ct140 = ((powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)) > 0.5f)? _ct138: _ct139);
    float  _ct141 = (_ct140 * 256.0f);
    float  _ct142 = 0.0f;
    float  _ct143 = (((_ct137 * 256.0f) > 0.0f)? _ct141: _ct142);
    float  _ct144 = (1.0f - ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))))));
    float  _ct145 = ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))));
    float  _ct146 = ((powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)) > 0.5f)? _ct144: _ct145);
    float  _ct147 = (1.0f - ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))))));
    float  _ct148 = ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))));
    float  _ct149 = ((powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)) > 0.5f)? _ct147: _ct148);
    float  _ct150 = (_ct149 * 256.0f);
    float  _ct151 = 0.0f;
    float  _ct152 = (((_ct146 * 256.0f) > 0.0f)? _ct150: _ct151);
    float  _ct153 = _ct152;
    float  _ct154 = 255.0f;
    float  _ct155 = ((_ct143 < 255.0f)? _ct153: _ct154);
    curveLUT[(_i0 - -32768)] = (unsigned char ) (_ct155);
  }
  for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 12; (_i1 <= 1931); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 16; (_i2 <= 2543); _i2 = (_i2 + 1))
      {
        process[(((_i0 * ((-48 + R) * (-64 + C))) + ((_i1 - 12) * (-64 + C))) + (_i2 - 16))] = curveLUT[(corrected[(((_i0 * ((-48 + R) * (-64 + C))) + ((-12 + _i1) * (-64 + C))) + (-16 + _i2))] - -32768)];
      }
    }
  }
  free(curveLUT);
  free(denoised);
  free(matrix);
  free(deinterleaved);
  free(b_b);
  free(g_gb);
  free(g_gr);
  free(r_r);
  free(g_b);
  free(g_r);
  free(b_gb);
  free(b_gr);
  free(b_r);
  free(greenX1);
  free(greenX2);
  free(r_b);
  free(r_gb);
  free(r_gr);
  free(blueX1);
  free(blueX2);
  free(green);
  free(redX1);
  free(redX2);
  free(blue);
  free(red);
  free(corrected);
}
