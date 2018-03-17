CXX = g++
CXXFLAGS = -g -std=c++0x

OBJS = main.o 

SRCS = main.cpp

HEADERS = circularList.hpp circular_impl.hpp


#target: dependencies
#	rule to build
#
main: ${OBJS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o main
	
${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean: 
	rm  *.o main
