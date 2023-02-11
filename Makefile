CC = g++
CFLAGS = -g -Wall

#I got this OS check from here https://stackoverflow.com/questions/4058840/makefile-that-distinguishes-between-windows-and-unix-like-systems
ifdef OS
   RM = del /Q
   FixPath = $(subst /,\,$1)
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
      FixPath = $1
   endif
endif

all: caesar

caesar: CaesarSolver.cpp CaesarRun.cpp
	$(CC) $(CFLAGS) -o caesar CaesarSolver.cpp CaesarRun.cpp

clean:
	$(RM) caesar.exe