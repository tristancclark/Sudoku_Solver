OBJ = sudoku.o	main.o
EXE = sudoku
CXX = g++
CXXFLAGS = -Wall	-g	-MMD

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^

-include $(OBJ:.o=.d)

clean:
	rm -f *.o *copy.dat *.d
