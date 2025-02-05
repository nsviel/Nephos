#pragma once

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_internal.h>
#include <iostream>
#include <fstream>
#include <string>

namespace llmr{class Node;}
namespace llmr{class Interface;}
namespace llmr{class Structure;}
namespace llmr{class Terminal;}


namespace llmr::gui{

class Terminal
{
public:
  //Constructor / Destructor
  Terminal(llmr::Node* node_llmr);
  ~Terminal();

public:
  //Main function
  void draw_terminal();
  
  //Subfunction
  void draw_console();
  void draw_input();
  void process_input(std::string command_line);
  std::string break_lines(const std::string& text);

private:
  llmr::Structure* llmr_struct;
  llmr::Interface* llmr_interface;
  llmr::Terminal* llmr_terminal;
};

}
