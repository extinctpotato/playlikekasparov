LIBS=-lGL -lglfw -lGLEW
HEADERS=models/all.h
FILES=lodepng.cpp main.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o main $(FILES)  $(LIBS) -I.
