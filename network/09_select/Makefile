BIN = TCPEchoServer-Select tag_server tag_client tag_server.mod tag_client.mod
INCLUDE = ../include
MYLIBDIR = ../mylib
CFLAGS = -I$(INCLUDE) -I$(MYLIBDIR)
MYLIB = $(MYLIBDIR)/mylib.a
TCPEchoServer-Select_O = AcceptTCPConnection.o CreateTCPServerSocket.o DieWithError.o HandleTCPClient.o TCPEchoServer-Select.o
tag_server_O = tag_server.o tag_session.o
tag_client_O = tag_client.o tag_session.o
tag_server.mod_O = tag_server.mod.o tag_session.mod.o
tag_client.mod_O = tag_client.mod.o tag_session.mod.o

all : $(BIN)

TCPEchoServer-Select : $(TCPEchoServer-Select_O)
	gcc -o TCPEchoServer-Select $(TCPEchoServer-Select_O)

tag_server : $(tag_server_O)
	gcc -o tag_server $(tag_server_O) $(MYLIB) -lcurses

tag_client : $(tag_client_O)
	gcc -o tag_client $(tag_client_O) $(MYLIB) -lcurses

tag_server.mod : $(tag_server.mod_O)
	gcc -o tag_server.mod $(tag_server.mod_O) $(MYLIB) -lcurses

tag_client.mod : $(tag_client.mod_O)
	gcc -o tag_client.mod $(tag_client.mod_O) $(MYLIB) -lcurses

%.o : %.c ../include/%.h %.h
	gcc -c $>

clean :
	rm -f $(BIN) $(TCPEchoServer-Select_O) $(tag_server_O) $(tag_client_O) $(tag_server.mod_O) $(tag_client.mod_O)
