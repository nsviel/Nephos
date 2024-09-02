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

  this->k4n_graph = new k4n::Graph(node_k4n);
  this->k4n_config = new k4n::playback::Configuration(node_k4n);
  this->k4n_playback = new k4n::playback::Playback(node_k4n);
  this->dat_sensor = node_element->get_dat_sensor();
  this->gui_playback = new k4n::gui::Playback(node_k4n);

  this->data.path = path;

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  dat_sensor->clean_sensor(*this);

  //---------------------------
}

//Main function
void Sensor::thread_init(){
  //---------------------------

  k4n_playback->init_info(*this);
  k4n_playback->init_playback(*this);
  k4n_playback->find_timestamp(*this);
  dat_sensor->init_sensor(*this);
  k4n_config->find_configuration(*this);
  k4n_config->find_calibration(*this);
  k4n_graph->init(*this);

  //---------------------------
}
void Sensor::thread_loop(){
  prf::monitor::Tasker* tasker = profiler.fetch_tasker("kinect::loop");
  //---------------------------

  tasker->loop(30);

  //Next capture
  tasker->task_begin("capture");
  this->manage_capture();
  if(!device.capture) return;
  tasker->task_end("capture");

  //Run processing
  k4n_graph->run(*this);

  //---------------------------
}
void Sensor::thread_end(){
  //---------------------------

  k4n_playback->close_playback(*this);

  //---------------------------
}

//Subfunction
void Sensor::manage_capture(){
  //---------------------------

  //Capture data
  bool ok = device.playback.get_next_capture(device.capture.get());

  //Check capture
  if(!ok){
    device.capture.reset();
  }

  //---------------------------
}
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
  if(state.pause){
    state.pause = false;
    auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(value));
    device.playback.seek_timestamp(ts, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    state.pause = true;
  }else{
    auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(value));
    device.playback.seek_timestamp(ts, K4A_PLAYBACK_SEEK_DEVICE_TIME);
  }

  //---------------------------
}
void Sensor::manage_gui(){
  //---------------------------

  std::shared_ptr<k4n::playback::Sensor> sensor(this);
  gui_playback->show_parameter(sensor);

  //---------------------------
}

}
