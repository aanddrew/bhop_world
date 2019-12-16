include common.make

OBJS=obj/*.o stage3/obj/*.o

%.o: %.cpp
	$(CXX) $(IFLAGS) -c -o obj/$@ $< $(LFLAGS) 

bhop_world: main.o
	+$(MAKE) -C engine/graphics
	+$(MAKE) -C engine/math
	+$(MAKE) -C engine/game
	+$(MAKE) -C engine/physics
	+$(MAKE) -C stage3
	$(CXX) -o bhop_world $(OBJS) $(LFLAGS)

.PHONY : clean
clean:
	-rm $(OBJS)
