LIBS=-lGL -lglfw -lGLEW
HEADERS=models/all.h shaderprogram.h misc.h
FILES=lodepng.cpp main.cpp shaderprogram.cpp misc.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o main $(FILES)  $(LIBS) -I.
