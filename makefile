main: maincpy.o sudoku.o
	g++ maincpy.o sudoku.o -o main
main.o: maincpy.cpp sudoku.h
	g++ -Wall -g -c maincpy.cpp
sudoku.o: sudoku.cpp sudoku.h
	g++ -Wall -g -c sudoku.cpp
clean:
	rm -f *.o main *copy.dat
