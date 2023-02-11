#include "Bar.hpp"
#include "Config.hpp"
#include <iostream>

using namespace std;

Bar::Bar(int barType, float value) : barType(barType), value(value)
{
  if (Config::isDebugMode)
  {
    cout << "   Constructing Bar" << endl;
  }
}

Bar::~Bar()
{
  if (Config::isDebugMode)
  {
    cout << "   Deconstructing Bar" << endl;
  }
}

int Bar::GetType() { return barType; }

float Bar::GetValue() { return value; }