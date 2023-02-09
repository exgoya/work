.SUFFIXES: .c .o

CC = g++
CFLAGS = -g -Wall

LFLAGS = -L$(GOLDILOCKS_HOME)/lib
LIB = -lgoldilocksc -lpthread -ldl -lm -lrt

INC = -I$(GOLDILOCKS_HOME)/include

all: select update1

select:
TARGET = select
OBJECTS = $(TARGET).o
SRCS = $(TARGET).cpp

$(TARGET):	$(OBJECTS)
		$(CC) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIB)

$(OBJECTS):	$(SRCS)
		$(CC) $(CFLAGS) -c $(INC) $(SRCS)
update1:
TARGET = update1
OBJECTS = $(TARGET).o
SRCS = $(TARGET).cpp

$(TARGET):	$(OBJECTS)
		$(CC) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIB)

$(OBJECTS):	$(SRCS)
		$(CC) $(CFLAGS) -c $(INC) $(SRCS)


clean:
		rm $(TARGET).o $(TARGET)

