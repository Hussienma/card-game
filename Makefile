
all:
	g++ -I./include ./source/*.cpp -o build -lSDL2main -lSDL2 -lSDL2_image
	./build
