CC := g++

FLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

SRCFILES := $(wildcard src/*.cpp)

all: $(SRCFILES:src/%.cpp=obj/%.o)
	$(CC) obj/*.o $(FLAGS) -o bin/prog

obj/%.o: src/%.cpp
	$(CC) -c $< $(FLAGS) -o $@ -I./inc

run: bin/prog
	bin/prog

.PHONY: clean
clean:
	rm -rf obj/*
	rm -rf bin/*
