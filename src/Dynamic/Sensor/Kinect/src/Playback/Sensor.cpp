#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Processing/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, utl::base::Path path){
  //---------------------------

  dyn::prc::Node* node_processing = node_k4n->get_node_processing();

  this->k4n_color = new k4n::color::Data(node_k4n);
  this->k4n_playback = new k4n::playback::Playback(node_k4n);
  this->k4n_image = new k4n::data::Image(node_k4n);
  this->k4n_cloud = new k4n::data::Cloud(node_k4n);
  this->gui_playback = new k4n::gui::Playback(node_k4n);
  this->dyn_operation = node_processing->get_ope_cloud();
  this->thr_pool = new dat::sensor::Pool(20);

  this->data->path = path;

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  k4n_playback->clean(*this);

  //---------------------------
}

//Main function
void Sensor::thread_init(){
  //---------------------------

  //Configuration
  k4n_playback->init(*this);

  //Graph
  graph.add_task("capture", [this](dat::base::Sensor& sensor){ k4n_playback->manage_capture(sensor); });
  graph.add_task("image", [this](dat::base::Sensor& sensor){ k4n_image->extract_data(sensor); });
  graph.add_task("cloud", [this](dat::base::Sensor& sensor){ k4n_cloud->extract_data(sensor); });
  graph.add_task("operation", [this](dat::base::Sensor& sensor){ dyn_operation->run_operation(sensor); });
  graph.add_dependency("capture", "image");
  graph.add_dependency("image", "cloud");
  graph.add_dependency("image", "operation");

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
  k4n_playback->clean(*this);

  //---------------------------
}

//Subfunction
void Sensor::query(float value){
  //---------------------------

  k4n_playback->manage_query(*this, value);

  //---------------------------
}
void Sensor::gui_config(){
  //---------------------------

  gui_playback->show_parameter(*this);

  //---------------------------
}
void Sensor::gui_info(){
  //---------------------------

  gui_playback->show_info(*this);

  //---------------------------
}

}
