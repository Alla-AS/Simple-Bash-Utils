CC = gcc -std=c11 -D_GNU_SOURCE
CFLAGS=-Wall -Werror -Wextra
SOURCES=s21_cat.c

all: s21_cat cat_test

s21_cat:
	$(CC) $(CFLAGS) $(SOURCES) -o s21_cat

cat_test:
	chmod +x t_cat.sh
	bash t_cat.sh

clean:
	rm -rf s21_cat 
	rm -rf *.a *.out *.o log.txt

check:
	cp ../../materials/linters/CPPLINT.cfg ./
	make s21_cat
	cppcheck --enable=all --suppress=missingIncludeSystem ./*.c
	python3 ../../materials/linters/cpplint.py --extensions=c ./*.c
	python3 ../../materials/linters/cpplint.py --extensions=c ./*.h
	rm -rf *.cfg

rebuild:
	make clean
	make all
	rm -rf  *.o *.a