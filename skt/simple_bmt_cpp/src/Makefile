INC=-I. -I${GOLDILOCKS_HOME}/include -I/home/son2865/work/simple_bmt_cpp/include
LIB_DIR=-L. -L${GOLDILOCKS_HOME}/lib
LIBS=-lgoldilocksc -lpthread -lm  -ldl -lrt
CFLAGS=-g -O0 -W -Wall
OBJS=SundbCbssPoc.o SundbCbssComm.o

all : 
	${CXX} ${CFLAGS} -c SundbCbssPoc.cpp ${INC}
	${CXX} ${CFLAGS} -c SundbCbssComm.cpp ${INC}
	${CXX} ${CFLAGS} -o SundbCbssPoc ${INC} ${LIB_DIR} ${OBJS} ${LIBS}

clean : 
	rm *.o SundbCbssPoc
