# flags

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

CFLAGS = -g -MD -c -std=c99
ADDIT_FLAGS = -pthread -lm

# pathes

SERVER_PATH 	= Server
SERVER_SOURCES 	= $(SERVER_PATH)/server_main.c
SERVER_OBJS		= $(SERVER_SOURCES:.c=.o)
SERVER_EXEC		= server


CLIENT_PATH  	= Client
CLIENT_SOURCES 	= $(CLIENT_PATH)/client_main.c $(CLIENT_PATH)/threads_int_func.c
CLIENT_OBJS		= $(CLIENT_SOURCES:.c=.o)
CLIENT_EXEC		= client



# names of output files

all: Bclient Bserver

### compile stuff

%.o: %.c
		$(CC) $(CFLAGS) -o $@ $<

# client

Bclient: $(CLIENT_SOURCES) $(CLIENT_EXEC)

$(CLIENT_EXEC): $(CLIENT_OBJS)
		$(CC) $(CLIENT_OBJS) $(ADDIT_FLAGS) -o $@

# Server

Bserver: $(SERVER_SOURCES) $(SERVER_EXEC)

$(SERVER_EXEC): $(SERVER_OBJS)
		$(CC) $(SERVER_OBJS) $(ADDIT_FLAGS) -o $@

## 

-include *.d

.PHONY: clean

clean:
	cd $(SERVER_PATH) && rm -rf *.o *.d
	cd $(CLIENT_PATH) && rm -rf *.o *.d
	cd $(LIB_PATH) && rm -rf *.o *.d
