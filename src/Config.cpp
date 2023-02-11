#include "Config.hpp"
#include <string>

using namespace std;

namespace Config
{
  string stockSym = "TSLA";

  string optionsApi = "https://yfapi.net/v7/finance/options/TSLA";

  string apiKey; // If you are trying to verify if this works, email me for this.

  string backTestApi = "https://yfapi.net/v7/finance/options/TSLA?date=";

  string backTestDate = "";

  bool isDebugMode = false;
  bool isRunningApi = true;
  bool isBackTesting = false;

  int interval = 10;

  namespace UI
  {
    namespace Font
    {
      int fontSize = 30;
      string fontPath = "./assets/font.ttf";
    } // namespace Font

    namespace Window
    {
      Color bgColor{23, 40, 65};
      string title = "Stock Engine";

      int resWidth = 1920;
      int resHeight = 1080;

      int windowWidth = 960;
      int windowHeight = 540;

    } // namespace Window

    namespace BackTestInput
    {
      int left = 1600;
      int top = 15;
      int width = 200;
      int height = 50;
    } // namespace BackTestInput

    namespace BackTestCheck
    {
      int left = 1850;
      int top = 15;
      int width = 40;
      int height = 40;
    } // namespace BackTestCheck

    namespace Logo
    {
      int left = 15;
      int top = 15;
      int width = 300;
      int height = 71;

      string logoPath = "./assets/logo-name.png";

    } // namespace Logo

    namespace Graph // keep track of events (split, etc.)
    {
      int left = 195;
      int top = 200;
      int width = 1500;
      int height = 600;

      Color lossColor{255, 0, 0}; // Constructed before initialization... may
                                  // want to construct on View
      Color winColor{0, 255, 0};
      Color entryColor{255, 0, 255};

      int barWidth = 14;
      int barGap = 3;

      int offsetLeft = 65;
      int offsetBottom = 25;

      float percentDrawnExcess = 0.1;

      int numTicks = 10;
      int lineWidth = 2;
    } // namespace Graph

  } // namespace UI

} // namespace Config
