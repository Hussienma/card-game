#pragma once
#include "Constants.h"
#include "RenderWindow.hpp"
#include "UI.hpp"
#include "Utils.hpp"

#include <SDL2/SDL.h>

class GameObject {
private:
public:
  GraphicsComponent *graphics;
  GameObject(GraphicsComponent *graphics) : graphics(graphics) {}
  GameObject(SDL_Rect position, GraphicsComponent *graphics)
      : position(position), graphics(graphics) {}
  SDL_Rect position;
  bool checkCollision(int x, int y) {
    return (x >= position.x && x <= position.x + position.w &&
            y >= position.y && y <= position.y + position.h);
  }
  virtual void update();
  virtual void render();
};

struct Animation {
  int currentFrame = 0;
  int totalFrames;
  bool finished = false;

  Animation() : totalFrames(40) {}
  Animation(int frames) : totalFrames(frames) {}
};

class Card : public GameObject {
private:
  CardType type;
  Color color;
  int value;
  Animation hoverAnimation;

public:
  bool hover = false;

  Card(CardType type, Color color, int value, GraphicsComponent *graphics)
      : type(type), color(color), value(value), GameObject(graphics) {
    position.x = 0;
    position.y = 0;
    position.w = CARD_WIDTH;
    position.h = CARD_HEIGHT;
  }
  virtual void update();
  Color getColor() { return color; }
  void setColor(Color val) { color = val; }
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
  SDL_Texture *shadowTexture;
  SDL_Rect frame;

  Sprite(SDL_Texture *texture, SDL_Rect frame)
      : texture(texture), frame(frame) {}
  Sprite(SDL_Texture *texture, SDL_Rect frame, SDL_Texture *shadowTexture)
      : texture(texture), frame(frame), shadowTexture(shadowTexture) {}
};

class GraphicsComponent {
private:
  RenderWindow *window;
  Sprite *sprite;
  bool renderShadows = false;

public:
  GraphicsComponent(RenderWindow *window, Sprite *sprite)
      : window(window), sprite(sprite) {}
  GraphicsComponent(RenderWindow *window, Sprite *sprite, bool renderShadows)
      : window(window), sprite(sprite), renderShadows(renderShadows) {}
  virtual void update(GameObject &obj) {
    if (renderShadows) {
      SDL_Rect shadowPosition = obj.position;
      shadowPosition.x -= 2;
      shadowPosition.y += 4;
      window->render(sprite->shadowTexture, shadowPosition);
    }

    window->render(sprite->texture, sprite->frame, obj.position);
  }

  virtual void update(Card &card) {
    if (renderShadows) {
      SDL_Rect shadowPosition = card.position;
      shadowPosition.x -= 2;
      shadowPosition.y -= 4;
      window->render(sprite->shadowTexture, shadowPosition);
    }

    window->render(sprite->texture, sprite->frame, card.position);
  }

  virtual void update(UI &ui);
  virtual void setColor(Uint8 r, Uint8 g, Uint8 b);
};
