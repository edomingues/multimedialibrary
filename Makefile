TARGET  := main
SRCS    := ${wildcard *.cpp} 
OBJS    := ${SRCS:.cpp=.o} 

CCFLAGS =
LDFLAGS = 
LIBS    =
INCL	=
OPT	= -Wall -O3
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
