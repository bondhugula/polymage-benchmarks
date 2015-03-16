PolyMage Benchmarks

All seven benchmarks are in the apps/ dir. For any of the benchmarks, say 
camera-pipe/

camera-pipe.so refers to the fully optimized Polymage code.  
camera-pipe-naive.so refers to the base code (naive C code parallelized and 
vectorized) and corresponds to PolyMage (base+vec) from the paper.

$ make camera-pipe

will build and run the optimized PolyMage code

$ make camera-pipe-naive

will build and run the base code.

$ make graph 

will generate a PNG file with the pipeline diagram.

For the video demos, please see video_demo/README.txt
