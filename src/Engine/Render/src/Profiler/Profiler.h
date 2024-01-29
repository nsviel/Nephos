#pragma once

#include <Utility/Specific/common.h>

namespace eng::render{class Node;}


namespace eng::render{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler(eng::render::Node* node_render, bool* show_window);
  ~Profiler();

public:
  //Main function


private:

};

}
