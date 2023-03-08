CC = g++
CFLAGS = -g -Wall

#I got this OS check from here https://stackoverflow.com/questions/4058840/makefile-that-distinguishes-between-windows-and-unix-like-systems
ifdef OS
   RM = del /Q
   EXT = .exe
   FixPath = $(subst /,\,$1)
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
      EXT =
      FixPath = $1
   endif
endif

.PHONY: all clean

all: caesar vigenere

caesar: CaesarSolver.o CaesarRun.o
	$(CC) $(CFLAGS) -o caesar CaesarSolver.o CaesarRun.o

vigenere: CaesarSolver.o Vigenere.o DataManipulation.o VigenereRun.o
	$(CC) $(CFLAGS) -o vigenere CaesarSolver.o Vigenere.o DataManipulation.o VigenereRun.o

CaesarSolver.o: CaesarSolver.cpp
	$(CC) -c CaesarSolver.cpp

CaesarRun.o: CaesarRun.cpp
	$(CC) -c CaesarRun.cpp

Vigenere.o: Vigenere.cpp
	$(CC) -c Vigenere.cpp

VigenereRun.o: VigenereRun.cpp
	$(CC) -c VigenereRun.cpp

DataManipulation.o: DataManipulation.cpp
	$(CC) -c DataManipulation.cpp

clean:
	$(RM) caesar$(EXT) vigenere$(EXT) *.o
