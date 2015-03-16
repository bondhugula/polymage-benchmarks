CXX=icpc
CXX_FLAGS=-openmp -ipo -O3 -xhost -fPIC -shared

#CXX=g++
#CXX_FLAGS=-fopenmp -O3 -fPIC -shared

all: bilateral_grid graph

naive: bilateral_grid_naive

bilateral_grid: bilateral.so
	python main.py ../../images/rgb.png 11

bilateral_grid_naive: bilateral_naive.so
	python main.py ../../images/rgb.png 11

bilateral.so: bilateral_grid_polymage.cpp
	$(CXX) $(CXX_FLAGS) bilateral_grid_polymage.cpp -o bilateral.so

bilateral_naive.so: bilateral_grid_polymage_naive.cpp
	$(CXX) $(CXX_FLAGS) bilateral_grid_polymage_naive.cpp -o bilateral.so

graph:
	dot -Tpng graph.dot >graph.png

clean:
	rm -f *.pyc *.so graph.png
