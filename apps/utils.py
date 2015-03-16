#!/usr/bin/env python

import numpy as np
import cv2
import os

def clock():
    return cv2.getTickCount() / cv2.getTickFrequency()

def printLine(toFile=None):
    if toFile:
        print >>toFile, "--------------------------------------------------"
    else:
        print "--------------------------------------------------"

def setmin(var, val):
    if var < val:
        var = val
    return var

def setmax(var, val):
    if var > val:
        var = val
    return var

def range_clamp(var, minval, maxval):
    if var < minval:
        var = minval
    elif var > maxval:
        var = maxval
    else:
        pass

    return var

def initOptionals(offset, nruns, rows, cols, args):
    temp_rows = rows
    temp_cols = cols

    if len(args) > offset :
        nruns = int(args[offset])
    if len(args) > offset+1 :
        temp_rows = int(args[offset+1])
        if len(args) > offset+2 :
            temp_cols = int(args[offset+2])
        else :
            temp_cols = temp_rows

    nruns = setmin(nruns, 1)
    temp_rows = range_clamp(temp_rows, 1, rows)
    temp_cols = range_clamp(temp_cols, 1, cols)

    rows = temp_rows
    cols = temp_cols

    return nruns, rows, cols

def image_clamp(image_in, image_out, \
          R, C, K, \
          dtype, dfactor, \
          left, total):
    if K > 1:
        # mid of top, bottom, left and right resp.
        image_out[0:left, left:C+left, 0:K] = \
            np.array(image_in[0, 0:C, 0:K] * dfactor, dtype)
        image_out[R+left:R+total, left:C+left, 0:K] = \
            np.array(image_in[R-1, 0:C, 0:K] * dfactor, dtype)
        image_out[left:left+R, 0:left, 0:K] = \
            np.array(image_in[0:R, 0, 0:K].reshape(R, 1, 3) * dfactor, dtype)
        image_out[left:left+R, left+C:C+total, 0:K] = \
            np.array(image_in[0:R, C-1, 0:K].reshape(R, 1, 3) * dfactor, dtype)
        # corners :
        image_out[0:left, 0:left, 0:K] = \
            image_out[left, 0:left, 0:K]
        image_out[0:left, left+C:C+total, 0:K] = \
            image_out[left, left+C:C+total, 0:K]
        image_out[left+R:R+total, 0:left, 0:K] = \
            image_out[left+R-1, 0:left, 0:K]
        image_out[left+R:R+total, left+C:C+total, 0:K] = \
            image_out[left+R-1, left+C:C+total, 0:K]
    else:
        # mid of top, bottom, left and right resp.
        image_out[0:left, left:C+left] = \
            np.array(image_in[0, 0:C] * dfactor, dtype)
        image_out[R+left:R+total, left:C+left] = \
            np.array(image_in[R-1, 0:C] * dfactor, dtype)
        image_out[left:left+R, 0:left] = \
            np.array(image_in[0:R, 0].reshape(R, 1) * dfactor, dtype)
        image_out[left:left+R, left+C:C+total] = \
            np.array(image_in[0:R, C-1].reshape(R, 1) * dfactor, dtype)
        # corners :
        image_out[0:left, 0:left] = \
            image_out[left, 0:left]
        image_out[0:left, left+C:C+total] = \
            image_out[left, left+C:C+total]
        image_out[left+R:R+total, 0:left] = \
            image_out[left+R-1, 0:left]
        image_out[left+R:R+total, left+C:C+total] = \
            image_out[left+R-1, left+C:C+total]
