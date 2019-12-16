include ../../../common.make

DEPS=*.h
../../obj/%.o: %.c $(DEPS)
	$(CXX) $(IFLAGS) -c -o $@ $< $(CFLAGS) 

all: ../../obj/stb_image.o
