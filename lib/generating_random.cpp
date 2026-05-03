#include <random>

int randInt(int start, int end)
{
  static std::random_device rd;
  static std::mt19937 mt(rd());
  std::uniform_int_distribution<> dist(start, end);
  return dist(mt);
}

double randFloat(int start, int end)
{
  static std::random_device rd;
  static std::mt19937 mt(rd());
  std::uniform_real_distribution<> dist(start, end);
  return dist(mt);
}