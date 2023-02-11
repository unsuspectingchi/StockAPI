#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class View
{
public:
  View(class App& app);
  ~View();

  bool Initialize();
  void Run();

  void DrawLogo();
  void DrawGraph(float high, float low);
  void DrawScale(float scalar, float drawnLow, float drawnRange);

  void Update(float high, float low);

private:
  class App& app;

  TTF_Font* font = NULL;
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_Texture* logoTex = NULL;
  SDL_Texture* fontTex = NULL;
};