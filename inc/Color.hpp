#pragma once

#include "SDL.h"

class Color
{
public:
  Color(Uint8 r, Uint8 g, Uint8 b);
  ~Color();

  Uint8 r;
  Uint8 g;
  Uint8 b;
};