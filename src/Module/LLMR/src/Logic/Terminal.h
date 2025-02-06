#pragma once

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_internal.h>
#include <iostream>
#include <fstream>
#include <string>

namespace llmr{class Node;}
namespace llmr{class Structure;}


namespace llmr{

class Terminal
{
public:
  //Constructor / Destructor
  Terminal(llmr::Node* node_llmr);
  ~Terminal();

public:
  //Main function
  void add_log(std::string log, std::string prefix);
  void clear_log();

private:
  llmr::Structure* llmr_struct;
};

}
