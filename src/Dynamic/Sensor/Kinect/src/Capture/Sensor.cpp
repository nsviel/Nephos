#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, int index){
  //---------------------------

  dyn::Node* node_dynamic = node_k4n->get_node_dynamic();

  this->k4n_processing = new k4n::Processing(node_k4n);
  this->k4n_config = new k4n::capture::Configuration(node_k4n);
  this->gui_capture = new k4n::gui::Capture(node_k4n);
  this->dyn_sensor = node_dynamic->get_dyn_sensor();

  this->vec_recorder.push_back(new k4n::capture::Recorder());
  this->device.index = index;
  this->name = "capture_" + std::to_string(index);
  this->data.name = name;

  //---------------------------
  dyn_sensor->init_sensor(this);
}
Sensor::~Sensor(){
  //---------------------------

  this->stop_thread();
  dyn_sensor->remove_sensor(this);

  //---------------------------
}

//Main function
void Sensor::thread_init(){
  //---------------------------

  //Init
  this->device.index = 0;
  this->device.handle = k4a::device::open(device.index);
  if(!device.handle.is_valid()) return;
  this->serial_number = device.handle.get_serialnum();
  this->device.version = device.handle.get_version();

  //Configuration
  k4n_config->make_sensor_configuration(this);
  k4n_config->make_sensor_color_configuration(this);
  k4n_config->find_calibration(this);
  this->device.handle.start_cameras(&device.configuration);

  //---------------------------
}
void Sensor::thread_loop(){
  prf::dynamic::Tasker* tasker = profiler.fetch_tasker("kinect::loop");
  //---------------------------

  tasker->loop();

  //Next capture
  tasker->task_begin("capture");
  k4a::capture* capture = manage_new_capture();
  if(capture == nullptr) return;
  tasker->task_end("capture");

  //Wait previous threads to finish
  tasker->task_begin("wait");
  this->manage_old_capture(capture);
  tasker->task_end("wait");

  //Run processing
  k4n_processing->start_thread(this);

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
k4a::capture* Sensor::manage_new_capture(){
  //---------------------------

  k4a::capture* capture = new k4a::capture();
  bool ok = device.handle.get_capture(capture, std::chrono::milliseconds(2000));
  if(!capture->is_valid()){
    delete capture;
    return nullptr;
  }

  //---------------------------
  return capture;
}
void Sensor::manage_old_capture(k4a::capture* capture){
  //---------------------------

  // Add the new capture to the queue
  queue.push(capture);

  // Check if the queue size exceeds 5
  k4n_processing->wait_thread();
  if(queue.size() > 5){
    // Delete the oldest capture
    delete queue.front();
    queue.pop();
  }

  // Update the sensor parameter
  this->device.capture = capture;

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
void Sensor::gui_config(){
  //---------------------------

  gui_capture->show_parameter(set_parent);

  //---------------------------
}

}
