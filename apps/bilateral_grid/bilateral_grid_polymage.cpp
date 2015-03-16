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
extern "C" void  pipeline_filtered(int  C, int  R, void * input_void_arg, void * filtered_void_arg)
{
  float * input;
  input = (float *) (input_void_arg);
  float * filtered;
  filtered = (float *) (filtered_void_arg);
  float * grid;
  grid = (float *) (malloc((sizeof(float ) * (((2 * (((((R - 1) / 8) - 1) - 1) + 1)) * (((((C - 1) / 8) - 1) - 1) + 1)) * 15))));
  float * blurx;
  blurx = (float *) (malloc((sizeof(float ) * (((2 * (((((R - 1) / 8) - 3) - 3) + 1)) * (((((C - 1) / 8) - 1) - 1) + 1)) * 11))));
  float * interpolated;
  interpolated = (float *) (malloc((sizeof(float ) * ((2 * (-56 + R)) * (-56 + C)))));
  #pragma omp parallel for
  for (int  _i0 = 0; (_i0 <= 1); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 1; (_i1 <= 325); _i1 = (_i1 + 1))
    {
      for (int  _i2 = 1; (_i2 <= 197); _i2 = (_i2 + 1))
      {
        #pragma ivdep
        for (int  _i3 = 0; (_i3 <= 14); _i3 = (_i3 + 1))
        {
          grid[((((_i0 * (((((((R - 1) / 8) - 1) - 1) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 15)) + ((_i1 - 1) * ((((((C - 1) / 8) - 1) - 1) + 1) * 15))) + ((_i2 - 1) * 15)) + _i3)] = 0;
        }
      }
    }
  }
  #pragma omp parallel for
  for (int  _i0 = 1; (_i0 <= 325); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 1; (_i1 <= 197); _i1 = (_i1 + 1))
    {
      for (int  _i2 = 0; (_i2 <= 8); _i2 = (_i2 + 1))
      {
        for (int  _i3 = 0; (_i3 <= 8); _i3 = (_i3 + 1))
        {
          grid[((((0 * (((((((R - 1) / 8) - 1) - 1) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 15)) + ((-1 + _i0) * ((((((C - 1) / 8) - 1) - 1) + 1) * 15))) + ((-1 + _i1) * 15)) + (2 + (int ) (((input[((((-4 + (8 * _i0)) + _i2) * C) + ((-4 + (8 * _i1)) + _i3))] * 10) + 0.5f))))] = (grid[((((0 * (((((((R - 1) / 8) - 1) - 1) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 15)) + ((-1 + _i0) * ((((((C - 1) / 8) - 1) - 1) + 1) * 15))) + ((-1 + _i1) * 15)) + (2 + (int ) (((input[((((-4 + (8 * _i0)) + _i2) * C) + ((-4 + (8 * _i1)) + _i3))] * 10) + 0.5f))))] + input[((((-4 + (8 * _i0)) + _i2) * C) + ((-4 + (8 * _i1)) + _i3))]);
          grid[((((1 * (((((((R - 1) / 8) - 1) - 1) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 15)) + ((-1 + _i0) * ((((((C - 1) / 8) - 1) - 1) + 1) * 15))) + ((-1 + _i1) * 15)) + (2 + (int ) (((input[((((-4 + (8 * _i0)) + _i2) * C) + ((-4 + (8 * _i1)) + _i3))] * 10) + 0.5f))))] = (grid[((((1 * (((((((R - 1) / 8) - 1) - 1) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 15)) + ((-1 + _i0) * ((((((C - 1) / 8) - 1) - 1) + 1) * 15))) + ((-1 + _i1) * 15)) + (2 + (int ) (((input[((((-4 + (8 * _i0)) + _i2) * C) + ((-4 + (8 * _i1)) + _i3))] * 10) + 0.5f))))] + 1);
        }
      }
    }
  }
  #pragma omp parallel for
  for (int  _T_i1 = -1; (_T_i1 <= 40); _T_i1 = (_T_i1 + 1))
  {
    float  blurz[2][12][128][11];
    for (int  _T_i2 = 0; (_T_i2 <= 1); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 1); _i0 = (_i0 + 1))
      {
        int  _ct1086 = ((325 < ((8 * _T_i1) + 11))? 325: ((8 * _T_i1) + 11));
        int  _ct1087 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
        for (int  _i1 = _ct1087; (_i1 <= _ct1086); _i1 = (_i1 + 1))
        {
          int  _ct1088 = ((197 < ((128 * _T_i2) + 127))? 197: ((128 * _T_i2) + 127));
          int  _ct1089 = ((1 > (128 * _T_i2))? 1: (128 * _T_i2));
          for (int  _i2 = _ct1089; (_i2 <= _ct1088); _i2 = (_i2 + 1))
          {
            #pragma ivdep
            for (int  _i3 = 2; (_i3 <= 12); _i3 = (_i3 + 1))
            {
              blurz[_i0][((-8 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)][(_i3 - 2)] = ((((grid[((((_i0 * (((((((R - 1) / 8) - 1) - 1) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 15)) + ((-1 + _i1) * ((((((C - 1) / 8) - 1) - 1) + 1) * 15))) + ((-1 + _i2) * 15)) + (-2 + _i3))] + (4 * grid[((((_i0 * (((((((R - 1) / 8) - 1) - 1) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 15)) + ((-1 + _i1) * ((((((C - 1) / 8) - 1) - 1) + 1) * 15))) + ((-1 + _i2) * 15)) + (-1 + _i3))])) + (6 * grid[((((_i0 * (((((((R - 1) / 8) - 1) - 1) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 15)) + ((-1 + _i1) * ((((((C - 1) / 8) - 1) - 1) + 1) * 15))) + ((-1 + _i2) * 15)) + _i3)])) + (4 * grid[((((_i0 * (((((((R - 1) / 8) - 1) - 1) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 15)) + ((-1 + _i1) * ((((((C - 1) / 8) - 1) - 1) + 1) * 15))) + ((-1 + _i2) * 15)) + (1 + _i3))])) + grid[((((_i0 * (((((((R - 1) / 8) - 1) - 1) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 15)) + ((-1 + _i1) * ((((((C - 1) / 8) - 1) - 1) + 1) * 15))) + ((-1 + _i2) * 15)) + (2 + _i3))]);
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 1); _i0 = (_i0 + 1))
      {
        int  _ct1090 = ((323 < ((8 * _T_i1) + 9))? 323: ((8 * _T_i1) + 9));
        int  _ct1091 = ((3 > ((8 * _T_i1) + 2))? 3: ((8 * _T_i1) + 2));
        for (int  _i1 = _ct1091; (_i1 <= _ct1090); _i1 = (_i1 + 1))
        {
          int  _ct1092 = ((197 < ((128 * _T_i2) + 127))? 197: ((128 * _T_i2) + 127));
          int  _ct1093 = ((1 > (128 * _T_i2))? 1: (128 * _T_i2));
          for (int  _i2 = _ct1093; (_i2 <= _ct1092); _i2 = (_i2 + 1))
          {
            #pragma ivdep
            for (int  _i3 = 2; (_i3 <= 12); _i3 = (_i3 + 1))
            {
              blurx[((((_i0 * (((((((R - 1) / 8) - 3) - 3) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 11)) + ((_i1 - 3) * ((((((C - 1) / 8) - 1) - 1) + 1) * 11))) + ((_i2 - 1) * 11)) + (_i3 - 2))] = ((((blurz[_i0][(-2 + ((-8 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)][(-2 + _i3)] + (4 * blurz[_i0][(-1 + ((-8 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)][(-2 + _i3)])) + (6 * blurz[_i0][((-8 * _T_i1) + _i1)][((-128 * _T_i2) + _i2)][(-2 + _i3)])) + (4 * blurz[_i0][(1 + ((-8 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)][(-2 + _i3)])) + blurz[_i0][(2 + ((-8 * _T_i1) + _i1))][((-128 * _T_i2) + _i2)][(-2 + _i3)]);
            }
          }
        }
      }
    }
  }
  #pragma omp parallel for
  for (int  _T_i1 = 2; (_T_i1 <= 323); _T_i1 = (_T_i1 + 1))
  {
    float  blury[2][2][17][11];
    for (int  _T_i2 = 0; (_T_i2 <= 12); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 1); _i0 = (_i0 + 1))
      {
        int  _ct1094 = ((323 < (_T_i1 + 1))? 323: (_T_i1 + 1));
        int  _ct1095 = ((3 > _T_i1)? 3: _T_i1);
        for (int  _i1 = _ct1095; (_i1 <= _ct1094); _i1 = (_i1 + 1))
        {
          int  _ct1096 = ((195 < ((16 * _T_i2) + 16))? 195: ((16 * _T_i2) + 16));
          int  _ct1097 = ((3 > (16 * _T_i2))? 3: (16 * _T_i2));
          for (int  _i2 = _ct1097; (_i2 <= _ct1096); _i2 = (_i2 + 1))
          {
            #pragma ivdep
            for (int  _i3 = 2; (_i3 <= 12); _i3 = (_i3 + 1))
            {
              blury[_i0][(-(_T_i1) + _i1)][((-16 * _T_i2) + _i2)][(_i3 - 2)] = ((((blurx[((((_i0 * (((((((R - 1) / 8) - 3) - 3) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 11)) + ((-3 + _i1) * ((((((C - 1) / 8) - 1) - 1) + 1) * 11))) + ((-3 + _i2) * 11)) + (-2 + _i3))] + (4 * blurx[((((_i0 * (((((((R - 1) / 8) - 3) - 3) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 11)) + ((-3 + _i1) * ((((((C - 1) / 8) - 1) - 1) + 1) * 11))) + ((-2 + _i2) * 11)) + (-2 + _i3))])) + (6 * blurx[((((_i0 * (((((((R - 1) / 8) - 3) - 3) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 11)) + ((-3 + _i1) * ((((((C - 1) / 8) - 1) - 1) + 1) * 11))) + ((-1 + _i2) * 11)) + (-2 + _i3))])) + (4 * blurx[((((_i0 * (((((((R - 1) / 8) - 3) - 3) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 11)) + ((-3 + _i1) * ((((((C - 1) / 8) - 1) - 1) + 1) * 11))) + (_i2 * 11)) + (-2 + _i3))])) + blurx[((((_i0 * (((((((R - 1) / 8) - 3) - 3) + 1) * (((((C - 1) / 8) - 1) - 1) + 1)) * 11)) + ((-3 + _i1) * ((((((C - 1) / 8) - 1) - 1) + 1) * 11))) + ((1 + _i2) * 11)) + (-2 + _i3))]);
            }
          }
        }
      }
      if (((_T_i1 <= 322) && (_T_i1 >= 3)))
      {
        for (int  _i0 = 0; (_i0 <= 1); _i0 = (_i0 + 1))
        {
          for (int  _i1 = (8 * _T_i1); (_i1 <= ((8 * _T_i1) + 7)); _i1 = (_i1 + 1))
          {
            int  _ct1098 = ((1559 < ((128 * _T_i2) + 127))? 1559: ((128 * _T_i2) + 127));
            int  _ct1099 = ((24 > (128 * _T_i2))? 24: (128 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct1099; (_i2 <= _ct1098); _i2 = (_i2 + 1))
            {
              interpolated[(((_i0 * ((-56 + R) * (-56 + C))) + ((_i1 - 24) * (-56 + C))) + (_i2 - 24))] = (((blury[_i0][(((-8 * _T_i1) + _i1) / 8)][(((-128 * _T_i2) + _i2) / 8)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)] + (((float ) ((_i1 % 8)) / 8) * (blury[_i0][((((-8 * _T_i1) + _i1) / 8) + 1)][(((-128 * _T_i2) + _i2) / 8)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)] - blury[_i0][(((-8 * _T_i1) + _i1) / 8)][(((-128 * _T_i2) + _i2) / 8)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)]))) + (((float ) ((_i2 % 8)) / 8) * ((blury[_i0][(((-8 * _T_i1) + _i1) / 8)][((((-128 * _T_i2) + _i2) / 8) + 1)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)] + (((float ) ((_i1 % 8)) / 8) * (blury[_i0][((((-8 * _T_i1) + _i1) / 8) + 1)][((((-128 * _T_i2) + _i2) / 8) + 1)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)] - blury[_i0][(((-8 * _T_i1) + _i1) / 8)][((((-128 * _T_i2) + _i2) / 8) + 1)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)]))) - (blury[_i0][(((-8 * _T_i1) + _i1) / 8)][(((-128 * _T_i2) + _i2) / 8)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)] + (((float ) ((_i1 % 8)) / 8) * (blury[_i0][((((-8 * _T_i1) + _i1) / 8) + 1)][(((-128 * _T_i2) + _i2) / 8)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)] - blury[_i0][(((-8 * _T_i1) + _i1) / 8)][(((-128 * _T_i2) + _i2) / 8)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)])))))) + (((input[((_i1 * C) + _i2)] * 10) - (int ) ((input[((_i1 * C) + _i2)] * 10))) * (((blury[_i0][(((-8 * _T_i1) + _i1) / 8)][(((-128 * _T_i2) + _i2) / 8)][(((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) + 1) - 2)] + (((float ) ((_i1 % 8)) / 8) * (blury[_i0][((((-8 * _T_i1) + _i1) / 8) + 1)][(((-128 * _T_i2) + _i2) / 8)][(((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) + 1) - 2)] - blury[_i0][(((-8 * _T_i1) + _i1) / 8)][(((-128 * _T_i2) + _i2) / 8)][(((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) + 1) - 2)]))) + (((float ) ((_i2 % 8)) / 8) * ((blury[_i0][(((-8 * _T_i1) + _i1) / 8)][((((-128 * _T_i2) + _i2) / 8) + 1)][(((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) + 1) - 2)] + (((float ) ((_i1 % 8)) / 8) * (blury[_i0][((((-8 * _T_i1) + _i1) / 8) + 1)][((((-128 * _T_i2) + _i2) / 8) + 1)][(((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) + 1) - 2)] - blury[_i0][(((-8 * _T_i1) + _i1) / 8)][((((-128 * _T_i2) + _i2) / 8) + 1)][(((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) + 1) - 2)]))) - (blury[_i0][(((-8 * _T_i1) + _i1) / 8)][(((-128 * _T_i2) + _i2) / 8)][(((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) + 1) - 2)] + (((float ) ((_i1 % 8)) / 8) * (blury[_i0][((((-8 * _T_i1) + _i1) / 8) + 1)][(((-128 * _T_i2) + _i2) / 8)][(((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) + 1) - 2)] - blury[_i0][(((-8 * _T_i1) + _i1) / 8)][(((-128 * _T_i2) + _i2) / 8)][(((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) + 1) - 2)])))))) - ((blury[_i0][(((-8 * _T_i1) + _i1) / 8)][(((-128 * _T_i2) + _i2) / 8)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)] + (((float ) ((_i1 % 8)) / 8) * (blury[_i0][((((-8 * _T_i1) + _i1) / 8) + 1)][(((-128 * _T_i2) + _i2) / 8)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)] - blury[_i0][(((-8 * _T_i1) + _i1) / 8)][(((-128 * _T_i2) + _i2) / 8)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)]))) + (((float ) ((_i2 % 8)) / 8) * ((blury[_i0][(((-8 * _T_i1) + _i1) / 8)][((((-128 * _T_i2) + _i2) / 8) + 1)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)] + (((float ) ((_i1 % 8)) / 8) * (blury[_i0][((((-8 * _T_i1) + _i1) / 8) + 1)][((((-128 * _T_i2) + _i2) / 8) + 1)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)] - blury[_i0][(((-8 * _T_i1) + _i1) / 8)][((((-128 * _T_i2) + _i2) / 8) + 1)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)]))) - (blury[_i0][(((-8 * _T_i1) + _i1) / 8)][(((-128 * _T_i2) + _i2) / 8)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)] + (((float ) ((_i1 % 8)) / 8) * (blury[_i0][((((-8 * _T_i1) + _i1) / 8) + 1)][(((-128 * _T_i2) + _i2) / 8)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)] - blury[_i0][(((-8 * _T_i1) + _i1) / 8)][(((-128 * _T_i2) + _i2) / 8)][((2 + (int ) ((input[((_i1 * C) + _i2)] * 10))) - 2)])))))))));
            }
          }
        }
      }
    }
  }
  #pragma omp parallel for
  for (int  _i1 = 24; (_i1 <= 2583); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 24; (_i2 <= 1559); _i2 = (_i2 + 1))
    {
      float  _ct1100 = (interpolated[(((0 * ((-56 + R) * (-56 + C))) + ((-24 + _i1) * (-56 + C))) + (-24 + _i2))] / interpolated[(((1 * ((-56 + R) * (-56 + C))) + ((-24 + _i1) * (-56 + C))) + (-24 + _i2))]);
      float  _ct1101 = input[((_i1 * C) + _i2)];
      float  _ct1102 = ((interpolated[(((1 * ((-56 + R) * (-56 + C))) + ((-24 + _i1) * (-56 + C))) + (-24 + _i2))] > 0)? _ct1100: _ct1101);
      filtered[((0 + ((_i1 - 24) * (-56 + C))) + (_i2 - 24))] = _ct1102;
    }
  }
  free(grid);
  free(blurx);
  free(interpolated);
}
