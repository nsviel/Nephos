#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, int index){
  //---------------------------

  this->k4n_image = new k4n::processing::Image(node_k4n);
  this->k4n_config = new k4n::capture::Configuration(node_k4n);
  this->gui_capture = new k4n::gui::Capture(node_k4n);

  this->vec_recorder.push_back(new k4n::capture::Recorder());
  this->device.idx_dev = index;
  this->name = "capture_" + std::to_string(index);
  this->data.name = name;

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Sensor::thread_init(){
  //---------------------------

  //Init
  this->device.idx_dev = 0;
  this->device.handle = k4a::device::open(device.idx_dev);
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
  prf::graph::Tasker* tasker = profiler.fetch_tasker("capture");
  //---------------------------

  tasker->loop_begin();

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
  k4n_image->start_thread(this);

  //Loop sleeping
  tasker->task_begin("pause");
  this->manage_pause();
  tasker->task_end("pause");

  tasker->loop_end();

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
  static std::queue<k4a::capture*> capture_queue;
  //---------------------------

  // Add the new capture to the queue
  capture_queue.push(capture);

  // Check if the queue size exceeds 5
  k4n_image->wait_thread();
  if(capture_queue.size() > 5){
    // Delete the oldest capture
    delete capture_queue.front();
    capture_queue.pop();
  }

  // Update the sensor parameter
  this->device.capture = capture;

  //---------------------------
}
void Sensor::manage_pause(){
  //---------------------------

  //If pause, wait until end pause or end thread
  if(state.pause || !state.play){
    //Clear profiler
    this->profiler.reset();

    //Pause loop
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return !state.pause || !thread_running; });
  }

  //---------------------------
}
void Sensor::gui_config(){
  //---------------------------

  gui_capture->show_parameter(set_parent);

  //---------------------------
}

}
