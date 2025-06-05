BIN = SigAction SigAction.mod UDPEchoServer-SIGIO
SigAction_O = DieWithError.o SigAction.o
SigAction.mod_O = DieWithError.o SigAction.mod.o
UDPEchoServer-SIGIO_O = DieWithError.o UDPEchoServer-SIGIO.o

all : $(BIN)

SigAction : $(SigAction_O)
	gcc -o SigAction $(SigAction_O)

SigAction.mod : $(SigAction.mod_O)
	gcc -o SigAction.mod $(SigAction.mod_O)

UDPEchoServer-SIGIO : $(UDPEchoServer-SIGIO_O)
	gcc -o UDPEchoServer-SIGIO $(UDPEchoServer-SIGIO_O)

%.o : %.c %.h
	gcc -c $>

clean :
	rm -f $(BIN) $(SigAction_O) $(SigAction.mod_O)
