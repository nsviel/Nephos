#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Processing/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n){
  //---------------------------

  dyn::prc::Node* node_processing = node_k4n->get_node_processing();
  dat::Node* node_data = node_k4n->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->k4n_graph = new k4n::Graph(node_k4n);
  this->k4n_config = new k4n::capture::Configuration(node_k4n);
  this->k4n_capture = new k4n::capture::Capture(node_k4n);
  this->gui_capture = new k4n::gui::Capture(node_k4n);
  this->dat_sensor = node_element->get_dat_sensor();

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  k4n_capture->clean(*this);

  //---------------------------
}

//Main function
void Sensor::thread_init(){
  //---------------------------

  //Configuration
  k4n_capture->init(*this);

  //Graph
  graph.clear();
  graph.add_task("capture", [this](dat::base::Sensor& sensor){ k4n_capture->manage_capture(sensor); });
  graph.add_task("data", [this](dat::base::Sensor& sensor){ k4n_image->extract_data(sensor); });
  graph.add_task("cloud", [this](dat::base::Sensor& sensor){ k4n_cloud->extract_data(sensor); });
  graph.add_task("operation", [this](dat::base::Sensor& sensor){ dyn_ope_cloud->run_operation(sensor); });
  graph.add_dependency("capture", "data");
  graph.add_dependency("data", "cloud");
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

  k4n_capture->clean(*this);

  //---------------------------
}

//Subfunction
void Sensor::manage_gui(){
  //---------------------------

  gui_capture->show_parameter(*this);

  //---------------------------
}

}
