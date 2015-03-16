CXX=icpc
CXX_FLAGS=-openmp -ipo -O3 -xhost -fPIC -shared

#CXX=g++
#CXX_FLAGS=-fopenmp -O3 -fPIC -shared

all: unsharp_mask graph

naive: unsharp_mask_naive

unsharp_mask: unsharp.so
	python main.py ../../images/grand_canyon2.jpg 0.001 3 11 2048 2048

unsharp_mask_naive: unsharp_naive.so
	python main.py ../../images/grand_canyon2.jpg 0.001 3 11 2048 2048

unsharp.so: unsharp_mask_polymage.cpp
	$(CXX) $(CXX_FLAGS) unsharp_mask_polymage.cpp -o unsharp.so

unsharp_naive.so: unsharp_mask_polymage_naive.cpp
	$(CXX) $(CXX_FLAGS) unsharp_mask_polymage_naive.cpp -o unsharp.so

graph:
	dot -Tpng graph.dot >graph.png

clean:
	rm -f *.pyc *.so graph.png
