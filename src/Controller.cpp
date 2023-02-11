#include "Controller.hpp"
#include "App.hpp"
#include "Config.hpp"
#include <iostream>

using namespace std;

Controller::Controller(App& app) : app(app)
{
  if (Config::isDebugMode)
  {
    cout << " Constructing Controller" << endl;
  }
}

Controller::~Controller()
{
  if (Config::isDebugMode)
  {
    cout << " Deconstructing Controller" << endl;
  }
}

void Controller::Initialize()
{
  if (Config::isDebugMode)
  {
    cout << " Initializing Controller" << endl;
  }
}

void Controller::Run()
{
  if (Config::isDebugMode)
  {
    // cout << " Running Controller" << endl;
  }

  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      app.Quit();
      break;
    }
  }
}