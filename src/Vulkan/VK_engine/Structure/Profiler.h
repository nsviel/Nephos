#pragma once

#include <vector>
#include <string>


namespace vk::profiler{

struct Command_buffer{
  //---------------------------

  std::string name = "";
  float duration = -1;

  //---------------------------
};

struct Structure{
  //---------------------------

  std::vector<vk::profiler::Command_buffer> vec_command_buffer;

  //---------------------------
};

}
