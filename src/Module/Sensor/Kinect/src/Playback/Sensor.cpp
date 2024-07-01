#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, utl::base::Path path){
  //---------------------------

  dyn::Node* node_dynamic = node_k4n->get_node_dynamic();

  this->k4n_image = new k4n::processing::Image(node_k4n);
  this->k4n_config = new k4n::playback::Configuration(node_k4n);
  this->dyn_sensor = node_dynamic->get_dyn_sensor();
  this->gui_playback = new k4n::gui::Playback(node_k4n);

  this->name = utl::path::get_name_from_path(path.build());
  this->data.path = path;
  this->data.name = utl::path::get_name_from_path(path.build());
  this->data.path.format = utl::path::get_format_from_path(path.build());
  this->depth_mode = "NFOV";

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

  //Init playback
  std::string path = data.path.build();
  if(path == "") return;
  this->playback = k4a::playback::open(path.c_str());
  if(!playback){
    std::cout<<"[error] Sensor opening problem"<<std::endl;
    return;
  }

  k4n_config->find_configuration(this);
  k4n_config->find_calibration(this);

  //---------------------------
}
void Sensor::thread_loop(){
  prf::dynamic::Tasker* tasker = profiler.fetch_tasker("kinect::loop");
  //---------------------------

  tasker->loop(30);

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
  this->manage_pause();

  //---------------------------
}
void Sensor::thread_end(){
  //---------------------------

  k4n_image->wait_thread();
  this->playback.close();

  //---------------------------
}

//Subfunction
k4a::capture* Sensor::manage_new_capture(){
  //---------------------------

  k4a::capture* capture = new k4a::capture();
  bool capture_left = playback.get_next_capture(capture);
  if(capture_left == false){
    capture = nullptr;
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
    profiler.pause = true;
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] { return !state.pause || !thread_running;});
    profiler.pause = false;
  }

  //---------------------------
}
void Sensor::manage_query(float value){
  //---------------------------

  if(value > timestamp.end){
    std::cout<<"[error] timestamp superior file end"<<std::endl;
    exit(0);
  }else if(value < timestamp.begin){
    std::cout<<"[error] timestamp inferior file begin"<<std::endl;
    exit(0);
  }

  if(state.pause){
    state.pause = false;
    auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(value));
    playback.seek_timestamp(ts, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    state.pause = true;
  }else{
    auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(value));
    playback.seek_timestamp(ts, K4A_PLAYBACK_SEEK_DEVICE_TIME);
  }

  //---------------------------
}
void Sensor::gui_config(){
  //---------------------------

  gui_playback->show_parameter(this);

  //---------------------------
}

}
