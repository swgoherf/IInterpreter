CXX = g++
CXXFLAGS = -std=c++17 -Wall -I.
TARGET = chago.exe
OBJ = main.o Lexer.o Interpreter.o

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Lexer.o: Lexer/Lexer.cpp
	$(CXX) $(CXXFLAGS) -c Lexer/Lexer.cpp -o Lexer.o

Interpreter.o: Interpreter/Interpreter.cpp
	$(CXX) $(CXXFLAGS) -c Interpreter/Interpreter.cpp -o Interpreter.o

clean:
	del /q *.o $(TARGET)