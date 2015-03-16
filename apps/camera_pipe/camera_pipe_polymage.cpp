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
  int * matrix;
  matrix = (int *) (malloc((sizeof(int ) * (3 * 4))));
  for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 0; (_i1 <= 3); _i1 = (_i1 + 1))
    {
      matrix[((_i0 * 4) + _i1)] = (int ) ((((matrix_3200[((_i0 * 4) + _i1)] * (((1.0f / colour_temp) - 0.0003125f) / -0.000169642857143f)) + (matrix_7000[((_i0 * 4) + _i1)] * (1 - (((1.0f / colour_temp) - 0.0003125f) / -0.000169642857143f)))) * 256.0f));
    }
  }
  #pragma omp parallel for schedule(static)
  #pragma ivdep
  for (int  _i0 = -32768; (_i0 <= 32767); _i0 = (_i0 + 1))
  {
    float  _ct49020 = (1.0f - ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))))));
    float  _ct49021 = ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))));
    float  _ct49022 = ((powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)) > 0.5f)? _ct49020: _ct49021);
    float  _ct49023 = (1.0f - ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))))));
    float  _ct49024 = ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))));
    float  _ct49025 = ((powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)) > 0.5f)? _ct49023: _ct49024);
    float  _ct49026 = (_ct49025 * 256.0f);
    float  _ct49027 = 0.0f;
    float  _ct49028 = (((_ct49022 * 256.0f) > 0.0f)? _ct49026: _ct49027);
    float  _ct49029 = (1.0f - ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))))));
    float  _ct49030 = ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))));
    float  _ct49031 = ((powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)) > 0.5f)? _ct49029: _ct49030);
    float  _ct49032 = (1.0f - ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * (1.0f - powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))))));
    float  _ct49033 = ((((2.0f - (2.0f * (2.0f - powf(2.0f, (contrast / 100.0f))))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))) + ((2.0f - powf(2.0f, (contrast / 100.0f))) * powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma))));
    float  _ct49034 = ((powf(((0.0f > ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f))))? 0.0f: ((1.0f < (float ) ((_i0 / 1024.0f)))? 1.0f: (float ) ((_i0 / 1024.0f)))), (1.0f / gamma)) > 0.5f)? _ct49032: _ct49033);
    float  _ct49035 = (_ct49034 * 256.0f);
    float  _ct49036 = 0.0f;
    float  _ct49037 = (((_ct49031 * 256.0f) > 0.0f)? _ct49035: _ct49036);
    float  _ct49038 = _ct49037;
    float  _ct49039 = 255.0f;
    float  _ct49040 = ((_ct49028 < 255.0f)? _ct49038: _ct49039);
    curveLUT[(_i0 - -32768)] = (unsigned char ) (_ct49040);
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = -1; (_T_i1 <= 30); _T_i1 = (_T_i1 + 1))
  {
    short int  denoised[80][272];
    short int  deinterleaved[4][40][136];
    short int  r_r[40][136];
    short int  g_gr[40][136];
    short int  b_b[40][136];
    short int  g_gb[40][136];
    short int  g_b[40][136];
    short int  greenX2[40][272];
    short int  blueX2[40][272];
    short int  redX1[40][272];
    short int  g_r[40][136];
    short int  greenX1[40][272];
    short int  b_gb[40][136];
    short int  r_b[40][136];
    short int  r_gr[40][136];
    short int  b_r[40][136];
    short int  r_gb[40][136];
    short int  b_gr[40][136];
    short int  redX2[40][272];
    short int  green[80][272];
    short int  blueX1[40][272];
    short int  red[80][272];
    short int  blue[80][272];
    short int  corrected[3][80][272];
    for (int  _T_i2 = -1; (_T_i2 <= 9); _T_i2 = (_T_i2 + 1))
    {
      int  _ct49041 = ((1937 < ((64 * _T_i1) + 79))? 1937: ((64 * _T_i1) + 79));
      int  _ct49042 = ((8 > (64 * _T_i1))? 8: (64 * _T_i1));
      for (int  _i1 = _ct49042; (_i1 <= _ct49041); _i1 = (_i1 + 1))
      {
        int  _ct49043 = ((2549 < ((256 * _T_i2) + 271))? 2549: ((256 * _T_i2) + 271));
        int  _ct49044 = ((12 > (256 * _T_i2))? 12: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct49044; (_i2 <= _ct49043); _i2 = (_i2 + 1))
        {
          short int  _ct49045 = img[(((-2 + _i1) * C) + _i2)];
          short int  _ct49046 = img[(((2 + _i1) * C) + _i2)];
          short int  _ct49047 = ((img[(((-2 + _i1) * C) + _i2)] < img[(((2 + _i1) * C) + _i2)])? _ct49045: _ct49046);
          short int  _ct49048 = img[((_i1 * C) + (-2 + _i2))];
          short int  _ct49049 = img[((_i1 * C) + (2 + _i2))];
          short int  _ct49050 = ((img[((_i1 * C) + (-2 + _i2))] < img[((_i1 * C) + (2 + _i2))])? _ct49048: _ct49049);
          short int  _ct49051 = img[(((-2 + _i1) * C) + _i2)];
          short int  _ct49052 = img[(((2 + _i1) * C) + _i2)];
          short int  _ct49053 = ((img[(((-2 + _i1) * C) + _i2)] < img[(((2 + _i1) * C) + _i2)])? _ct49051: _ct49052);
          short int  _ct49054 = img[((_i1 * C) + (-2 + _i2))];
          short int  _ct49055 = img[((_i1 * C) + (2 + _i2))];
          short int  _ct49056 = ((img[((_i1 * C) + (-2 + _i2))] < img[((_i1 * C) + (2 + _i2))])? _ct49054: _ct49055);
          short int  _ct49057 = _ct49053;
          short int  _ct49058 = _ct49056;
          short int  _ct49059 = ((_ct49047 < _ct49050)? _ct49057: _ct49058);
          short int  _ct49060 = img[(((-2 + _i1) * C) + _i2)];
          short int  _ct49061 = img[(((2 + _i1) * C) + _i2)];
          short int  _ct49062 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct49060: _ct49061);
          short int  _ct49063 = img[((_i1 * C) + (-2 + _i2))];
          short int  _ct49064 = img[((_i1 * C) + (2 + _i2))];
          short int  _ct49065 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct49063: _ct49064);
          short int  _ct49066 = img[(((-2 + _i1) * C) + _i2)];
          short int  _ct49067 = img[(((2 + _i1) * C) + _i2)];
          short int  _ct49068 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct49066: _ct49067);
          short int  _ct49069 = img[((_i1 * C) + (-2 + _i2))];
          short int  _ct49070 = img[((_i1 * C) + (2 + _i2))];
          short int  _ct49071 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct49069: _ct49070);
          short int  _ct49072 = _ct49068;
          short int  _ct49073 = _ct49071;
          short int  _ct49074 = ((_ct49062 > _ct49065)? _ct49072: _ct49073);
          short int  _ct49075 = img[(((-2 + _i1) * C) + _i2)];
          short int  _ct49076 = img[(((2 + _i1) * C) + _i2)];
          short int  _ct49077 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct49075: _ct49076);
          short int  _ct49078 = img[((_i1 * C) + (-2 + _i2))];
          short int  _ct49079 = img[((_i1 * C) + (2 + _i2))];
          short int  _ct49080 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct49078: _ct49079);
          short int  _ct49081 = img[(((-2 + _i1) * C) + _i2)];
          short int  _ct49082 = img[(((2 + _i1) * C) + _i2)];
          short int  _ct49083 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct49081: _ct49082);
          short int  _ct49084 = img[((_i1 * C) + (-2 + _i2))];
          short int  _ct49085 = img[((_i1 * C) + (2 + _i2))];
          short int  _ct49086 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct49084: _ct49085);
          short int  _ct49087 = _ct49083;
          short int  _ct49088 = _ct49086;
          short int  _ct49089 = ((_ct49077 > _ct49080)? _ct49087: _ct49088);
          short int  _ct49090 = _ct49089;
          short int  _ct49091 = img[((_i1 * C) + _i2)];
          short int  _ct49092 = ((_ct49074 < img[((_i1 * C) + _i2)])? _ct49090: _ct49091);
          short int  _ct49093 = img[(((-2 + _i1) * C) + _i2)];
          short int  _ct49094 = img[(((2 + _i1) * C) + _i2)];
          short int  _ct49095 = ((img[(((-2 + _i1) * C) + _i2)] < img[(((2 + _i1) * C) + _i2)])? _ct49093: _ct49094);
          short int  _ct49096 = img[((_i1 * C) + (-2 + _i2))];
          short int  _ct49097 = img[((_i1 * C) + (2 + _i2))];
          short int  _ct49098 = ((img[((_i1 * C) + (-2 + _i2))] < img[((_i1 * C) + (2 + _i2))])? _ct49096: _ct49097);
          short int  _ct49099 = img[(((-2 + _i1) * C) + _i2)];
          short int  _ct49100 = img[(((2 + _i1) * C) + _i2)];
          short int  _ct49101 = ((img[(((-2 + _i1) * C) + _i2)] < img[(((2 + _i1) * C) + _i2)])? _ct49099: _ct49100);
          short int  _ct49102 = img[((_i1 * C) + (-2 + _i2))];
          short int  _ct49103 = img[((_i1 * C) + (2 + _i2))];
          short int  _ct49104 = ((img[((_i1 * C) + (-2 + _i2))] < img[((_i1 * C) + (2 + _i2))])? _ct49102: _ct49103);
          short int  _ct49105 = _ct49101;
          short int  _ct49106 = _ct49104;
          short int  _ct49107 = ((_ct49095 < _ct49098)? _ct49105: _ct49106);
          short int  _ct49108 = img[(((-2 + _i1) * C) + _i2)];
          short int  _ct49109 = img[(((2 + _i1) * C) + _i2)];
          short int  _ct49110 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct49108: _ct49109);
          short int  _ct49111 = img[((_i1 * C) + (-2 + _i2))];
          short int  _ct49112 = img[((_i1 * C) + (2 + _i2))];
          short int  _ct49113 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct49111: _ct49112);
          short int  _ct49114 = img[(((-2 + _i1) * C) + _i2)];
          short int  _ct49115 = img[(((2 + _i1) * C) + _i2)];
          short int  _ct49116 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct49114: _ct49115);
          short int  _ct49117 = img[((_i1 * C) + (-2 + _i2))];
          short int  _ct49118 = img[((_i1 * C) + (2 + _i2))];
          short int  _ct49119 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct49117: _ct49118);
          short int  _ct49120 = _ct49116;
          short int  _ct49121 = _ct49119;
          short int  _ct49122 = ((_ct49110 > _ct49113)? _ct49120: _ct49121);
          short int  _ct49123 = img[(((-2 + _i1) * C) + _i2)];
          short int  _ct49124 = img[(((2 + _i1) * C) + _i2)];
          short int  _ct49125 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct49123: _ct49124);
          short int  _ct49126 = img[((_i1 * C) + (-2 + _i2))];
          short int  _ct49127 = img[((_i1 * C) + (2 + _i2))];
          short int  _ct49128 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct49126: _ct49127);
          short int  _ct49129 = img[(((-2 + _i1) * C) + _i2)];
          short int  _ct49130 = img[(((2 + _i1) * C) + _i2)];
          short int  _ct49131 = ((img[(((-2 + _i1) * C) + _i2)] > img[(((2 + _i1) * C) + _i2)])? _ct49129: _ct49130);
          short int  _ct49132 = img[((_i1 * C) + (-2 + _i2))];
          short int  _ct49133 = img[((_i1 * C) + (2 + _i2))];
          short int  _ct49134 = ((img[((_i1 * C) + (-2 + _i2))] > img[((_i1 * C) + (2 + _i2))])? _ct49132: _ct49133);
          short int  _ct49135 = _ct49131;
          short int  _ct49136 = _ct49134;
          short int  _ct49137 = ((_ct49125 > _ct49128)? _ct49135: _ct49136);
          short int  _ct49138 = _ct49137;
          short int  _ct49139 = img[((_i1 * C) + _i2)];
          short int  _ct49140 = ((_ct49122 < img[((_i1 * C) + _i2)])? _ct49138: _ct49139);
          short int  _ct49141 = _ct49107;
          short int  _ct49142 = _ct49140;
          short int  _ct49143 = ((_ct49059 > _ct49092)? _ct49141: _ct49142);
          denoised[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = _ct49143;
        }
      }
      int  _ct49144 = ((968 < ((32 * _T_i1) + 39))? 968: ((32 * _T_i1) + 39));
      int  _ct49145 = ((4 > ((32 * _T_i1) + 1))? 4: ((32 * _T_i1) + 1));
      for (int  _i1 = _ct49145; (_i1 <= _ct49144); _i1 = (_i1 + 1))
      {
        int  _ct49146 = ((1274 < ((128 * _T_i2) + 135))? 1274: ((128 * _T_i2) + 135));
        int  _ct49147 = ((6 > ((128 * _T_i2) + 1))? 6: ((128 * _T_i2) + 1));
        #pragma ivdep
        for (int  _i2 = _ct49147; (_i2 <= _ct49146); _i2 = (_i2 + 1))
        {
          deinterleaved[0][((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = denoised[(2 * ((-32 * _T_i1) + _i1))][(2 * ((-128 * _T_i2) + _i2))];
        }
      }
      int  _ct49148 = ((968 < ((32 * _T_i1) + 39))? 968: ((32 * _T_i1) + 39));
      int  _ct49149 = ((4 > ((32 * _T_i1) + 1))? 4: ((32 * _T_i1) + 1));
      for (int  _i1 = _ct49149; (_i1 <= _ct49148); _i1 = (_i1 + 1))
      {
        int  _ct49150 = ((1274 < ((128 * _T_i2) + 135))? 1274: ((128 * _T_i2) + 135));
        int  _ct49151 = ((6 > ((128 * _T_i2) + 1))? 6: ((128 * _T_i2) + 1));
        #pragma ivdep
        for (int  _i2 = _ct49151; (_i2 <= _ct49150); _i2 = (_i2 + 1))
        {
          deinterleaved[1][((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = denoised[(2 * ((-32 * _T_i1) + _i1))][(1 + (2 * ((-128 * _T_i2) + _i2)))];
        }
      }
      int  _ct49152 = ((968 < ((32 * _T_i1) + 39))? 968: ((32 * _T_i1) + 39));
      int  _ct49153 = ((4 > ((32 * _T_i1) + 1))? 4: ((32 * _T_i1) + 1));
      for (int  _i1 = _ct49153; (_i1 <= _ct49152); _i1 = (_i1 + 1))
      {
        int  _ct49154 = ((1274 < ((128 * _T_i2) + 135))? 1274: ((128 * _T_i2) + 135));
        int  _ct49155 = ((6 > ((128 * _T_i2) + 1))? 6: ((128 * _T_i2) + 1));
        #pragma ivdep
        for (int  _i2 = _ct49155; (_i2 <= _ct49154); _i2 = (_i2 + 1))
        {
          deinterleaved[2][((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = denoised[(1 + (2 * ((-32 * _T_i1) + _i1)))][(2 * ((-128 * _T_i2) + _i2))];
        }
      }
      int  _ct49156 = ((968 < ((32 * _T_i1) + 39))? 968: ((32 * _T_i1) + 39));
      int  _ct49157 = ((4 > ((32 * _T_i1) + 1))? 4: ((32 * _T_i1) + 1));
      for (int  _i1 = _ct49157; (_i1 <= _ct49156); _i1 = (_i1 + 1))
      {
        int  _ct49158 = ((1274 < ((128 * _T_i2) + 135))? 1274: ((128 * _T_i2) + 135));
        int  _ct49159 = ((6 > ((128 * _T_i2) + 1))? 6: ((128 * _T_i2) + 1));
        #pragma ivdep
        for (int  _i2 = _ct49159; (_i2 <= _ct49158); _i2 = (_i2 + 1))
        {
          deinterleaved[3][((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = denoised[(1 + (2 * ((-32 * _T_i1) + _i1)))][(1 + (2 * ((-128 * _T_i2) + _i2)))];
        }
      }
      int  _ct49160 = ((968 < ((32 * _T_i1) + 38))? 968: ((32 * _T_i1) + 38));
      int  _ct49161 = ((4 > ((32 * _T_i1) + 1))? 4: ((32 * _T_i1) + 1));
      for (int  _i1 = _ct49161; (_i1 <= _ct49160); _i1 = (_i1 + 1))
      {
        int  _ct49162 = ((1274 < ((128 * _T_i2) + 134))? 1274: ((128 * _T_i2) + 134));
        int  _ct49163 = ((6 > ((128 * _T_i2) + 1))? 6: ((128 * _T_i2) + 1));
        #pragma ivdep
        for (int  _i2 = _ct49163; (_i2 <= _ct49162); _i2 = (_i2 + 1))
        {
          r_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = deinterleaved[1][((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)];
        }
      }
      int  _ct49164 = ((968 < ((32 * _T_i1) + 38))? 968: ((32 * _T_i1) + 38));
      int  _ct49165 = ((4 > ((32 * _T_i1) + 1))? 4: ((32 * _T_i1) + 1));
      for (int  _i1 = _ct49165; (_i1 <= _ct49164); _i1 = (_i1 + 1))
      {
        int  _ct49166 = ((1274 < ((128 * _T_i2) + 134))? 1274: ((128 * _T_i2) + 134));
        int  _ct49167 = ((6 > ((128 * _T_i2) + 1))? 6: ((128 * _T_i2) + 1));
        #pragma ivdep
        for (int  _i2 = _ct49167; (_i2 <= _ct49166); _i2 = (_i2 + 1))
        {
          g_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = deinterleaved[0][((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)];
        }
      }
      int  _ct49168 = ((968 < ((32 * _T_i1) + 38))? 968: ((32 * _T_i1) + 38));
      int  _ct49169 = ((4 > ((32 * _T_i1) + 1))? 4: ((32 * _T_i1) + 1));
      for (int  _i1 = _ct49169; (_i1 <= _ct49168); _i1 = (_i1 + 1))
      {
        int  _ct49170 = ((1274 < ((128 * _T_i2) + 134))? 1274: ((128 * _T_i2) + 134));
        int  _ct49171 = ((6 > ((128 * _T_i2) + 1))? 6: ((128 * _T_i2) + 1));
        #pragma ivdep
        for (int  _i2 = _ct49171; (_i2 <= _ct49170); _i2 = (_i2 + 1))
        {
          b_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = deinterleaved[2][((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)];
        }
      }
      int  _ct49172 = ((968 < ((32 * _T_i1) + 38))? 968: ((32 * _T_i1) + 38));
      int  _ct49173 = ((4 > ((32 * _T_i1) + 1))? 4: ((32 * _T_i1) + 1));
      for (int  _i1 = _ct49173; (_i1 <= _ct49172); _i1 = (_i1 + 1))
      {
        int  _ct49174 = ((1274 < ((128 * _T_i2) + 134))? 1274: ((128 * _T_i2) + 134));
        int  _ct49175 = ((6 > ((128 * _T_i2) + 1))? 6: ((128 * _T_i2) + 1));
        #pragma ivdep
        for (int  _i2 = _ct49175; (_i2 <= _ct49174); _i2 = (_i2 + 1))
        {
          g_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = deinterleaved[3][((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)];
        }
      }
      int  _ct49176 = ((967 < ((32 * _T_i1) + 38))? 967: ((32 * _T_i1) + 38));
      int  _ct49177 = ((5 > ((32 * _T_i1) + 2))? 5: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49177; (_i1 <= _ct49176); _i1 = (_i1 + 1))
      {
        int  _ct49178 = ((1273 < ((128 * _T_i2) + 134))? 1273: ((128 * _T_i2) + 134));
        int  _ct49179 = ((7 > ((128 * _T_i2) + 2))? 7: ((128 * _T_i2) + 2));
        #pragma ivdep
        for (int  _i2 = _ct49179; (_i2 <= _ct49178); _i2 = (_i2 + 1))
        {
          short int  _ct49180 = (g_gb[((-32 * _T_i1) + _i1)][(-1 + ((-128 * _T_i2) + _i2))] - g_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)]);
          short int  _ct49181 = (g_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - g_gb[((-32 * _T_i1) + _i1)][(-1 + ((-128 * _T_i2) + _i2))]);
          short int  _ct49182 = ((g_gb[((-32 * _T_i1) + _i1)][(-1 + ((-128 * _T_i2) + _i2))] > g_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)])? _ct49180: _ct49181);
          short int  _ct49183 = (g_gr[(1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)] - g_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)]);
          short int  _ct49184 = (g_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - g_gr[(1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)]);
          short int  _ct49185 = ((g_gr[(1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)] > g_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)])? _ct49183: _ct49184);
          int  _ct49186 = ((g_gb[((-32 * _T_i1) + _i1)][(-1 + ((-128 * _T_i2) + _i2))] + g_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)]) / 2);
          int  _ct49187 = ((g_gr[(1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)] + g_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)]) / 2);
          int  _ct49188 = ((_ct49182 < _ct49185)? _ct49186: _ct49187);
          g_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = _ct49188;
        }
      }
      int  _ct49189 = ((966 < ((32 * _T_i1) + 38))? 966: ((32 * _T_i1) + 38));
      int  _ct49190 = ((6 > ((32 * _T_i1) + 2))? 6: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49190; (_i1 <= _ct49189); _i1 = (_i1 + 1))
      {
        int  _ct49191 = ((2543 < ((256 * _T_i2) + 267))? 2543: ((256 * _T_i2) + 267));
        int  _ct49192 = ((17 > ((256 * _T_i2) + 3))? 17: ((256 * _T_i2) + 3));
        #pragma ivdep
        for (int  _i2 = _ct49192; (_i2 <= _ct49191); _i2 = (_i2 + 2))
        {
          greenX2[((-32 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = g_gb[((-32 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)];
        }
      }
      int  _ct49193 = ((966 < ((32 * _T_i1) + 38))? 966: ((32 * _T_i1) + 38));
      int  _ct49194 = ((6 > ((32 * _T_i1) + 2))? 6: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49194; (_i1 <= _ct49193); _i1 = (_i1 + 1))
      {
        int  _ct49195 = ((2542 < ((256 * _T_i2) + 268))? 2542: ((256 * _T_i2) + 268));
        int  _ct49196 = ((16 > ((256 * _T_i2) + 4))? 16: ((256 * _T_i2) + 4));
        #pragma ivdep
        for (int  _i2 = _ct49196; (_i2 <= _ct49195); _i2 = (_i2 + 2))
        {
          blueX2[((-32 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = b_b[((-32 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)];
        }
      }
      int  _ct49197 = ((966 < ((32 * _T_i1) + 38))? 966: ((32 * _T_i1) + 38));
      int  _ct49198 = ((6 > ((32 * _T_i1) + 2))? 6: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49198; (_i1 <= _ct49197); _i1 = (_i1 + 1))
      {
        int  _ct49199 = ((2543 < ((256 * _T_i2) + 267))? 2543: ((256 * _T_i2) + 267));
        int  _ct49200 = ((17 > ((256 * _T_i2) + 3))? 17: ((256 * _T_i2) + 3));
        #pragma ivdep
        for (int  _i2 = _ct49200; (_i2 <= _ct49199); _i2 = (_i2 + 2))
        {
          redX1[((-32 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = r_r[((-32 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)];
        }
      }
      int  _ct49201 = ((967 < ((32 * _T_i1) + 38))? 967: ((32 * _T_i1) + 38));
      int  _ct49202 = ((5 > ((32 * _T_i1) + 2))? 5: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49202; (_i1 <= _ct49201); _i1 = (_i1 + 1))
      {
        int  _ct49203 = ((1273 < ((128 * _T_i2) + 134))? 1273: ((128 * _T_i2) + 134));
        int  _ct49204 = ((7 > ((128 * _T_i2) + 2))? 7: ((128 * _T_i2) + 2));
        #pragma ivdep
        for (int  _i2 = _ct49204; (_i2 <= _ct49203); _i2 = (_i2 + 1))
        {
          short int  _ct49205 = (g_gr[((-32 * _T_i1) + _i1)][(1 + ((-128 * _T_i2) + _i2))] - g_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)]);
          short int  _ct49206 = (g_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - g_gr[((-32 * _T_i1) + _i1)][(1 + ((-128 * _T_i2) + _i2))]);
          short int  _ct49207 = ((g_gr[((-32 * _T_i1) + _i1)][(1 + ((-128 * _T_i2) + _i2))] > g_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)])? _ct49205: _ct49206);
          short int  _ct49208 = (g_gb[(-1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)] - g_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)]);
          short int  _ct49209 = (g_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - g_gb[(-1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)]);
          short int  _ct49210 = ((g_gb[(-1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)] > g_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)])? _ct49208: _ct49209);
          int  _ct49211 = ((g_gr[((-32 * _T_i1) + _i1)][(1 + ((-128 * _T_i2) + _i2))] + g_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)]) / 2);
          int  _ct49212 = ((g_gb[(-1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)] + g_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)]) / 2);
          int  _ct49213 = ((_ct49207 < _ct49210)? _ct49211: _ct49212);
          g_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = _ct49213;
        }
      }
      int  _ct49214 = ((966 < ((32 * _T_i1) + 38))? 966: ((32 * _T_i1) + 38));
      int  _ct49215 = ((6 > ((32 * _T_i1) + 2))? 6: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49215; (_i1 <= _ct49214); _i1 = (_i1 + 1))
      {
        int  _ct49216 = ((2542 < ((256 * _T_i2) + 268))? 2542: ((256 * _T_i2) + 268));
        int  _ct49217 = ((16 > ((256 * _T_i2) + 4))? 16: ((256 * _T_i2) + 4));
        #pragma ivdep
        for (int  _i2 = _ct49217; (_i2 <= _ct49216); _i2 = (_i2 + 2))
        {
          greenX1[((-32 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = g_gr[((-32 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)];
        }
      }
      int  _ct49218 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49219 = ((6 > ((32 * _T_i1) + 2))? 6: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49219; (_i1 <= _ct49218); _i1 = (_i1 + 1))
      {
        int  _ct49220 = ((2542 < ((256 * _T_i2) + 266))? 2542: ((256 * _T_i2) + 266));
        int  _ct49221 = ((16 > ((256 * _T_i2) + 4))? 16: ((256 * _T_i2) + 4));
        #pragma ivdep
        for (int  _i2 = _ct49221; (_i2 <= _ct49220); _i2 = (_i2 + 2))
        {
          greenX2[((-32 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = g_b[((-32 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)];
        }
      }
      int  _ct49222 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49223 = ((6 > ((32 * _T_i1) + 2))? 6: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49223; (_i1 <= _ct49222); _i1 = (_i1 + 1))
      {
        int  _ct49224 = ((1272 < ((128 * _T_i2) + 133))? 1272: ((128 * _T_i2) + 133));
        int  _ct49225 = ((8 > ((128 * _T_i2) + 2))? 8: ((128 * _T_i2) + 2));
        #pragma ivdep
        for (int  _i2 = _ct49225; (_i2 <= _ct49224); _i2 = (_i2 + 1))
        {
          b_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = ((g_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - ((g_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] + g_b[((-32 * _T_i1) + _i1)][(1 + ((-128 * _T_i2) + _i2))]) / 2)) + ((b_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] + b_b[((-32 * _T_i1) + _i1)][(1 + ((-128 * _T_i2) + _i2))]) / 2));
        }
      }
      int  _ct49226 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49227 = ((6 > ((32 * _T_i1) + 2))? 6: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49227; (_i1 <= _ct49226); _i1 = (_i1 + 1))
      {
        int  _ct49228 = ((1272 < ((128 * _T_i2) + 133))? 1272: ((128 * _T_i2) + 133));
        int  _ct49229 = ((8 > ((128 * _T_i2) + 2))? 8: ((128 * _T_i2) + 2));
        #pragma ivdep
        for (int  _i2 = _ct49229; (_i2 <= _ct49228); _i2 = (_i2 + 1))
        {
          short int  _ct49230 = (r_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - r_r[(1 + ((-32 * _T_i1) + _i1))][(-1 + ((-128 * _T_i2) + _i2))]);
          short int  _ct49231 = (r_r[(1 + ((-32 * _T_i1) + _i1))][(-1 + ((-128 * _T_i2) + _i2))] - r_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)]);
          short int  _ct49232 = ((r_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] > r_r[(1 + ((-32 * _T_i1) + _i1))][(-1 + ((-128 * _T_i2) + _i2))])? _ct49230: _ct49231);
          short int  _ct49233 = (r_r[((-32 * _T_i1) + _i1)][(-1 + ((-128 * _T_i2) + _i2))] - r_r[(1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)]);
          short int  _ct49234 = (r_r[(1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)] - r_r[((-32 * _T_i1) + _i1)][(-1 + ((-128 * _T_i2) + _i2))]);
          short int  _ct49235 = ((r_r[((-32 * _T_i1) + _i1)][(-1 + ((-128 * _T_i2) + _i2))] > r_r[(1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)])? _ct49233: _ct49234);
          int  _ct49236 = ((g_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - ((g_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] + g_r[(1 + ((-32 * _T_i1) + _i1))][(-1 + ((-128 * _T_i2) + _i2))]) / 2)) + ((r_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] + r_r[(1 + ((-32 * _T_i1) + _i1))][(-1 + ((-128 * _T_i2) + _i2))]) / 2));
          int  _ct49237 = ((g_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - ((g_r[((-32 * _T_i1) + _i1)][(-1 + ((-128 * _T_i2) + _i2))] + g_r[(1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)]) / 2)) + ((r_r[((-32 * _T_i1) + _i1)][(-1 + ((-128 * _T_i2) + _i2))] + r_r[(1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)]) / 2));
          int  _ct49238 = ((_ct49232 < _ct49235)? _ct49236: _ct49237);
          r_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = _ct49238;
        }
      }
      int  _ct49239 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49240 = ((6 > ((32 * _T_i1) + 2))? 6: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49240; (_i1 <= _ct49239); _i1 = (_i1 + 1))
      {
        int  _ct49241 = ((1272 < ((128 * _T_i2) + 133))? 1272: ((128 * _T_i2) + 133));
        int  _ct49242 = ((8 > ((128 * _T_i2) + 2))? 8: ((128 * _T_i2) + 2));
        #pragma ivdep
        for (int  _i2 = _ct49242; (_i2 <= _ct49241); _i2 = (_i2 + 1))
        {
          r_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = ((g_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - ((g_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] + g_r[((-32 * _T_i1) + _i1)][(-1 + ((-128 * _T_i2) + _i2))]) / 2)) + ((r_r[((-32 * _T_i1) + _i1)][(-1 + ((-128 * _T_i2) + _i2))] + r_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)]) / 2));
        }
      }
      int  _ct49243 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49244 = ((6 > ((32 * _T_i1) + 2))? 6: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49244; (_i1 <= _ct49243); _i1 = (_i1 + 1))
      {
        int  _ct49245 = ((1272 < ((128 * _T_i2) + 133))? 1272: ((128 * _T_i2) + 133));
        int  _ct49246 = ((8 > ((128 * _T_i2) + 2))? 8: ((128 * _T_i2) + 2));
        #pragma ivdep
        for (int  _i2 = _ct49246; (_i2 <= _ct49245); _i2 = (_i2 + 1))
        {
          short int  _ct49247 = (b_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - b_b[(-1 + ((-32 * _T_i1) + _i1))][(1 + ((-128 * _T_i2) + _i2))]);
          short int  _ct49248 = (b_b[(-1 + ((-32 * _T_i1) + _i1))][(1 + ((-128 * _T_i2) + _i2))] - b_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)]);
          short int  _ct49249 = ((b_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] > b_b[(-1 + ((-32 * _T_i1) + _i1))][(1 + ((-128 * _T_i2) + _i2))])? _ct49247: _ct49248);
          short int  _ct49250 = (b_b[((-32 * _T_i1) + _i1)][(1 + ((-128 * _T_i2) + _i2))] - b_b[(-1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)]);
          short int  _ct49251 = (b_b[(-1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)] - b_b[((-32 * _T_i1) + _i1)][(1 + ((-128 * _T_i2) + _i2))]);
          short int  _ct49252 = ((b_b[((-32 * _T_i1) + _i1)][(1 + ((-128 * _T_i2) + _i2))] > b_b[(-1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)])? _ct49250: _ct49251);
          int  _ct49253 = ((g_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - ((g_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] + g_b[(-1 + ((-32 * _T_i1) + _i1))][(1 + ((-128 * _T_i2) + _i2))]) / 2)) + ((b_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] + b_b[(-1 + ((-32 * _T_i1) + _i1))][(1 + ((-128 * _T_i2) + _i2))]) / 2));
          int  _ct49254 = ((g_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - ((g_b[((-32 * _T_i1) + _i1)][(1 + ((-128 * _T_i2) + _i2))] + g_b[(-1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)]) / 2)) + ((b_b[((-32 * _T_i1) + _i1)][(1 + ((-128 * _T_i2) + _i2))] + b_b[(-1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)]) / 2));
          int  _ct49255 = ((_ct49249 < _ct49252)? _ct49253: _ct49254);
          b_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = _ct49255;
        }
      }
      int  _ct49256 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49257 = ((6 > ((32 * _T_i1) + 2))? 6: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49257; (_i1 <= _ct49256); _i1 = (_i1 + 1))
      {
        int  _ct49258 = ((1272 < ((128 * _T_i2) + 133))? 1272: ((128 * _T_i2) + 133));
        int  _ct49259 = ((8 > ((128 * _T_i2) + 2))? 8: ((128 * _T_i2) + 2));
        #pragma ivdep
        for (int  _i2 = _ct49259; (_i2 <= _ct49258); _i2 = (_i2 + 1))
        {
          r_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = ((g_gb[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - ((g_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] + g_r[(1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)]) / 2)) + ((r_r[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] + r_r[(1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)]) / 2));
        }
      }
      int  _ct49260 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49261 = ((6 > ((32 * _T_i1) + 2))? 6: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49261; (_i1 <= _ct49260); _i1 = (_i1 + 1))
      {
        int  _ct49262 = ((2543 < ((256 * _T_i2) + 267))? 2543: ((256 * _T_i2) + 267));
        int  _ct49263 = ((17 > ((256 * _T_i2) + 5))? 17: ((256 * _T_i2) + 5));
        #pragma ivdep
        for (int  _i2 = _ct49263; (_i2 <= _ct49262); _i2 = (_i2 + 2))
        {
          greenX1[((-32 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = g_r[((-32 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)];
        }
      }
      int  _ct49264 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49265 = ((6 > ((32 * _T_i1) + 2))? 6: ((32 * _T_i1) + 2));
      for (int  _i1 = _ct49265; (_i1 <= _ct49264); _i1 = (_i1 + 1))
      {
        int  _ct49266 = ((1272 < ((128 * _T_i2) + 133))? 1272: ((128 * _T_i2) + 133));
        int  _ct49267 = ((8 > ((128 * _T_i2) + 2))? 8: ((128 * _T_i2) + 2));
        #pragma ivdep
        for (int  _i2 = _ct49267; (_i2 <= _ct49266); _i2 = (_i2 + 1))
        {
          b_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] = ((g_gr[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] - ((g_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] + g_b[(-1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)]) / 2)) + ((b_b[((-32 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)] + b_b[(-1 + ((-32 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)]) / 2));
        }
      }
      int  _ct49268 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49269 = ((6 > ((32 * _T_i1) + 3))? 6: ((32 * _T_i1) + 3));
      for (int  _i1 = _ct49269; (_i1 <= _ct49268); _i1 = (_i1 + 1))
      {
        int  _ct49270 = ((2543 < ((256 * _T_i2) + 265))? 2543: ((256 * _T_i2) + 265));
        int  _ct49271 = ((17 > ((256 * _T_i2) + 5))? 17: ((256 * _T_i2) + 5));
        #pragma ivdep
        for (int  _i2 = _ct49271; (_i2 <= _ct49270); _i2 = (_i2 + 2))
        {
          blueX2[((-32 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = b_gb[((-32 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)];
        }
      }
      int  _ct49272 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49273 = ((6 > ((32 * _T_i1) + 3))? 6: ((32 * _T_i1) + 3));
      for (int  _i1 = _ct49273; (_i1 <= _ct49272); _i1 = (_i1 + 1))
      {
        int  _ct49274 = ((2542 < ((256 * _T_i2) + 266))? 2542: ((256 * _T_i2) + 266));
        int  _ct49275 = ((16 > ((256 * _T_i2) + 6))? 16: ((256 * _T_i2) + 6));
        #pragma ivdep
        for (int  _i2 = _ct49275; (_i2 <= _ct49274); _i2 = (_i2 + 2))
        {
          redX2[((-32 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = r_b[((-32 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)];
        }
      }
      int  _ct49276 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49277 = ((6 > ((32 * _T_i1) + 3))? 6: ((32 * _T_i1) + 3));
      for (int  _i1 = _ct49277; (_i1 <= _ct49276); _i1 = (_i1 + 1))
      {
        int  _ct49278 = ((2543 < ((256 * _T_i2) + 265))? 2543: ((256 * _T_i2) + 265));
        int  _ct49279 = ((17 > ((256 * _T_i2) + 5))? 17: ((256 * _T_i2) + 5));
        #pragma ivdep
        for (int  _i2 = _ct49279; (_i2 <= _ct49278); _i2 = (_i2 + 2))
        {
          redX2[((-32 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = r_gb[((-32 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)];
        }
      }
      int  _ct49280 = ((1930 < ((64 * _T_i1) + 74))? 1930: ((64 * _T_i1) + 74));
      int  _ct49281 = ((12 > ((64 * _T_i1) + 6))? 12: ((64 * _T_i1) + 6));
      for (int  _i1 = _ct49281; (_i1 <= _ct49280); _i1 = (_i1 + 2))
      {
        int  _ct49282 = ((2543 < ((256 * _T_i2) + 266))? 2543: ((256 * _T_i2) + 266));
        int  _ct49283 = ((16 > ((256 * _T_i2) + 5))? 16: ((256 * _T_i2) + 5));
        #pragma ivdep
        for (int  _i2 = _ct49283; (_i2 <= _ct49282); _i2 = (_i2 + 1))
        {
          green[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = greenX1[(((-64 * _T_i1) + _i1) / 2)][((-256 * _T_i2) + _i2)];
        }
      }
      int  _ct49284 = ((1931 < ((64 * _T_i1) + 73))? 1931: ((64 * _T_i1) + 73));
      int  _ct49285 = ((13 > ((64 * _T_i1) + 5))? 13: ((64 * _T_i1) + 5));
      for (int  _i1 = _ct49285; (_i1 <= _ct49284); _i1 = (_i1 + 2))
      {
        int  _ct49286 = ((2543 < ((256 * _T_i2) + 266))? 2543: ((256 * _T_i2) + 266));
        int  _ct49287 = ((16 > ((256 * _T_i2) + 5))? 16: ((256 * _T_i2) + 5));
        #pragma ivdep
        for (int  _i2 = _ct49287; (_i2 <= _ct49286); _i2 = (_i2 + 1))
        {
          green[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = greenX2[(((-64 * _T_i1) + _i1) / 2)][((-256 * _T_i2) + _i2)];
        }
      }
      int  _ct49288 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49289 = ((6 > ((32 * _T_i1) + 3))? 6: ((32 * _T_i1) + 3));
      for (int  _i1 = _ct49289; (_i1 <= _ct49288); _i1 = (_i1 + 1))
      {
        int  _ct49290 = ((2542 < ((256 * _T_i2) + 266))? 2542: ((256 * _T_i2) + 266));
        int  _ct49291 = ((16 > ((256 * _T_i2) + 6))? 16: ((256 * _T_i2) + 6));
        #pragma ivdep
        for (int  _i2 = _ct49291; (_i2 <= _ct49290); _i2 = (_i2 + 2))
        {
          redX1[((-32 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = r_gr[((-32 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)];
        }
      }
      int  _ct49292 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49293 = ((6 > ((32 * _T_i1) + 3))? 6: ((32 * _T_i1) + 3));
      for (int  _i1 = _ct49293; (_i1 <= _ct49292); _i1 = (_i1 + 1))
      {
        int  _ct49294 = ((2542 < ((256 * _T_i2) + 266))? 2542: ((256 * _T_i2) + 266));
        int  _ct49295 = ((16 > ((256 * _T_i2) + 6))? 16: ((256 * _T_i2) + 6));
        #pragma ivdep
        for (int  _i2 = _ct49295; (_i2 <= _ct49294); _i2 = (_i2 + 2))
        {
          blueX1[((-32 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = b_gr[((-32 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)];
        }
      }
      int  _ct49296 = ((966 < ((32 * _T_i1) + 37))? 966: ((32 * _T_i1) + 37));
      int  _ct49297 = ((6 > ((32 * _T_i1) + 3))? 6: ((32 * _T_i1) + 3));
      for (int  _i1 = _ct49297; (_i1 <= _ct49296); _i1 = (_i1 + 1))
      {
        int  _ct49298 = ((2543 < ((256 * _T_i2) + 265))? 2543: ((256 * _T_i2) + 265));
        int  _ct49299 = ((17 > ((256 * _T_i2) + 5))? 17: ((256 * _T_i2) + 5));
        #pragma ivdep
        for (int  _i2 = _ct49299; (_i2 <= _ct49298); _i2 = (_i2 + 2))
        {
          blueX1[((-32 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = b_r[((-32 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)];
        }
      }
      int  _ct49300 = ((1930 < ((64 * _T_i1) + 72))? 1930: ((64 * _T_i1) + 72));
      int  _ct49301 = ((12 > ((64 * _T_i1) + 6))? 12: ((64 * _T_i1) + 6));
      for (int  _i1 = _ct49301; (_i1 <= _ct49300); _i1 = (_i1 + 2))
      {
        int  _ct49302 = ((2543 < ((256 * _T_i2) + 265))? 2543: ((256 * _T_i2) + 265));
        int  _ct49303 = ((16 > ((256 * _T_i2) + 6))? 16: ((256 * _T_i2) + 6));
        #pragma ivdep
        for (int  _i2 = _ct49303; (_i2 <= _ct49302); _i2 = (_i2 + 1))
        {
          red[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = redX1[(((-64 * _T_i1) + _i1) / 2)][((-256 * _T_i2) + _i2)];
        }
      }
      int  _ct49304 = ((1931 < ((64 * _T_i1) + 73))? 1931: ((64 * _T_i1) + 73));
      int  _ct49305 = ((13 > ((64 * _T_i1) + 7))? 13: ((64 * _T_i1) + 7));
      for (int  _i1 = _ct49305; (_i1 <= _ct49304); _i1 = (_i1 + 2))
      {
        int  _ct49306 = ((2543 < ((256 * _T_i2) + 265))? 2543: ((256 * _T_i2) + 265));
        int  _ct49307 = ((16 > ((256 * _T_i2) + 6))? 16: ((256 * _T_i2) + 6));
        #pragma ivdep
        for (int  _i2 = _ct49307; (_i2 <= _ct49306); _i2 = (_i2 + 1))
        {
          red[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = redX2[(((-64 * _T_i1) + _i1) / 2)][((-256 * _T_i2) + _i2)];
        }
      }
      int  _ct49308 = ((1930 < ((64 * _T_i1) + 72))? 1930: ((64 * _T_i1) + 72));
      int  _ct49309 = ((12 > ((64 * _T_i1) + 6))? 12: ((64 * _T_i1) + 6));
      for (int  _i1 = _ct49309; (_i1 <= _ct49308); _i1 = (_i1 + 2))
      {
        int  _ct49310 = ((2543 < ((256 * _T_i2) + 265))? 2543: ((256 * _T_i2) + 265));
        int  _ct49311 = ((16 > ((256 * _T_i2) + 6))? 16: ((256 * _T_i2) + 6));
        #pragma ivdep
        for (int  _i2 = _ct49311; (_i2 <= _ct49310); _i2 = (_i2 + 1))
        {
          blue[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = blueX1[(((-64 * _T_i1) + _i1) / 2)][((-256 * _T_i2) + _i2)];
        }
      }
      int  _ct49312 = ((1931 < ((64 * _T_i1) + 73))? 1931: ((64 * _T_i1) + 73));
      int  _ct49313 = ((13 > ((64 * _T_i1) + 7))? 13: ((64 * _T_i1) + 7));
      for (int  _i1 = _ct49313; (_i1 <= _ct49312); _i1 = (_i1 + 2))
      {
        int  _ct49314 = ((2543 < ((256 * _T_i2) + 265))? 2543: ((256 * _T_i2) + 265));
        int  _ct49315 = ((16 > ((256 * _T_i2) + 6))? 16: ((256 * _T_i2) + 6));
        #pragma ivdep
        for (int  _i2 = _ct49315; (_i2 <= _ct49314); _i2 = (_i2 + 1))
        {
          blue[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = blueX2[(((-64 * _T_i1) + _i1) / 2)][((-256 * _T_i2) + _i2)];
        }
      }
      int  _ct49316 = ((1931 < ((64 * _T_i1) + 72))? 1931: ((64 * _T_i1) + 72));
      int  _ct49317 = ((12 > ((64 * _T_i1) + 7))? 12: ((64 * _T_i1) + 7));
      for (int  _i1 = _ct49317; (_i1 <= _ct49316); _i1 = (_i1 + 1))
      {
        int  _ct49318 = ((2543 < ((256 * _T_i2) + 264))? 2543: ((256 * _T_i2) + 264));
        int  _ct49319 = ((16 > ((256 * _T_i2) + 7))? 16: ((256 * _T_i2) + 7));
        #pragma ivdep
        for (int  _i2 = _ct49319; (_i2 <= _ct49318); _i2 = (_i2 + 1))
        {
          corrected[2][((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = ((((matrix[((0 * 4) + 3)] + (matrix[(0 * 4)] * red[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)])) + (matrix[((0 * 4) + 1)] * green[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)])) + (matrix[((0 * 4) + 2)] * blue[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)])) / 256);
        }
      }
      int  _ct49320 = ((1931 < ((64 * _T_i1) + 72))? 1931: ((64 * _T_i1) + 72));
      int  _ct49321 = ((12 > ((64 * _T_i1) + 7))? 12: ((64 * _T_i1) + 7));
      for (int  _i1 = _ct49321; (_i1 <= _ct49320); _i1 = (_i1 + 1))
      {
        int  _ct49322 = ((2543 < ((256 * _T_i2) + 264))? 2543: ((256 * _T_i2) + 264));
        int  _ct49323 = ((16 > ((256 * _T_i2) + 7))? 16: ((256 * _T_i2) + 7));
        #pragma ivdep
        for (int  _i2 = _ct49323; (_i2 <= _ct49322); _i2 = (_i2 + 1))
        {
          corrected[1][((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = ((((matrix[((1 * 4) + 3)] + (matrix[(1 * 4)] * red[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)])) + (matrix[((1 * 4) + 1)] * green[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)])) + (matrix[((1 * 4) + 2)] * blue[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)])) / 256);
        }
      }
      int  _ct49324 = ((1931 < ((64 * _T_i1) + 72))? 1931: ((64 * _T_i1) + 72));
      int  _ct49325 = ((12 > ((64 * _T_i1) + 7))? 12: ((64 * _T_i1) + 7));
      for (int  _i1 = _ct49325; (_i1 <= _ct49324); _i1 = (_i1 + 1))
      {
        int  _ct49326 = ((2543 < ((256 * _T_i2) + 264))? 2543: ((256 * _T_i2) + 264));
        int  _ct49327 = ((16 > ((256 * _T_i2) + 7))? 16: ((256 * _T_i2) + 7));
        #pragma ivdep
        for (int  _i2 = _ct49327; (_i2 <= _ct49326); _i2 = (_i2 + 1))
        {
          corrected[0][((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = ((((matrix[((2 * 4) + 3)] + (matrix[(2 * 4)] * red[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)])) + (matrix[((2 * 4) + 1)] * green[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)])) + (matrix[((2 * 4) + 2)] * blue[((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)])) / 256);
        }
      }
      for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
      {
        int  _ct49328 = ((1931 < ((64 * _T_i1) + 71))? 1931: ((64 * _T_i1) + 71));
        int  _ct49329 = ((12 > ((64 * _T_i1) + 8))? 12: ((64 * _T_i1) + 8));
        for (int  _i1 = _ct49329; (_i1 <= _ct49328); _i1 = (_i1 + 1))
        {
          int  _ct49330 = ((2543 < ((256 * _T_i2) + 263))? 2543: ((256 * _T_i2) + 263));
          int  _ct49331 = ((16 > ((256 * _T_i2) + 8))? 16: ((256 * _T_i2) + 8));
          #pragma ivdep
          for (int  _i2 = _ct49331; (_i2 <= _ct49330); _i2 = (_i2 + 1))
          {
            process[(((_i0 * ((-48 + R) * (-64 + C))) + ((_i1 - 12) * (-64 + C))) + (_i2 - 16))] = curveLUT[(corrected[_i0][((-64 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] - -32768)];
          }
        }
      }
    }
  }
  free(curveLUT);
  free(matrix);
}
