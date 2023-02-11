#pragma once

#include "SDL.h"

class Controller
{
public:
  Controller(class App& app);
  ~Controller();

  void Initialize();
  void Run();

private:
  class App& app;
};