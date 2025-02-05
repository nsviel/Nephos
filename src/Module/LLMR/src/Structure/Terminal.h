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
  ImVector<const char*> vec_command;
  ImVector<char*>       history;
  ImGuiTextFilter       filter;
  char                  input_buffer[256];
  int                   history_pose;    // -1: new line, 0..History.Size-1 browsing history.
  bool                  is_autoscroll = true;
  bool                  scroll_to_bottom;

  //---------------------------
};

}
