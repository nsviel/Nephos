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

  rlx_capture->init(*this);

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
