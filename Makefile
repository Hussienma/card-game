
run:
	g++ -I./include ./source/*.cpp -o Uno -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
	./Uno
debug:
	g++ -o Debug -g -I./include ./source/*.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
	./Debug
compile windows:
	x86_64-w64-mingw32-g++ -I./SDL2/include -L./SDL2/lib -I./include -o Uno ./source/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
