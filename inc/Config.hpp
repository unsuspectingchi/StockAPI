#pragma once
#include "Color.hpp"
#include "SDL.h"

#include <string>

namespace Config
{
  extern std::string stockSym;

  extern std::string optionsApi;

  extern std::string backTestApi;

  extern std::string apiKey;
  extern int interval;

  extern bool isDebugMode;
  extern bool isRunningApi;
  extern bool isBackTesting;

  namespace UI
  {
    namespace Font
    {
      extern int fontSize;
      extern std::string fontPath;
    } // namespace Font
    namespace Window
    {
      extern Color bgColor;
      extern std::string title;

      extern int resWidth;
      extern int resHeight;

      extern int windowWidth;
      extern int windowHeight;

    } // namespace Window
    namespace BackTestInput
    {
      extern int left;
      extern int top;
      extern int width;
      extern int height;
    } // namespace BackTestInput
    namespace BackTestCheck
    {
      extern int left;
      extern int top;
      extern int width;
      extern int height;
    } // namespace BackTestCheck
    namespace Logo
    {
      extern int left;
      extern int top;
      extern int width;
      extern int height;

      extern std::string logoPath;
    } // namespace Logo

    namespace Graph
    {
      extern int left;
      extern int top;
      extern int width;
      extern int height;

      extern Color lossColor;
      extern Color winColor;
      extern Color entryColor;

      extern int barWidth;
      extern int barGap;

      extern int offsetLeft;
      extern int offsetBottom;

      extern float percentDrawnExcess;

      extern int numTicks;
      extern int lineWidth;
    } // namespace Graph
  }   // namespace UI
} // namespace Config