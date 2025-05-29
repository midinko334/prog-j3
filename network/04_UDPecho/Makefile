BIN = UDPESERVER UDPECLIENT
SERVER_O = UDPEchoServer.c DieWithError.c
CLIENT_O = UDPEchoClient.c DieWithError.c

all : $(BIN)

UDPESERVER : $(SERVER_O)
	gcc -o UDPEchoSERVER $(SERVER_O)

UDPECLIENT : $(CLIENT_O)
	gcc -o UDPEchoCLIENT $(CLIENT_O)

%.o : %.c UDPEcho.h
	gcc -c $>

clean :
	rm -f $(BIN)
