ifeq ($(OS),Windows_NT)
	CC=gcc
else
	CC=i686-w64-mingw32-gcc-win32
endif
LIBS = -luser32 -lgdi32
DEPS = globals.h eventhandler.h shapes.h
OBJ = shapes.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(LIBS)

all: master slave

master: masterhandler.o $(OBJ)
	$(CC) -o $@.exe $^ $(LIBS)

slave: slavehandler.o $(OBJ)
	$(CC) -o $@.exe $^ $(LIBS)

	
.PHONY: clean

clean:
	rm *.o
