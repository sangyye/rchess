# compiler options
#--------------------------------
CC = gcc
CFLAGS = -Wall -g -pedantic

# project files
#--------------------------------
SERVER = chessServer
SERVER_OBJECTS = server.o chess_svc.o chess_xdr.o

CLIENT = chessClient
CLIENT_OBJECTS = client.o chess_clnt.o chess_xdr.o

# rules
#----------------------------------
all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJECTS)
	$(CC) -o $@ $+
 
$(CLIENT): $(CLIENT_OBJECTS)
	$(CC) -o $@ $+

# generic rule for compiling *.c -> *.o
%.o: %.c
	$(CC) $(CFLAGS)  -c $*.c

clean:
	rm -f $(SERVER) $(CLIENT) $(SERVER_OBJECTS) $(CLIENT_OBJECTS)
