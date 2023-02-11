#include "Graph.hpp"
#include "Bar.hpp"
#include "Config.hpp"
#include <iostream>

using namespace std;

Graph::Graph()
{
  if (Config::isDebugMode)
  {
    cout << "  Constructing Graph" << endl;
  }
}

Graph::~Graph()
{
  if (Config::isDebugMode)
  {
    cout << "  Deconstructing Graph" << endl;
  }

  for (auto bar : bars)
  {
    delete bar;
  }
  bars.clear();
}

void Graph::Initialize()
{
  if (Config::isDebugMode)
  {
    cout << "  Initializing Graph" << endl;
  }
}

void Graph::Update(float newValue, bool isEntry)
{
  if (Config::isDebugMode)
  {
    cout << "  Updating Graph" << endl;
  }

  bars.emplace_back(new Bar(isEntry                ? 2
                            : newValue > lastValue ? 1
                                                   : 0,
                            newValue));
  lastValue = newValue;
}

Bar* Graph::GetBar(int index) { return bars.at(index); }

int Graph::GetNumBars() { return bars.size(); }