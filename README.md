# jxo-game
I dunno, some game...

win-32

g++ -std=c++17 -I dependencies/SDL2/include -L dependencies/SDL2/lib -I dependencies/SDL2_image/include -L dependencies/SDL2_image/lib -I dependencies/box2d/include -L dependencies/box2d/lib -o main src/main.cpp src/utils/*.cpp src/game_engine/*.cpp src/models/*.cpp -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l box2d