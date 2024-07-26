#pragma once

class RenderWindow;
class Game;
class Player;
class GameObject;
class Card;
class UI;
class LinkedList;

class InputComponent;
class PlayerInputCOmponent;
class UIInputComponent;

class GraphicsComponent;
class Sprite;

enum Color { RED, YELLOW, GREEN, BLUE, BLACK };
enum CardType { NUMBER, DRAW_2, DRAW_4, WILD, REVERSE, SKIP };
enum CardState { IN_DECK, IN_HAND, PLAYED };

enum ApplicationState { MAIN_MENU, IN_GAME };
