#pragma once

#include <thread>
#include <string>


namespace prf::vulkan{

struct Thread{
  //---------------------------

  std::thread::id ID;
  std::string name;

  //---------------------------
};

struct Info{
  //---------------------------

  std::string selected_gpu;

  //---------------------------
};

}
