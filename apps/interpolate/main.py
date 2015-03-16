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
libinterpolate = ctypes.cdll.LoadLibrary("./interpolate.so")
interpolate = libinterpolate.pipeline_interpolate

# initialize the app. parameters
def initVars(image, alpha, nruns, rows, cols, args):
    if len(args) < 3 :
        print "Usage:\n" + args[0] + \
              " image alpha [[nruns] [rows [cols]]]"
        sys.exit(1)
    else :
        image = cv2.imread(args[1], cv2.CV_LOAD_IMAGE_COLOR)
        alpha = cv2.imread(args[2], cv2.CV_LOAD_IMAGE_GRAYSCALE)
        optionalArgStart = 3

        assert image.shape[0] == alpha.shape[0] and \
               image.shape[1] == alpha.shape[1]

        # Optional Parameters
        # default
        nruns = 6
        rows, cols = 2560, 1536
        nruns, rows, cols = initOptionals(optionalArgStart, \
                                          nruns, rows, cols, args)

    return image, alpha, nruns, rows, cols

#-------------------------------------------------------------------

image = ''
alpha = ''
nruns, rows, cols = 0, 0, 0

# initialize
image, alpha, nruns, rows, cols = \
    initVars(image, alpha, \
             nruns, rows, cols, sys.argv)

# Values set to
printLine()
print 'image: \"', sys.argv[1], '\"'
print 'alpha: \"', sys.argv[2], '\"'
print 'nruns =',nruns,', rows =',rows,', cols =',cols

if rows != 2560 or cols != 1536:
    print "Please use 1536x2560 image size"
    sys.exit(0)

R = image.shape[0]
C = image.shape[1]

# move colour dimension outside
image_flip = np.rollaxis(image, 2)

# add alpha channel to image along with 
# other colour channels
imgalpha = np.append(image_flip, alpha)
imgalpha = imgalpha.reshape(4, R, C)

# get image roi
row_base = (R - rows)/2
col_base = (C - cols)/2

imgalpha_region = imgalpha[0:4, \
                           row_base:row_base+rows+2, \
                           col_base:col_base+cols+2]

# add ghost region
imgalpha_ghost = \
    np.empty((4, rows+2, cols+2), np.float32)
imgalpha_ghost[0:4, 1:rows+1, 1:cols+1] = \
    imgalpha_region

# convert input image to floating point
imgalpha_f = np.float32(imgalpha_ghost) / 255.0

# result array
res = np.empty((3, rows, cols), np.float32)

# start timer
print "-------------------------------"
startTime = time.clock()
avgTime = 0
for run in range(1, nruns+1):
    frameStart = clock()
    # Compute
    interpolate(ctypes.c_int(cols), ctypes.c_int(rows), \
                ctypes.c_void_p(imgalpha_f.ctypes.data), \
                ctypes.c_void_p(res.ctypes.data)
               )
    frameEnd = clock()
    frameTime = float(frameEnd) - float(frameStart)

    if run != 1:
        print frameEnd*1000 - frameStart*1000, "ms"
        avgTime += frameTime

print "-------------------------------"
print "avg time: ", (avgTime/(nruns-1))*1000, "ms"
print "-------------------------------"

# Display

# reshape and move colour dimension inside

image_show = image[row_base : row_base+rows,
                   col_base : col_base+cols,
                   0:3]

alpha_show = alpha[row_base : row_base+rows,
                   col_base : col_base+cols]

output_show = np.rollaxis(res, 0, 3)

cv2.namedWindow("input", cv2.WINDOW_NORMAL)
cv2.namedWindow("alpha", cv2.WINDOW_NORMAL)
cv2.namedWindow("output", cv2.WINDOW_NORMAL)
ch = 0xFF
while [ ch != ord('q') ]:
    ch = 0xFF & cv2.waitKey(1)
    cv2.imshow("input", image_show)
    cv2.imshow("alpha", alpha_show)
    cv2.imshow("output", output_show)
    if ch == ord('q'):
        break

cv2.destroyAllWindows()
