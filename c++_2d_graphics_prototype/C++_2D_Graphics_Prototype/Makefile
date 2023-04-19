all: compile run

compile:
	g++ main.cpp Player.hpp Player.cpp -o game.exe -I ./include -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lshell32
run:
	.\game.exe