'''
  Copyright (c) 2015-, Ravi Teja Mullapudi, Vinay Vasista, CSA Indian 
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
'''

import ctypes
import numpy as np
import time
import cv2
import sys
sys.path.insert(0, '../')
from utils import clock, initOptionals, \
                   printLine, image_clamp

# shared library, and function
libblending = ctypes.cdll.LoadLibrary("./blending.so")
blending = libblending.pipeline_blend

# initialize the app. parameters
def initVars(image1, image2, mask, nruns, rows, cols, args):
    if len(args) < 3 :
        print "Usage:\n" + args[0] + \
              " image1 image2 [[nruns] [rows [cols]]]"
        sys.exit(1)
    else :
        image1 = cv2.imread(args[1], cv2.CV_LOAD_IMAGE_COLOR)
        image2 = cv2.imread(args[2], cv2.CV_LOAD_IMAGE_COLOR)
        optionalArgStart = 3

        assert image1.shape == image2.shape

        # Optional Parameters
        # default
        nruns = 6
        rows, cols = 2048, 2048
        nruns, rows, cols = initOptionals(optionalArgStart, \
                                          nruns, rows, cols, args)

    return image1, image2, mask, nruns, rows, cols

#------------------------------------------------------------------

image1 = ''
image2 = ''
mask = ''
nruns, rows, cols = 0, 0, 0

# initialize
image1, image2, mask, nruns, rows, cols = \
    initVars(image1, image2, mask, \
             nruns, rows, cols, sys.argv)

# Values set to
printLine()
print 'image1: \"', sys.argv[1], '\"'
print 'image2: \"', sys.argv[2], '\"'
print 'mask: \"', sys.argv[3], '\"'
print 'nruns =',nruns,', rows =',rows,', cols =',cols

if rows != 2048 or cols != 2048:
    print "Please use 2048x2048 image size"
    sys.exit(0)

R = image1.shape[0]
C = image1.shape[1]

off_left = 31
total_pad = 60

# convert input image to floating point
image1_f = np.float32(image1) / 255.0
image2_f = np.float32(image2) / 255.0

# get image roi
row_base = (R - rows)/2
col_base = (C - cols)/2

image_region1 = image1_f[row_base : row_base+rows, \
                         col_base : col_base+cols]
image_region2 = image2_f[row_base : row_base+rows, \
                         col_base : col_base+cols]

# create ghost zone and copy image roi

# Image 1:
image1_ghost = np.empty((rows+total_pad, cols+total_pad, 3), np.float32)
image1_ghost[off_left:rows+off_left, off_left:cols+off_left, 0:3] = \
    np.array(image_region1[0:rows, 0:cols, 0:3], np.float32)
# clamp the boundary portions
image_clamp(image_region1, image1_ghost,
     rows, cols, 3,
     np.float32, 1,
     off_left, total_pad)

# Image 2
image2_ghost = np.empty((rows+total_pad, cols+total_pad, 3), np.float32)
image2_ghost[off_left:rows+off_left, off_left:cols+off_left, 0:3] = \
    np.array(image_region2[0:rows, 0:cols, 0:3], np.float32)
# clamp the boundary portions
image_clamp(image_region2, image2_ghost,
     rows, cols, 3,
     np.float32, 1,
     off_left, total_pad)

# create a simple mask of size (rows+total_pad) x (cols+total_pad)
maskRow = 820
half1 = np.zeros((maskRow, cols+total_pad), np.float32)
half2 = np.ones((rows+total_pad-maskRow, cols+total_pad), np.float32)

mask_ghost = np.vstack((half1, half2))

# move colour dimension outside
image1_f_flip = np.rollaxis(image1_ghost, 2).ravel()
image2_f_flip = np.rollaxis(image2_ghost, 2).ravel()

# result array
res = np.empty((3, rows, cols), np.float32)

# start timer
print "-------------------------------"
startTime = time.clock()
avgTime = 0
for run in range(1, nruns+1):
    frameStart = clock()
    # Compute
    blending(ctypes.c_int(cols+total_pad), \
             ctypes.c_int(rows+total_pad), \
             ctypes.c_void_p(image1_f_flip.ctypes.data), \
             ctypes.c_void_p(image2_f_flip.ctypes.data), \
             ctypes.c_void_p(mask_ghost.ctypes.data), \
             ctypes.c_void_p(res.ctypes.data))
    frameEnd = clock()
    frameTime = float(frameEnd) - float(frameStart)

    if run != 1:
        print "time taken: ", frameEnd*1000 - frameStart*1000, "ms"
        avgTime += frameTime

print "-------------------------------"
print "avg time: ", (avgTime/(nruns-1))*1000, "ms"
print "-------------------------------"


# Display

# reshape and move colour dimension inside
output_image = np.rollaxis(res, 0, 3)

cv2.namedWindow("input1", cv2.WINDOW_NORMAL)
cv2.namedWindow("input2", cv2.WINDOW_NORMAL)
cv2.namedWindow("mask", cv2.WINDOW_NORMAL)
cv2.namedWindow("output", cv2.WINDOW_NORMAL)
ch = 0xFF

while [ ch != ord('q') ]:
    ch = 0xFF & cv2.waitKey(1)
    cv2.imshow("input1", image1[row_base:row_base+rows, \
                                col_base:col_base+cols])
    cv2.imshow("input2", image2[row_base:row_base+rows, \
                                col_base:col_base+cols])
    cv2.imshow("mask", mask_ghost[off_left:off_left+rows, \
                            off_left:off_left+cols])
    cv2.imshow("output", output_image)
    if ch == ord('q'):
        break

cv2.destroyAllWindows()
