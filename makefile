main: maincpy.o sudoku.o
	g++ -Wall maincpy.o sudoku.o -o main
maincpy.o: main.cpp sudoku.h
	g++ -Wall -g -c maincpy.cpp
sudoku.o: sudoku.cpp sudoku.h
	g++ -Wall -g -c sudoku.cpp
clean:
	rm -f *.o main
