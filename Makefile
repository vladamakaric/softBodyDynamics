SRC = $(wildcard src/*.cpp)
LIB = -lGL -lGLU -lSDL -lSDLmain

all: 
	g++ $(SRC) -o sbd $(LIB) 

clean:
	@echo Cleaning up...
	@rm sbd
	@echo Done.
