##################################################################
# sample
#
##################################################################

CC = gcc
CFLAGS = -g -Wall

INC = -I$(GOLDILOCKS_HOME)/include
LFLAGS = -L$(GOLDILOCKS_HOME)/lib

CSMODE=0

LIB = -lgoldilocksesql -lpthread -ldl -lm -lrt
ifeq ($(CSMODE), 1)
    LIB += -lgoldilocksc
else
    ifeq ($(MIXMODE), 1)
        LIB += -lgoldilocks
    else
        LIB += -lgoldilocksa
    endif
endif

GPEC = gpec
GPECFLAGS =
#GPECFLAGS = --unsafe-null --no-prompt

BINS = overview \
       sample1 \
       sample2 \
       sample3 \
       sample4 \
       sample5 \
       dyn1 \
       dyn2 \
       number \
       date_time \
       thread1 \
       fetch_struct_array \
       xa \
       long_binary \
       psm \
       whenever \
       preprocess

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), all)
TARGET = $(MAKECMDGOALS)
OBJECT = $(TARGET).o
C_SRC  = $(TARGET).c
endif
endif

##################################################################
# implicit rules
##################################################################
.SUFFIXES: .gc .c .o

.gc.c:
	$(GPEC) $(GPECFLAGS) $^

.c.o:
	$(CC) $(CFLAGS) -c $(INC) $^

##################################################################
# build rules
##################################################################
NoTarget :
	@echo "Syntax : make {all | sample_name | clean}"
	@echo "sample_name is one of '$(BINS)'"

all :
	for target in $(BINS); do \
		$(MAKE) $$target;     \
	done

$(OBJECT) : $(C_SRC)
$(TARGET) : $(OBJECT)
	$(CC) -o $@ $^ $(LFLAGS) $(LIB)

clean :
	rm -rf $(BINS) *.o *~ core
