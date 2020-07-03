BINFOLDER := bin/

INCFOLDER := inc/

SRCFOLDER := src/

OBJFOLDER := obj/

CC := g++

FLAGS :=

LINKER_FLAGS := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

SRCFILES := $(wildcard src/*.cpp)
all: $(SRCFILES:src/%.cpp=obj/%.o)
	$(CC) $(FLAGS) obj/*.o -o bin/prog $(LINKER_FLAGS)
obj/%.o: src/%.cpp
	$(CC) $(FLAGS) -c $< -o $@ -I./inc $(LINKER_FLAGS)
run: bin/prog
	bin/prog
.PHONY: clean
clean:
	rm -rf obj/*
	rm -rf bin/*

# OBJS = game.cpp

# FLAGS =

# LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# all : $(OBJS)
# 	g++ $(OBJS) $(FLAGS) $(LINKER_FLAGS) -o prog