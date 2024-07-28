# Uno card game in C++ using SDL2

![Screenshot from 2024-07-28 19-53-28](https://github.com/user-attachments/assets/8667b734-5129-4088-a0fa-b88bcf7407f5)


This is a game I made while learning the SDL library. SDL(Simple Direct Layer) is a cross-platform library that provides api to access graphics, audio, keyboard and joysticks.

## Game Rules:

![Screenshot from 2024-07-28 19-57-41](https://github.com/user-attachments/assets/be964e8d-43e2-4d4b-a064-f8a36efed9e9)
![Screenshot from 2024-07-28 19-58-15](https://github.com/user-attachments/assets/823b8dda-a07c-4792-b2a4-b6c5ff6c2aa7)
![Screenshot from 2024-07-28 19-56-49](https://github.com/user-attachments/assets/e14e0e1a-eeb5-4962-8390-5c2814a5f26b)


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
