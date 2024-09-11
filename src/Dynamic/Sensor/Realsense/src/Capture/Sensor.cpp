#include "Sensor.h"

#include <Realsense/Namespace.h>
#include <Processing/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace rlx::capture{

//Constructor / Destructor
Sensor::Sensor(rlx::Node* node_realsense){
  //---------------------------

  dyn::prc::Node* node_processing = node_realsense->get_node_processing();

  this->rlx_struct = node_realsense->get_rlx_struct();
  this->rlx_capture = new rlx::capture::Capture(node_realsense);
  this->rlx_color = new rlx::processing::Color(node_realsense);
  this->rlx_depth = new rlx::processing::Depth(node_realsense);
  this->rlx_ir = new rlx::processing::Infrared(node_realsense);
  this->rlx_cloud = new rlx::processing::Cloud(node_realsense);
  this->dyn_operation = node_processing->get_ope_cloud();
  this->thr_pool = new dat::sensor::Pool(20);

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------



  //---------------------------
}

//Main function
void Sensor::thread_init(){
  //---------------------------

  //Configuration
  rlx_capture->init(*this);

  //Graph
  graph.add_task("capture", [this](dat::base::Sensor& sensor){ rlx_capture->capture(sensor); });
  //graph.add_task("color", [this](dat::base::Sensor& sensor){ rlx_color->extract_data(sensor); });
  //graph.add_task("depth", [this](dat::base::Sensor& sensor){ rlx_depth->extract_data(sensor); });
  graph.add_task("ir", [this](dat::base::Sensor& sensor){ rlx_ir->extract_data(sensor); });
  graph.add_task("cloud", [this](dat::base::Sensor& sensor){ rlx_cloud->extract_data(sensor); });
  graph.add_task("operation", [this](dat::base::Sensor& sensor){ dyn_operation->run_operation(sensor); });
  graph.add_dependency("capture", "color");
  graph.add_dependency("capture", "depth");
  graph.add_dependency("capture", "ir");
  graph.add_dependency("capture", "cloud");
  graph.add_dependency("cloud", "operation");

  //---------------------------
}
void Sensor::thread_loop(){
  //---------------------------

  graph.execute(*thr_pool, *this);

  //---------------------------
}
void Sensor::thread_end(){
  //---------------------------

  graph.wait_completion();
  rlx_capture->clean(*this);

  //---------------------------
}

//Subfunction
void Sensor::gui_config(){
  //---------------------------



  //---------------------------
}
void Sensor::gui_info(){
  //---------------------------


  //---------------------------
}

}
