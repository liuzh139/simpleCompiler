BISON	= bison -d -v
FLEX		= flex
CC		= gcc
CXX		= g++ -g -ggdb
TARGET	= lang

all: $(TARGET)

$(TARGET): ast.o parser.o lexer.o main.o
	$(CXX) -o $(TARGET) ast.o parser.o lexer.o main.o

lexer.o: lexer.l
	$(FLEX) -o lexer.cpp lexer.l
	$(CXX) -c -o lexer.o lexer.cpp

parser.o: parser.y
	$(BISON) -o parser.cpp parser.y
	$(CXX) -c -o parser.o parser.cpp

genast: ast.cpp

ast.cpp:
	python3 genast.py -i lang.def -o ast

ast.o: ast.cpp
	$(CXX) -c -o ast.o ast.cpp

main.o: main.cpp
	$(CXX) -c -o main.o main.cpp

.PHONY: clean
clean:
	rm -f *.o lexer.cpp parser.cpp parser.hpp ast.hpp ast.cpp parser.output $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET) < tests/test01.lang
	./$(TARGET) < tests/test02.lang
	./$(TARGET) < tests/test03.lang
	./$(TARGET) < tests/test04.lang
	./$(TARGET) < tests/test05.lang
	./$(TARGET) < tests/test06.lang
	./$(TARGET) < tests/test07.lang
	./$(TARGET) < tests/test08.lang
	./$(TARGET) < tests/test09.lang
	./$(TARGET) < tests/test10.lang
	./$(TARGET) < tests/test11.lang
	./$(TARGET) < tests/test12.lang
	./$(TARGET) < tests/test13.lang
	./$(TARGET) < tests/test14.lang
	./$(TARGET) < tests/test15.lang
	./$(TARGET) < tests/test16.lang
	./$(TARGET) < tests/test17.lang
	./$(TARGET) < tests/test18.lang
	./$(TARGET) < tests/test19.lang
	./$(TARGET) < tests/test20.lang
	./$(TARGET) < tests/test21.lang
	./$(TARGET) < tests/test22.lang
	./$(TARGET) < tests/test23.lang
	./$(TARGET) < tests/test24.lang
	./$(TARGET) < tests/test25.lang
	./$(TARGET) < tests/test26.lang
	./$(TARGET) < tests/test27.lang
	./$(TARGET) < tests/test28.lang
	./$(TARGET) < tests/test29.lang
	./$(TARGET) < tests/test30.lang
	./$(TARGET) < tests/test31.lang
	./$(TARGET) < tests/test32.lang
	./$(TARGET) < tests/test33.lang
	./$(TARGET) < tests/test34.lang
	./$(TARGET) < tests/test35.lang
	./$(TARGET) < tests/test36.lang
	./$(TARGET) < tests/test37.lang
	./$(TARGET) < tests/test38.lang
	./$(TARGET) < tests/test39.lang
