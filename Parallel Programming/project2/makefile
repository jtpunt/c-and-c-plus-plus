CXX = g++
CXXFLAGS = -lm -fopenmp

OBJS = project2.o 

SRCS = project2.cpp


#target: dependencies
#	rule to build
#
main: ${OBJS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o project2
	
${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean: 
	rm  *.o project2