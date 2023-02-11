#pragma once

#include <string>
#include <vector>

class Graph
{
public:
  Graph();
  ~Graph();

  void Initialize();
  void Update(float newValue, bool isEntry);

  class Bar* GetBar(int index);
  int GetNumBars();

private:
  std::vector<class Bar*> bars;
  float lastValue;
};