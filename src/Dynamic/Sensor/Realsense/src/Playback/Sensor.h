#pragma once

#include <Realsense/src/Structure/Sensor.h>

namespace rlx{class Node;}
namespace rlx{class Structure;}
namespace rlx::capture{class Capture;}
namespace rlx::processing{class Color;}
namespace rlx::processing{class Depth;}
namespace rlx::processing{class Cloud;}
namespace rlx::processing{class Infrared;}
namespace dyn::prc::cloud{class Operation;}
namespace dat::sensor{class Pool;}


namespace rlx::playback{

class Sensor : public rlx::base::Sensor
{
public:
  //Constructor / Destructor
  Sensor(rlx::Node* node_realsense, utl::base::Path path);
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
  rlx::processing::Cloud* rlx_cloud;
  rlx::processing::Infrared* rlx_ir;
  dyn::prc::cloud::Operation* dyn_operation;
  dat::sensor::Pool* thr_pool;
};


}
