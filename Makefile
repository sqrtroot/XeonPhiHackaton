# Use Intel CPP compiler 
#CC = g++
CC = icpc

CXXFLAGS = --std=c++11
CXXFLAGS += -O2 -ltbb -I"/usr/local/include/"
LDFLAGS = -ltbb

ray_tracer:
	$(CC) $(CXXFLAGS) -o ray_tracer coordinate.cc main.cpp material.cpp ray.cpp scene.cc sphere.cc $(LDFLAGS)
