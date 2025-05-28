#*********************************************/
#*       File name:  Makefile                */
#*    Project name:  socket/3moku            */
#*      Month/Year:  Jan/2003                */
#*          Author:  Shuichi YUKITA          */
#*         Amender:  Yasuyuki SAITO          */
#*********************************************/

MYLIBDIR =  ../mylib

MYLIB    =  $(MYLIBDIR)/mylib.a

CFLAGS   =  -I$(MYLIBDIR) -g

BIN      =	server \
		client


all:	$(BIN)

clean:
	rm -f $(BIN) *.o *~


server.o \
client.o \
goban.o: \
		goban.h



server: \
		server.o \
		goban.o
	gcc -o $@  $^  $(MYLIB)

client: \
		client.o \
		goban.o
	gcc -o $@  $^  $(MYLIB)
