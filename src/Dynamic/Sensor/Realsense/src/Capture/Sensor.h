#pragma once

#include <Realsense/src/Structure/Sensor.h>

namespace rlx{class Node;}
namespace rlx{class Structure;}
namespace rlx::capture{class Capture;}
namespace rlx::processing{class Color;}
namespace rlx::processing{class Depth;}
namespace dyn::prc::cloud{class Operation;}
namespace dat::sensor{class Pool;}


namespace rlx::capture{

class Sensor : public rlx::base::Sensor
{
public:
  //Constructor / Destructor
  Sensor(rlx::Node* node_realsense);
  ~Sensor();

public:
  //Main function
  void thread_init();
  void thread_loop();
  void thread_end();

  //Subfunction
  void gui_config();
  void gui_info();

private:
  rlx::Structure* rlx_struct;
  rlx::capture::Capture* rlx_capture;
  rlx::processing::Color* rlx_color;
  rlx::processing::Depth* rlx_depth;
  dyn::prc::cloud::Operation* dyn_operation;
  dat::sensor::Pool* thr_pool;
};


}
