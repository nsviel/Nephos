#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>
#include <Processing/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, int index){
  //---------------------------

  dyn::prc::Node* node_processing = node_k4n->get_node_processing();
  dat::Node* node_data = node_k4n->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->k4n_processing = new k4n::Processing(node_k4n);
  this->k4n_config = new k4n::capture::Configuration(node_k4n);
  this->k4n_capture = new k4n::capture::Capture(node_k4n);
  this->gui_capture = new k4n::gui::Capture(node_k4n);
  this->dat_sensor = node_element->get_dat_sensor();

  this->device.index = index;

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  this->stop_thread();
  dat_sensor->remove_sensor(*this);

  //---------------------------
}

//Main function
void Sensor::thread_init(){
  //---------------------------

  dat_sensor->init_sensor(*this);
  k4n_capture->init_device(*this);
  k4n_config->make_sensor_configuration(*this);
  k4n_config->make_sensor_color_configuration(*this);
  k4n_config->find_calibration(*this);
  k4n_capture->init_capture(*this);

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
  k4n_processing->start_thread(*this);

  //Loop sleeping
  this->manage_pause();

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
void Sensor::manage_pause(){
  //---------------------------

  //If pause, wait until end pause or end thread
  if(state.pause || !state.play){
    profiler.pause = true;
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this] { return !state.pause || !thread_running;});
    profiler.pause = false;
  }

  //---------------------------
}
void Sensor::manage_gui(){
  //---------------------------

  gui_capture->show_parameter(set_parent.lock());

  //---------------------------
}

}
