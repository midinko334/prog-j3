BIN = server client server.mod client.mod
MYLIBDIR = ../mylib
MYLIB = $(MYLIBDIR)/mylib.a
CFLAGS = -I$(MYLIBDIR)
server_O = server.o sessionman.o
client_O = client.o session.o
server.mod_O = server.o sessionman.mod.o
client.mod_O = client.mod.o session.mod.o

all : $(BIN)

server : $(server_O)
	gcc -o server $(server_O) $(MYLIB) -lcurses

client : $(client_O)
	gcc -o client $(client_O) $(MYLIB) -lcurses

server.mod : $(server.mod_O)
	gcc -o server.mod $(server.mod_O) $(MYLIB) -lcurses

client.mod : $(client.mod_O)
	gcc -o client.mod $(client.mod_O) $(MYLIB) -lcurses

%.o : %.c ../include/%.h %.h
	gcc -c $>

clean :
	rm -f $(BIN) $(TCPEchoServer-Select_O) $(server_O) $(client_O) $(server.mod_O) $(client.mod_O)
