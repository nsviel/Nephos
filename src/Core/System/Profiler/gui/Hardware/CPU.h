#pragma once

#include <imgui/core/imgui.h>

namespace prf{class Node;}
namespace prf{class Structure;}
namespace prf::dynamic{class Profiler;}
namespace prf::hardware{class Profiler;}
namespace prf::hardware{class Device;}
namespace prf::hardware{class Structure;}
namespace prf::hardware{class Profiler;}
namespace prf::gui{class Profiler;}


namespace prf::gui::hardware{

class CPU
{
public:
  //Constructor / Destructor
  CPU(prf::Node* node_profiler);
  ~CPU();

public:
  //Main function
  void draw_tab();

  //Subfunction
  void draw_cpu_info();

private:
  prf::Structure* prf_struct;
  prf::hardware::Profiler* prf_hardware;
};

}
