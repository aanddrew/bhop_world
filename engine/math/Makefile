include ../../common.make

DEPS=*.h
../../obj/%.o: %.cpp $(DEPS)
	$(CXX) $(IFLAGS) -c -o $@ $< $(CFLAGS) 

all: ../../obj/Vec3.o ../../obj/Vec2.o ../../obj/Mat3.o ../../obj/Mat4.o ../../obj/Vec4.o ../../obj/Utils.o
