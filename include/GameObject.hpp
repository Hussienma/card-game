#pragma once
#include "Constants.h"
#include "RenderWindow.hpp"
#include <SDL2/SDL.h>
#include <fmtmsg.h>

enum Color { RED, YELLOW, GREEN, BLUE, BLACK };
enum CardType { NUMBER, DRAW_2, DRAW_4, WILD, REVERSE, SKIP };
enum CardState { IN_DECK, IN_HAND, PLAYED };

class GraphicsComponent;
class InputComponent;

class GameObject {
private:
  GraphicsComponent *graphics;

public:
  GameObject(GraphicsComponent *graphics) : graphics(graphics) {}
  SDL_Rect position;
  bool checkCollision(int x, int y) {
    return (x >= position.x && x <= position.x + position.w &&
            y >= position.y && y <= position.y + position.h);
  }
  virtual void update();
  virtual void render();
};

class Card : public GameObject {
private:
  CardType type;
  Color color;
  int value;

public:
  bool hover = false;

  Card(CardType type, Color color, int value, GraphicsComponent *graphics)
      : type(type), color(color), value(value), GameObject(graphics) {
    position.x = 0;
    position.y = 0;
    position.w = CARD_WIDTH;
    position.h = CARD_HEIGHT;
  }
  Color getColor() { return color; }
  std::string getColorString() {
    switch (color) {
    case YELLOW:
      return "Yellow";
    case GREEN:
      return "Green";
    case RED:
      return "Red";
    case BLUE:
      return "Blue";
    case BLACK:
      return "Black";
    default:
      return "Unknown";
    }
  }
  int getValue() { return value; }
  CardType getType() { return type; }
  std::string getTypeString() {
    switch (type) {
    case DRAW_2:
      return "+2";
      break;
    case DRAW_4:
      return "+4";
      break;
    case REVERSE:
      return "Reverse";
      break;
    case SKIP:
      return "Skip";
      break;
    case WILD:
      return "Wild";
      break;
    default:
      return "Unknown";
    }
  }
  std::string to_string() {
    if (type == NUMBER)
      return std::to_string(value) + " of " + getColorString();
    if (type == DRAW_4 || type == WILD)
      return getTypeString();
    return getTypeString() + " of " + getColorString();
  }
};

struct Sprite {
  SDL_Texture *texture;
  SDL_Rect frame;

  Sprite(SDL_Texture *texture, SDL_Rect frame)
      : texture(texture), frame(frame) {}
};

class GraphicsComponent {
private:
  RenderWindow *window;
  Sprite *sprite;

public:
  GraphicsComponent(RenderWindow *window, Sprite *sprite)
      : window(window), sprite(sprite) {}
  virtual void update(GameObject &obj) {
    window->render(sprite->texture, sprite->frame, obj.position);
  }

  virtual void update(Card &card) {
    std::cout << "Rendering " << card.getColorString() << " of "
              << card.getValue() << std::endl;
    window->render(sprite->texture, card.position, sprite->frame);
  }
};

class Player;
class Game;

class InputComponent {
private:
public:
  InputComponent() {}
  virtual void update(Game &game, Player &player);
};