#pragma once

#include <vector>
#include <string>

namespace gui{class Node;}


namespace gui::interface{

class State
{
public:
  //Constructor / Destructor
  State(gui::Node* gui);
  ~State();

public:
  //Main function
  void dock_save_state();
  void dock_load_state();

private:
  std::vector<std::string> vec_path;
  std::string current;
};

}
