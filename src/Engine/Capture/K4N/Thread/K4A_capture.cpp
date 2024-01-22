#include "K4A_capture.h"

#include <Engine/Engine.h>
#include <Utility/Function/Timer/FPS_counter.h>
#include <Utility/Function/Timer/FPS_control.h>
#include <Engine/Capture/K4N/Utils/Namespace.h>


//Constructor / Destructor
K4A_capture::K4A_capture(Engine* engine){
  //---------------------------

  this->fps_counter = new FPS_counter();
  this->fps_control = new FPS_control(30);
  this->k4a_data = new k4n::data::Data();
  this->k4a_processing = new k4n::data::Cloud(engine);
  this->configuration = new k4n::config::Configuration();
  this->k4n_calibration = new k4n::config::Calibration();

  //---------------------------
}
K4A_capture::~K4A_capture(){
  //---------------------------

  this->stop_thread();
  this->thread.join();

  //---------------------------
}

//Main function
void K4A_capture::start_thread(k4n::dev::Sensor* device){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&K4A_capture::run_thread, this, device);
  }

  //---------------------------
}

//Subfunction
void K4A_capture::run_thread(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  //Init elements
  sensor->param.index =0;
  k4a::device device = k4a::device::open(sensor->param.index);
  k4a::capture capture;

  //Configuration
  sensor->param.device = &device;
  sensor->param.serial_number = device.get_serialnum();
  configuration->make_device_configuration(sensor);
  k4n_calibration->make_capture_calibration(sensor);
  k4n_calibration->make_device_transformation(sensor);

  //Start camera
  sensor->param.version = device.get_version();
  this->manage_color_setting(sensor);
  device.start_cameras(&sensor->param.configuration);

  //Start capture thread
  this->thread_running = true;
  while(thread_running && sensor){
    fps_control->start();

    auto timeout = std::chrono::milliseconds(2000);
    device.get_capture(&capture, timeout);
    if(!capture) continue;

    //Capture data
    k4a_data->find_data_from_capture(sensor, capture);
    k4a_processing->convert_into_cloud(sensor);
    this->manage_pause(sensor);
    this->manage_recording(sensor, capture);

    //FPS
    fps_control->stop();
    sensor->param.fps.current = fps_counter->update();
  }

  //---------------------------
}
void K4A_capture::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void K4A_capture::manage_pause(k4n::dev::Sensor* sensor){
  //---------------------------

  //If pause, wait until end pause or end thread
  if(sensor->master->player.pause){
    while(sensor->master->player.pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
void K4A_capture::manage_recording(k4n::dev::Sensor* sensor, k4a::capture capture){
  //---------------------------
/*
  k4a::record& recorder = sensor->recorder.recorder;

  //Start recording
  if(sensor->player.record && !recorder.is_valid()){
    recorder = k4a::record::create(sensor->recorder.path.c_str(), *sensor->param.device, sensor->param.configuration);
    recorder.write_header();
    sensor->recorder.ts_beg = sensor->master->player.ts_cur;
  }

  //Recording
  if(sensor->player.record && recorder.is_valid()){
    recorder.write_capture(capture);
    sensor->recorder.ts_rec = sensor->master->player.ts_cur - sensor->recorder.ts_beg;
  }

  //Flush to file when finish
  if(!sensor->player.record && recorder.is_valid()){
    recorder.flush();
    recorder.close();
  }
*/
  //---------------------------
}
void K4A_capture::manage_color_setting(k4n::dev::Sensor* sensor){
  //---------------------------

  sensor->param.device->set_color_control(sensor->color.config.exposure.command, sensor->color.config.exposure.mode, sensor->color.config.exposure.value);
  sensor->param.device->set_color_control(sensor->color.config.white_balance.command, sensor->color.config.white_balance.mode, sensor->color.config.white_balance.value);
  sensor->param.device->set_color_control(sensor->color.config.brightness.command, sensor->color.config.brightness.mode, sensor->color.config.brightness.value);
  sensor->param.device->set_color_control(sensor->color.config.contrast.command, sensor->color.config.contrast.mode, sensor->color.config.contrast.value);
  sensor->param.device->set_color_control(sensor->color.config.saturation.command, sensor->color.config.saturation.mode, sensor->color.config.saturation.value);
  sensor->param.device->set_color_control(sensor->color.config.sharpness.command, sensor->color.config.sharpness.mode, sensor->color.config.sharpness.value);
  sensor->param.device->set_color_control(sensor->color.config.gain.command, sensor->color.config.gain.mode, sensor->color.config.gain.value);
  sensor->param.device->set_color_control(sensor->color.config.backlight_compensation.command, sensor->color.config.backlight_compensation.mode, sensor->color.config.backlight_compensation.value);
  sensor->param.device->set_color_control(sensor->color.config.power_frequency.command, sensor->color.config.power_frequency.mode, sensor->color.config.power_frequency.value);

  //---------------------------
}
