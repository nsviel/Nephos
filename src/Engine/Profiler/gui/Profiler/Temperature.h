#pragma once

#include <Utility/Specific/Common.h>
#include <Profiler/gui/Profiler/Struct_profiler.h>

namespace prf{class Node;}


namespace prf::gui{

class Temperature : public prf::gui::Profiler
{
public:
  //Constructor / Destructor
  Temperature(prf::Node* node_profiler);
  ~Temperature();

public:
  //Main function
  void draw_profiler();

  //Tab function

private:
};

}
