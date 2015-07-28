#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <cmath>
#include <string.h>
#include "simple_pool_allocator.h"
#define isl_min(x,y) ((x) < (y) ? (x) : (y))
#define isl_max(x,y) ((x) > (y) ? (x) : (y))
#define isl_floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
extern "C" void  pipeline_laplacian_naive(int  C, int  R, float  alpha, float  beta, void * img_colour_void_arg, void * laplacian_void_arg)
{
  unsigned char * img_colour_orig;
  img_colour_orig = (unsigned char *) (img_colour_void_arg);
  unsigned char * laplacian;
  laplacian = (unsigned char *) (laplacian_void_arg);

  float * img;
  img = (float *) (pool_allocate((sizeof(float ) * (R * C))));
  float * remapLUT;
  remapLUT = (float *) (pool_allocate((sizeof(float ) * 1536)));
  float * Dx_inGPyramid_L1;
  Dx_inGPyramid_L1 = (float *) (pool_allocate((sizeof(float ) * (((((R / 2) - 2) - 1) + 1) * (-2 + C)))));
  float * gPyramid_L0;
  gPyramid_L0 = (float *) (pool_allocate((sizeof(float ) * ((4 * R) * C))));
  float * D_inGPyramid_L1;
  D_inGPyramid_L1 = (float *) (pool_allocate((sizeof(float ) * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1)))));
  float * Dx_gPyramid_L1;
  Dx_gPyramid_L1 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 2) - 2) - 1) + 1)) * (-2 + C)))));
  float * D_gPyramid_L1;
  D_gPyramid_L1 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 2) - 2) - 1) + 1)) * ((((C / 2) - 2) - 1) + 1)))));
  float * Dx_inGPyramid_L2;
  Dx_inGPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * (((((R / 4) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1)))));
  float * D_inGPyramid_L2;
  D_inGPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1)))));
  float * Dx_gPyramid_L2;
  Dx_gPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 4) - 2) - 1) + 1)) * ((((C / 2) - 2) - 1) + 1)))));
  float * Ux_lPyramid_L0;
  Ux_lPyramid_L0 = (float *) (pool_allocate((sizeof(float ) * ((4 * (-92 + R)) * (((((C / 2) - 32) + 2) - 15) + 1)))));
  float * D_gPyramid_L2;
  D_gPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 4) - 2) - 1) + 1)) * ((((C / 4) - 2) - 1) + 1)))));
  float * Dx_inGPyramid_L3;
  Dx_inGPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * (((((R / 8) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1)))));
  float * U_lPyramid_L0;
  U_lPyramid_L0 = (float *) (pool_allocate((sizeof(float ) * ((4 * (-92 + R)) * (-92 + C)))));
  float * D_inGPyramid_L3;
  D_inGPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1)))));
  float * Dx_gPyramid_L3;
  Dx_gPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 8) - 2) - 1) + 1)) * ((((C / 4) - 2) - 1) + 1)))));
  float * Ux_lPyramid_L1;
  Ux_lPyramid_L1 = (float *) (pool_allocate((sizeof(float ) * ((4 * (((((R / 2) - 32) + 2) - 15) + 1)) * (((((C / 4) - 16) + 2) - 7) + 1)))));
  float * outLPyramid_L0;
  outLPyramid_L0 = (float *) (pool_allocate((sizeof(float ) * ((-92 + R) * (-92 + C)))));
  float * D_gPyramid_L3;
  D_gPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 8) - 2) - 1) + 1)) * ((((C / 8) - 2) - 1) + 1)))));
  float * Dx_inGPyramid_L4;
  Dx_inGPyramid_L4 = (float *) (pool_allocate((sizeof(float ) * (((((R / 16) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1)))));
  float * U_lPyramid_L1;
  U_lPyramid_L1 = (float *) (pool_allocate((sizeof(float ) * ((4 * (((((R / 2) - 32) + 2) - 15) + 1)) * (((((C / 2) - 32) + 2) - 15) + 1)))));
  float * D_inGPyramid_L4;
  D_inGPyramid_L4 = (float *) (pool_allocate((sizeof(float ) * (((((R / 16) - 2) - 1) + 1) * ((((C / 16) - 2) - 1) + 1)))));
  float * Dx_gPyramid_L4;
  Dx_gPyramid_L4 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 16) - 2) - 1) + 1)) * ((((C / 8) - 2) - 1) + 1)))));
  float * Ux_lPyramid_L2;
  Ux_lPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * ((4 * (((((R / 4) - 16) + 2) - 7) + 1)) * (((((C / 8) - 8) + 2) - 3) + 1)))));
  float * outLPyramid_L1;
  outLPyramid_L1 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 2) - 32) + 2) - 15) + 1)))));
  float * D_gPyramid_L4;
  D_gPyramid_L4 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 16) - 2) - 1) + 1)) * ((((C / 16) - 2) - 1) + 1)))));
  float * U_lPyramid_L2;
  U_lPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * ((4 * (((((R / 4) - 16) + 2) - 7) + 1)) * (((((C / 4) - 16) + 2) - 7) + 1)))));
  float * Ux_lPyramid_L3;
  Ux_lPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * ((4 * (((((R / 8) - 8) + 2) - 3) + 1)) * (((((C / 16) - 4) + 2) - 1) + 1)))));
  float * outLPyramid_L2;
  outLPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 4) - 16) + 2) - 7) + 1)))));
  float * outLPyramid_L4;
  outLPyramid_L4 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 16) - 4) + 2) - 1) + 1) * (((((C / 16) - 4) + 2) - 1) + 1)))));
  float * U_lPyramid_L3;
  U_lPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * ((4 * (((((R / 8) - 8) + 2) - 3) + 1)) * (((((C / 8) - 8) + 2) - 3) + 1)))));
  float * Ux_outGPyramid_L3;
  Ux_outGPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 16) - 4) + 2) - 1) + 1)))));
  float * outLPyramid_L3;
  outLPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 8) - 8) + 2) - 3) + 1)))));
  float * outGPyramid_L3;
  outGPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 8) - 8) + 2) - 3) + 1)))));
  float * Ux_outGPyramid_L2;
  Ux_outGPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 8) - 8) + 2) - 3) + 1)))));
  float * outGPyramid_L2;
  outGPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 4) - 16) + 2) - 7) + 1)))));
  float * Ux_outGPyramid_L1;
  Ux_outGPyramid_L1 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 4) - 16) + 2) - 7) + 1)))));
  float * outGPyramid_L1;
  outGPyramid_L1 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 2) - 32) + 2) - 15) + 1)))));
  float * Ux_result_ref_gray;
  Ux_result_ref_gray = (float *) (pool_allocate((sizeof(float ) * ((-92 + R) * (((((C / 2) - 32) + 2) - 15) + 1)))));
  float * result_ref_gray;
  result_ref_gray = (float *) (pool_allocate((sizeof(float ) * ((-92 + R) * (-92 + C)))));

  short unsigned int *img_colour;
  img_colour = (short unsigned int *) (pool_allocate((sizeof(short unsigned int) * (R * C * 3))));

  int off_left = 31;
  int total_pad = 92;

  int _R = R-total_pad;
  int _C = C-total_pad;

  #pragma omp parallel for schedule(static)
  for (int _i0 = off_left; _i0 < _R+off_left; _i0++)
  {
    for (int _i1 = off_left; _i1 < _C+off_left; _i1++)
    {
      #pragma ivdep
      for (int _i2 = 0; _i2 <= 2; _i2++)
      {
        img_colour[_i0 * C * 3 + _i1 * 3 + _i2] = ((unsigned short int)(img_colour_orig[(_i0-off_left)*(_C)*3 + (_i1-off_left)*3 + _i2])) * 256;
      }
    }
  }
  for (int _i0 = off_left; _i0 < _R+off_left; _i0++)
  {
    for (int _i1 = 0; _i1 < off_left; _i1++)
    {
      for (int _i2 = 0; _i2 <= 2; _i2++)
      {
        img_colour[_i0 * C * 3 + _i1 * 3 + _i2] = img_colour[(_i0) * C * 3 + off_left * 3 + _i2];
      }
    }
  }
  for (int _i0 = off_left; _i0 < _R+off_left; _i0++)
  {
    for (int _i1 = _C+off_left; _i1 < C; _i1++)
    {
      for (int _i2 = 0; _i2 <= 2; _i2++)
      {
        img_colour[_i0 * C * 3 + _i1 * 3 + _i2] = img_colour[(_i0) * C * 3 + (_C+(off_left-1)) * 3 + _i2];
      }
    }
  }

  for (int _i0 = 0; _i0 < off_left; _i0++)
  {
    for (int _i1 = 0; _i1 < off_left; _i1++)
    {
      for (int _i2 = 0; _i2 <= 2; _i2++)
      {
        img_colour[_i0 * C * 3 + _i1 * 3 + _i2] = img_colour[off_left * C * 3 + off_left * 3 + _i2];
      }
    }
  }
  for (int _i0 = 0; _i0 < off_left; _i0++)
  {
    for (int _i1 = off_left; _i1 < _C+off_left; _i1++)
    {
      for (int _i2 = 0; _i2 <= 2; _i2++)
      {
        img_colour[_i0 * C * 3 + _i1 * 3 + _i2] = img_colour[off_left * C * 3 + _i1 * 3 + _i2];
      }
    }
  }
  for (int _i0 = 0; _i0 < off_left; _i0++)
  {
    for (int _i1 = _C+off_left; _i1 < C; _i1++)
    {
      for (int _i2 = 0; _i2 <= 2; _i2++)
      {
        img_colour[_i0 * C * 3 + _i1 * 3 + _i2] = img_colour[off_left * C * 3 + (_C+(off_left-1)) * 3 + _i2];
      }
    }
  }

  for (int _i0 = _R+off_left; _i0 < R; _i0++)
  {
    for (int _i1 = 0; _i1 < off_left; _i1++)
    {
      for (int _i2 = 0; _i2 <= 2; _i2++)
      {
        img_colour[_i0 * C * 3 + _i1 * 3 + _i2] = img_colour[(_R+(off_left-1)) * C * 3 + off_left * 3 + _i2];
      }
    }
  }
  for (int _i0 = _R+off_left; _i0 < R; _i0++)
  {
    for (int _i1 = off_left; _i1 < _C+off_left; _i1++)
    {
      for (int _i2 = 0; _i2 <= 2; _i2++)
      {
        img_colour[_i0 * C * 3 + _i1 * 3 + _i2] = img_colour[(_R+(off_left-1)) * C + _i1 * 3 + _i2];
      }
    }
  }
  for (int _i0 = _R+off_left; _i0 < R; _i0++)
  {
    for (int _i1 = _C+off_left; _i1 < C; _i1++)
    {
      for (int _i2 = 0; _i2 <= 2; _i2++)
      {
        img_colour[_i0 * C * 3 + _i1 * 3 + _i2] = img_colour[(_R+(off_left-1)) * C * 3 + (_C+(off_left-1)) * 3 + _i2];
      }
    }
  }

  for (int  _i0 = -768; (_i0 <= 767); _i0 = (_i0 + 1))
  {
    remapLUT[(_i0 - -768)] = ((alpha * ((float ) (_i0) / 256.0f)) * std::exp(((-(((float ) (_i0) / 256.0f)) * ((float ) (_i0) / 256.0f)) / 2.0f)));
  }

  #pragma omp parallel for schedule(static)
  for (int  _i1 = 0; (_i1 < R); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 0; (_i2 < C); _i2 = (_i2 + 1))
    {
      img[((_i1 * C) + _i2)] = ((((0.299f * img_colour[(((_i1 * C * 3)) + _i2 * 3 + 2)]) + (0.587f * img_colour[(((_i1 * C * 3)) + _i2 * 3 + 1)])) + (0.114f * img_colour[(((_i1 * C * 3)) + _i2 * 3)])) / 65535.0f);
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 0; (_i1 < R); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 0; (_i2 < C); _i2 = (_i2 + 1))
      {
        int  _ct0 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (768.0f)));
        int  _ct1 = 0;
        int  _ct2 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (768.0f))) > 0)? _ct0: _ct1);
        int  _ct3 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (768.0f)));
        int  _ct4 = 0;
        int  _ct5 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (768.0f))) > 0)? _ct3: _ct4);
        int  _ct6 = _ct5;
        int  _ct7 = 768;
        int  _ct8 = ((_ct2 < 768)? _ct6: _ct7);
        gPyramid_L0[(((_i0 * (R * C)) + (_i1 * C)) + _i2)] = (((beta * (img[((_i1 * C) + _i2)] - (_i0 * 0.333333333333f))) + (_i0 * 0.333333333333f)) + remapLUT[((_ct8 - (256 * _i0)) - -768)]);
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 1; (_i1 < ((R / 2) - 1)); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 1; (_i2 < (C - 1)); _i2 = (_i2 + 1))
      {
        Dx_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * (-2 + C))) + ((_i1 - 1) * (-2 + C))) + (_i2 - 1))] = ((((gPyramid_L0[(((_i0 * (R * C)) + ((-1 + (2 * _i1)) * C)) + _i2)] + (3.0f * gPyramid_L0[(((_i0 * (R * C)) + ((2 * _i1) * C)) + _i2)])) + (3.0f * gPyramid_L0[(((_i0 * (R * C)) + ((1 + (2 * _i1)) * C)) + _i2)])) + gPyramid_L0[(((_i0 * (R * C)) + ((2 + (2 * _i1)) * C)) + _i2)]) * 0.125f);
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 1; (_i1 < ((R / 2) - 1)); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 1; (_i2 < ((C / 2) - 1)); _i2 = (_i2 + 1))
      {
        D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((_i1 - 1) * ((((C / 2) - 2) - 1) + 1))) + (_i2 - 1))] = ((((Dx_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * (-2 + C))) + ((-1 + _i1) * (-2 + C))) + (-2 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * (-2 + C))) + ((-1 + _i1) * (-2 + C))) + (-1 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * (-2 + C))) + ((-1 + _i1) * (-2 + C))) + (2 * _i2))])) + Dx_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * (-2 + C))) + ((-1 + _i1) * (-2 + C))) + (1 + (2 * _i2)))]) * 0.125f);
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 1; (_i1 < ((R / 2) - 1)); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 1; (_i2 < (C - 1)); _i2 = (_i2 + 1))
    {
      Dx_inGPyramid_L1[(((_i1 - 1) * (-2 + C)) + (_i2 - 1))] = ((((img[(((-1 + (2 * _i1)) * C) + _i2)] + (3.0f * img[(((2 * _i1) * C) + _i2)])) + (3.0f * img[(((1 + (2 * _i1)) * C) + _i2)])) + img[(((2 + (2 * _i1)) * C) + _i2)]) * 0.125f);
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 1; (_i1 < ((R / 4) - 1)); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 1; (_i2 < ((C / 2) - 1)); _i2 = (_i2 + 1))
      {
        Dx_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((_i1 - 1) * ((((C / 2) - 2) - 1) + 1))) + (_i2 - 1))] = ((((D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((-2 + (2 * _i1)) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))] + (3.0f * D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((-1 + (2 * _i1)) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))])) + (3.0f * D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((2 * _i1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))])) + D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((1 + (2 * _i1)) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))]) * 0.125f);
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 1; (_i1 < ((R / 2) - 1)); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 1; (_i2 < ((C / 2) - 1)); _i2 = (_i2 + 1))
    {
      D_inGPyramid_L1[(((_i1 - 1) * ((((C / 2) - 2) - 1) + 1)) + (_i2 - 1))] = ((((Dx_inGPyramid_L1[(((-1 + _i1) * (-2 + C)) + (-2 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L1[(((-1 + _i1) * (-2 + C)) + (-1 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L1[(((-1 + _i1) * (-2 + C)) + (2 * _i2))])) + Dx_inGPyramid_L1[(((-1 + _i1) * (-2 + C)) + (1 + (2 * _i2)))]) * 0.125f);
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 1; (_i1 < ((R / 4) - 1)); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 1; (_i2 < ((C / 4) - 1)); _i2 = (_i2 + 1))
      {
        D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((_i1 - 1) * ((((C / 4) - 2) - 1) + 1))) + (_i2 - 1))] = ((((Dx_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 2) - 2) - 1) + 1))) + (-2 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 2) - 2) - 1) + 1))) + (2 * _i2))])) + Dx_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 2) - 2) - 1) + 1))) + (1 + (2 * _i2)))]) * 0.125f);
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 1; (_i1 < ((R / 4) - 1)); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 1; (_i2 < ((C / 2) - 1)); _i2 = (_i2 + 1))
    {
      Dx_inGPyramid_L2[(((_i1 - 1) * ((((C / 2) - 2) - 1) + 1)) + (_i2 - 1))] = ((((D_inGPyramid_L1[(((-2 + (2 * _i1)) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] + (3.0f * D_inGPyramid_L1[(((-1 + (2 * _i1)) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))])) + (3.0f * D_inGPyramid_L1[(((2 * _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))])) + D_inGPyramid_L1[(((1 + (2 * _i1)) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))]) * 0.125f);
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 1; (_i1 < ((R / 8) - 1)); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 1; (_i2 < ((C / 4) - 1)); _i2 = (_i2 + 1))
      {
        Dx_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((_i1 - 1) * ((((C / 4) - 2) - 1) + 1))) + (_i2 - 1))] = ((((D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((-2 + (2 * _i1)) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))] + (3.0f * D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((-1 + (2 * _i1)) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))])) + (3.0f * D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((2 * _i1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))])) + D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((1 + (2 * _i1)) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))]) * 0.125f);
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 1; (_i1 < ((R / 4) - 1)); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 1; (_i2 < ((C / 4) - 1)); _i2 = (_i2 + 1))
    {
      D_inGPyramid_L2[(((_i1 - 1) * ((((C / 4) - 2) - 1) + 1)) + (_i2 - 1))] = ((((Dx_inGPyramid_L2[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-2 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L2[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L2[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (2 * _i2))])) + Dx_inGPyramid_L2[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (1 + (2 * _i2)))]) * 0.125f);
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 1; (_i1 < ((R / 8) - 1)); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 1; (_i2 < ((C / 8) - 1)); _i2 = (_i2 + 1))
      {
        D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((_i1 - 1) * ((((C / 8) - 2) - 1) + 1))) + (_i2 - 1))] = ((((Dx_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 4) - 2) - 1) + 1))) + (-2 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 4) - 2) - 1) + 1))) + (2 * _i2))])) + Dx_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 4) - 2) - 1) + 1))) + (1 + (2 * _i2)))]) * 0.125f);
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 1; (_i1 < ((R / 8) - 1)); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 1; (_i2 < ((C / 4) - 1)); _i2 = (_i2 + 1))
    {
      Dx_inGPyramid_L3[(((_i1 - 1) * ((((C / 4) - 2) - 1) + 1)) + (_i2 - 1))] = ((((D_inGPyramid_L2[(((-2 + (2 * _i1)) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] + (3.0f * D_inGPyramid_L2[(((-1 + (2 * _i1)) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))])) + (3.0f * D_inGPyramid_L2[(((2 * _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))])) + D_inGPyramid_L2[(((1 + (2 * _i1)) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))]) * 0.125f);
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 1; (_i1 < ((R / 16) - 1)); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 1; (_i2 < ((C / 8) - 1)); _i2 = (_i2 + 1))
      {
        Dx_gPyramid_L4[(((_i0 * (((((R / 16) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((_i1 - 1) * ((((C / 8) - 2) - 1) + 1))) + (_i2 - 1))] = ((((D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((-2 + (2 * _i1)) * ((((C / 8) - 2) - 1) + 1))) + (-1 + _i2))] + (3.0f * D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((-1 + (2 * _i1)) * ((((C / 8) - 2) - 1) + 1))) + (-1 + _i2))])) + (3.0f * D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((2 * _i1) * ((((C / 8) - 2) - 1) + 1))) + (-1 + _i2))])) + D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((1 + (2 * _i1)) * ((((C / 8) - 2) - 1) + 1))) + (-1 + _i2))]) * 0.125f);
      }
    }
  }
  for (int  _i1 = 1; (_i1 < ((R / 8) - 1)); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 1; (_i2 < ((C / 8) - 1)); _i2 = (_i2 + 1))
    {
      D_inGPyramid_L3[(((_i1 - 1) * ((((C / 8) - 2) - 1) + 1)) + (_i2 - 1))] = ((((Dx_inGPyramid_L3[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-2 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L3[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L3[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (2 * _i2))])) + Dx_inGPyramid_L3[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (1 + (2 * _i2)))]) * 0.125f);
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    for (int  _i1 = 1; (_i1 < ((R / 16) - 1)); _i1 = (_i1 + 1))
    {
      for (int  _i2 = 1; (_i2 < ((C / 16) - 1)); _i2 = (_i2 + 1))
      {
        D_gPyramid_L4[(((_i0 * (((((R / 16) - 2) - 1) + 1) * ((((C / 16) - 2) - 1) + 1))) + ((_i1 - 1) * ((((C / 16) - 2) - 1) + 1))) + (_i2 - 1))] = ((((Dx_gPyramid_L4[(((_i0 * (((((R / 16) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 8) - 2) - 1) + 1))) + (-2 + (2 * _i2)))] + (3.0f * Dx_gPyramid_L4[(((_i0 * (((((R / 16) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 8) - 2) - 1) + 1))) + (-1 + (2 * _i2)))])) + (3.0f * Dx_gPyramid_L4[(((_i0 * (((((R / 16) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 8) - 2) - 1) + 1))) + (2 * _i2))])) + Dx_gPyramid_L4[(((_i0 * (((((R / 16) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 8) - 2) - 1) + 1))) + (1 + (2 * _i2)))]) * 0.125f);
      }
    }
  }
  for (int  _i1 = 1; (_i1 < ((R / 16) - 1)); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 1; (_i2 < ((C / 8) - 1)); _i2 = (_i2 + 1))
    {
      Dx_inGPyramid_L4[(((_i1 - 1) * ((((C / 8) - 2) - 1) + 1)) + (_i2 - 1))] = ((((D_inGPyramid_L3[(((-2 + (2 * _i1)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] + (3.0f * D_inGPyramid_L3[(((-1 + (2 * _i1)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))])) + (3.0f * D_inGPyramid_L3[(((2 * _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))])) + D_inGPyramid_L3[(((1 + (2 * _i1)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))]) * 0.125f);
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 3; (_i1 < ((R / 8) - 5)); _i1 = (_i1 + 2))
    {
      #pragma ivdep
      for (int  _i2 = 1; (_i2 < ((C / 16) - 1)); _i2 = (_i2 + 1))
      {
        Ux_lPyramid_L3[(((_i0 * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((_i1 - 3) * (((((C / 16) - 4) + 2) - 1) + 1))) + (_i2 - 1))] = ((0.25f * D_gPyramid_L4[(((_i0 * (((((R / 16) - 2) - 1) + 1) * ((((C / 16) - 2) - 1) + 1))) + ((((_i1 / 2) + 1) - 1) * ((((C / 16) - 2) - 1) + 1))) + (-1 + _i2))]) + (0.75f * D_gPyramid_L4[(((_i0 * (((((R / 16) - 2) - 1) + 1) * ((((C / 16) - 2) - 1) + 1))) + (((_i1 / 2) - 1) * ((((C / 16) - 2) - 1) + 1))) + (-1 + _i2))]));
      }
      if ((R >= ((8 * _i1) + 56)))
      {
        #pragma ivdep
        for (int  _i2 = 1; (_i2 < ((C / 16) - 1)); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L3[(((_i0 * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 16) - 4) + 2) - 1) + 1))) + (((_i1 + 1) - 3) * (((((C / 16) - 4) + 2) - 1) + 1))) + (_i2 - 1))] = ((0.25f * D_gPyramid_L4[(((_i0 * (((((R / 16) - 2) - 1) + 1) * ((((C / 16) - 2) - 1) + 1))) + (((((_i1 + 1) / 2) - 1) - 1) * ((((C / 16) - 2) - 1) + 1))) + (-1 + _i2))]) + (0.75f * D_gPyramid_L4[(((_i0 * (((((R / 16) - 2) - 1) + 1) * ((((C / 16) - 2) - 1) + 1))) + ((((_i1 + 1) / 2) - 1) * ((((C / 16) - 2) - 1) + 1))) + (-1 + _i2))]));
        }
      }
    }
  }
  for (int  _i1 = 1; (_i1 < ((R / 16) - 1)); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 1; (_i2 < ((C / 16) - 1)); _i2 = (_i2 + 1))
    {
      D_inGPyramid_L4[(((_i1 - 1) * ((((C / 16) - 2) - 1) + 1)) + (_i2 - 1))] = ((((Dx_inGPyramid_L4[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-2 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L4[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L4[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (2 * _i2))])) + Dx_inGPyramid_L4[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (1 + (2 * _i2)))]) * 0.125f);
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 3; (_i1 < ((R / 8) - 5)); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 3; (_i2 < ((C / 8) - 5)); _i2 = (_i2 + 1))
      {
        float  _ct9 = ((0.25f * Ux_lPyramid_L3[(((_i0 * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((-3 + _i1) * (((((C / 16) - 4) + 2) - 1) + 1))) + (((_i2 / 2) - 1) - 1))]) + (0.75f * Ux_lPyramid_L3[(((_i0 * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((-3 + _i1) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((_i2 / 2) - 1))]));
        float  _ct10 = ((0.25f * Ux_lPyramid_L3[(((_i0 * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((-3 + _i1) * (((((C / 16) - 4) + 2) - 1) + 1))) + (((_i2 / 2) + 1) - 1))]) + (0.75f * Ux_lPyramid_L3[(((_i0 * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((-3 + _i1) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((_i2 / 2) - 1))]));
        float  _ct11 = (((_i2 % 2) == 0)? _ct9: _ct10);
        U_lPyramid_L3[(((_i0 * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 8) - 8) + 2) - 3) + 1))) + ((_i1 - 3) * (((((C / 8) - 8) + 2) - 3) + 1))) + (_i2 - 3))] = (D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 8) - 2) - 1) + 1))) + (-1 + _i2))] - _ct11);
      }
    }
  }
  for (int  _i1 = 1; (_i1 < ((R / 16) - 1)); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 1; (_i2 < ((C / 16) - 1)); _i2 = (_i2 + 1))
    {
      int  _ct12 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct13 = 0;
      int  _ct14 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct12: _ct13);
      int  _ct15 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct16 = 0;
      int  _ct17 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct15: _ct16);
      int  _ct18 = _ct17;
      int  _ct19 = 2;
      int  _ct20 = ((_ct14 < 2)? _ct18: _ct19);
      int  _ct21 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct22 = 0;
      int  _ct23 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct21: _ct22);
      int  _ct24 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct25 = 0;
      int  _ct26 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct24: _ct25);
      int  _ct27 = _ct26;
      int  _ct28 = 2;
      int  _ct29 = ((_ct23 < 2)? _ct27: _ct28);
      int  _ct30 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct31 = 0;
      int  _ct32 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct30: _ct31);
      int  _ct33 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct34 = 0;
      int  _ct35 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct33: _ct34);
      int  _ct36 = _ct35;
      int  _ct37 = 2;
      int  _ct38 = ((_ct32 < 2)? _ct36: _ct37);
      int  _ct39 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct40 = 0;
      int  _ct41 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct39: _ct40);
      int  _ct42 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct43 = 0;
      int  _ct44 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct42: _ct43);
      int  _ct45 = _ct44;
      int  _ct46 = 2;
      int  _ct47 = ((_ct41 < 2)? _ct45: _ct46);
      outLPyramid_L4[(((_i1 - 1) * (((((C / 16) - 4) + 2) - 1) + 1)) + (_i2 - 1))] = (((1.0f - ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct20)) * D_gPyramid_L4[(((_ct29 * (((((R / 16) - 2) - 1) + 1) * ((((C / 16) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 16) - 2) - 1) + 1))) + (-1 + _i2))]) + (((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct38) * D_gPyramid_L4[((((_ct47 + 1) * (((((R / 16) - 2) - 1) + 1) * ((((C / 16) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 16) - 2) - 1) + 1))) + (-1 + _i2))]));
    }
  }
  for (int  _i1 = 3; (_i1 < ((R / 8) - 5)); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 3; (_i2 < ((C / 8) - 5)); _i2 = (_i2 + 1))
    {
      int  _ct48 = (int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct49 = 0;
      int  _ct50 = (((int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct48: _ct49);
      int  _ct51 = (int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct52 = 0;
      int  _ct53 = (((int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct51: _ct52);
      int  _ct54 = _ct53;
      int  _ct55 = 2;
      int  _ct56 = ((_ct50 < 2)? _ct54: _ct55);
      int  _ct57 = (int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct58 = 0;
      int  _ct59 = (((int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct57: _ct58);
      int  _ct60 = (int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct61 = 0;
      int  _ct62 = (((int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct60: _ct61);
      int  _ct63 = _ct62;
      int  _ct64 = 2;
      int  _ct65 = ((_ct59 < 2)? _ct63: _ct64);
      int  _ct66 = (int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct67 = 0;
      int  _ct68 = (((int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct66: _ct67);
      int  _ct69 = (int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct70 = 0;
      int  _ct71 = (((int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct69: _ct70);
      int  _ct72 = _ct71;
      int  _ct73 = 2;
      int  _ct74 = ((_ct68 < 2)? _ct72: _ct73);
      int  _ct75 = (int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct76 = 0;
      int  _ct77 = (((int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct75: _ct76);
      int  _ct78 = (int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct79 = 0;
      int  _ct80 = (((int ) ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct78: _ct79);
      int  _ct81 = _ct80;
      int  _ct82 = 2;
      int  _ct83 = ((_ct77 < 2)? _ct81: _ct82);
      outLPyramid_L3[(((_i1 - 3) * (((((C / 8) - 8) + 2) - 3) + 1)) + (_i2 - 3))] = (((1.0f - ((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct56)) * U_lPyramid_L3[(((_ct65 * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 8) - 8) + 2) - 3) + 1))) + ((-3 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1))) + (-3 + _i2))]) + (((D_inGPyramid_L3[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct74) * U_lPyramid_L3[((((_ct83 + 1) * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 8) - 8) + 2) - 3) + 1))) + ((-3 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1))) + (-3 + _i2))]));
    }
  }
  for (int  _i1 = 3; (_i1 < ((R / 8) - 5)); _i1 = (_i1 + 2))
  {
    for (int  _i2 = 1; (_i2 < ((C / 16) - 1)); _i2 = (_i2 + 1))
    {
      Ux_outGPyramid_L3[(((_i1 - 3) * (((((C / 16) - 4) + 2) - 1) + 1)) + (_i2 - 1))] = ((0.25f * outLPyramid_L4[(((((_i1 / 2) + 1) - 1) * (((((C / 16) - 4) + 2) - 1) + 1)) + (-1 + _i2))]) + (0.75f * outLPyramid_L4[((((_i1 / 2) - 1) * (((((C / 16) - 4) + 2) - 1) + 1)) + (-1 + _i2))]));
    }
    if ((R >= ((8 * _i1) + 56)))
    {
      for (int  _i2 = 1; (_i2 < ((C / 16) - 1)); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L3[((((_i1 + 1) - 3) * (((((C / 16) - 4) + 2) - 1) + 1)) + (_i2 - 1))] = ((0.25f * outLPyramid_L4[((((((_i1 + 1) / 2) - 1) - 1) * (((((C / 16) - 4) + 2) - 1) + 1)) + (-1 + _i2))]) + (0.75f * outLPyramid_L4[(((((_i1 + 1) / 2) - 1) * (((((C / 16) - 4) + 2) - 1) + 1)) + (-1 + _i2))]));
      }
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 7; (_i1 < ((R / 4) - 13)); _i1 = (_i1 + 2))
    {
      #pragma ivdep
      for (int  _i2 = 3; (_i2 < ((C / 8) - 5)); _i2 = (_i2 + 1))
      {
        Ux_lPyramid_L2[(((_i0 * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 8) - 8) + 2) - 3) + 1))) + ((_i1 - 7) * (((((C / 8) - 8) + 2) - 3) + 1))) + (_i2 - 3))] = ((0.25f * D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((((_i1 / 2) + 1) - 1) * ((((C / 8) - 2) - 1) + 1))) + (-1 + _i2))]) + (0.75f * D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + (((_i1 / 2) - 1) * ((((C / 8) - 2) - 1) + 1))) + (-1 + _i2))]));
      }
      if ((R >= ((4 * _i1) + 60)))
      {
        #pragma ivdep
        for (int  _i2 = 3; (_i2 < ((C / 8) - 5)); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L2[(((_i0 * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 8) - 8) + 2) - 3) + 1))) + (((_i1 + 1) - 7) * (((((C / 8) - 8) + 2) - 3) + 1))) + (_i2 - 3))] = ((0.25f * D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + (((((_i1 + 1) / 2) - 1) - 1) * ((((C / 8) - 2) - 1) + 1))) + (-1 + _i2))]) + (0.75f * D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((((_i1 + 1) / 2) - 1) * ((((C / 8) - 2) - 1) + 1))) + (-1 + _i2))]));
        }
      }
    }
  }
  for (int  _i1 = 3; (_i1 < ((R / 8) - 5)); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 3; (_i2 < ((C / 8) - 5)); _i2 = (_i2 + 1))
    {
      float  _ct84 = ((0.25f * Ux_outGPyramid_L3[(((-3 + _i1) * (((((C / 16) - 4) + 2) - 1) + 1)) + (((_i2 / 2) - 1) - 1))]) + (0.75f * Ux_outGPyramid_L3[(((-3 + _i1) * (((((C / 16) - 4) + 2) - 1) + 1)) + ((_i2 / 2) - 1))]));
      float  _ct85 = ((0.25f * Ux_outGPyramid_L3[(((-3 + _i1) * (((((C / 16) - 4) + 2) - 1) + 1)) + (((_i2 / 2) + 1) - 1))]) + (0.75f * Ux_outGPyramid_L3[(((-3 + _i1) * (((((C / 16) - 4) + 2) - 1) + 1)) + ((_i2 / 2) - 1))]));
      float  _ct86 = (((_i2 % 2) == 0)? _ct84: _ct85);
      outGPyramid_L3[(((_i1 - 3) * (((((C / 8) - 8) + 2) - 3) + 1)) + (_i2 - 3))] = (outLPyramid_L3[(((-3 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1)) + (-3 + _i2))] + _ct86);
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 7; (_i1 < ((R / 4) - 13)); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 7; (_i2 < ((C / 4) - 13)); _i2 = (_i2 + 1))
      {
        float  _ct87 = ((0.25f * Ux_lPyramid_L2[(((_i0 * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 8) - 8) + 2) - 3) + 1))) + ((-7 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1))) + (((_i2 / 2) - 1) - 3))]) + (0.75f * Ux_lPyramid_L2[(((_i0 * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 8) - 8) + 2) - 3) + 1))) + ((-7 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1))) + ((_i2 / 2) - 3))]));
        float  _ct88 = ((0.25f * Ux_lPyramid_L2[(((_i0 * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 8) - 8) + 2) - 3) + 1))) + ((-7 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1))) + (((_i2 / 2) + 1) - 3))]) + (0.75f * Ux_lPyramid_L2[(((_i0 * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 8) - 8) + 2) - 3) + 1))) + ((-7 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1))) + ((_i2 / 2) - 3))]));
        float  _ct89 = (((_i2 % 2) == 0)? _ct87: _ct88);
        U_lPyramid_L2[(((_i0 * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 4) - 16) + 2) - 7) + 1))) + ((_i1 - 7) * (((((C / 4) - 16) + 2) - 7) + 1))) + (_i2 - 7))] = (D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))] - _ct89);
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 7; (_i1 < ((R / 4) - 13)); _i1 = (_i1 + 2))
  {
    #pragma ivdep
    for (int  _i2 = 3; (_i2 < ((C / 8) - 5)); _i2 = (_i2 + 1))
    {
      Ux_outGPyramid_L2[(((_i1 - 7) * (((((C / 8) - 8) + 2) - 3) + 1)) + (_i2 - 3))] = ((0.25f * outGPyramid_L3[(((((_i1 / 2) + 1) - 3) * (((((C / 8) - 8) + 2) - 3) + 1)) + (-3 + _i2))]) + (0.75f * outGPyramid_L3[((((_i1 / 2) - 3) * (((((C / 8) - 8) + 2) - 3) + 1)) + (-3 + _i2))]));
    }
    if ((R >= ((4 * _i1) + 60)))
    {
      #pragma ivdep
      for (int  _i2 = 3; (_i2 < ((C / 8) - 5)); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L2[((((_i1 + 1) - 7) * (((((C / 8) - 8) + 2) - 3) + 1)) + (_i2 - 3))] = ((0.25f * outGPyramid_L3[((((((_i1 + 1) / 2) - 1) - 3) * (((((C / 8) - 8) + 2) - 3) + 1)) + (-3 + _i2))]) + (0.75f * outGPyramid_L3[(((((_i1 + 1) / 2) - 3) * (((((C / 8) - 8) + 2) - 3) + 1)) + (-3 + _i2))]));
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 7; (_i1 < ((R / 4) - 13)); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 7; (_i2 < ((C / 4) - 13)); _i2 = (_i2 + 1))
    {
      int  _ct90 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct91 = 0;
      int  _ct92 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct90: _ct91);
      int  _ct93 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct94 = 0;
      int  _ct95 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct93: _ct94);
      int  _ct96 = _ct95;
      int  _ct97 = 2;
      int  _ct98 = ((_ct92 < 2)? _ct96: _ct97);
      int  _ct99 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct100 = 0;
      int  _ct101 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct99: _ct100);
      int  _ct102 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct103 = 0;
      int  _ct104 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct102: _ct103);
      int  _ct105 = _ct104;
      int  _ct106 = 2;
      int  _ct107 = ((_ct101 < 2)? _ct105: _ct106);
      int  _ct108 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct109 = 0;
      int  _ct110 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct108: _ct109);
      int  _ct111 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct112 = 0;
      int  _ct113 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct111: _ct112);
      int  _ct114 = _ct113;
      int  _ct115 = 2;
      int  _ct116 = ((_ct110 < 2)? _ct114: _ct115);
      int  _ct117 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct118 = 0;
      int  _ct119 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct117: _ct118);
      int  _ct120 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct121 = 0;
      int  _ct122 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct120: _ct121);
      int  _ct123 = _ct122;
      int  _ct124 = 2;
      int  _ct125 = ((_ct119 < 2)? _ct123: _ct124);
      outLPyramid_L2[(((_i1 - 7) * (((((C / 4) - 16) + 2) - 7) + 1)) + (_i2 - 7))] = (((1.0f - ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct98)) * U_lPyramid_L2[(((_ct107 * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 4) - 16) + 2) - 7) + 1))) + ((-7 + _i1) * (((((C / 4) - 16) + 2) - 7) + 1))) + (-7 + _i2))]) + (((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct116) * U_lPyramid_L2[((((_ct125 + 1) * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 4) - 16) + 2) - 7) + 1))) + ((-7 + _i1) * (((((C / 4) - 16) + 2) - 7) + 1))) + (-7 + _i2))]));
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 15; (_i1 < ((R / 2) - 29)); _i1 = (_i1 + 2))
    {
      #pragma ivdep
      for (int  _i2 = 7; (_i2 < ((C / 4) - 13)); _i2 = (_i2 + 1))
      {
        Ux_lPyramid_L1[(((_i0 * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 4) - 16) + 2) - 7) + 1))) + ((_i1 - 15) * (((((C / 4) - 16) + 2) - 7) + 1))) + (_i2 - 7))] = ((0.25f * D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((((_i1 / 2) + 1) - 1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))]) + (0.75f * D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + (((_i1 / 2) - 1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))]));
      }
      if ((R >= ((2 * _i1) + 62)))
      {
        #pragma ivdep
        for (int  _i2 = 7; (_i2 < ((C / 4) - 13)); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L1[(((_i0 * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 4) - 16) + 2) - 7) + 1))) + (((_i1 + 1) - 15) * (((((C / 4) - 16) + 2) - 7) + 1))) + (_i2 - 7))] = ((0.25f * D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + (((((_i1 + 1) / 2) - 1) - 1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))]) + (0.75f * D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((((_i1 + 1) / 2) - 1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))]));
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 7; (_i1 < ((R / 4) - 13)); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 7; (_i2 < ((C / 4) - 13)); _i2 = (_i2 + 1))
    {
      float  _ct126 = ((0.25f * Ux_outGPyramid_L2[(((-7 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1)) + (((_i2 / 2) - 1) - 3))]) + (0.75f * Ux_outGPyramid_L2[(((-7 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1)) + ((_i2 / 2) - 3))]));
      float  _ct127 = ((0.25f * Ux_outGPyramid_L2[(((-7 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1)) + (((_i2 / 2) + 1) - 3))]) + (0.75f * Ux_outGPyramid_L2[(((-7 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1)) + ((_i2 / 2) - 3))]));
      float  _ct128 = (((_i2 % 2) == 0)? _ct126: _ct127);
      outGPyramid_L2[(((_i1 - 7) * (((((C / 4) - 16) + 2) - 7) + 1)) + (_i2 - 7))] = (outLPyramid_L2[(((-7 + _i1) * (((((C / 4) - 16) + 2) - 7) + 1)) + (-7 + _i2))] + _ct128);
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 15; (_i1 < ((R / 2) - 29)); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 15; (_i2 < ((C / 2) - 29)); _i2 = (_i2 + 1))
      {
        float  _ct129 = ((0.25f * Ux_lPyramid_L1[(((_i0 * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 4) - 16) + 2) - 7) + 1))) + ((-15 + _i1) * (((((C / 4) - 16) + 2) - 7) + 1))) + (((_i2 / 2) - 1) - 7))]) + (0.75f * Ux_lPyramid_L1[(((_i0 * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 4) - 16) + 2) - 7) + 1))) + ((-15 + _i1) * (((((C / 4) - 16) + 2) - 7) + 1))) + ((_i2 / 2) - 7))]));
        float  _ct130 = ((0.25f * Ux_lPyramid_L1[(((_i0 * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 4) - 16) + 2) - 7) + 1))) + ((-15 + _i1) * (((((C / 4) - 16) + 2) - 7) + 1))) + (((_i2 / 2) + 1) - 7))]) + (0.75f * Ux_lPyramid_L1[(((_i0 * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 4) - 16) + 2) - 7) + 1))) + ((-15 + _i1) * (((((C / 4) - 16) + 2) - 7) + 1))) + ((_i2 / 2) - 7))]));
        float  _ct131 = (((_i2 % 2) == 0)? _ct129: _ct130);
        U_lPyramid_L1[(((_i0 * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 2) - 32) + 2) - 15) + 1))) + ((_i1 - 15) * (((((C / 2) - 32) + 2) - 15) + 1))) + (_i2 - 15))] = (D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))] - _ct131);
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 15; (_i1 < ((R / 2) - 29)); _i1 = (_i1 + 2))
  {
    #pragma ivdep
    for (int  _i2 = 7; (_i2 < ((C / 4) - 13)); _i2 = (_i2 + 1))
    {
      Ux_outGPyramid_L1[(((_i1 - 15) * (((((C / 4) - 16) + 2) - 7) + 1)) + (_i2 - 7))] = ((0.25f * outGPyramid_L2[(((((_i1 / 2) + 1) - 7) * (((((C / 4) - 16) + 2) - 7) + 1)) + (-7 + _i2))]) + (0.75f * outGPyramid_L2[((((_i1 / 2) - 7) * (((((C / 4) - 16) + 2) - 7) + 1)) + (-7 + _i2))]));
    }
    if ((R >= ((2 * _i1) + 62)))
    {
      #pragma ivdep
      for (int  _i2 = 7; (_i2 < ((C / 4) - 13)); _i2 = (_i2 + 1))
      {
        Ux_outGPyramid_L1[((((_i1 + 1) - 15) * (((((C / 4) - 16) + 2) - 7) + 1)) + (_i2 - 7))] = ((0.25f * outGPyramid_L2[((((((_i1 + 1) / 2) - 1) - 7) * (((((C / 4) - 16) + 2) - 7) + 1)) + (-7 + _i2))]) + (0.75f * outGPyramid_L2[(((((_i1 + 1) / 2) - 7) * (((((C / 4) - 16) + 2) - 7) + 1)) + (-7 + _i2))]));
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 15; (_i1 < ((R / 2) - 29)); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 15; (_i2 < ((C / 2) - 29)); _i2 = (_i2 + 1))
    {
      int  _ct132 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct133 = 0;
      int  _ct134 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct132: _ct133);
      int  _ct135 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct136 = 0;
      int  _ct137 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct135: _ct136);
      int  _ct138 = _ct137;
      int  _ct139 = 2;
      int  _ct140 = ((_ct134 < 2)? _ct138: _ct139);
      int  _ct141 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct142 = 0;
      int  _ct143 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct141: _ct142);
      int  _ct144 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct145 = 0;
      int  _ct146 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct144: _ct145);
      int  _ct147 = _ct146;
      int  _ct148 = 2;
      int  _ct149 = ((_ct143 < 2)? _ct147: _ct148);
      int  _ct150 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct151 = 0;
      int  _ct152 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct150: _ct151);
      int  _ct153 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct154 = 0;
      int  _ct155 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct153: _ct154);
      int  _ct156 = _ct155;
      int  _ct157 = 2;
      int  _ct158 = ((_ct152 < 2)? _ct156: _ct157);
      int  _ct159 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct160 = 0;
      int  _ct161 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct159: _ct160);
      int  _ct162 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct163 = 0;
      int  _ct164 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct162: _ct163);
      int  _ct165 = _ct164;
      int  _ct166 = 2;
      int  _ct167 = ((_ct161 < 2)? _ct165: _ct166);
      outLPyramid_L1[(((_i1 - 15) * (((((C / 2) - 32) + 2) - 15) + 1)) + (_i2 - 15))] = (((1.0f - ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct140)) * U_lPyramid_L1[(((_ct149 * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 2) - 32) + 2) - 15) + 1))) + ((-15 + _i1) * (((((C / 2) - 32) + 2) - 15) + 1))) + (-15 + _i2))]) + (((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct158) * U_lPyramid_L1[((((_ct167 + 1) * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 2) - 32) + 2) - 15) + 1))) + ((-15 + _i1) * (((((C / 2) - 32) + 2) - 15) + 1))) + (-15 + _i2))]));
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 31; (_i1 < (R - 61)); _i1 = (_i1 + 2))
    {
      #pragma ivdep
      for (int  _i2 = 15; (_i2 < ((C / 2) - 29)); _i2 = (_i2 + 1))
      {
        Ux_lPyramid_L0[(((_i0 * ((-92 + R) * (((((C / 2) - 32) + 2) - 15) + 1))) + ((_i1 - 31) * (((((C / 2) - 32) + 2) - 15) + 1))) + (_i2 - 15))] = ((0.25f * D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((((_i1 / 2) + 1) - 1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))]) + (0.75f * D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + (((_i1 / 2) - 1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))]));
      }
      if ((R >= (_i1 + 63)))
      {
        #pragma ivdep
        for (int  _i2 = 15; (_i2 < ((C / 2) - 29)); _i2 = (_i2 + 1))
        {
          Ux_lPyramid_L0[(((_i0 * ((-92 + R) * (((((C / 2) - 32) + 2) - 15) + 1))) + (((_i1 + 1) - 31) * (((((C / 2) - 32) + 2) - 15) + 1))) + (_i2 - 15))] = ((0.25f * D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + (((((_i1 + 1) / 2) - 1) - 1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))]) + (0.75f * D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((((_i1 + 1) / 2) - 1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))]));
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 15; (_i1 < ((R / 2) - 29)); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 15; (_i2 < ((C / 2) - 29)); _i2 = (_i2 + 1))
    {
      float  _ct168 = ((0.25f * Ux_outGPyramid_L1[(((-15 + _i1) * (((((C / 4) - 16) + 2) - 7) + 1)) + (((_i2 / 2) - 1) - 7))]) + (0.75f * Ux_outGPyramid_L1[(((-15 + _i1) * (((((C / 4) - 16) + 2) - 7) + 1)) + ((_i2 / 2) - 7))]));
      float  _ct169 = ((0.25f * Ux_outGPyramid_L1[(((-15 + _i1) * (((((C / 4) - 16) + 2) - 7) + 1)) + (((_i2 / 2) + 1) - 7))]) + (0.75f * Ux_outGPyramid_L1[(((-15 + _i1) * (((((C / 4) - 16) + 2) - 7) + 1)) + ((_i2 / 2) - 7))]));
      float  _ct170 = (((_i2 % 2) == 0)? _ct168: _ct169);
      outGPyramid_L1[(((_i1 - 15) * (((((C / 2) - 32) + 2) - 15) + 1)) + (_i2 - 15))] = (outLPyramid_L1[(((-15 + _i1) * (((((C / 2) - 32) + 2) - 15) + 1)) + (-15 + _i2))] + _ct170);
    }
  }
  for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
  {
    #pragma omp parallel for schedule(static)
    for (int  _i1 = 31; (_i1 < (R - 61)); _i1 = (_i1 + 1))
    {
      #pragma ivdep
      for (int  _i2 = 31; (_i2 < (C - 61)); _i2 = (_i2 + 1))
      {
        float  _ct171 = ((0.25f * Ux_lPyramid_L0[(((_i0 * ((-92 + R) * (((((C / 2) - 32) + 2) - 15) + 1))) + ((-31 + _i1) * (((((C / 2) - 32) + 2) - 15) + 1))) + (((_i2 / 2) - 1) - 15))]) + (0.75f * Ux_lPyramid_L0[(((_i0 * ((-92 + R) * (((((C / 2) - 32) + 2) - 15) + 1))) + ((-31 + _i1) * (((((C / 2) - 32) + 2) - 15) + 1))) + ((_i2 / 2) - 15))]));
        float  _ct172 = ((0.25f * Ux_lPyramid_L0[(((_i0 * ((-92 + R) * (((((C / 2) - 32) + 2) - 15) + 1))) + ((-31 + _i1) * (((((C / 2) - 32) + 2) - 15) + 1))) + (((_i2 / 2) + 1) - 15))]) + (0.75f * Ux_lPyramid_L0[(((_i0 * ((-92 + R) * (((((C / 2) - 32) + 2) - 15) + 1))) + ((-31 + _i1) * (((((C / 2) - 32) + 2) - 15) + 1))) + ((_i2 / 2) - 15))]));
        float  _ct173 = (((_i2 % 2) == 0)? _ct171: _ct172);
        U_lPyramid_L0[(((_i0 * ((-92 + R) * (-92 + C))) + ((_i1 - 31) * (-92 + C))) + (_i2 - 31))] = (gPyramid_L0[(((_i0 * (R * C)) + (_i1 * C)) + _i2)] - _ct173);
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 31; (_i1 < (R - 61)); _i1 = (_i1 + 2))
  {
    #pragma ivdep
    for (int  _i2 = 15; (_i2 < ((C / 2) - 29)); _i2 = (_i2 + 1))
    {
      Ux_result_ref_gray[(((_i1 - 31) * (((((C / 2) - 32) + 2) - 15) + 1)) + (_i2 - 15))] = ((0.25f * outGPyramid_L1[(((((_i1 / 2) + 1) - 15) * (((((C / 2) - 32) + 2) - 15) + 1)) + (-15 + _i2))]) + (0.75f * outGPyramid_L1[((((_i1 / 2) - 15) * (((((C / 2) - 32) + 2) - 15) + 1)) + (-15 + _i2))]));
    }
    if ((R >= (_i1 + 63)))
    {
      #pragma ivdep
      for (int  _i2 = 15; (_i2 < ((C / 2) - 29)); _i2 = (_i2 + 1))
      {
        Ux_result_ref_gray[((((_i1 + 1) - 31) * (((((C / 2) - 32) + 2) - 15) + 1)) + (_i2 - 15))] = ((0.25f * outGPyramid_L1[((((((_i1 + 1) / 2) - 1) - 15) * (((((C / 2) - 32) + 2) - 15) + 1)) + (-15 + _i2))]) + (0.75f * outGPyramid_L1[(((((_i1 + 1) / 2) - 15) * (((((C / 2) - 32) + 2) - 15) + 1)) + (-15 + _i2))]));
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 31; (_i1 < (R - 61)); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 31; (_i2 < (C - 61)); _i2 = (_i2 + 1))
    {
      int  _ct174 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
      int  _ct175 = 0;
      int  _ct176 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct174: _ct175);
      int  _ct177 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
      int  _ct178 = 0;
      int  _ct179 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct177: _ct178);
      int  _ct180 = _ct179;
      int  _ct181 = 2;
      int  _ct182 = ((_ct176 < 2)? _ct180: _ct181);
      int  _ct183 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
      int  _ct184 = 0;
      int  _ct185 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct183: _ct184);
      int  _ct186 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
      int  _ct187 = 0;
      int  _ct188 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct186: _ct187);
      int  _ct189 = _ct188;
      int  _ct190 = 2;
      int  _ct191 = ((_ct185 < 2)? _ct189: _ct190);
      int  _ct192 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
      int  _ct193 = 0;
      int  _ct194 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct192: _ct193);
      int  _ct195 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
      int  _ct196 = 0;
      int  _ct197 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct195: _ct196);
      int  _ct198 = _ct197;
      int  _ct199 = 2;
      int  _ct200 = ((_ct194 < 2)? _ct198: _ct199);
      int  _ct201 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
      int  _ct202 = 0;
      int  _ct203 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct201: _ct202);
      int  _ct204 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
      int  _ct205 = 0;
      int  _ct206 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct204: _ct205);
      int  _ct207 = _ct206;
      int  _ct208 = 2;
      int  _ct209 = ((_ct203 < 2)? _ct207: _ct208);
      outLPyramid_L0[(((_i1 - 31) * (-92 + C)) + (_i2 - 31))] = (((1.0f - ((img[((_i1 * C) + _i2)] * (float ) (3)) - _ct182)) * U_lPyramid_L0[(((_ct191 * ((-92 + R) * (-92 + C))) + ((-31 + _i1) * (-92 + C))) + (-31 + _i2))]) + (((img[((_i1 * C) + _i2)] * (float ) (3)) - _ct200) * U_lPyramid_L0[((((_ct209 + 1) * ((-92 + R) * (-92 + C))) + ((-31 + _i1) * (-92 + C))) + (-31 + _i2))]));
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 31; (_i1 < (R - 61)); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = 31; (_i2 < (C - 61)); _i2 = (_i2 + 1))
    {
      float  _ct210 = ((0.25f * Ux_result_ref_gray[(((-31 + _i1) * (((((C / 2) - 32) + 2) - 15) + 1)) + (((_i2 / 2) - 1) - 15))]) + (0.75f * Ux_result_ref_gray[(((-31 + _i1) * (((((C / 2) - 32) + 2) - 15) + 1)) + ((_i2 / 2) - 15))]));
      float  _ct211 = ((0.25f * Ux_result_ref_gray[(((-31 + _i1) * (((((C / 2) - 32) + 2) - 15) + 1)) + (((_i2 / 2) + 1) - 15))]) + (0.75f * Ux_result_ref_gray[(((-31 + _i1) * (((((C / 2) - 32) + 2) - 15) + 1)) + ((_i2 / 2) - 15))]));
      float  _ct212 = (((_i2 % 2) == 0)? _ct210: _ct211);
      result_ref_gray[(((_i1 - 31) * (-92 + C)) + (_i2 - 31))] = (outLPyramid_L0[(((-31 + _i1) * (-92 + C)) + (-31 + _i2))] + _ct212);
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _i1 = 31; (_i1 < (R - 61)); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 31; (_i2 < (C - 61)); _i2 = (_i2 + 1))
    {
      #pragma ivdep
      for (int  _i0 = 0; (_i0 <= 2); _i0 = (_i0 + 1))
      {
        float  _ct20426 = ((result_ref_gray[(((-31 + _i1) * (-92 + C)) + (-31 + _i2))] * ((img_colour[(((_i1 * C * 3)) + _i2 * 3 + _i0)] / 65535.0f) + 0.01f)) / (img[((_i1 * C) + _i2)] + 0.01f));
        float  _ct20427 = 0.0f;
        float  _ct20428 = ((((result_ref_gray[(((-31 + _i1) * (-92 + C)) + (-31 + _i2))] * ((img_colour[(((_i1 * C * 3)) + _i2 * 3 + _i0)] / 65535.0f) + 0.01f)) / (img[((_i1 * C) + _i2)] + 0.01f)) > 0.0f)? _ct20426: _ct20427);
        float  _ct20429 = ((result_ref_gray[(((-31 + _i1) * (-92 + C)) + (-31 + _i2))] * ((img_colour[(((_i1 * C * 3)) + _i2 * 3 + _i0)] / 65535.0f) + 0.01f)) / (img[((_i1 * C) + _i2)] + 0.01f));
        float  _ct20430 = 0.0f;
        float  _ct20431 = ((((result_ref_gray[(((-31 + _i1) * (-92 + C)) + (-31 + _i2))] * ((img_colour[(((_i1 * C * 3)) + _i2 * 3 + _i0)] / 65535.0f) + 0.01f)) / (img[((_i1 * C) + _i2)] + 0.01f)) > 0.0f)? _ct20429: _ct20430);
        float  _ct20432 = _ct20431;
        float  _ct20433 = 1.0f;
        float  _ct20434 = ((_ct20428 < 1.0f)? _ct20432: _ct20433);
        laplacian[((((_i1 - 31) * (-92 + C) * 3)) + (_i2 - 31) * 3 + _i0)] = (unsigned char) ((_ct20434 * 255.0f));
      }
    }
  }
  pool_deallocate(img);
  pool_deallocate(img_colour);
  pool_deallocate(remapLUT);
  pool_deallocate(Dx_inGPyramid_L1);
  pool_deallocate(gPyramid_L0);
  pool_deallocate(D_inGPyramid_L1);
  pool_deallocate(Dx_gPyramid_L1);
  pool_deallocate(D_gPyramid_L1);
  pool_deallocate(Dx_inGPyramid_L2);
  pool_deallocate(D_inGPyramid_L2);
  pool_deallocate(Dx_gPyramid_L2);
  pool_deallocate(Ux_lPyramid_L0);
  pool_deallocate(D_gPyramid_L2);
  pool_deallocate(Dx_inGPyramid_L3);
  pool_deallocate(U_lPyramid_L0);
  pool_deallocate(D_inGPyramid_L3);
  pool_deallocate(Dx_gPyramid_L3);
  pool_deallocate(Ux_lPyramid_L1);
  pool_deallocate(outLPyramid_L0);
  pool_deallocate(D_gPyramid_L3);
  pool_deallocate(Dx_inGPyramid_L4);
  pool_deallocate(U_lPyramid_L1);
  pool_deallocate(D_inGPyramid_L4);
  pool_deallocate(Dx_gPyramid_L4);
  pool_deallocate(Ux_lPyramid_L2);
  pool_deallocate(outLPyramid_L1);
  pool_deallocate(D_gPyramid_L4);
  pool_deallocate(U_lPyramid_L2);
  pool_deallocate(Ux_lPyramid_L3);
  pool_deallocate(outLPyramid_L2);
  pool_deallocate(outLPyramid_L4);
  pool_deallocate(U_lPyramid_L3);
  pool_deallocate(Ux_outGPyramid_L3);
  pool_deallocate(outLPyramid_L3);
  pool_deallocate(outGPyramid_L3);
  pool_deallocate(Ux_outGPyramid_L2);
  pool_deallocate(outGPyramid_L2);
  pool_deallocate(Ux_outGPyramid_L1);
  pool_deallocate(outGPyramid_L1);
  pool_deallocate(Ux_result_ref_gray);
  pool_deallocate(result_ref_gray);
}
