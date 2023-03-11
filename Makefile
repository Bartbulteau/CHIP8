CXX := g++
CXXFLAGS := -Wall -Werror -std=c++11

#LIBS INSTALLED IN A STANDARD WAY
LIBS := -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system
INCLUDES := -I/usr/local/Cellar/sfml/2.5.1_2/include

SOURCEDIR := src

SRC := $(shell find $(SOURCEDIR) -name '*.cpp')

OBJ := $(SRC:%.cpp=%.o)

BIN := GBEmu 

all:$(BIN)

$(OBJ:%.o) : $(SRC:%.cpp)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INCLUDES)

$(BIN) : $(OBJ)
	$(CXX) -o $@ main.cpp $^ $(LIBS) $(CXXFLAGS)

shallowclean:
	rm -f main.o
	rm -f $(OBJ)

clean:
	rm -f main.o
	rm -f $(OBJ)
	rm -f $(BIN)

total:
	make clean
	make
	clear
	./$(BIN)