
all:
	g++ -I./include ./source/*.cpp -o Uno\ Build -lSDL2main -lSDL2 -lSDL2_image
	./Uno\ Build
