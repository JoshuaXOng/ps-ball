obj_wildcard := $(wildcard *.o)

target := c++17
external_dependencies := -I dependencies/SDL2/include -L dependencies/SDL2/lib -I dependencies/SDL2_image/include -L dependencies/SDL2_image/lib -I dependencies/box2d/include -L dependencies/box2d/lib -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l box2d
src_code := src/main.cpp src/utils/*.cpp src/game_engine/*.cpp src/models/*.cpp

build: 
	g++ -std=${target} ${external_dependencies} -o main ${src_code}