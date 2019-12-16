include ../../common.make

DEPS=*.h
../obj/%.o: %.cpp $(DEPS)
	$(CXX) $(IFLAGS) -c -o $@ $< $(CFLAGS) 

all: ../obj/Mesh.o ../obj/Camera.o ../obj/Texture.o ../obj/Shader.o ../obj/
	+$(MAKE) -C stbi
