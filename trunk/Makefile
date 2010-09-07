TARGET  := main
SRCS    := ${wildcard *.cpp} 
OBJS    := ${SRCS:.cpp=.o} 

CCFLAGS = -Wall -fpic -O3
LDFLAGS = 
LIBS    =
INCL	=
CC	= g++


.PHONY: all clean distclean 
all:: ${TARGET} 

${TARGET}: ${OBJS} 
	${CC} ${LDFLAGS} ${INCL} ${OPT} -o $@ $^ ${LIBS} 
	
${OBJS}: %.o: %.cpp
	${CC} ${CCFLAGS} ${INCL} ${OPT} -o $@ -c $< 
	
clean::
	-rm -f *~ *.o ${TARGET}
	-rm -rf html

doc::
	-doxygen libMultimedia.cfg

distclean:: clean
