CC		= gcc
CXX		= g++
CXXFLAGS	= -g
TARGET	= calculator

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp

.PHONY: run
run: $(TARGET)
	@chmod u+x runtests.sh
	./runtests.sh

.PHONY: clean
clean:
	rm -f *.o *~ $(TARGET)
	rm -rf *.dSYM
