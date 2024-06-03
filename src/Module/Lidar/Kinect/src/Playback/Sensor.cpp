#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, utl::media::Path path) : k4n::dev::Sensor(node_k4n){
  //---------------------------

  this->gui_playback = new k4n::gui::Playback(node_k4n);
  this->path = path;
  this->format = utl::path::get_format_from_path(path.data);
  this->file_size = utl::file::size(path.data);
  this->path = path;
  this->name = utl::path::get_name_from_path(path.data);

  //Transformation
  glm::mat4 mat = utl::transformation::find_transformation_from_file(path.transformation);
  pose.model = mat;
  pose.model_init = mat;

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::info(){
  //---------------------------

  gui_playback->show_parameter(this);

  //---------------------------
}
void Sensor::thread_init(){
  //---------------------------

  //Init playback
  if(path.data == "") return;
  this->playback = k4a::playback::open(path.data.c_str());
  if(!playback){
    cout<<"[error] Sensor opening problem"<<endl;
    return;
  }

  k4n_config->find_playback_configuration(this);
  k4n_config->find_playback_calibration(this);
  k4n_config->make_transformation_from_calibration(this);

  //---------------------------
}
void Sensor::thread_loop(){
  //---------------------------

  prf::graph::Tasker* tasker = profiler->get_or_create_tasker("kinect::playback");
  tasker->loop_begin(30);

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

  k4n_image->wait_thread();
  this->playback.close();

  //---------------------------
}

//Subfunction
k4a::capture* Sensor::manage_new_capture(){
  dyn::base::Player* player = &master->player;
  //---------------------------

  k4a::capture* capture = new k4a::capture();
  bool capture_left = playback.get_next_capture(capture);
  if(capture_left == false){
    capture = nullptr;

    if(color.data.timestamp == player->ts_end){
      master->manage_restart();
    }
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
    //Clear thread profiler and wait subthread fulfillment
    this->profiler->reset();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    //Pause loop
    this->thread_paused = true;
    while(player->pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    this->thread_paused = false;
  }

  //---------------------------
}
void Sensor::manage_reset(){
  dyn::base::Player* player = &master->player;
  //---------------------------

  this->manage_ts_query(player->ts_beg);

  //---------------------------
}
void Sensor::manage_ts_query(float value){
  //---------------------------

  auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(value));
  playback.seek_timestamp(ts, K4A_PLAYBACK_SEEK_DEVICE_TIME);

  //---------------------------
}


}
