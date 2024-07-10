#pragma once

#include <imgui/core/imgui.h>
#include <mutex>


namespace vk::gui{

struct Structure{
  //---------------------------

  ImDrawData* draw = nullptr;
  std::mutex mutex;

  //---------------------------
};

}
