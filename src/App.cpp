#include "App.hpp"
#include "Config.hpp"
#include <iostream>

using namespace std;

App::App() : model(*this), view(*this), controller(*this)
{
  if (Config::isDebugMode)
  {
    cout << "Constructing App" << endl;
  }

  Initialize();
}

App::~App()
{
  if (Config::isDebugMode)
  {
    cout << "Deconstructing App" << endl;
  }
}

void App::Quit() { isRunning = false; }

void App::Initialize()
{
  if (Config::isDebugMode)
  {
    cout << "Initializing App" << endl;
  }

  model.Initialize();
  if (view.Initialize())
  {
    controller.Initialize();
    Run();
  }
}

void App::Run()
{
  if (Config::isDebugMode)
  {
    cout << "Running App" << endl;
  }

  model.agent.Update();

  while (isRunning)
  {
    model.Run();
    view.Run();
    controller.Run();
  }
}