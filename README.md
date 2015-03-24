===================
PolyMage Benchmarks
===================

Requirements
============

python 2.7

OpenCV 2.4.8 (with QT or gtk support, with video codec support for the video demo)

OpenCV python bindings

g++ (GNU C++ compiler) > 4.8 or icpc (Intel C/C++ compiler) > 12.0

How to run the benchmarks
=========================

All seven benchmarks are in the apps/ dir. For any of the benchmarks, say 
camera_pipe/

camera_pipe.so refers to the fully optimized Polymage code.  
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
