BIN = SERVER CLIENT
SERVER_O = server.mod.c
CLIENT_O = client.mod.c

all : $(BIN)

SERVER : $(SERVER_O)
	gcc -o SERVER $(SERVER_O)

CLIENT : $(CLIENT_O)
	gcc -o CLIENT $(CLIENT_O)

%.o : %.c %.h
	gcc -c $>

clean :
	rm -f $(BIN) %.o
