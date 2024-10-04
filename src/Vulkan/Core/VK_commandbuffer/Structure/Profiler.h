#pragma once

#include <unordered_map>
#include <vector>
#include <string>


namespace vk::profiler{

struct Structure{
  //---------------------------

  std::unordered_map<std::string, float> map_duration;

  //---------------------------
};

}
