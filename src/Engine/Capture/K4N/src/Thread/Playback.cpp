#include "Playback.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


namespace eng::k4n::thread{

//Constructor / Destructor
Playback::Playback(eng::k4n::Node* node_k4n){
  //---------------------------

  this->fps_counter = new utl::fps::Counter();
  this->fps_control = new utl::fps::Control(30);

  this->k4a_data = new eng::k4n::data::Data();
  this->k4a_cloud = new eng::k4n::data::Cloud(node_k4n);
  this->k4n_image = new eng::k4n::data::Image();
  this->k4n_configuration = new eng::k4n::config::Configuration();
  this->k4n_calibration = new eng::k4n::config::Calibration();
  this->k4n_operation= new eng::k4n::utils::Operation();

  //---------------------------
}
Playback::~Playback(){
  //---------------------------

  this->stop_thread();
  this->thread.join();

  //---------------------------
}

//Main function
void Playback::start_thread(eng::k4n::dev::Sensor* sensor){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Playback::run_thread, this, sensor);
  }

  //---------------------------
}
void Playback::run_thread(eng::k4n::dev::Sensor* sensor){
  utl::element::Profiler* profiler = sensor->cap_profiler;
  //---------------------------

  //Init playback
  k4a::playback playback = k4a::playback::open(sensor->param.path_data.c_str());
  if(!playback) return;
  this->thread_running = true;
  sensor->param.playback = &playback;

  k4n_configuration->find_playback_configuration(sensor);
  k4n_configuration->make_device_configuration(sensor);
  k4n_calibration->find_playback_calibration(sensor);
  k4n_calibration->make_device_transformation(sensor);

  //Playback thread
  k4a::capture capture;
  while(thread_running){
    profiler->loop_begin();
    fps_control->start();

    //Next capture
    profiler->task_begin("capture");
    playback.get_next_capture(&capture);
    profiler->task_end("capture");
    if(!capture) continue;

    //Find data from capture
    profiler->task_begin("data");
    k4a_data->find_data_from_capture(sensor, capture);
    profiler->task_end("data");

    //Convert data into cloud
    profiler->task_begin("cloud");
    k4a_cloud->convert_into_cloud(sensor);
    profiler->task_end("cloud");

    profiler->task_begin("image");
    k4n_image->make_images(sensor);
    profiler->task_end("image");

    //Manage event
    this->manage_pause(sensor);
    this->manage_restart(sensor);

    //FPS control
    profiler->task_begin("sleep");
    fps_control->stop();
    fps_control->set_fps_max(sensor->param.fps.query);
    sensor->param.fps.current = fps_counter->update();
    profiler->task_end("sleep", vec4(50, 50, 50, 255));
    profiler->loop_end();
  }

  playback.close();

  //---------------------------
}
void Playback::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//Subfunction
void Playback::manage_pause(eng::k4n::dev::Sensor* sensor){
  utl::element::Profiler* profiler = sensor->cap_profiler;
  //---------------------------

  //If pause, wait until end pause or end thread
  bool& is_paused = sensor->master->player.pause;
  if(is_paused || !sensor->master->player.play){
    profiler->clear();
    while(is_paused && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
void Playback::manage_restart(eng::k4n::dev::Sensor* sensor){
  //---------------------------

  if(sensor->color.data.timestamp >= sensor->master->player.ts_end){
    sensor->master->manage_restart();
  }

  //---------------------------
}
void Playback::manage_recording(eng::k4n::dev::Sensor* sensor, k4a::capture capture){
  //---------------------------
/*
  k4a::record& recorder = sensor->recorder.recorder;

  //Start recording
  if(sensor->player.record && !recorder.is_valid()){
    recorder = k4a::record::create(sensor->recorder.path.c_str(), *sensor->param.device, sensor->param.configuration);
    recorder.write_header();
    sensor->recorder.ts_beg = sensor->color.data.timestamp;
  }

  //Recording
  if(sensor->player.record && recorder.is_valid()){
    recorder.write_capture(capture);
    sensor->recorder.ts_rec = sensor->color.data.timestamp - sensor->recorder.ts_beg;
  }

  //Flush to file when finish
  if(!sensor->player.record && recorder.is_valid()){
    recorder.flush();
    recorder.close();
  }
*/
  //---------------------------
}


}
