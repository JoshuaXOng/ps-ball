target := c++17
obj_wildcard := $(wildcard *.o)

build: $(obj_wildcard)
	g++ -std=${target} $(obj_wildcard) -o main
src:
	g++ -std=${target} -c src/main.cpp src/utils/*.cpp src/game_engine/*.cpp src/models/*.cpp
dependencies:
	g++ -std=${target} -c -I dependencies/SDL2/include -L dependencies/SDL2/lib -I dependencies/SDL2_image/include -L dependencies/SDL2_image/lib -I dependencies/box2d/include -L dependencies/box2d/lib -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l box2d
