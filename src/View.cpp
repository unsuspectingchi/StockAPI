#include "View.hpp"
#include "App.hpp"
#include "Bar.hpp"
#include "Config.hpp"
#include <iostream>

using namespace std;

View::View(App& app) : app(app)
{
  if (Config::isDebugMode)
  {
    cout << " Constructing View" << endl;
  }
}

View::~View()
{
  if (Config::isDebugMode)
  {
    cout << " Deconstructing View" << endl;
  }

  TTF_CloseFont(font);
  SDL_DestroyTexture(logoTex);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();
}

bool View::Initialize()
{
  if (Config::isDebugMode)
  {
    cout << " Initializing View" << endl;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    cout << "Failed to initializing SDL.";
    return false;
  }

  TTF_Init();

  window = SDL_CreateWindow(Config::UI::Window::title.c_str(),
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            Config::UI::Window::windowWidth,
                            Config::UI::Window::windowHeight, 0);

  Uint32 render_flags = SDL_RENDERER_ACCELERATED;
  renderer = SDL_CreateRenderer(window, -1, render_flags);

  SDL_Surface* logoSurface = IMG_Load(Config::UI::Logo::logoPath.c_str());
  logoTex = SDL_CreateTextureFromSurface(renderer, logoSurface);
  SDL_FreeSurface(logoSurface);

  font = TTF_OpenFont(Config::UI::Font::fontPath.c_str(),
                      Config::UI::Font::fontSize);

  SDL_RenderSetLogicalSize(renderer, Config::UI::Window::resWidth,
                           Config::UI::Window::resHeight);

  app.view.Update(900, 700);
  return true;
}

void View::Run()
{
  if (Config::isDebugMode)
  {
    // cout << " Running View" << endl;
  }
}

void View::Update(float high, float low)
{
  SDL_SetRenderDrawColor(renderer, Config::UI::Window::bgColor.r,
                         Config::UI::Window::bgColor.g,
                         Config::UI::Window::bgColor.b, 255);
  SDL_RenderClear(renderer);

  DrawLogo();
  DrawGraph(high, low);

  SDL_RenderPresent(renderer);
}

void View::DrawScale(float scalar, float drawnLow, float drawnRange)
{
  for (int i = 0; i < Config::UI::Graph::numTicks + 1; ++i)
  {
    SDL_Color bgColor{Config::UI::Window::bgColor.r,
                      Config::UI::Window::bgColor.g,
                      Config::UI::Window::bgColor.b, 255};

    SDL_Surface* fontSurface = TTF_RenderText_Blended(
        font,
        to_string(
            (int)((drawnLow + i * (drawnRange / Config::UI::Graph::numTicks))))
            .c_str(),
        bgColor);
    fontTex = SDL_CreateTextureFromSurface(renderer, fontSurface);
    SDL_FreeSurface(fontSurface);

    float magicNumber =
        Config::UI::Graph::top +
        (Config::UI::Graph::height - Config::UI::Graph::offsetBottom) -
        (i * (drawnRange / (Config::UI::Graph::numTicks)) * scalar);

    SDL_Rect chartName;
    chartName.x = Config::UI::Graph::left;
    chartName.y = magicNumber - Config::UI::Font::fontSize / 2;

    SDL_QueryTexture(fontTex, NULL, NULL, &chartName.w, &chartName.h);

    SDL_SetRenderDrawColor(renderer, Config::UI::Window::bgColor.r,
                           Config::UI::Window::bgColor.g,
                           Config::UI::Window::bgColor.b, 255);
    SDL_Rect line;
    line.x = Config::UI::Graph::left + Config::UI::Graph::offsetLeft;
    line.y = magicNumber;
    line.w = Config::UI::Graph::width - (Config::UI::Graph::offsetLeft * 2);
    line.h = Config::UI::Graph::lineWidth;

    SDL_RenderFillRect(renderer, &line);

    SDL_RenderCopy(renderer, fontTex, NULL, &chartName);

    SDL_DestroyTexture(fontTex);
  }
}

void View::DrawLogo()
{
  SDL_Rect logo;
  logo.x = Config::UI::Logo::left;
  logo.y = Config::UI::Logo::top;
  logo.w = Config::UI::Logo::width;
  logo.h = Config::UI::Logo::height;
  SDL_RenderCopy(renderer, logoTex, NULL, &logo);
}

void View::DrawGraph(float high, float low)
{
  SDL_Rect graph;
  graph.x = Config::UI::Graph::left;
  graph.y = Config::UI::Graph::top;
  graph.w = Config::UI::Graph::width;
  graph.h = Config::UI::Graph::height;

  SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255);
  SDL_RenderFillRect(renderer, &graph);

  float range = high - low;

  float drawnHigh = high + Config::UI::Graph::percentDrawnExcess * range;
  float drawnLow = low - Config::UI::Graph::percentDrawnExcess * range;
  float drawnRange = drawnHigh - drawnLow;

  int graphHeight =
      (Config::UI::Graph::height - (Config::UI::Graph::offsetBottom * 2));

  DrawScale(graphHeight / drawnRange, drawnLow, drawnRange);

  for (int i = 0; i < app.model.graph.GetNumBars(); ++i)
  {
    SDL_Rect bar;

    bar.w = Config::UI::Graph::barWidth;
    bar.h = (int)(app.model.graph.GetBar(i)->GetValue() - drawnLow) *
            (graphHeight / drawnRange);
    bar.x = graph.x + Config::UI::Graph::offsetLeft +
            i * Config::UI::Graph::barWidth + (Config::UI::Graph::barGap * i);
    bar.y = graph.y + graph.h - Config::UI::Graph::offsetBottom - bar.h;

    int barType = app.model.graph.GetBar(i)->GetType();
    switch (barType)
    {
    case 2:
      SDL_SetRenderDrawColor(renderer, Config::UI::Graph::entryColor.r,
                             Config::UI::Graph::entryColor.g,
                             Config::UI::Graph::entryColor.b, 255);
      break;
    case 1:
      SDL_SetRenderDrawColor(renderer, Config::UI::Graph::winColor.r,
                             Config::UI::Graph::winColor.g,
                             Config::UI::Graph::winColor.b, 255);
      break;
    case 0:
      SDL_SetRenderDrawColor(renderer, Config::UI::Graph::lossColor.r,
                             Config::UI::Graph::lossColor.g,
                             Config::UI::Graph::lossColor.b, 255);
      break;
    }

    SDL_RenderFillRect(renderer, &bar);
  }
}