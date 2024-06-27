#pragma once

#include <imgui/core/imgui.h>

namespace prf{class Node;}
namespace prf{class Structure;}
namespace prf::base{class Profiler;}
namespace prf::hardware{class Profiler;}
namespace prf::hardware{class Device;}
namespace prf::hardware{class Structure;}
namespace prf::hardware{class Profiler;}
namespace prf::gui{class Profiler;}


namespace prf::gui::hardware{

class GPU
{
public:
  //Constructor / Destructor
  GPU(prf::Node* node_profiler);
  ~GPU();

public:
  //Main function
  void draw_tab();

  //Subfunction
  void draw_gpu_info();
  void draw_gpu_queue();

private:
  prf::Structure* prf_struct;
  prf::hardware::Profiler* prf_hardware;
};

}
