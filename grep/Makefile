CC= gcc -std=c11 -D_GNU_SOURCE
CFLAGS= -g -Wall -Wextra -Werror
SOURCES= s21_grep.c

all: s21_grep grep_test

s21_grep:
	$(CC) $(CFLAGS) $(SOURCES) -o s21_grep

grep_test:
	chmod +x t_grep.sh
	bash t_grep.sh

check:
	cp ../../materials/linters/CPPLINT.cfg ./
	make s21_grep
	cppcheck --enable=all --suppress=missingIncludeSystem ./*.c
	python3 ../../materials/linters/cpplint.py --extensions=c ./*.c
	python3 ../../materials/linters/cpplint.py --extensions=c ./*.h
	rm -rf *.cfg

clean:
	rm -rf s21_grep 
	rm -rf *.a *.out *.o log.txt

rebuild:
	make clean
	make all
	rm -rf  *.o *.a