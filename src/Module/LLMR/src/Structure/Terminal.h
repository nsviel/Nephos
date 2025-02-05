#pragma once

#include <LLMR/src/Structure/Item.h>
#include <imgui/core/imgui.h>
#include <imgui/core/imgui_internal.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


namespace llmr::structure{

struct Terminal{
  //---------------------------

  std::vector<llmr::structure::Item> vec_item;
  char input_buffer[256];
  bool is_autoscroll = true;
  bool scroll_to_bottom = true;

  //---------------------------
};

}
