COMPILE = g++ 
FLAGS = -Wall -Werror -ansi -pedantic 
SRCDIR = src/main.cpp

all: 
	$(COMPILE) $(FLAGS) $(SRCDIR)

clean:
	rm -rf *~ *.o a.out
