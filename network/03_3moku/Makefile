#*********************************************/
#*       File name:  Makefile                */
#*    Project name:  socket/3moku            */
#*      Month/Year:  Jan/2003                */
#*          Author:  Shuichi YUKITA          */
#*         Amender:  Yasuyuki SAITO          */
#*********************************************/

MYLIBDIR =  ./mylib

MYLIB    =  $(MYLIBDIR)/mylib.a

CFLAGS   =  -I$(MYLIBDIR) -g

BIN      =	server \
		client


all:	$(BIN)

clean:
	rm -f $(BIN) *.o *~


server.mod.o \
client.mod.o \
goban.mod.o: \
		goban.mod.h



server: \
		server.mod.o \
		goban.mod.o
	gcc -o $@  $^  $(MYLIB)

client: \
		client.mod.o \
		goban.mod.o
	gcc -o $@  $^  $(MYLIB)

%.o : %.mod.c
	gcc -c $>
