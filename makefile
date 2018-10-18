main: maincpy.o sudoku.o
	g++ maincpy.o sudoku.o -o main
main.o: maincpy.cpp sudoku.h
	g++ -Wall -g -c maincpy.cpp
sudoku.o: sudokurefined.cpp sudoku.h
	g++ -Wall -g -c sudokurefined.cpp -o sudoku.o
clean:
	rm -f *.o main *copy.dat
