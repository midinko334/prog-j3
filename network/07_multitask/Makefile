BIN = fork TCPEchoServer-Fork
TCPEchoServer-Fork_O = AcceptTCPConnection.o CreateTCPServerSocket.o DieWithError.o HandleTCPClient.o TCPEchoServer-Fork.o
TCPEchoServer-Fork.o = $(INCLUDE)/TCPEchoServer.h
fork_O = fork.o
INCLUDE = ../include
CFLAGS = -I $(INCLUDE)

all : $(BIN)

TCPEchoServer-Fork : $(TCPEchoServer-Fork_O)
	gcc -o TCPEchoServer-Fork $(TCPEchoServer-Fork_O)

fork : $(fork_O)
	gcc -o fork $(fork_O)

%.o : %.c %.h
	gcc -c $>

clean :
	rm -f $(BIN)
