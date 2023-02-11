#include "Agent.hpp"
#include "Config.hpp"
#include "Model.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;
using namespace std;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb,
                            void* userp)
{
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

Agent::Agent(Model& model) : model(model)
{
  if (Config::isDebugMode)
  {
    cout << "  Constructing Agent" << endl;
  }
}

Agent::~Agent()
{
  if (Config::isDebugMode)
  {
    cout << "  Deconstructing Agent" << endl;
  }
}

void Agent::Initialize()
{
  if (Config::isDebugMode)
  {
    cout << "  Initializing Agent" << endl;
  }

  time = chrono::system_clock::now();
}

void Agent::Run()
{
  if (Config::isDebugMode)
  {
    // cout << "  Running Agent" << endl;
  }

  auto curr = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = curr - time;

  if (elapsed_seconds.count() > Config::interval)
  {
    Update();
    time = std::chrono::system_clock::now();
  }
}

void Agent::Update()
{
  if (Config::isDebugMode)
  {
    cout << "  Updating Agent" << endl;
  }

  string result;

  if (Config::isRunningApi)
  {
    GetOptionsData(result, Config::apiKey, Config::optionsApi);
  }
  else if (Config::isBackTesting)
  {
    GetOptionsData(result, Config::apiKey, Config::backTestApi);
  }
  else
  {
    // optimize
    std::ifstream file("./options-example.json");

    if (file)
    {
      std::stringstream buffer;

      buffer << file.rdbuf();

      file.close();

      result = buffer.str();
    }
  }

  model.Update(result);
}

void Agent::GetOptionsData(string& output, string& apiKey, string& api)
{
  CURL* hnd = curl_easy_init();
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);

  struct curl_slist* headers = NULL;
  headers = curl_slist_append(headers, apiKey.c_str());
  curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

  curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(hnd, CURLOPT_URL, api.c_str());
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &output);

  curl_easy_perform(hnd);
  curl_easy_cleanup(hnd);
}

float Agent::ParseBidPrice(string& result)
{
  string num;
  char ch = result.at(result.find("bid") + 5);
  int count = 1;
  while (ch != ',')
  {
    num.push_back(ch);
    ch = result.at(result.find("bid") + 5 + count);
    count++;
  }

  return stof(num);
}

float Agent::ParseAskPrice(string& result)
{
  string num;
  char ch = result.at(result.find("ask") + 5);
  int count = 1;
  while (ch != ',')
  {
    num.push_back(ch);
    ch = result.at(result.find("ask") + 5 + count);
    count++;
  }

  return stof(num);
}