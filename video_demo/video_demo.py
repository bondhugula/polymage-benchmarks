import ctypes
import numpy as np
import time
import cv2
import sys

from common import clock, draw_str, StatValue

# load polymage shared libraries
libharris = ctypes.cdll.LoadLibrary("./harris.so")
libunsharp = ctypes.cdll.LoadLibrary("./unsharp.so")
libbilateral = ctypes.cdll.LoadLibrary("./bilateral.so")

harris = libharris.pipeline_harris
harris_naive = libharris.pipeline_harris_naive

unsharp = libunsharp.pipeline_mask
unsharp_naive = libunsharp.pipeline_mask_naive

bilateral = libbilateral.pipeline_bilateral
bilateral_naive = libbilateral.pipeline_bilateral_naive

fn = sys.argv[1]
cap = cv2.VideoCapture(fn)

frames = 0
startTime = time.clock()
cv_mode = True
naive_mode = False
harris_mode = False
unsharp_mode = False
bilateral_mode = False

thresh = 0.001
weight = 3

while(cap.isOpened()):
    ret, frame = cap.read()

    frameStart = clock()
    rows = frame.shape[0]
    cols = frame.shape[1]
    if harris_mode:
        if cv_mode:
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            gray = np.float32(gray) / 4.0
            res = cv2.cornerHarris(gray, 3, 3, 0.04)
        else:
            if naive_mode:
                res = np.zeros((rows, cols), np.float32) 
                harris_naive(ctypes.c_int(cols-2), \
                             ctypes.c_int(rows-2), \
                             ctypes.c_void_p(frame.ctypes.data), \
                             ctypes.c_void_p(res.ctypes.data))
            else:
                res = np.zeros((rows, cols), np.float32) 
                harris(ctypes.c_int(cols-2), \
                       ctypes.c_int(rows-2), \
                       ctypes.c_void_p(frame.ctypes.data), \
                       ctypes.c_void_p(res.ctypes.data))

    elif unsharp_mode:
        if naive_mode:
            res = np.empty((3, rows-4, cols-4), np.float32).ravel()
            unsharp_naive(ctypes.c_int(cols-4), \
                          ctypes.c_int(rows-4), \
                          ctypes.c_float(thresh), \
                          ctypes.c_float(weight), \
                          ctypes.c_void_p(frame.ctypes.data), \
                          ctypes.c_void_p(res.ctypes.data))
            res = res.reshape(rows-4, cols-4, 3)
        else:
            res = np.empty((3, rows-4, cols-4), np.float32).ravel()
            unsharp(ctypes.c_int(cols-4), \
                    ctypes.c_int(rows-4), \
                    ctypes.c_float(thresh), \
                    ctypes.c_float(weight), \
                    ctypes.c_void_p(frame.ctypes.data), \
                    ctypes.c_void_p(res.ctypes.data))
            res = res.reshape(rows-4, cols-4, 3)

    elif bilateral_mode:
        if naive_mode:
            res = np.zeros((rows, cols), np.float32)
            bilateral_naive(ctypes.c_int(cols+56), \
                            ctypes.c_int(rows+56), \
                            ctypes.c_void_p(frame.ctypes.data), \
                            ctypes.c_void_p(res.ctypes.data))
        else:
            res = np.zeros((rows, cols), np.float32)
            bilateral(ctypes.c_int(cols+56), \
                      ctypes.c_int(rows+56), \
                      ctypes.c_void_p(frame.ctypes.data), \
                      ctypes.c_void_p(res.ctypes.data))
    else:
        res = frame

    frameEnd = clock()

    cv2.rectangle(res, (0, 0), (750, 150), (255, 255, 255), thickness=cv2.cv.CV_FILLED)

    draw_str(res, (40, 40),      "frame interval :  %.1f ms" % (frameEnd*1000 - frameStart*1000))
    if cv_mode and harris_mode:
        draw_str(res, (40, 80),  "Pipeline        :  " + str("OpenCV"))
    elif bilateral_mode or harris_mode or unsharp_mode:
        if naive_mode:
            draw_str(res, (40, 80),  "Pipeline        :  " + str("PolyMage (Naive)"))
        else:
            draw_str(res, (40, 80),  "Pipeline        :  " + str("PolyMage (Opt)"))
    else:
        draw_str(res, (40, 80),  "Pipeline        :  ")

    if harris_mode:
        draw_str(res, (40, 120), "Benchmark    :  " + str("Harris Corner"))
    elif bilateral_mode:
        draw_str(res, (40, 120), "Benchmark    :  " + str("Bilateral Grid"))
    elif unsharp_mode:
        draw_str(res, (40, 120), "Benchmark    :  " + str("Unsharp Mask"))
    else:
        draw_str(res, (40, 120), "Benchmark    :  ")

    cv2.imshow('threaded video', res)

    ch = 0xFF & cv2.waitKey(1)
    if ch == ord('q'):
        break
    if ch == ord(' '):
        cv_mode = not cv_mode
    if ch == ord('n'):
        naive_mode = not naive_mode
    if ch == ord('h'):
        harris_mode = not harris_mode
        bilateral_mode = False
        unsharp_mode = False
    if ch == ord('u'):
        unsharp_mode = not unsharp_mode
        bilateral_mode = False
        harris_mode = False
    if ch == ord('b'):
        bilateral_mode = not bilateral_mode
        harris_mode = False
        unsharp_mode = False
    frames += 1

cap.release()
cv2.destroyAllWindows()
