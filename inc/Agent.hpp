#pragma once

#include <chrono>
#include <curl/curl.h>
#include <string>

class Agent
{
public:
  Agent(class Model& model);
  ~Agent();

  void Initialize();
  void Run();

  void Update();

  void GetOptionsData(std::string& output, std::string& apiKey,
                      std::string& api);

  float ParseBidPrice(std::string& result);
  float ParseAskPrice(std::string& result);

private:
  class Model& model;
  CURL* hnd;

  std::chrono::system_clock::time_point time;
};