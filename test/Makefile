CXX = g++

CXXFLAGS = -std=c++11 -Wall
CXXFLAGS += `wx-config --cxxflags`
CXXFLAGS += -g -pg
LDFLAGS  += `wx-config --libs gl,core,base`

all: test_frame

test_frame: TestApp.cc
	$(CXX) $(LDFLAGS) -o test_frame  $(LDFLAGS) $(LDLIBS)

make clean:
	-rm -f *.o
