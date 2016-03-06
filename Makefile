COMPILE = g++ 
FLAGS = -Wall -Werror -ansi -pedantic
SRCDIR = src/main.cpp

all:
	mkdir -p bin
	$(COMPILE) $(FLAGS) $(SRCDIR) -o bin/rshell

rshell:
	mkdir -p bin
	$(COMPILE) $(FLAGS) $(SRCDIR) -o bin/rshell

clean:
	rm -r bin
	rm -rf *~ *.o a.out