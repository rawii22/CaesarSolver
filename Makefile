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

all: caesar vigenere

caesar: CaesarSolver.cpp CaesarRun.cpp
	$(CC) $(CFLAGS) -o caesar CaesarSolver.cpp CaesarRun.cpp

vigenere: CaesarSolver.cpp Vigenere.cpp DataManipulation.cpp VigenereRun.cpp
	$(CC) $(CFLAGS) -o vigenere CaesarSolver.cpp Vigenere.cpp DataManipulation.cpp VigenereRun.cpp

clean:
	$(RM) caesar$(EXT) vigenere$(EXT) a$(EXT)