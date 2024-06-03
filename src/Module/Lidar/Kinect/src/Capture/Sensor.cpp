#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, int index) : k4n::dev::Sensor(node_k4n){
  //---------------------------

  this->gui_capture = new k4n::gui::Capture(node_k4n);

  this->device.idx_dev = index;
  this->name = "capture_" + to_string(index);

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Sensor::info(){
  //---------------------------

  gui_capture->show_parameter(master);

  //---------------------------
}
void Sensor::thread_init(){
  //---------------------------

  //Init elements
  this->device.idx_dev = 0;
  this->device.handle = k4a::device::open(device.idx_dev);
  if(!device.handle.is_valid()) return;

  this->device.serial_number = device.handle.get_serialnum();
  this->device.version = device.handle.get_version();

  //Configuration
  k4n_config->make_sensor_configuration(this);
  k4n_config->make_sensor_color_configuration(this);
  k4n_config->make_capture_calibration(this);
  k4n_config->make_transformation_from_calibration(this);
  this->device.handle.start_cameras(&device.configuration);

  //---------------------------
}
void Sensor::thread_loop(){
  //---------------------------

  prf::graph::Tasker* tasker = profiler->get_or_create_tasker("capture");
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
  dyn::base::Player* player = &master->player;
  //---------------------------

  //If pause, wait until end pause or end thread
  if(player->pause || !player->play){
    profiler->reset();
    while(player->pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
void Sensor::manage_reset(){
  //---------------------------

  //this->reset();
  //this->run_thread();

  //---------------------------
}
void Sensor::manage_configuration(){
  //---------------------------

  k4n_config->make_sensor_color_configuration(this);
  this->color.config = master->config.color;
  this->depth.config = master->config.depth;
  this->ir.config = master->config.ir;

  //---------------------------
}

}
