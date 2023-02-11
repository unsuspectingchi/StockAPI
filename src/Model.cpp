#include "Model.hpp"
#include "App.hpp"
#include "Config.hpp"
#include <iostream>

using namespace std;

Model::Model(App& app) : agent(*this), graph(), app(app)
{
  if (Config::isDebugMode)
  {
    cout << " Constructing Model" << endl;
  }
}

Model::~Model()
{
  if (Config::isDebugMode)
  {
    cout << " Deconstructing Model" << endl;
  }
}

void Model::Initialize()
{
  if (Config::isDebugMode)
  {
    cout << " Initializing Model" << endl;
  }
  agent.Initialize();
  graph.Initialize();
}

void Model::Run()
{
  if (Config::isDebugMode)
  {
    // cout << " Running Model" << endl;
  }
  agent.Run();
}

void Model::Update(string& result)
{
  graph.Update(agent.ParseAskPrice(result), false);

  // Pass on to other updates
  app.view.Update(300, 150);
}