BIN = UDPEchoClient-Timeout
UDPEchoClient-Timeout_O = UDPEchoClient-Timeout.o DieWithError.o

all : $(BIN)

UDPEchoClient-Timeout : $(UDPEchoClient-Timeout_O)
	gcc -o UDPEchoClient-Timeout $(UDPEchoClient-Timeout_O)

%.o : %.c %.h
	gcc -c $>

clean :
	rm -f $(BIN) $(UDPEchoClient-Timeout_O)
