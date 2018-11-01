CXX = g++
CXXFLAGS = -lm -fopenmp

OBJS = project0.o 

SRCS = project0.cpp


#target: dependencies
#	rule to build
#
main: ${OBJS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o project0
	
${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean: 
	rm  *.o project0