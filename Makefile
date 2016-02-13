COMPILE = g++ 
FLAGS = -Wall -Werror -ansi -pendantic 
SRCDIR = src/main.cpp

all: 
	$(COMPILE) $(FLAGS) $(SRCDIR)

clean:
	rm -rf *~ *.o a.out
