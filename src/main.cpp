#include "Config.hpp"
#include "App.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  if (Config::isDebugMode)
  {
    cout << "Running main" << endl;
  }
  App app{};
}