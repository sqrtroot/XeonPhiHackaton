# Use Intel CPP compiler 
#CC = g++
CC = icpc

CXXFLAGS = --std=c++11 -O3

LDFLAGS = 
 
BS_hackaton: BS_hackaton.o
	$(CC) $(CXXFLAGS) -o BS_hackaton BS_hackaton.o $(LDFLAGS)

BS_hackaton.o: BS_hackaton.cpp
	$(CC) $(CXXFLAGS) -c BS_hackaton.cpp

clean: 
	rm -rf *.o BS_hackaton

