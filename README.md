# Uno card game in C++ using SDL2

This is a game I made while learning the SDL library. SDL(Simple Direct Layer) is a cross-platform library that provides api to access graphics, audio, keyboard and joysticks.

## Game Rules:
It is a simple 2-player Uno game with the exception that you can't put a +2 over a +2 to give the opponent +4 (might add that later). You apply either play the same color or the same value of the last card played or draw a card (using spacebar). There are also wild cards which change the playing color. First player to play all there cards wins.

## How to Compile For Linux:
A Makefile is provided with the command 
```
make run
```

to compile for linux. The command:

```
g++ -I./include ./source/*.cpp -o Uno -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
```

can also be used

## How to Compile for Windows:
You use Windows LOL. There is an executable provided in the repo however if you want to compile from source the Makefile command:

```
make compile windows
```


can be used. Alternatively, You can run the command:

```
g++ -I./SDL2/include -L./SDL2/lib -I./include -o Uno ./source/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -std=gnu++11
```
MinGW is required for those commands. I recommend <a href="https://nuwen.net/mingw.html">This Distro</a> as the official one causes some errors.

## Currently Known Issues
Here are some of the current issues with the game which I am working on. Let me know if you find any more (thanks! :)
1. The game freezes during the opponent's turn.
2. It's hard tell when's your turn.
3. The opponent AI is too simple/predictable.

## Future Updates
While I do plan to add multiplayer for it eventually, it is not something I want to be doing right now.
