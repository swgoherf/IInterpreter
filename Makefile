CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = chago.exe
OBJ = main.o Lexer.o Interpreter.o

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Lexer.o: Lexer.cpp
	$(CXX) $(CXXFLAGS) -c Lexer.cpp

Interpreter.o: Interpreter.cpp
	$(CXX) $(CXXFLAGS) -c Interpreter.cpp

clean:
	del /q *.o $(TARGET)