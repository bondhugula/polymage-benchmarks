===================
PolyMage Benchmarks
===================

Requirements
============

1) Python 2.x

2) OpenCV 2.4.7 or higher (with QT/GTK support, video codec support for the 
video demo), Python bindings for OpenCV. On a Fedora Linux system, these can 
be installed with 

$ sudo yum -y install opencv python-opencv

3) g++ (GNU C++ compiler) version 4.8 or higher or Intel C/C++ compiler (icpc) 
12.0 or higher (recommended: icpc 14.0 or higher)

How to run the benchmarks
=========================

All seven benchmarks are in the apps/ dir. For any of the benchmarks, say 
camera_pipe/,

camera_pipe_opt.so refers to the fully optimized Polymage code.  
camera_pipe_naive.so refers to the base code (naive C code parallelized and 
vectorized) and corresponds to PolyMage (base+vec) from the paper.

Set the enviroment variable GOMP_CPU_AFFINITY=0-{NUM_THREADS} for pinning threads to reduce variance between runs

$ make camera_pipe

will build and run the optimized PolyMage code

$ make camera_pipe_naive

will build and run the base code.

$ make graph 

will generate a PNG file with the pipeline diagram.

For the video demos, please see video_demo/README.txt
