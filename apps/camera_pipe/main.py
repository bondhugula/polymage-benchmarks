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
libcamera = ctypes.cdll.LoadLibrary("./camera_pipe.so")
camera_pipe = libcamera.pipeline_process

# initialize the app. parameters
def initVars(image, colour_temp, contrast, gamma, nruns, rows, cols, args):
    if len(args) < 4 :
        print "Usage:\n" + args[0] + \
              " colour_temp contrast gamma [[nruns] [rows [cols]]]"
        sys.exit(1)
    else :
        # use raw image of size 1968 x 2592
        image = cv2.imread("../../images/bayer_raw.png", -1)
        colour_temp = float(args[1])
        contrast = float(args[2])
        gamma = float(args[3])
        optionalArgStart = 4

        # Optional Parameters
        # default
        nruns = 6
        rows, cols = 1968, 2592
        nruns, rows, cols = initOptionals(optionalArgStart, \
                                          nruns, rows, cols, args)

    return image, colour_temp, contrast, gamma, nruns, rows, cols

#------------------------------------------------------------------

image = ''
colour_temp, contrast, gamma = 3700, 50, 2.0
nruns, rows, cols = 0, 0, 0

# initialize
image, colour_temp, contrast, gamma, nruns, rows, cols = \
    initVars(image, colour_temp, contrast, gamma, \
             nruns, rows, cols, sys.argv)

# Values set to
printLine()
print 'image: \"', sys.argv[1], '\"'
print 'colour_temp =',colour_temp,\
      'contrast =',contrast,\
      'gamma =',gamma
print 'nruns =',nruns,', rows =',rows,', cols =',cols

if rows != 1968 or cols != 2592:
    print "Please use raw image of size 2592x1968"
    sys.exit(0)

# convert input image to short
image_16S = np.array(image)
image_16S = image_16S.astype(np.int16)

matrix_3200 = np.float32(
                [[ 1.6697, -0.2693, -0.4004, -42.4346],
                 [-0.3576,  1.0615,  1.5949, -37.1158],
                 [-0.2175, -1.8751,  6.9640, -26.6970]]
                )

matrix_7000 = np.float32(
                [[ 2.2997, -0.4478,  0.1706, -39.0923],
                 [-0.3826,  1.5906, -0.2080, -25.4311],
                 [-0.0888, -0.7344,  2.2832, -20.0826]]
                )

# result array
res = np.empty((3, rows-48, cols-64), np.uint8)

# start timer
startTime = time.clock()
avgTime = 0
for run in range(1, nruns+1):
    frameStart = clock()
    # Compute
    camera_pipe(ctypes.c_int(cols), ctypes.c_int(rows),
                ctypes.c_float(colour_temp),
                ctypes.c_float(contrast),
                ctypes.c_float(gamma),
                ctypes.c_void_p(image_16S.ctypes.data),
                ctypes.c_void_p(matrix_3200.ctypes.data),
                ctypes.c_void_p(matrix_7000.ctypes.data),
                ctypes.c_void_p(res.ctypes.data))
    frameEnd = clock()
    frameTime = float(frameEnd) - float(frameStart)

    if run != 1:
        print frameEnd*1000 - frameStart*1000, "ms"
        avgTime += frameTime
print "-------------------------------"
print "avg time: ", (avgTime/(nruns-1))*1000, "ms"
print "-------------------------------"

# move colour dimension inside
output_image = np.rollaxis(res, 0, 3)

# Display
cv2.namedWindow("input", cv2.WINDOW_NORMAL)
cv2.namedWindow("output", cv2.WINDOW_NORMAL)
ch = 0xFF
while [ ch != ord('q') ]:
    ch = 0xFF & cv2.waitKey(1)
    cv2.imshow("input", image)
    cv2.imshow("output", output_image)
    if ch == ord('q'):
        break

cv2.destroyAllWindows()
