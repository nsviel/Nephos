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

  this->rlx_capture = new rlx::capture::Capture(node_realsense);
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
/*  graph.add_task("image", [this](dat::base::Sensor& sensor){ k4n_image->extract_data(sensor); });
  graph.add_task("cloud", [this](dat::base::Sensor& sensor){ k4n_cloud->extract_data(sensor); });
  graph.add_task("operation", [this](dat::base::Sensor& sensor){ dyn_operation->run_operation(sensor); });
  graph.add_dependency("capture", "image");
  graph.add_dependency("image", "cloud");
  graph.add_dependency("cloud", "operation");*/


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
