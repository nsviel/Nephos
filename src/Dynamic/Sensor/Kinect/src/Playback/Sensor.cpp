#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Processing/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, utl::base::Path path){
  //---------------------------

  dyn::prc::Node* node_processing = node_k4n->get_node_processing();

  this->k4n_processing = new k4n::Processing(node_k4n);
  this->k4n_config = new k4n::playback::Configuration(node_k4n);
  this->k4n_playback = new k4n::playback::Playback(node_k4n);
  //this->dat_sensor = node_processing->get_dat_sensor();
  this->gui_playback = new k4n::gui::Playback(node_k4n);

  this->data.path = path;

  //---------------------------
  //std::shared_ptr<k4n::playback::Sensor> sensor(this);
  //dat_sensor->init_sensor(sensor);
}
Sensor::~Sensor(){
  //---------------------------

  this->stop_thread();
  //std::shared_ptr<k4n::playback::Sensor> sensor(this);
  //dat_sensor->remove_sensor(sensor);

  //---------------------------
}

//Main function
void Sensor::thread_init(){
  //---------------------------

  k4n_playback->init_playback(*this);
  k4n_config->find_configuration(*this);
  k4n_config->find_calibration(*this);

  //---------------------------
}
void Sensor::thread_loop(){
  //prf::monitor::Tasker* tasker = profiler.fetch_tasker("kinect::loop");
  //---------------------------

  //tasker->loop(30);

  //Next capture
  //tasker->task_begin("capture");
  k4a::capture* capture = manage_new_capture();
  if(capture == nullptr) return;
  //tasker->task_end("capture");

  //Wait previous threads to finish
  //tasker->task_begin("wait");
  this->manage_old_capture(capture);
  //tasker->task_end("wait");

  //Run processing
  std::shared_ptr<k4n::playback::Sensor> sensor = std::static_pointer_cast<k4n::playback::Sensor>(k4n::base::Sensor::shared_from_this());
  k4n_processing->start_thread(sensor);

  //Loop sleeping
  this->manage_pause();

  //---------------------------
}
void Sensor::thread_end(){
  //---------------------------

  k4n_processing->wait_thread();
  k4n_playback->close_playback(*this);

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
void Sensor::gui_config(){
  //---------------------------

  std::shared_ptr<k4n::playback::Sensor> sensor(this);
  gui_playback->show_parameter(sensor);

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

}
