#pragma once

#include "Controller.hpp"
#include "Model.hpp"
#include "View.hpp"

class App
{
public:
  App();
  ~App();

  void Initialize();
  void Run();

  void Quit();

  Model model;
  View view;
  Controller controller;

private:
  bool isRunning = true;
};