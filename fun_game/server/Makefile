# -*- MakeFile -*-

ifeq ($(OS), Windows_NT)
	target = win
	clr = win_clean
else
	target = linux
	clr = linux_clean
endif

all: $(target)

linux: main.o main.h
	gcc main.o -o server

win: main.o main.h
	gcc main.o -o server -lws2_32

clean: $(clr)

linux_clean:
	rm -f *.o server

win_clean:
	del *.o server.exe
