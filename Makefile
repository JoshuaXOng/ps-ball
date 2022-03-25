obj_wildcard := $(wildcard *.o)

target := c++17
external_header_dirs := -I dependencies/SDL2/include -I dependencies/SDL2_image/include -I dependencies/box2d/include
additional_search_dirs := -L dependencies/SDL2/lib -L dependencies/SDL2_image/lib -L dependencies/box2d/lib
external_libs := -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l box2d
src_code := src/main.cpp

build: 
	g++ -std=${target} ${external_header_dirs} ${additional_search_dirs} -o main ${src_code} ${external_libs}
