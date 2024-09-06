#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>
#include <Processing/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, utl::base::Path path){
  //---------------------------

  dyn::prc::Node* node_processing = node_k4n->get_node_processing();
  dat::Node* node_data = node_k4n->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->node_k4n = node_k4n;
  this->k4n_graph = new k4n::Graph(node_k4n);
  this->k4n_config = new k4n::playback::Configuration(node_k4n);
  this->k4n_playback = new k4n::playback::Playback(node_k4n);
  this->dat_sensor = node_element->get_dat_sensor();
  this->gui_playback = new k4n::gui::Playback(node_k4n);
  this->k4n_image = new k4n::processing::image::Data(node_k4n);
  this->k4n_cloud = new k4n::processing::cloud::Data(node_k4n);
  this->dyn_ope_cloud = node_processing->get_ope_cloud();
  this->thr_pool = new dat::sensor::Pool(100);

  this->data->path = path;
  this->type_sensor = "playback";

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

  k4n_playback->init(*this);

  graph.clear();
  graph.add_task("capture", [this](dat::base::Sensor& sensor){ k4n_playback->manage_capture(sensor); });
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

  graph.wait_completion();
  k4n_playback->clean(*this);

  //---------------------------
}

//Subfunction
void Sensor::manage_query(float value){
  //---------------------------

  //Check value validity
  if(value > timestamp.end){
    std::cout<<"[error] timestamp superior file end"<<std::endl;
    return;
  }else if(value < timestamp.begin){
    std::cout<<"[error] timestamp inferior file begin"<<std::endl;
    return;
  }

  //Apply query
  if(state.pause || state.query){
    this->pause(false);
    auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(value));
    device.playback.seek_timestamp(ts, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    this->pause(true);
  }else{
    auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(value));
    device.playback.seek_timestamp(ts, K4A_PLAYBACK_SEEK_DEVICE_TIME);
  }

  //---------------------------
}
void Sensor::manage_gui(){
  //---------------------------

  gui_playback->show_parameter(*this);

  //---------------------------
}

}
