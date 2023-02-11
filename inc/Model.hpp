#pragma once

#include "Agent.hpp"
#include "Graph.hpp"
#include <string>

class Model
{
public:
  Model(class App& app);
  ~Model();

  void Initialize();
  void Run();

  void Update(std::string& result);

  Agent agent;
  Graph graph;

private:
  class App& app;
};