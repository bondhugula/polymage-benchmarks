CXX=icpc
CXXFLAGS=-xhost -openmp -fPIC -shared -O3

all: harris.so bilateral.so unsharp.so

harris.so: harris_polymage.cpp
	$(CXX) $(CXXFLAGS) -o harris.so harris_polymage.cpp

bilateral.so: bilateral_polymage.cpp
	$(CXX) $(CXXFLAGS) -o bilateral.so bilateral_polymage.cpp

unsharp.so: unsharp_polymage.cpp
	$(CXX) $(CXXFLAGS) -o unsharp.so unsharp_polymage.cpp

clean:
	rm -f *.so *.pyc
