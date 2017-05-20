# To compile and run the simple shell, just
# have all 3 files in the same directory:
#   Makefile  shell.c  shell.h
# And then run: make
# You will then get a "shell" binary, which
# you can run with: ./shell
#
all: shell

shell: shell.c shell.h
	gcc -Wall -o shell shell.c

clean: clean_all

clean_all:
	rm -f shell
