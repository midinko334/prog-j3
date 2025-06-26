BIN = TCPEchoServer-Thread TCPEchoServer-ForkN
TCPEchoServer-Thread_O = AcceptTCPConnection.o CreateTCPServerSocket.o DieWithError.o HandleTCPClient.o TCPEchoServer-Thread.o
TCPEchoServer-ForkN_O = AcceptTCPConnection.o CreateTCPServerSocket.o DieWithError.o HandleTCPClient.o TCPEchoServer-ForkN.o
INCLUDE = ../include
CFLAGS = -I$(INCLUDE)

all : $(BIN)

TCPEchoServer-Thread : $(TCPEchoServer-Thread_O)
	gcc -pthread -o TCPEchoServer-Thread $(TCPEchoServer-Thread_O)

TCPEchoServer-ForkN : $(TCPEchoServer-ForkN_O)
	gcc -o TCPEchoServer-ForkN $(TCPEchoServer-ForkN_O)

%.o : %.c ../include/%.h
	gcc -c $>

clean :
	rm -f $(BIN) $(TCPEchoServer-Thread_O) $(TCPEchoServer-ForkN_O)
