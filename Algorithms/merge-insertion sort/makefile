CXX = g++
CXXFLAGS = -g -std=c++0x

OBJS = main.o insertionsort.o mergesort.o

SRCS = main.cpp insertionsort.cpp mergesort.cpp

HEADERS = main.hpp insertionsort.hpp mergesort.hpp


#target: dependencies
#	rule to build
#
main: ${OBJS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o main
	
${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean: 
	rm  *.o main
