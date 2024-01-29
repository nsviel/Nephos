#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}


namespace gui::interface{

class Docking
{
public:
  //Constructor / Destructor
  Docking(gui::Node* gui);
  ~Docking();

public:
  //Main functions
  void docker_space_main();

private:
};

}
