include ../../common.make

DEPS=*.h
../../obj/%.o: %.cpp $(DEPS)
	$(CXX) $(IFLAGS) -c -o $@ $< $(CFLAGS) 

all: ../../obj/Player.o ../../obj/PlayerController.o ../../obj/Game.o ../../obj/GameSettings.o ../../obj/Map.o ../../obj/Bsp.o
