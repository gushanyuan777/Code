CC=g++
CFLAGS=-std=c++11 -Wall

all: test report

test: test.cpp HeapSort.h
	$(CC) $(CFLAGS) -o test test.cpp

report: report.tex
	pdflatex report.tex
	pdflatex report.tex

clean:
	rm -f test report.pdf