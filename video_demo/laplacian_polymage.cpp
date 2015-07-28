#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <cmath>
#include <string.h>
#include "simple_pool_allocator.h"
#define isl_min(x,y) ((x) < (y) ? (x) : (y))
#define isl_max(x,y) ((x) > (y) ? (x) : (y))
#define isl_floord(n,d) (((n)<0) ? -((-(n)+(d)-1)/(d)) : (n)/(d))
extern "C" void  pipeline_laplacian(int  C, int  R, float  alpha, float  beta, void * img_colour_void_arg, void * laplacian_void_arg)
{
  unsigned char * img_colour;
  img_colour = (unsigned char *) (img_colour_void_arg);
  unsigned char * laplacian;
  laplacian = (unsigned char *) (laplacian_void_arg);

  float * img;
  img = (float *) (pool_allocate((sizeof(float ) * (R * C))));
  float * remapLUT;
  remapLUT = (float *) (pool_allocate((sizeof(float ) * 1536)));
  float * gPyramid_L0;
  gPyramid_L0 = (float *) (pool_allocate((sizeof(float ) * ((4 * R) * C))));
  float * D_inGPyramid_L1;
  D_inGPyramid_L1 = (float *) (pool_allocate((sizeof(float ) * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1)))));
  float * D_gPyramid_L1;
  D_gPyramid_L1 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 2) - 2) - 1) + 1)) * ((((C / 2) - 2) - 1) + 1)))));
  float * D_inGPyramid_L2;
  D_inGPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1)))));
  float * D_gPyramid_L2;
  D_gPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 4) - 2) - 1) + 1)) * ((((C / 4) - 2) - 1) + 1)))));
  float * Dx_inGPyramid_L3;
  Dx_inGPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * (((((R / 8) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1)))));
  float * D_inGPyramid_L3;
  D_inGPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1)))));
  float * D_gPyramid_L3;
  D_gPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 8) - 2) - 1) + 1)) * ((((C / 8) - 2) - 1) + 1)))));
  float * Dx_inGPyramid_L4;
  Dx_inGPyramid_L4 = (float *) (pool_allocate((sizeof(float ) * (((((R / 16) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1)))));
  float * D_inGPyramid_L4;
  D_inGPyramid_L4 = (float *) (pool_allocate((sizeof(float ) * (((((R / 16) - 2) - 1) + 1) * ((((C / 16) - 2) - 1) + 1)))));
  float * Dx_gPyramid_L4;
  Dx_gPyramid_L4 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 16) - 2) - 1) + 1)) * ((((C / 8) - 2) - 1) + 1)))));
  float * D_gPyramid_L4;
  D_gPyramid_L4 = (float *) (pool_allocate((sizeof(float ) * ((4 * ((((R / 16) - 2) - 1) + 1)) * ((((C / 16) - 2) - 1) + 1)))));
  float * Ux_lPyramid_L3;
  Ux_lPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * ((4 * (((((R / 8) - 8) + 2) - 3) + 1)) * (((((C / 16) - 4) + 2) - 1) + 1)))));
  float * outLPyramid_L4;
  outLPyramid_L4 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 16) - 4) + 2) - 1) + 1) * (((((C / 16) - 4) + 2) - 1) + 1)))));
  float * Ux_outGPyramid_L3;
  Ux_outGPyramid_L3 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 16) - 4) + 2) - 1) + 1)))));
  float * Ux_outGPyramid_L2;
  Ux_outGPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 8) - 8) + 2) - 3) + 1)))));
  float * outGPyramid_L2;
  outGPyramid_L2 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 4) - 16) + 2) - 7) + 1) * (((((C / 4) - 16) + 2) - 7) + 1)))));
  float * outGPyramid_L1;
  outGPyramid_L1 = (float *) (pool_allocate((sizeof(float ) * ((((((R / 2) - 32) + 2) - 15) + 1) * (((((C / 2) - 32) + 2) - 15) + 1)))));
  float * result_ref_gray;
  result_ref_gray = (float *) (pool_allocate((sizeof(float ) * ((-92 + R) * (-92 + C)))));
  for (int  _i0 = -768; (_i0 <= 767); _i0 = (_i0 + 1))
  {
    remapLUT[(_i0 - -768)] = ((alpha * ((float ) (_i0) / 256.0f)) * std::exp(((-(((float ) (_i0) / 256.0f)) * ((float ) (_i0) / 256.0f)) / 2.0f)));
  }

  int off_left = 31;
  int total_pad = 92;

  int _R = R-total_pad;
  int _C = C-total_pad;

  #pragma omp parallel for schedule(static)
  for (int  _i1 = off_left; (_i1 < _R+off_left); _i1 = (_i1 + 1))
  {
    #pragma ivdep
    for (int  _i2 = off_left; (_i2 < _C+off_left); _i2 = (_i2 + 1))
    {
      img[((_i1 * C) + _i2)] = ((((0.299f * img_colour[((((_i1-off_left) * _C * 3)) + (_i2-off_left) * 3 + 2)]) + (0.587f * img_colour[((((_i1-off_left) * _C * 3)) + (_i2-off_left) * 3 + 1)])) + (0.114f * img_colour[((((_i1-off_left) * _C * 3)) + (_i2-off_left) * 3)])))/255.0;
    }
  }

  for (int _i0 = off_left; _i0 < _R+off_left; _i0++)
  {
    for (int _i1 = 0; _i1 < off_left; _i1++)
    {
        img[_i0 * C + _i1] = img[(_i0) * C + off_left];
    }
  }
  for (int _i0 = off_left; _i0 < _R+off_left; _i0++)
  {
    for (int _i1 = _C+off_left; _i1 < C; _i1++)
    {
        img[_i0 * C + _i1] = img[(_i0) * C + (_C+(off_left-1))];
    }
  }

  for (int _i0 = 0; _i0 < off_left; _i0++)
  {
    for (int _i1 = 0; _i1 < off_left; _i1++)
    {
        img[_i0 * C + _i1] = img[off_left * C + off_left];
    }
  }
  for (int _i0 = 0; _i0 < off_left; _i0++)
  {
    for (int _i1 = off_left; _i1 < _C+off_left; _i1++)
    {
        img[_i0 * C + _i1] = img[off_left * C + _i1];
    }
  }
  for (int _i0 = 0; _i0 < off_left; _i0++)
  {
    for (int _i1 = _C+off_left; _i1 < C; _i1++)
    {
        img[_i0 * C + _i1] = img[off_left * C + (_C+(off_left-1))];
    }
  }

  for (int _i0 = _R+off_left; _i0 < R; _i0++)
  {
    for (int _i1 = 0; _i1 < off_left; _i1++)
    {
        img[_i0 * C + _i1] = img[(_R+(off_left-1)) * C + off_left];
    }
  }
  for (int _i0 = _R+off_left; _i0 < R; _i0++)
  {
    for (int _i1 = off_left; _i1 < _C+off_left; _i1++)
    {
        img[_i0 * C + _i1] = img[(_R+(off_left-1)) * C + _i1];
    }
  }
  for (int _i0 = _R+off_left; _i0 < R; _i0++)
  {
    for (int _i1 = _C+off_left; _i1 < C; _i1++)
    {
        img[_i0 * C + _i1] = img[(_R+(off_left-1)) * C + (_C+(off_left-1))];
    }
  }

  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= ((R - 4) / 16)); _T_i1 = (_T_i1 + 1))
  {
    float  Dx_inGPyramid_L1[8][259];
    for (int  _T_i2 = -1; (_T_i2 <= ((C - 2) / 256)); _T_i2 = (_T_i2 + 1))
    {
      int  _ct32613 = ((((8 * _T_i1) + 7) < ((R / 2) - 2))? ((8 * _T_i1) + 7): ((R / 2) - 2));
      int  _ct32614 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
      for (int  _i1 = _ct32614; (_i1 <= _ct32613); _i1 = (_i1 + 1))
      {
        int  _ct32615 = (((C - 2) < ((256 * _T_i2) + 258))? (C - 2): ((256 * _T_i2) + 258));
        int  _ct32616 = ((1 > (256 * _T_i2))? 1: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct32616; (_i2 <= _ct32615); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L1[((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = ((((img[(((-1 + (2 * _i1)) * C) + _i2)] + (3.0f * img[(((2 * _i1) * C) + _i2)])) + (3.0f * img[(((1 + (2 * _i1)) * C) + _i2)])) + img[(((2 + (2 * _i1)) * C) + _i2)]) * 0.125f);
        }
      }
      if ((_T_i2 >= 0))
      {
        int  _ct32617 = ((((8 * _T_i1) + 7) < ((R / 2) - 2))? ((8 * _T_i1) + 7): ((R / 2) - 2));
        int  _ct32618 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
        for (int  _i1 = _ct32618; (_i1 <= _ct32617); _i1 = (_i1 + 1))
        {
          int  _ct32619 = (((C - 4) < ((256 * _T_i2) + 256))? (C - 4): ((256 * _T_i2) + 256));
          #pragma ivdep
          for (int  _i2 = ((256 * _T_i2) + 2); (_i2 <= _ct32619); _i2 = (_i2 + 2))
          {
            D_inGPyramid_L1[(((_i1 - 1) * ((((C / 2) - 2) - 1) + 1)) + ((_i2 / 2) - 1))] = ((((Dx_inGPyramid_L1[((-8 * _T_i1) + _i1)][(-1 + (2 * ((_i2 / 2) - (128 * _T_i2))))] + (3.0f * Dx_inGPyramid_L1[((-8 * _T_i1) + _i1)][(2 * ((_i2 / 2) - (128 * _T_i2)))])) + (3.0f * Dx_inGPyramid_L1[((-8 * _T_i1) + _i1)][(1 + (2 * ((_i2 / 2) - (128 * _T_i2))))])) + Dx_inGPyramid_L1[((-8 * _T_i1) + _i1)][(2 + (2 * ((_i2 / 2) - (128 * _T_i2))))]) * 0.125f);
          }
        }
      }
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
        int  _ct32620 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (768.0f)));
        int  _ct32621 = 0;
        int  _ct32622 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (768.0f))) > 0)? _ct32620: _ct32621);
        int  _ct32623 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (768.0f)));
        int  _ct32624 = 0;
        int  _ct32625 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (768.0f))) > 0)? _ct32623: _ct32624);
        int  _ct32626 = _ct32625;
        int  _ct32627 = 768;
        int  _ct32628 = ((_ct32622 < 768)? _ct32626: _ct32627);
        gPyramid_L0[(((_i0 * (R * C)) + (_i1 * C)) + _i2)] = (((beta * (img[((_i1 * C) + _i2)] - (_i0 * 0.333333333333f))) + (_i0 * 0.333333333333f)) + remapLUT[((_ct32628 - (256 * _i0)) - -768)]);
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= ((R - 8) / 32)); _T_i1 = (_T_i1 + 1))
  {
    float  Dx_inGPyramid_L2[8][259];
    for (int  _T_i2 = -1; (_T_i2 <= ((C - 4) / 512)); _T_i2 = (_T_i2 + 1))
    {
      int  _ct32629 = ((((8 * _T_i1) + 7) < ((R / 4) - 2))? ((8 * _T_i1) + 7): ((R / 4) - 2));
      int  _ct32630 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
      for (int  _i1 = _ct32630; (_i1 <= _ct32629); _i1 = (_i1 + 1))
      {
        int  _ct32631 = ((((256 * _T_i2) + 258) < ((C / 2) - 2))? ((256 * _T_i2) + 258): ((C / 2) - 2));
        int  _ct32632 = ((1 > (256 * _T_i2))? 1: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct32632; (_i2 <= _ct32631); _i2 = (_i2 + 1))
        {
          Dx_inGPyramid_L2[((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = ((((D_inGPyramid_L1[(((-2 + (2 * _i1)) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] + (3.0f * D_inGPyramid_L1[(((-1 + (2 * _i1)) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))])) + (3.0f * D_inGPyramid_L1[(((2 * _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))])) + D_inGPyramid_L1[(((1 + (2 * _i1)) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))]) * 0.125f);
        }
      }
      if ((_T_i2 >= 0))
      {
        int  _ct32633 = ((((8 * _T_i1) + 7) < ((R / 4) - 2))? ((8 * _T_i1) + 7): ((R / 4) - 2));
        int  _ct32634 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
        for (int  _i1 = _ct32634; (_i1 <= _ct32633); _i1 = (_i1 + 1))
        {
          int  _ct32635 = ((((256 * _T_i2) + 256) < ((C / 2) - 4))? ((256 * _T_i2) + 256): ((C / 2) - 4));
          #pragma ivdep
          for (int  _i2 = ((256 * _T_i2) + 2); (_i2 <= _ct32635); _i2 = (_i2 + 2))
          {
            D_inGPyramid_L2[(((_i1 - 1) * ((((C / 4) - 2) - 1) + 1)) + ((_i2 / 2) - 1))] = ((((Dx_inGPyramid_L2[((-8 * _T_i1) + _i1)][(-1 + (2 * ((_i2 / 2) - (128 * _T_i2))))] + (3.0f * Dx_inGPyramid_L2[((-8 * _T_i1) + _i1)][(2 * ((_i2 / 2) - (128 * _T_i2)))])) + (3.0f * Dx_inGPyramid_L2[((-8 * _T_i1) + _i1)][(1 + (2 * ((_i2 / 2) - (128 * _T_i2))))])) + Dx_inGPyramid_L2[((-8 * _T_i1) + _i1)][(2 + (2 * ((_i2 / 2) - (128 * _T_i2))))]) * 0.125f);
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= ((R - 4) / 16)); _T_i1 = (_T_i1 + 1))
  {
    float  Dx_gPyramid_L1[4][8][259];
    for (int  _T_i2 = -1; (_T_i2 <= ((C - 2) / 256)); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct32636 = ((((8 * _T_i1) + 7) < ((R / 2) - 2))? ((8 * _T_i1) + 7): ((R / 2) - 2));
        int  _ct32637 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
        for (int  _i1 = _ct32637; (_i1 <= _ct32636); _i1 = (_i1 + 1))
        {
          int  _ct32638 = (((C - 2) < ((256 * _T_i2) + 258))? (C - 2): ((256 * _T_i2) + 258));
          int  _ct32639 = ((1 > (256 * _T_i2))? 1: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct32639; (_i2 <= _ct32638); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L1[_i0][((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = ((((gPyramid_L0[(((_i0 * (R * C)) + ((-1 + (2 * _i1)) * C)) + _i2)] + (3.0f * gPyramid_L0[(((_i0 * (R * C)) + ((2 * _i1) * C)) + _i2)])) + (3.0f * gPyramid_L0[(((_i0 * (R * C)) + ((1 + (2 * _i1)) * C)) + _i2)])) + gPyramid_L0[(((_i0 * (R * C)) + ((2 + (2 * _i1)) * C)) + _i2)]) * 0.125f);
          }
        }
      }
      if ((_T_i2 >= 0))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct32640 = ((((8 * _T_i1) + 7) < ((R / 2) - 2))? ((8 * _T_i1) + 7): ((R / 2) - 2));
          int  _ct32641 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
          for (int  _i1 = _ct32641; (_i1 <= _ct32640); _i1 = (_i1 + 1))
          {
            int  _ct32642 = (((C - 4) < ((256 * _T_i2) + 256))? (C - 4): ((256 * _T_i2) + 256));
            #pragma ivdep
            for (int  _i2 = ((256 * _T_i2) + 2); (_i2 <= _ct32642); _i2 = (_i2 + 2))
            {
              D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((_i1 - 1) * ((((C / 2) - 2) - 1) + 1))) + ((_i2 / 2) - 1))] = ((((Dx_gPyramid_L1[_i0][((-8 * _T_i1) + _i1)][(-1 + (2 * ((_i2 / 2) - (128 * _T_i2))))] + (3.0f * Dx_gPyramid_L1[_i0][((-8 * _T_i1) + _i1)][(2 * ((_i2 / 2) - (128 * _T_i2)))])) + (3.0f * Dx_gPyramid_L1[_i0][((-8 * _T_i1) + _i1)][(1 + (2 * ((_i2 / 2) - (128 * _T_i2))))])) + Dx_gPyramid_L1[_i0][((-8 * _T_i1) + _i1)][(2 + (2 * ((_i2 / 2) - (128 * _T_i2))))]) * 0.125f);
            }
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= ((R - 8) / 32)); _T_i1 = (_T_i1 + 1))
  {
    float  Dx_gPyramid_L2[4][8][259];
    for (int  _T_i2 = -1; (_T_i2 <= ((C - 4) / 512)); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct32643 = ((((8 * _T_i1) + 7) < ((R / 4) - 2))? ((8 * _T_i1) + 7): ((R / 4) - 2));
        int  _ct32644 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
        for (int  _i1 = _ct32644; (_i1 <= _ct32643); _i1 = (_i1 + 1))
        {
          int  _ct32645 = ((((256 * _T_i2) + 258) < ((C / 2) - 2))? ((256 * _T_i2) + 258): ((C / 2) - 2));
          int  _ct32646 = ((1 > (256 * _T_i2))? 1: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct32646; (_i2 <= _ct32645); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L2[_i0][((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = ((((D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((-2 + (2 * _i1)) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))] + (3.0f * D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((-1 + (2 * _i1)) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))])) + (3.0f * D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((2 * _i1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))])) + D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((1 + (2 * _i1)) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))]) * 0.125f);
          }
        }
      }
      if ((_T_i2 >= 0))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct32647 = ((((8 * _T_i1) + 7) < ((R / 4) - 2))? ((8 * _T_i1) + 7): ((R / 4) - 2));
          int  _ct32648 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
          for (int  _i1 = _ct32648; (_i1 <= _ct32647); _i1 = (_i1 + 1))
          {
            int  _ct32649 = ((((256 * _T_i2) + 256) < ((C / 2) - 4))? ((256 * _T_i2) + 256): ((C / 2) - 4));
            #pragma ivdep
            for (int  _i2 = ((256 * _T_i2) + 2); (_i2 <= _ct32649); _i2 = (_i2 + 2))
            {
              D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((_i1 - 1) * ((((C / 4) - 2) - 1) + 1))) + ((_i2 / 2) - 1))] = ((((Dx_gPyramid_L2[_i0][((-8 * _T_i1) + _i1)][(-1 + (2 * ((_i2 / 2) - (128 * _T_i2))))] + (3.0f * Dx_gPyramid_L2[_i0][((-8 * _T_i1) + _i1)][(2 * ((_i2 / 2) - (128 * _T_i2)))])) + (3.0f * Dx_gPyramid_L2[_i0][((-8 * _T_i1) + _i1)][(1 + (2 * ((_i2 / 2) - (128 * _T_i2))))])) + Dx_gPyramid_L2[_i0][((-8 * _T_i1) + _i1)][(2 + (2 * ((_i2 / 2) - (128 * _T_i2))))]) * 0.125f);
            }
          }
        }
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
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 <= ((R - 16) / 64)); _T_i1 = (_T_i1 + 1))
  {
    float  Dx_gPyramid_L3[4][8][259];
    for (int  _T_i2 = -1; (_T_i2 <= ((C - 8) / 1024)); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct32650 = ((((8 * _T_i1) + 7) < ((R / 8) - 2))? ((8 * _T_i1) + 7): ((R / 8) - 2));
        int  _ct32651 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
        for (int  _i1 = _ct32651; (_i1 <= _ct32650); _i1 = (_i1 + 1))
        {
          int  _ct32652 = ((((256 * _T_i2) + 258) < ((C / 4) - 2))? ((256 * _T_i2) + 258): ((C / 4) - 2));
          int  _ct32653 = ((1 > (256 * _T_i2))? 1: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct32653; (_i2 <= _ct32652); _i2 = (_i2 + 1))
          {
            Dx_gPyramid_L3[_i0][((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = ((((D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((-2 + (2 * _i1)) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))] + (3.0f * D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((-1 + (2 * _i1)) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))])) + (3.0f * D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((2 * _i1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))])) + D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((1 + (2 * _i1)) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))]) * 0.125f);
          }
        }
      }
      if ((_T_i2 >= 0))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct32654 = ((((8 * _T_i1) + 7) < ((R / 8) - 2))? ((8 * _T_i1) + 7): ((R / 8) - 2));
          int  _ct32655 = ((1 > (8 * _T_i1))? 1: (8 * _T_i1));
          for (int  _i1 = _ct32655; (_i1 <= _ct32654); _i1 = (_i1 + 1))
          {
            int  _ct32656 = ((((256 * _T_i2) + 256) < ((C / 4) - 4))? ((256 * _T_i2) + 256): ((C / 4) - 4));
            #pragma ivdep
            for (int  _i2 = ((256 * _T_i2) + 2); (_i2 <= _ct32656); _i2 = (_i2 + 2))
            {
              D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((_i1 - 1) * ((((C / 8) - 2) - 1) + 1))) + ((_i2 / 2) - 1))] = ((((Dx_gPyramid_L3[_i0][((-8 * _T_i1) + _i1)][(-1 + (2 * ((_i2 / 2) - (128 * _T_i2))))] + (3.0f * Dx_gPyramid_L3[_i0][((-8 * _T_i1) + _i1)][(2 * ((_i2 / 2) - (128 * _T_i2)))])) + (3.0f * Dx_gPyramid_L3[_i0][((-8 * _T_i1) + _i1)][(1 + (2 * ((_i2 / 2) - (128 * _T_i2))))])) + Dx_gPyramid_L3[_i0][((-8 * _T_i1) + _i1)][(2 + (2 * ((_i2 / 2) - (128 * _T_i2))))]) * 0.125f);
            }
          }
        }
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
  for (int  _i1 = 1; (_i1 < ((R / 16) - 1)); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 1; (_i2 < ((C / 8) - 1)); _i2 = (_i2 + 1))
    {
      Dx_inGPyramid_L4[(((_i1 - 1) * ((((C / 8) - 2) - 1) + 1)) + (_i2 - 1))] = ((((D_inGPyramid_L3[(((-2 + (2 * _i1)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] + (3.0f * D_inGPyramid_L3[(((-1 + (2 * _i1)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))])) + (3.0f * D_inGPyramid_L3[(((2 * _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))])) + D_inGPyramid_L3[(((1 + (2 * _i1)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))]) * 0.125f);
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
    for (int  _i2 = 1; (_i2 < ((C / 16) - 1)); _i2 = (_i2 + 1))
    {
      D_inGPyramid_L4[(((_i1 - 1) * ((((C / 16) - 2) - 1) + 1)) + (_i2 - 1))] = ((((Dx_inGPyramid_L4[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-2 + (2 * _i2)))] + (3.0f * Dx_inGPyramid_L4[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (-1 + (2 * _i2)))])) + (3.0f * Dx_inGPyramid_L4[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (2 * _i2))])) + Dx_inGPyramid_L4[(((-1 + _i1) * ((((C / 8) - 2) - 1) + 1)) + (1 + (2 * _i2)))]) * 0.125f);
    }
  }
  for (int  _i1 = 1; (_i1 < ((R / 16) - 1)); _i1 = (_i1 + 1))
  {
    for (int  _i2 = 1; (_i2 < ((C / 16) - 1)); _i2 = (_i2 + 1))
    {
      int  _ct32657 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct32658 = 0;
      int  _ct32659 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32657: _ct32658);
      int  _ct32660 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct32661 = 0;
      int  _ct32662 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32660: _ct32661);
      int  _ct32663 = _ct32662;
      int  _ct32664 = 2;
      int  _ct32665 = ((_ct32659 < 2)? _ct32663: _ct32664);
      int  _ct32666 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct32667 = 0;
      int  _ct32668 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32666: _ct32667);
      int  _ct32669 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct32670 = 0;
      int  _ct32671 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32669: _ct32670);
      int  _ct32672 = _ct32671;
      int  _ct32673 = 2;
      int  _ct32674 = ((_ct32668 < 2)? _ct32672: _ct32673);
      int  _ct32675 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct32676 = 0;
      int  _ct32677 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32675: _ct32676);
      int  _ct32678 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct32679 = 0;
      int  _ct32680 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32678: _ct32679);
      int  _ct32681 = _ct32680;
      int  _ct32682 = 2;
      int  _ct32683 = ((_ct32677 < 2)? _ct32681: _ct32682);
      int  _ct32684 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct32685 = 0;
      int  _ct32686 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32684: _ct32685);
      int  _ct32687 = (int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
      int  _ct32688 = 0;
      int  _ct32689 = (((int ) ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32687: _ct32688);
      int  _ct32690 = _ct32689;
      int  _ct32691 = 2;
      int  _ct32692 = ((_ct32686 < 2)? _ct32690: _ct32691);
      outLPyramid_L4[(((_i1 - 1) * (((((C / 16) - 4) + 2) - 1) + 1)) + (_i2 - 1))] = (((1.0f - ((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct32665)) * D_gPyramid_L4[(((_ct32674 * (((((R / 16) - 2) - 1) + 1) * ((((C / 16) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 16) - 2) - 1) + 1))) + (-1 + _i2))]) + (((D_inGPyramid_L4[(((-1 + _i1) * ((((C / 16) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct32683) * D_gPyramid_L4[((((_ct32692 + 1) * (((((R / 16) - 2) - 1) + 1) * ((((C / 16) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 16) - 2) - 1) + 1))) + (-1 + _i2))]));
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
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = -1; (_T_i1 < (((R + 16) / 32) - 1)); _T_i1 = (_T_i1 + 1))
  {
    float  U_lPyramid_L3[4][10][256];
    float  outLPyramid_L3[10][256];
    float  outGPyramid_L3[10][256];
    for (int  _T_i2 = 0; (_T_i2 <= ((C - 48) / 2048)); _T_i2 = (_T_i2 + 1))
    {
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct32693 = ((((8 * _T_i1) + 18) < ((R / 4) - 12))? ((8 * _T_i1) + 18): ((R / 4) - 12));
        int  _ct32694 = ((6 > (8 * _T_i1))? 6: (8 * _T_i1));
        for (int  _i1 = _ct32694; (_i1 <= _ct32693); _i1 = (_i1 + 2))
        {
          int  _ct32695 = ((((256 * _T_i2) + 255) < ((C / 8) - 6))? ((256 * _T_i2) + 255): ((C / 8) - 6));
          int  _ct32696 = ((3 > (256 * _T_i2))? 3: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct32696; (_i2 <= _ct32695); _i2 = (_i2 + 1))
          {
            float  _ct32697 = ((0.25f * Ux_lPyramid_L3[(((_i0 * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((-3 + (_i1 / 2)) * (((((C / 16) - 4) + 2) - 1) + 1))) + (((_i2 / 2) - 1) - 1))]) + (0.75f * Ux_lPyramid_L3[(((_i0 * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((-3 + (_i1 / 2)) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((_i2 / 2) - 1))]));
            float  _ct32698 = ((0.25f * Ux_lPyramid_L3[(((_i0 * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((-3 + (_i1 / 2)) * (((((C / 16) - 4) + 2) - 1) + 1))) + (((_i2 / 2) + 1) - 1))]) + (0.75f * Ux_lPyramid_L3[(((_i0 * ((((((R / 8) - 8) + 2) - 3) + 1) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((-3 + (_i1 / 2)) * (((((C / 16) - 4) + 2) - 1) + 1))) + ((_i2 / 2) - 1))]));
            float  _ct32699 = (((_i2 % 2) == 0)? _ct32697: _ct32698);
            U_lPyramid_L3[_i0][((_i1 / 2) - (4 * _T_i1))][((-256 * _T_i2) + _i2)] = (D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1))) + (-1 + _i2))] - _ct32699);
          }
        }
      }
      int  _ct32700 = ((((8 * _T_i1) + 16) < ((R / 4) - 12))? ((8 * _T_i1) + 16): ((R / 4) - 12));
      int  _ct32701 = ((6 > ((8 * _T_i1) + 2))? 6: ((8 * _T_i1) + 2));
      for (int  _i1 = _ct32701; (_i1 <= _ct32700); _i1 = (_i1 + 2))
      {
        int  _ct32702 = ((((256 * _T_i2) + 255) < ((C / 8) - 6))? ((256 * _T_i2) + 255): ((C / 8) - 6));
        int  _ct32703 = ((3 > (256 * _T_i2))? 3: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct32703; (_i2 <= _ct32702); _i2 = (_i2 + 1))
        {
          int  _ct32704 = (int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32705 = 0;
          int  _ct32706 = (((int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32704: _ct32705);
          int  _ct32707 = (int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32708 = 0;
          int  _ct32709 = (((int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32707: _ct32708);
          int  _ct32710 = _ct32709;
          int  _ct32711 = 2;
          int  _ct32712 = ((_ct32706 < 2)? _ct32710: _ct32711);
          int  _ct32713 = (int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32714 = 0;
          int  _ct32715 = (((int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32713: _ct32714);
          int  _ct32716 = (int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32717 = 0;
          int  _ct32718 = (((int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32716: _ct32717);
          int  _ct32719 = _ct32718;
          int  _ct32720 = 2;
          int  _ct32721 = ((_ct32715 < 2)? _ct32719: _ct32720);
          int  _ct32722 = (int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32723 = 0;
          int  _ct32724 = (((int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32722: _ct32723);
          int  _ct32725 = (int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32726 = 0;
          int  _ct32727 = (((int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32725: _ct32726);
          int  _ct32728 = _ct32727;
          int  _ct32729 = 2;
          int  _ct32730 = ((_ct32724 < 2)? _ct32728: _ct32729);
          int  _ct32731 = (int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32732 = 0;
          int  _ct32733 = (((int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32731: _ct32732);
          int  _ct32734 = (int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32735 = 0;
          int  _ct32736 = (((int ) ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32734: _ct32735);
          int  _ct32737 = _ct32736;
          int  _ct32738 = 2;
          int  _ct32739 = ((_ct32733 < 2)? _ct32737: _ct32738);
          outLPyramid_L3[((_i1 / 2) - (4 * _T_i1))][((-256 * _T_i2) + _i2)] = (((1.0f - ((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct32712)) * U_lPyramid_L3[_ct32721][((_i1 / 2) - (4 * _T_i1))][((-256 * _T_i2) + _i2)]) + (((D_inGPyramid_L3[(((-1 + (_i1 / 2)) * ((((C / 8) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct32730) * U_lPyramid_L3[(_ct32739 + 1)][((_i1 / 2) - (4 * _T_i1))][((-256 * _T_i2) + _i2)]));
        }
      }
      int  _ct32740 = ((((8 * _T_i1) + 14) < ((R / 4) - 12))? ((8 * _T_i1) + 14): ((R / 4) - 12));
      int  _ct32741 = ((6 > ((8 * _T_i1) + 4))? 6: ((8 * _T_i1) + 4));
      for (int  _i1 = _ct32741; (_i1 <= _ct32740); _i1 = (_i1 + 2))
      {
        int  _ct32742 = ((((256 * _T_i2) + 255) < ((C / 8) - 6))? ((256 * _T_i2) + 255): ((C / 8) - 6));
        int  _ct32743 = ((3 > (256 * _T_i2))? 3: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct32743; (_i2 <= _ct32742); _i2 = (_i2 + 1))
        {
          float  _ct32744 = ((0.25f * Ux_outGPyramid_L3[(((-3 + (_i1 / 2)) * (((((C / 16) - 4) + 2) - 1) + 1)) + (((_i2 / 2) - 1) - 1))]) + (0.75f * Ux_outGPyramid_L3[(((-3 + (_i1 / 2)) * (((((C / 16) - 4) + 2) - 1) + 1)) + ((_i2 / 2) - 1))]));
          float  _ct32745 = ((0.25f * Ux_outGPyramid_L3[(((-3 + (_i1 / 2)) * (((((C / 16) - 4) + 2) - 1) + 1)) + (((_i2 / 2) + 1) - 1))]) + (0.75f * Ux_outGPyramid_L3[(((-3 + (_i1 / 2)) * (((((C / 16) - 4) + 2) - 1) + 1)) + ((_i2 / 2) - 1))]));
          float  _ct32746 = (((_i2 % 2) == 0)? _ct32744: _ct32745);
          outGPyramid_L3[((_i1 / 2) - (4 * _T_i1))][((-256 * _T_i2) + _i2)] = (outLPyramid_L3[((_i1 / 2) - (4 * _T_i1))][((-256 * _T_i2) + _i2)] + _ct32746);
        }
      }
      int  _ct32747 = ((((8 * _T_i1) + 12) < ((R / 4) - 14))? ((8 * _T_i1) + 12): ((R / 4) - 14));
      int  _ct32748 = ((8 > ((8 * _T_i1) + 6))? 8: ((8 * _T_i1) + 6));
      for (int  _i1 = _ct32748; (_i1 <= _ct32747); _i1 = (_i1 + 2))
      {
        int  _ct32749 = ((((256 * _T_i2) + 255) < ((C / 8) - 6))? ((256 * _T_i2) + 255): ((C / 8) - 6));
        int  _ct32750 = ((3 > (256 * _T_i2))? 3: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct32750; (_i2 <= _ct32749); _i2 = (_i2 + 1))
        {
          Ux_outGPyramid_L2[(((_i1 - 7) * (((((C / 8) - 8) + 2) - 3) + 1)) + (_i2 - 3))] = ((0.25f * outGPyramid_L3[((((-8 * _T_i1) + _i1) / 2) - 1)][((-256 * _T_i2) + _i2)]) + (0.75f * outGPyramid_L3[(((-8 * _T_i1) + _i1) / 2)][((-256 * _T_i2) + _i2)]));
        }
      }
      if ((_T_i1 >= 0))
      {
        int  _ct32751 = ((((8 * _T_i1) + 13) < ((R / 4) - 14))? ((8 * _T_i1) + 13): ((R / 4) - 14));
        for (int  _i1 = ((8 * _T_i1) + 7); (_i1 <= _ct32751); _i1 = (_i1 + 2))
        {
          int  _ct32752 = ((((256 * _T_i2) + 255) < ((C / 8) - 6))? ((256 * _T_i2) + 255): ((C / 8) - 6));
          int  _ct32753 = ((3 > (256 * _T_i2))? 3: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct32753; (_i2 <= _ct32752); _i2 = (_i2 + 1))
          {
            Ux_outGPyramid_L2[(((_i1 - 7) * (((((C / 8) - 8) + 2) - 3) + 1)) + (_i2 - 3))] = ((0.25f * outGPyramid_L3[((((-8 * _T_i1) + _i1) / 2) + 1)][((-256 * _T_i2) + _i2)]) + (0.75f * outGPyramid_L3[(((-8 * _T_i1) + _i1) / 2)][((-256 * _T_i2) + _i2)]));
          }
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 0; (_T_i1 < (((R + 8) / 32) - 1)); _T_i1 = (_T_i1 + 1))
  {
    float  Ux_lPyramid_L2[4][8][131];
    float  U_lPyramid_L2[4][8][262];
    float  outLPyramid_L2[8][262];
    for (int  _T_i2 = 0; (_T_i2 <= ((C - 48) / 1024)); _T_i2 = (_T_i2 + 1))
    {
      if ((_T_i1 >= 1))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct32754 = ((((8 * _T_i1) + 6) < ((R / 4) - 14))? ((8 * _T_i1) + 6): ((R / 4) - 14));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct32754); _i1 = (_i1 + 2))
          {
            int  _ct32755 = ((((256 * _T_i2) + 260) < ((C / 4) - 12))? ((256 * _T_i2) + 260): ((C / 4) - 12));
            int  _ct32756 = ((6 > (256 * _T_i2))? 6: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct32756; (_i2 <= _ct32755); _i2 = (_i2 + 2))
            {
              Ux_lPyramid_L2[_i0][((-8 * _T_i1) + _i1)][((_i2 / 2) - (128 * _T_i2))] = ((0.25f * D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((((_i1 / 2) - 1) - 1) * ((((C / 8) - 2) - 1) + 1))) + (-1 + (_i2 / 2)))]) + (0.75f * D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + (((_i1 / 2) - 1) * ((((C / 8) - 2) - 1) + 1))) + (-1 + (_i2 / 2)))]));
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct32757 = ((((8 * _T_i1) + 7) < ((R / 4) - 14))? ((8 * _T_i1) + 7): ((R / 4) - 14));
        int  _ct32758 = ((7 > ((8 * _T_i1) + 1))? 7: ((8 * _T_i1) + 1));
        for (int  _i1 = _ct32758; (_i1 <= _ct32757); _i1 = (_i1 + 2))
        {
          int  _ct32759 = ((((256 * _T_i2) + 260) < ((C / 4) - 12))? ((256 * _T_i2) + 260): ((C / 4) - 12));
          int  _ct32760 = ((6 > (256 * _T_i2))? 6: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct32760; (_i2 <= _ct32759); _i2 = (_i2 + 2))
          {
            Ux_lPyramid_L2[_i0][((-8 * _T_i1) + _i1)][((_i2 / 2) - (128 * _T_i2))] = ((0.25f * D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + ((((_i1 / 2) + 1) - 1) * ((((C / 8) - 2) - 1) + 1))) + (-1 + (_i2 / 2)))]) + (0.75f * D_gPyramid_L3[(((_i0 * (((((R / 8) - 2) - 1) + 1) * ((((C / 8) - 2) - 1) + 1))) + (((_i1 / 2) - 1) * ((((C / 8) - 2) - 1) + 1))) + (-1 + (_i2 / 2)))]));
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct32761 = ((((8 * _T_i1) + 7) < ((R / 4) - 14))? ((8 * _T_i1) + 7): ((R / 4) - 14));
        int  _ct32762 = ((7 > (8 * _T_i1))? 7: (8 * _T_i1));
        for (int  _i1 = _ct32762; (_i1 <= _ct32761); _i1 = (_i1 + 1))
        {
          int  _ct32763 = ((((256 * _T_i2) + 260) < ((C / 4) - 14))? ((256 * _T_i2) + 260): ((C / 4) - 14));
          int  _ct32764 = ((7 > ((256 * _T_i2) + 1))? 7: ((256 * _T_i2) + 1));
          #pragma ivdep
          for (int  _i2 = _ct32764; (_i2 <= _ct32763); _i2 = (_i2 + 1))
          {
            float  _ct32765 = ((0.25f * Ux_lPyramid_L2[_i0][((-8 * _T_i1) + _i1)][((((-256 * _T_i2) + _i2) / 2) - 1)]) + (0.75f * Ux_lPyramid_L2[_i0][((-8 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)]));
            float  _ct32766 = ((0.25f * Ux_lPyramid_L2[_i0][((-8 * _T_i1) + _i1)][((((-256 * _T_i2) + _i2) / 2) + 1)]) + (0.75f * Ux_lPyramid_L2[_i0][((-8 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)]));
            float  _ct32767 = (((_i2 % 2) == 0)? _ct32765: _ct32766);
            U_lPyramid_L2[_i0][((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = (D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + _i2))] - _ct32767);
          }
        }
      }
      int  _ct32768 = ((((8 * _T_i1) + 7) < ((R / 4) - 14))? ((8 * _T_i1) + 7): ((R / 4) - 14));
      int  _ct32769 = ((7 > (8 * _T_i1))? 7: (8 * _T_i1));
      for (int  _i1 = _ct32769; (_i1 <= _ct32768); _i1 = (_i1 + 1))
      {
        int  _ct32770 = ((((256 * _T_i2) + 259) < ((C / 4) - 14))? ((256 * _T_i2) + 259): ((C / 4) - 14));
        int  _ct32771 = ((7 > ((256 * _T_i2) + 2))? 7: ((256 * _T_i2) + 2));
        #pragma ivdep
        for (int  _i2 = _ct32771; (_i2 <= _ct32770); _i2 = (_i2 + 1))
        {
          int  _ct32772 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32773 = 0;
          int  _ct32774 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32772: _ct32773);
          int  _ct32775 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32776 = 0;
          int  _ct32777 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32775: _ct32776);
          int  _ct32778 = _ct32777;
          int  _ct32779 = 2;
          int  _ct32780 = ((_ct32774 < 2)? _ct32778: _ct32779);
          int  _ct32781 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32782 = 0;
          int  _ct32783 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32781: _ct32782);
          int  _ct32784 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32785 = 0;
          int  _ct32786 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32784: _ct32785);
          int  _ct32787 = _ct32786;
          int  _ct32788 = 2;
          int  _ct32789 = ((_ct32783 < 2)? _ct32787: _ct32788);
          int  _ct32790 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32791 = 0;
          int  _ct32792 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32790: _ct32791);
          int  _ct32793 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32794 = 0;
          int  _ct32795 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32793: _ct32794);
          int  _ct32796 = _ct32795;
          int  _ct32797 = 2;
          int  _ct32798 = ((_ct32792 < 2)? _ct32796: _ct32797);
          int  _ct32799 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32800 = 0;
          int  _ct32801 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32799: _ct32800);
          int  _ct32802 = (int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32803 = 0;
          int  _ct32804 = (((int ) ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32802: _ct32803);
          int  _ct32805 = _ct32804;
          int  _ct32806 = 2;
          int  _ct32807 = ((_ct32801 < 2)? _ct32805: _ct32806);
          outLPyramid_L2[((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = (((1.0f - ((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct32780)) * U_lPyramid_L2[_ct32789][((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)]) + (((D_inGPyramid_L2[(((-1 + _i1) * ((((C / 4) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct32798) * U_lPyramid_L2[(_ct32807 + 1)][((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)]));
        }
      }
      int  _ct32808 = ((((8 * _T_i1) + 7) < ((R / 4) - 14))? ((8 * _T_i1) + 7): ((R / 4) - 14));
      int  _ct32809 = ((7 > (8 * _T_i1))? 7: (8 * _T_i1));
      for (int  _i1 = _ct32809; (_i1 <= _ct32808); _i1 = (_i1 + 1))
      {
        int  _ct32810 = ((((256 * _T_i2) + 258) < ((C / 4) - 14))? ((256 * _T_i2) + 258): ((C / 4) - 14));
        int  _ct32811 = ((7 > ((256 * _T_i2) + 3))? 7: ((256 * _T_i2) + 3));
        #pragma ivdep
        for (int  _i2 = _ct32811; (_i2 <= _ct32810); _i2 = (_i2 + 1))
        {
          float  _ct32812 = ((0.25f * Ux_outGPyramid_L2[(((-7 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1)) + (((_i2 / 2) - 1) - 3))]) + (0.75f * Ux_outGPyramid_L2[(((-7 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1)) + ((_i2 / 2) - 3))]));
          float  _ct32813 = ((0.25f * Ux_outGPyramid_L2[(((-7 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1)) + (((_i2 / 2) + 1) - 3))]) + (0.75f * Ux_outGPyramid_L2[(((-7 + _i1) * (((((C / 8) - 8) + 2) - 3) + 1)) + ((_i2 / 2) - 3))]));
          float  _ct32814 = (((_i2 % 2) == 0)? _ct32812: _ct32813);
          outGPyramid_L2[(((_i1 - 7) * (((((C / 4) - 16) + 2) - 7) + 1)) + (_i2 - 7))] = (outLPyramid_L2[((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] + _ct32814);
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 1; (_T_i1 < (((R + 4) / 16) - 3)); _T_i1 = (_T_i1 + 1))
  {
    float  Ux_lPyramid_L1[4][8][131];
    float  Ux_outGPyramid_L1[8][131];
    float  U_lPyramid_L1[4][8][262];
    float  outLPyramid_L1[8][262];
    for (int  _T_i2 = 0; (_T_i2 <= ((C - 56) / 512)); _T_i2 = (_T_i2 + 1))
    {
      if ((_T_i1 >= 2))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct32815 = ((((8 * _T_i1) + 6) < ((R / 2) - 30))? ((8 * _T_i1) + 6): ((R / 2) - 30));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct32815); _i1 = (_i1 + 2))
          {
            int  _ct32816 = ((((256 * _T_i2) + 260) < ((C / 2) - 28))? ((256 * _T_i2) + 260): ((C / 2) - 28));
            int  _ct32817 = ((14 > (256 * _T_i2))? 14: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct32817; (_i2 <= _ct32816); _i2 = (_i2 + 2))
            {
              Ux_lPyramid_L1[_i0][((-8 * _T_i1) + _i1)][((_i2 / 2) - (128 * _T_i2))] = ((0.25f * D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((((_i1 / 2) - 1) - 1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + (_i2 / 2)))]) + (0.75f * D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + (((_i1 / 2) - 1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + (_i2 / 2)))]));
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct32818 = ((((8 * _T_i1) + 7) < ((R / 2) - 30))? ((8 * _T_i1) + 7): ((R / 2) - 30));
        int  _ct32819 = ((15 > ((8 * _T_i1) + 1))? 15: ((8 * _T_i1) + 1));
        for (int  _i1 = _ct32819; (_i1 <= _ct32818); _i1 = (_i1 + 2))
        {
          int  _ct32820 = ((((256 * _T_i2) + 260) < ((C / 2) - 28))? ((256 * _T_i2) + 260): ((C / 2) - 28));
          int  _ct32821 = ((14 > (256 * _T_i2))? 14: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct32821; (_i2 <= _ct32820); _i2 = (_i2 + 2))
          {
            Ux_lPyramid_L1[_i0][((-8 * _T_i1) + _i1)][((_i2 / 2) - (128 * _T_i2))] = ((0.25f * D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + ((((_i1 / 2) + 1) - 1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + (_i2 / 2)))]) + (0.75f * D_gPyramid_L2[(((_i0 * (((((R / 4) - 2) - 1) + 1) * ((((C / 4) - 2) - 1) + 1))) + (((_i1 / 2) - 1) * ((((C / 4) - 2) - 1) + 1))) + (-1 + (_i2 / 2)))]));
          }
        }
      }
      if ((_T_i1 >= 2))
      {
        int  _ct32822 = ((((8 * _T_i1) + 6) < ((R / 2) - 30))? ((8 * _T_i1) + 6): ((R / 2) - 30));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct32822); _i1 = (_i1 + 2))
        {
          int  _ct32823 = ((((256 * _T_i2) + 260) < ((C / 2) - 28))? ((256 * _T_i2) + 260): ((C / 2) - 28));
          int  _ct32824 = ((14 > (256 * _T_i2))? 14: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct32824; (_i2 <= _ct32823); _i2 = (_i2 + 2))
          {
            Ux_outGPyramid_L1[((-8 * _T_i1) + _i1)][((_i2 / 2) - (128 * _T_i2))] = ((0.25f * outGPyramid_L2[(((((_i1 / 2) - 1) - 7) * (((((C / 4) - 16) + 2) - 7) + 1)) + (-7 + (_i2 / 2)))]) + (0.75f * outGPyramid_L2[((((_i1 / 2) - 7) * (((((C / 4) - 16) + 2) - 7) + 1)) + (-7 + (_i2 / 2)))]));
          }
        }
      }
      int  _ct32825 = ((((8 * _T_i1) + 7) < ((R / 2) - 30))? ((8 * _T_i1) + 7): ((R / 2) - 30));
      int  _ct32826 = ((15 > ((8 * _T_i1) + 1))? 15: ((8 * _T_i1) + 1));
      for (int  _i1 = _ct32826; (_i1 <= _ct32825); _i1 = (_i1 + 2))
      {
        int  _ct32827 = ((((256 * _T_i2) + 260) < ((C / 2) - 28))? ((256 * _T_i2) + 260): ((C / 2) - 28));
        int  _ct32828 = ((14 > (256 * _T_i2))? 14: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct32828; (_i2 <= _ct32827); _i2 = (_i2 + 2))
        {
          Ux_outGPyramid_L1[((-8 * _T_i1) + _i1)][((_i2 / 2) - (128 * _T_i2))] = ((0.25f * outGPyramid_L2[(((((_i1 / 2) + 1) - 7) * (((((C / 4) - 16) + 2) - 7) + 1)) + (-7 + (_i2 / 2)))]) + (0.75f * outGPyramid_L2[((((_i1 / 2) - 7) * (((((C / 4) - 16) + 2) - 7) + 1)) + (-7 + (_i2 / 2)))]));
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct32829 = ((((8 * _T_i1) + 7) < ((R / 2) - 30))? ((8 * _T_i1) + 7): ((R / 2) - 30));
        int  _ct32830 = ((15 > (8 * _T_i1))? 15: (8 * _T_i1));
        for (int  _i1 = _ct32830; (_i1 <= _ct32829); _i1 = (_i1 + 1))
        {
          int  _ct32831 = ((((256 * _T_i2) + 260) < ((C / 2) - 30))? ((256 * _T_i2) + 260): ((C / 2) - 30));
          int  _ct32832 = ((15 > ((256 * _T_i2) + 1))? 15: ((256 * _T_i2) + 1));
          #pragma ivdep
          for (int  _i2 = _ct32832; (_i2 <= _ct32831); _i2 = (_i2 + 1))
          {
            float  _ct32833 = ((0.25f * Ux_lPyramid_L1[_i0][((-8 * _T_i1) + _i1)][((((-256 * _T_i2) + _i2) / 2) - 1)]) + (0.75f * Ux_lPyramid_L1[_i0][((-8 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)]));
            float  _ct32834 = ((0.25f * Ux_lPyramid_L1[_i0][((-8 * _T_i1) + _i1)][((((-256 * _T_i2) + _i2) / 2) + 1)]) + (0.75f * Ux_lPyramid_L1[_i0][((-8 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)]));
            float  _ct32835 = (((_i2 % 2) == 0)? _ct32833: _ct32834);
            U_lPyramid_L1[_i0][((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = (D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((-1 + _i1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + _i2))] - _ct32835);
          }
        }
      }
      int  _ct32836 = ((((8 * _T_i1) + 7) < ((R / 2) - 30))? ((8 * _T_i1) + 7): ((R / 2) - 30));
      int  _ct32837 = ((15 > (8 * _T_i1))? 15: (8 * _T_i1));
      for (int  _i1 = _ct32837; (_i1 <= _ct32836); _i1 = (_i1 + 1))
      {
        int  _ct32838 = ((((256 * _T_i2) + 259) < ((C / 2) - 30))? ((256 * _T_i2) + 259): ((C / 2) - 30));
        int  _ct32839 = ((15 > ((256 * _T_i2) + 2))? 15: ((256 * _T_i2) + 2));
        #pragma ivdep
        for (int  _i2 = _ct32839; (_i2 <= _ct32838); _i2 = (_i2 + 1))
        {
          int  _ct32840 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32841 = 0;
          int  _ct32842 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32840: _ct32841);
          int  _ct32843 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32844 = 0;
          int  _ct32845 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32843: _ct32844);
          int  _ct32846 = _ct32845;
          int  _ct32847 = 2;
          int  _ct32848 = ((_ct32842 < 2)? _ct32846: _ct32847);
          int  _ct32849 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32850 = 0;
          int  _ct32851 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32849: _ct32850);
          int  _ct32852 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32853 = 0;
          int  _ct32854 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32852: _ct32853);
          int  _ct32855 = _ct32854;
          int  _ct32856 = 2;
          int  _ct32857 = ((_ct32851 < 2)? _ct32855: _ct32856);
          int  _ct32858 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32859 = 0;
          int  _ct32860 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32858: _ct32859);
          int  _ct32861 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32862 = 0;
          int  _ct32863 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32861: _ct32862);
          int  _ct32864 = _ct32863;
          int  _ct32865 = 2;
          int  _ct32866 = ((_ct32860 < 2)? _ct32864: _ct32865);
          int  _ct32867 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32868 = 0;
          int  _ct32869 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32867: _ct32868);
          int  _ct32870 = (int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)));
          int  _ct32871 = 0;
          int  _ct32872 = (((int ) ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3))) > 0)? _ct32870: _ct32871);
          int  _ct32873 = _ct32872;
          int  _ct32874 = 2;
          int  _ct32875 = ((_ct32869 < 2)? _ct32873: _ct32874);
          outLPyramid_L1[((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = (((1.0f - ((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct32848)) * U_lPyramid_L1[_ct32857][((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)]) + (((D_inGPyramid_L1[(((-1 + _i1) * ((((C / 2) - 2) - 1) + 1)) + (-1 + _i2))] * (float ) (3)) - _ct32866) * U_lPyramid_L1[(_ct32875 + 1)][((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)]));
        }
      }
      int  _ct32876 = ((((8 * _T_i1) + 7) < ((R / 2) - 30))? ((8 * _T_i1) + 7): ((R / 2) - 30));
      int  _ct32877 = ((15 > (8 * _T_i1))? 15: (8 * _T_i1));
      for (int  _i1 = _ct32877; (_i1 <= _ct32876); _i1 = (_i1 + 1))
      {
        int  _ct32878 = ((((256 * _T_i2) + 258) < ((C / 2) - 30))? ((256 * _T_i2) + 258): ((C / 2) - 30));
        int  _ct32879 = ((15 > ((256 * _T_i2) + 3))? 15: ((256 * _T_i2) + 3));
        #pragma ivdep
        for (int  _i2 = _ct32879; (_i2 <= _ct32878); _i2 = (_i2 + 1))
        {
          float  _ct32880 = ((0.25f * Ux_outGPyramid_L1[((-8 * _T_i1) + _i1)][((((-256 * _T_i2) + _i2) / 2) - 1)]) + (0.75f * Ux_outGPyramid_L1[((-8 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)]));
          float  _ct32881 = ((0.25f * Ux_outGPyramid_L1[((-8 * _T_i1) + _i1)][((((-256 * _T_i2) + _i2) / 2) + 1)]) + (0.75f * Ux_outGPyramid_L1[((-8 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)]));
          float  _ct32882 = (((_i2 % 2) == 0)? _ct32880: _ct32881);
          outGPyramid_L1[(((_i1 - 15) * (((((C / 2) - 32) + 2) - 15) + 1)) + (_i2 - 15))] = (outLPyramid_L1[((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] + _ct32882);
        }
      }
    }
  }
  #pragma omp parallel for schedule(static)
  for (int  _T_i1 = 3; (_T_i1 < (((R + 2) / 8) - 7)); _T_i1 = (_T_i1 + 1))
  {
    float  Ux_lPyramid_L0[4][8][131];
    float  Ux_result_ref_gray[8][131];
    float  U_lPyramid_L0[4][8][262];
    float  outLPyramid_L0[8][262];
    for (int  _T_i2 = 0; (_T_i2 <= ((C - 60) / 256)); _T_i2 = (_T_i2 + 1))
    {
      if ((_T_i1 >= 4))
      {
        for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
        {
          int  _ct32883 = (((R - 62) < ((8 * _T_i1) + 6))? (R - 62): ((8 * _T_i1) + 6));
          for (int  _i1 = (8 * _T_i1); (_i1 <= _ct32883); _i1 = (_i1 + 2))
          {
            int  _ct32884 = (((C - 60) < ((256 * _T_i2) + 260))? (C - 60): ((256 * _T_i2) + 260));
            int  _ct32885 = ((30 > (256 * _T_i2))? 30: (256 * _T_i2));
            #pragma ivdep
            for (int  _i2 = _ct32885; (_i2 <= _ct32884); _i2 = (_i2 + 2))
            {
              Ux_lPyramid_L0[_i0][((-8 * _T_i1) + _i1)][((_i2 / 2) - (128 * _T_i2))] = ((0.25f * D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((((_i1 / 2) - 1) - 1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + (_i2 / 2)))]) + (0.75f * D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + (((_i1 / 2) - 1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + (_i2 / 2)))]));
            }
          }
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct32886 = (((R - 62) < ((8 * _T_i1) + 7))? (R - 62): ((8 * _T_i1) + 7));
        int  _ct32887 = ((31 > ((8 * _T_i1) + 1))? 31: ((8 * _T_i1) + 1));
        for (int  _i1 = _ct32887; (_i1 <= _ct32886); _i1 = (_i1 + 2))
        {
          int  _ct32888 = (((C - 60) < ((256 * _T_i2) + 260))? (C - 60): ((256 * _T_i2) + 260));
          int  _ct32889 = ((30 > (256 * _T_i2))? 30: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct32889; (_i2 <= _ct32888); _i2 = (_i2 + 2))
          {
            Ux_lPyramid_L0[_i0][((-8 * _T_i1) + _i1)][((_i2 / 2) - (128 * _T_i2))] = ((0.25f * D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + ((((_i1 / 2) + 1) - 1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + (_i2 / 2)))]) + (0.75f * D_gPyramid_L1[(((_i0 * (((((R / 2) - 2) - 1) + 1) * ((((C / 2) - 2) - 1) + 1))) + (((_i1 / 2) - 1) * ((((C / 2) - 2) - 1) + 1))) + (-1 + (_i2 / 2)))]));
          }
        }
      }
      if ((_T_i1 >= 4))
      {
        int  _ct32890 = (((R - 62) < ((8 * _T_i1) + 6))? (R - 62): ((8 * _T_i1) + 6));
        for (int  _i1 = (8 * _T_i1); (_i1 <= _ct32890); _i1 = (_i1 + 2))
        {
          int  _ct32891 = (((C - 60) < ((256 * _T_i2) + 260))? (C - 60): ((256 * _T_i2) + 260));
          int  _ct32892 = ((30 > (256 * _T_i2))? 30: (256 * _T_i2));
          #pragma ivdep
          for (int  _i2 = _ct32892; (_i2 <= _ct32891); _i2 = (_i2 + 2))
          {
            Ux_result_ref_gray[((-8 * _T_i1) + _i1)][((_i2 / 2) - (128 * _T_i2))] = ((0.25f * outGPyramid_L1[(((((_i1 / 2) - 1) - 15) * (((((C / 2) - 32) + 2) - 15) + 1)) + (-15 + (_i2 / 2)))]) + (0.75f * outGPyramid_L1[((((_i1 / 2) - 15) * (((((C / 2) - 32) + 2) - 15) + 1)) + (-15 + (_i2 / 2)))]));
          }
        }
      }
      int  _ct32893 = (((R - 62) < ((8 * _T_i1) + 7))? (R - 62): ((8 * _T_i1) + 7));
      int  _ct32894 = ((31 > ((8 * _T_i1) + 1))? 31: ((8 * _T_i1) + 1));
      for (int  _i1 = _ct32894; (_i1 <= _ct32893); _i1 = (_i1 + 2))
      {
        int  _ct32895 = (((C - 60) < ((256 * _T_i2) + 260))? (C - 60): ((256 * _T_i2) + 260));
        int  _ct32896 = ((30 > (256 * _T_i2))? 30: (256 * _T_i2));
        #pragma ivdep
        for (int  _i2 = _ct32896; (_i2 <= _ct32895); _i2 = (_i2 + 2))
        {
          Ux_result_ref_gray[((-8 * _T_i1) + _i1)][((_i2 / 2) - (128 * _T_i2))] = ((0.25f * outGPyramid_L1[(((((_i1 / 2) + 1) - 15) * (((((C / 2) - 32) + 2) - 15) + 1)) + (-15 + (_i2 / 2)))]) + (0.75f * outGPyramid_L1[((((_i1 / 2) - 15) * (((((C / 2) - 32) + 2) - 15) + 1)) + (-15 + (_i2 / 2)))]));
        }
      }
      for (int  _i0 = 0; (_i0 <= 3); _i0 = (_i0 + 1))
      {
        int  _ct32897 = (((R - 62) < ((8 * _T_i1) + 7))? (R - 62): ((8 * _T_i1) + 7));
        int  _ct32898 = ((31 > (8 * _T_i1))? 31: (8 * _T_i1));
        for (int  _i1 = _ct32898; (_i1 <= _ct32897); _i1 = (_i1 + 1))
        {
          int  _ct32899 = (((C - 62) < ((256 * _T_i2) + 260))? (C - 62): ((256 * _T_i2) + 260));
          int  _ct32900 = ((31 > ((256 * _T_i2) + 1))? 31: ((256 * _T_i2) + 1));
          #pragma ivdep
          for (int  _i2 = _ct32900; (_i2 <= _ct32899); _i2 = (_i2 + 1))
          {
            float  _ct32901 = ((0.25f * Ux_lPyramid_L0[_i0][((-8 * _T_i1) + _i1)][((((-256 * _T_i2) + _i2) / 2) - 1)]) + (0.75f * Ux_lPyramid_L0[_i0][((-8 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)]));
            float  _ct32902 = ((0.25f * Ux_lPyramid_L0[_i0][((-8 * _T_i1) + _i1)][((((-256 * _T_i2) + _i2) / 2) + 1)]) + (0.75f * Ux_lPyramid_L0[_i0][((-8 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)]));
            float  _ct32903 = (((_i2 % 2) == 0)? _ct32901: _ct32902);
            U_lPyramid_L0[_i0][((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = (gPyramid_L0[(((_i0 * (R * C)) + (_i1 * C)) + _i2)] - _ct32903);
          }
        }
      }
      int  _ct32904 = (((R - 62) < ((8 * _T_i1) + 7))? (R - 62): ((8 * _T_i1) + 7));
      int  _ct32905 = ((31 > (8 * _T_i1))? 31: (8 * _T_i1));
      for (int  _i1 = _ct32905; (_i1 <= _ct32904); _i1 = (_i1 + 1))
      {
        int  _ct32906 = (((C - 62) < ((256 * _T_i2) + 259))? (C - 62): ((256 * _T_i2) + 259));
        int  _ct32907 = ((31 > ((256 * _T_i2) + 2))? 31: ((256 * _T_i2) + 2));
        #pragma ivdep
        for (int  _i2 = _ct32907; (_i2 <= _ct32906); _i2 = (_i2 + 1))
        {
          int  _ct32908 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
          int  _ct32909 = 0;
          int  _ct32910 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct32908: _ct32909);
          int  _ct32911 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
          int  _ct32912 = 0;
          int  _ct32913 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct32911: _ct32912);
          int  _ct32914 = _ct32913;
          int  _ct32915 = 2;
          int  _ct32916 = ((_ct32910 < 2)? _ct32914: _ct32915);
          int  _ct32917 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
          int  _ct32918 = 0;
          int  _ct32919 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct32917: _ct32918);
          int  _ct32920 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
          int  _ct32921 = 0;
          int  _ct32922 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct32920: _ct32921);
          int  _ct32923 = _ct32922;
          int  _ct32924 = 2;
          int  _ct32925 = ((_ct32919 < 2)? _ct32923: _ct32924);
          int  _ct32926 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
          int  _ct32927 = 0;
          int  _ct32928 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct32926: _ct32927);
          int  _ct32929 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
          int  _ct32930 = 0;
          int  _ct32931 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct32929: _ct32930);
          int  _ct32932 = _ct32931;
          int  _ct32933 = 2;
          int  _ct32934 = ((_ct32928 < 2)? _ct32932: _ct32933);
          int  _ct32935 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
          int  _ct32936 = 0;
          int  _ct32937 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct32935: _ct32936);
          int  _ct32938 = (int ) ((img[((_i1 * C) + _i2)] * (float ) (3)));
          int  _ct32939 = 0;
          int  _ct32940 = (((int ) ((img[((_i1 * C) + _i2)] * (float ) (3))) > 0)? _ct32938: _ct32939);
          int  _ct32941 = _ct32940;
          int  _ct32942 = 2;
          int  _ct32943 = ((_ct32937 < 2)? _ct32941: _ct32942);
          outLPyramid_L0[((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] = (((1.0f - ((img[((_i1 * C) + _i2)] * (float ) (3)) - _ct32916)) * U_lPyramid_L0[_ct32925][((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)]) + (((img[((_i1 * C) + _i2)] * (float ) (3)) - _ct32934) * U_lPyramid_L0[(_ct32943 + 1)][((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)]));
        }
      }
      int  _ct32944 = (((R - 62) < ((8 * _T_i1) + 7))? (R - 62): ((8 * _T_i1) + 7));
      int  _ct32945 = ((31 > (8 * _T_i1))? 31: (8 * _T_i1));
      for (int  _i1 = _ct32945; (_i1 <= _ct32944); _i1 = (_i1 + 1))
      {
        int  _ct32946 = (((C - 62) < ((256 * _T_i2) + 258))? (C - 62): ((256 * _T_i2) + 258));
        int  _ct32947 = ((31 > ((256 * _T_i2) + 3))? 31: ((256 * _T_i2) + 3));
        #pragma ivdep
        for (int  _i2 = _ct32947; (_i2 <= _ct32946); _i2 = (_i2 + 1))
        {
          float  _ct32948 = ((0.25f * Ux_result_ref_gray[((-8 * _T_i1) + _i1)][((((-256 * _T_i2) + _i2) / 2) - 1)]) + (0.75f * Ux_result_ref_gray[((-8 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)]));
          float  _ct32949 = ((0.25f * Ux_result_ref_gray[((-8 * _T_i1) + _i1)][((((-256 * _T_i2) + _i2) / 2) + 1)]) + (0.75f * Ux_result_ref_gray[((-8 * _T_i1) + _i1)][(((-256 * _T_i2) + _i2) / 2)]));
          float  _ct32950 = (((_i2 % 2) == 0)? _ct32948: _ct32949);
          result_ref_gray[(((_i1 - 31) * (-92 + C)) + (_i2 - 31))] = (outLPyramid_L0[((-8 * _T_i1) + _i1)][((-256 * _T_i2) + _i2)] + _ct32950);
        }
      }
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
        float  _ct20426 = ((result_ref_gray[(((-31 + _i1) * (-92 + C)) + (-31 + _i2))] * ((img_colour[((((_i1-31) * _C * 3)) + (_i2-31) * 3 + _i0)] / 256.0f) + 0.01f)) / (img[((_i1 * C) + _i2)] + 0.01f));
        float  _ct20427 = 0.0f;
        float  _ct20428 = ((((result_ref_gray[(((-31 + _i1) * (-92 + C)) + (-31 + _i2))] * ((img_colour[((((_i1-31) * _C * 3)) + (_i2-31) * 3 + _i0)] / 256.0f) + 0.01f)) / (img[((_i1 * C) + _i2)] + 0.01f)) > 0.0f)? _ct20426: _ct20427);
        float  _ct20429 = ((result_ref_gray[(((-31 + _i1) * (-92 + C)) + (-31 + _i2))] * ((img_colour[((((_i1-31) * _C * 3)) + (_i2-31) * 3 + _i0)] / 256.0f) + 0.01f)) / (img[((_i1 * C) + _i2)] + 0.01f));
        float  _ct20430 = 0.0f;
        float  _ct20431 = ((((result_ref_gray[(((-31 + _i1) * (-92 + C)) + (-31 + _i2))] * ((img_colour[((((_i1-31) * _C * 3)) + (_i2-31) * 3 + _i0)] / 256.0f) + 0.01f)) / (img[((_i1 * C) + _i2)] + 0.01f)) > 0.0f)? _ct20429: _ct20430);
        float  _ct20432 = _ct20431;
        float  _ct20433 = 1.0f;
        float  _ct20434 = ((_ct20428 < 1.0f)? _ct20432: _ct20433);
        //laplacian[((((_i1 - 31) * (-92 + C) * 3)) + (_i2 - 31) * 3 + _i0)] = (short unsigned int ) ((_ct20434 * 65535.0f));
        laplacian[((((_i1 - 31) * (-92 + C) * 3)) + (_i2 - 31) * 3 + _i0)] = (unsigned char) ((_ct20434 * 255.0f));
      }
    }
  }
  pool_deallocate(img);
  pool_deallocate(remapLUT);
  pool_deallocate(gPyramid_L0);
  pool_deallocate(D_inGPyramid_L1);
  pool_deallocate(D_gPyramid_L1);
  pool_deallocate(D_inGPyramid_L2);
  pool_deallocate(D_gPyramid_L2);
  pool_deallocate(Dx_inGPyramid_L3);
  pool_deallocate(D_inGPyramid_L3);
  pool_deallocate(D_gPyramid_L3);
  pool_deallocate(Dx_inGPyramid_L4);
  pool_deallocate(D_inGPyramid_L4);
  pool_deallocate(Dx_gPyramid_L4);
  pool_deallocate(D_gPyramid_L4);
  pool_deallocate(Ux_lPyramid_L3);
  pool_deallocate(outLPyramid_L4);
  pool_deallocate(Ux_outGPyramid_L3);
  pool_deallocate(Ux_outGPyramid_L2);
  pool_deallocate(outGPyramid_L2);
  pool_deallocate(outGPyramid_L1);
  pool_deallocate(result_ref_gray);
}
