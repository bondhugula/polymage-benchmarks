CXX=icpc
CXXFLAGS=-xhost -openmp -fPIC -shared -O3

all: harris.so bilateral.so unsharp.so laplacian.so harris_naive.so bilateral_naive.so unsharp_naive.so laplacian_naive.so

harris.so: harris_polymage.cpp
	$(CXX) $(CXXFLAGS) -o harris.so harris_polymage.cpp simple_pool_allocator.cpp

harris_naive.so: harris_naive.cpp
	$(CXX) $(CXXFLAGS) -o harris_naive.so harris_naive.cpp simple_pool_allocator.cpp

bilateral.so: bilateral_polymage.cpp
	$(CXX) $(CXXFLAGS) -o bilateral.so bilateral_polymage.cpp simple_pool_allocator.cpp

bilateral_naive.so: bilateral_naive.cpp
	$(CXX) $(CXXFLAGS) -o bilateral_naive.so bilateral_naive.cpp simple_pool_allocator.cpp

unsharp.so: unsharp_polymage.cpp
	$(CXX) $(CXXFLAGS) -o unsharp.so unsharp_polymage.cpp simple_pool_allocator.cpp

unsharp_naive.so: unsharp_naive.cpp
	$(CXX) $(CXXFLAGS) -o unsharp_naive.so unsharp_naive.cpp simple_pool_allocator.cpp

laplacian.so: laplacian_polymage.cpp
	$(CXX) $(CXXFLAGS) -o laplacian.so laplacian_polymage.cpp simple_pool_allocator.cpp

laplacian_naive.so: laplacian_naive.cpp
	$(CXX) $(CXXFLAGS) -o laplacian_naive.so laplacian_naive.cpp simple_pool_allocator.cpp

clean:
	rm -f *.so *.pyc
