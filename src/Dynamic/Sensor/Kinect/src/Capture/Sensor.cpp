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

  this->device.index = k4n_struct->connection.current_ID++;


  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  dat_sensor->clean_sensor(*this);
  k4n_struct->connection.current_ID--;

  //---------------------------
}

//Main function
void Sensor::thread_init(){
  //---------------------------

  k4n_capture->init_info(*this);
  k4n_capture->init_device(*this);
  dat_sensor->init_sensor(*this);
  k4n_config->make_sensor_configuration(*this);
  k4n_config->make_sensor_color_configuration(*this);
  k4n_config->find_calibration(*this);
  k4n_capture->init_capture(*this);
  k4n_graph->init(*this);

  //---------------------------
}
void Sensor::thread_loop(){
  prf::monitor::Tasker* tasker = profiler.fetch_tasker("kinect::loop");
  //---------------------------

  tasker->loop();

  //Next capture
  tasker->task_begin("capture");
  this->manage_capture();
  if(!device.capture) return;
  tasker->task_end("capture");

  //Run processing
  tasker->task_begin("graph");
  k4n_graph->run(*this);
  tasker->task_end("graph");

  //---------------------------
}
void Sensor::thread_end(){
  //---------------------------

  this->device.handle.close();

  //---------------------------
}

//Subfunction
void Sensor::manage_capture(){
  //---------------------------

  //Capture data
  bool ok = device.handle.get_capture(device.capture.get(), std::chrono::milliseconds(2000));
  //va trop vite, il faut faire un system de capture et oublie

  //Check capture
  if(!ok){
    device.capture.reset();
  }

  //---------------------------
}
void Sensor::manage_gui(){
  //---------------------------

  gui_capture->show_parameter(*this);

  //---------------------------
}

}
