#include "Color.hpp"
#include "Config.hpp"
#include <iostream>

using namespace std;

Color::Color(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b)
{
  if (Config::isDebugMode)
  {
    cout << "  Constructed color" << endl;
  }
}

Color::~Color()
{
  if (Config::isDebugMode)
  {
    cout << "  Deconstructed color" << endl;
  }
}