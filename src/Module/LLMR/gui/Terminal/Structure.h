#pragma once

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_internal.h>
#include <iostream>
#include <fstream>
#include <string>


namespace llmr::gui::terminal{

struct Structure{
  //---------------------------

  ImVector<char*>       vec_item;
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
