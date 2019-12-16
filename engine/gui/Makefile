include ../../common.make

DEPS=*.h
../../obj/%.o: %.cpp $(DEPS)
	$(CXX) $(IFLAGS) -c -o $@ $< $(CFLAGS)

all: ../../obj/Button.o ../../obj/Menu.o 
