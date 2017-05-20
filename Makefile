# Use Intel CPP compiler 
#CC = g++
CC = icpc

CXXFLAGS = --std=c++11
CXXFLAGS += -O2 -ltbb -I"/usr/local/include/"
LDFLAGS = -L/opt/intel/lib -L/opt/intel/lib/intel64 -L/opt/intel/tbb/lib -L/opt/intel/mkl/lib
 
BS_hackaton: BS_hackaton.o
	$(CC) $(CXXFLAGS) -o BS_hackaton BS_hackaton.o $(LDFLAGS)

BS_hackaton.o: BS_hackaton.cpp
	$(CC) $(CXXFLAGS) -c BS_hackaton.cpp

clean: 
	rm -rf *.o BS_hackaton

