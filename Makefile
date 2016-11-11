FLAGS_SO    = -fpic
LINKER_SO   = -shared
LIBS_SDL    = -lSDL2 -lSDL2_image -lSDL2_ttf
INCLUDE     = /usr/include/SDL2/
PARAMETER   = -std=c++11

SRC_ENGINE = src/engine/*.cc

SRC_GAME_SPACE = src/scene_space.cc src/game.cc

main : space

space : engine $(SRC_GAME_SPACE) Makefile
	g++ $(PARAMETER) -o space $(SRC_GAME_SPACE) -Wl,-rpath=./ -L./ -lengine \
	-I $(INCLUDE) -I src/engine/ -L/usr/lib/x86_64-linux-gnu $(LIBS_SDL)

engine : libengine.so

libengine.so : $(SRC_ENGINE) Makefile
	g++ -c $(PARAMETER) $(FLAGS_SO) -I $(INCLUDE) $(SRC_ENGINE)
	g++ $(LINKER_SO) -o libengine.so *.o -L/usr/lib/x86_64-linux-gnu $(LIBS_SDL)
	rm *.o
