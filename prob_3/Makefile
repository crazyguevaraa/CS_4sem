# flags
CC = gcc
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

CFLAGS = -g -v -std=c99 -Werror -Wall -Wextra -Wnarrowing -Wwrite-strings -Wcast-qual -Wundef -Wstrict-prototypes -Wbad-function-cast -Wlong-long -Wconversion -Wunused-parameter
ADDIT_FLAGS = -pthread -lm

# pathes
VPATH = clc_core client server
LIB_PATH		= /clc_core
LIB_SOURCES 	= $(LIB_PATH)/calc.c $(LIB_PATH)/CPUTopology.c
LIB_OBJS		= $(LIB_SOURCES:.c=.o)


SERVER_PATH 	= /server
SERVER_SOURCES 	= $(SERVER_PATH)/server_main.c
SERVER_OBJS		= $(SERVER_SOURCES:.c=.o)
SERVER_EXEC		= svr


CLIENT_PATH  	= /client
CLIENT_SOURCES 	= $(CLIENT_PATH)/client_main.c $(LIB_PATH)/calc.c
CLIENT_OBJS		= $(CLIENT_SOURCES:.c=.o)
CLIENT_EXEC		= clt



# names of output files
.PHONY: all clean
all: Bclient Bserver

### compile stuff

# client

Bclient: client/client_main.o clc_core/calc.o
		$(CC) $^ $(CFLAGS) -o $@

Bserver: server/server_main.o
		$(CC) $^ $(CFLAGS) -o $@

%.o: %.c %.h
	$(CC) $< $(CFLAGS) -o $@

client/client_main.o: client/client_main.c clc_core/info.h clc_core/calc.h 
		$(CC) $< $(CFLAGS) -o $@

clc_core/calc.o: clc_core/calc.c clc_core/CPUTopology.c clc_core/calc.h clc_core/CPUTopology.h
		$(CC) $^ $(CFLAGS) -o $@	

server/server_main.o: server/server_main.c clc_core/info.h
		$(CC) $^ $(CFLAGS) -o $@

## 

-include *.d

clean:
	cd $(SERVER_PATH) && rm -rf *.o *.d
	cd $(CLIENT_PATH) && rm -rf *.o *.d
	cd $(LIB_PATH) && rm -rf *.o *.d
