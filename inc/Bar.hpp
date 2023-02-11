#pragma once

class Bar
{
public:
  Bar(int barType, float value);
  ~Bar();

  void Initialize();
  void Run();

  int GetType();
  float GetValue();

private:
  int barType; // Loss = 0, Win = 1, Entry = 2
  float value;
};