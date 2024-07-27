#pragma once
#include "Game.hpp"
#include "Player.hpp"
#include "Controller.hpp"

#include <SDL2/SDL.h>

class InputComponent {
public:
  InputComponent() {}
  virtual void update(Game &game, Player &player){}
  virtual void update(Game &game, UI &ui){}
};

class PlayerInputComponent : public InputComponent {
public:
  PlayerInputComponent(): InputComponent(){}
  virtual void update(Game &game, Player &player);
};

class PlayerAIInputComponent : public InputComponent {
public:
  PlayerAIInputComponent(): InputComponent(){}
  virtual void update(Game &game, Player &player);
};

class UIInputComponent : public InputComponent {
public:
  UIInputComponent(): InputComponent() {}
  virtual void update(Game &game, UI &ui);
};
