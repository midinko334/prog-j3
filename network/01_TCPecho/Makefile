BIN = TCPESERVER TCPECLIENT
SERVER_O = TCPEchoServer.c HandleTCPClient.c DieWithError.c
CLIENT_O = TCPEchoClient.c DieWithError.c

all : $(BIN)

TCPESERVER : $(SERVER_O)
	gcc -o TCPEchoSERVER $(SERVER_O)

TCPECLIENT : $(CLIENT_O)
	gcc -o TCPEchoCLIENT $(CLIENT_O)

%.o : %.c TCPEcho.h
	gcc -c $>

clean :
	rm -f $(BIN)
