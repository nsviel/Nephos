#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace prf::base{class Profiler;}
namespace prf::hardware{class Profiler;}
namespace prf::hardware{class Device;}
namespace prf::hardware{class Structure;}
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
  void show_profiler(prf::base::Profiler* profiler);

  //Tab function
  void draw_tab_gpu(prf::hardware::Structure* prf_struct, ImVec2 graph_dim);
  void draw_tab_device(prf::hardware::Structure* prf_struct, ImVec2 graph_dim);

  //Subfunction
  void draw_device_info(prf::hardware::Device& device);
  void draw_device_queue_families(prf::hardware::Device& device);
  void draw_gpu_info(prf::hardware::Structure* prf_struct);
  void draw_gpu_queue(prf::hardware::Structure* prf_struct);

private:
};

}
