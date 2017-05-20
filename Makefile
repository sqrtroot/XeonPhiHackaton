# Use Intel CPP compiler 
#CC = g++
CC = icpc

CXXFLAGS = --std=c++11
CXXFLAGS += -O2 -ltbb -I"/usr/local/include/"
LDFLAGS = -ltbb

ray_tracer:
	$(CC) $(CXXFLAGS) -o ray_tracer coordinate.cc main.cpp material.cpp ray.cpp scene.cc sphere.cc $(LDFLAGS)

#BS_hackaton: BS_hackaton.o
	#$(CC) $(CXXFLAGS) -o BS_hackaton BS_hackaton.o $(LDFLAGS)

#BS_hackaton.o: BS_hackaton.cpp
	#$(CC) $(CXXFLAGS) -c BS_hackaton.cpp

#clean: 
	#rm -rf *.o BS_hackaton

