#pragma once

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_internal.h>
#include <iostream>
#include <fstream>
#include <string>

namespace llmr{class Interface;}
namespace llmr{class Node;}
namespace llmr{class Structure;}


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

  //Log function
  void add_log(std::string log, std::string prefix);
  void clear_log();

  //Subfunction
  void draw_console();
  void draw_input();
  void process_input(std::string command_line);
  std::string break_lines(const std::string& text);

private:
  llmr::Structure* llmr_struct;
  llmr::Interface* llmr_interface;
};

}
