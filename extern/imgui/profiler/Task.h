#pragma once

#include <cstdint>
#include <string>

namespace ImProfil{

struct Task{
  double startTime;
  double endTime;
  std::string name;
};

struct Graph_task{
  double startTime;
  double endTime;
  std::string name;
  uint32_t color;
  double GetLength(){
    return endTime - startTime;
  }
};

}
