# Common arguments called with all compilation statements
COMMON_ARGUMENTS          := -Wall -Werror #-g #-pg
OPTIMIZATION_LEVEL        := -O3
PING_PONG_FILE            := stewart_nate_lab5.c
PING_PONG_HEADER          := stewart_nate_lab5.h
PING_PONG_OUTPUT          := a.out 
BINARIES := $(PING_PONG_OUTPUT)

all: $(BINARIES) 

$(PING_PONG_OUTPUT): $(PING_PONG_FILE) $(PING_PONG_HEADER)
	mpicc $(COMMON_ARGUMENTS) $(OPTIMIZATION_LEVEL) $(PING_PONG_FILE) -o $(PING_PONG_OUTPUT)

clean:
	rm -f $(BINARIES) *.out *.o  
