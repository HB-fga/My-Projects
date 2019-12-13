# Executavel
BINFOLDER := bin/
# .hpp
INCFOLDER := inc/
# .cpp
SRCFOLDER := src/
# .o
OBJFOLDER := obj/
CC := g++
CFLAGS := `pkg-config --libs --cflags sdl2`
SRCFILES := $(wildcard src/*.cpp)
all: $(SRCFILES:src/%.cpp=obj/%.o)
	$(CC) obj/*.o -o bin/prog $(CFLAGS)
obj/%.o: src/%.cpp
	$(CC) -c $< -o $@ -I./inc $(CFLAGS)
run: bin/prog
	bin/prog
.PHONY: clean
clean:
	rm -rf obj/*
	rm -rf bin/*
