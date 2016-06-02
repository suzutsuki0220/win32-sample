PROG=SimpleWindow.exe
SRC=SimpleWindow.c send_packet.c
OBJS=$(SRC:.c=.o)
RC=menu.rc
WINDRES=$(RC:.rc=.o)
CC=gcc
CFLAGS=-Wall -O3 -finput-charset=cp932 -fexec-charset=cp932
LDFLAGS=-mwindows -lws2_32
RM=del /Q

.PHONY: all clean

all: $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(PROG): $(OBJS) $(WINDRES)
	$(CC) $(CFLAGS) $(OBJS) $(WINDRES) $(LDFLAGS) -o $@

$(WINDRES): $(RC)
	windres $(RC) $(WINDRES)

clean:
	$(RM) $(OBJS) $(WINDRES) $(PROG)
