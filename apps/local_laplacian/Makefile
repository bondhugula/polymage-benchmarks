CXX=icpc
CXX_FLAGS=-openmp -ipo -O3 -xhost -fPIC -shared

#CXX=g++
#CXX_FLAGS=-fopenmp -O3 -fPIC -shared

all: local_laplacian graph

naive: local_laplacian_naive

local_laplacian: laplacian.so
	python main.py ../../images/rgb.png 1 1 11

local_laplacian_naive: laplacian_naive.so
	python main.py ../../images/rgb.png 1 1 11

laplacian.so: laplacian_polymage.cpp
	$(CXX) $(CXX_FLAGS) laplacian_polymage.cpp -o laplacian.so

laplacian_naive.so: laplacian_polymage_naive.cpp
	$(CXX) $(CXX_FLAGS) laplacian_polymage_naive.cpp -o laplacian.so

graph:
	dot -Tpng graph.dot >graph.png

clean:
	rm -f *.pyc *.so graph.png
