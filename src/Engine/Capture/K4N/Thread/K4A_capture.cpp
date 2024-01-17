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
void K4A_capture::run_thread(k4n::dev::Sensor* k4n_sensor){
  if(k4n_sensor == nullptr) return;
  //---------------------------

  //Init elements
  k4n_sensor->param.index =0;
  k4a::device device = k4a::device::open(k4n_sensor->param.index);
  k4a::capture capture;

  //Configuration
  k4n_sensor->param.device = &device;
  k4n_sensor->param.serial_number = device.get_serialnum();
  configuration->make_device_configuration(k4n_sensor);
  k4n_calibration->make_capture_calibration(k4n_sensor);
  k4n_calibration->make_device_transformation(k4n_sensor);

  //Start camera
  k4n_sensor->param.version = device.get_version();
  this->manage_color_setting(k4n_sensor);
  device.start_cameras(&k4n_sensor->param.configuration);

  //Start capture thread
  this->thread_running = true;
  while(thread_running && k4n_sensor){
    fps_control->start();

    auto timeout = std::chrono::milliseconds(2000);
    device.get_capture(&capture, timeout);
    if(!capture) continue;

    //Capture data
    k4a_data->find_data_from_capture(k4n_sensor, capture);
    k4a_processing->convert_into_cloud(k4n_sensor);
    this->manage_pause(k4n_sensor);
    this->manage_recording(k4n_sensor, capture);

    //FPS
    fps_control->stop();
    k4n_sensor->param.fps.current = fps_counter->update();
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
void K4A_capture::manage_pause(k4n::dev::Sensor* k4n_sensor){
  //---------------------------

  //If pause, wait until end pause or end thread
  if(k4n_sensor->player.pause){
    while(k4n_sensor->player.pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
void K4A_capture::manage_recording(k4n::dev::Sensor* k4n_sensor, k4a::capture capture){
  //---------------------------

  k4a::record& recorder = k4n_sensor->recorder.recorder;

  //Start recording
  if(k4n_sensor->player.record && !recorder.is_valid()){
    recorder = k4a::record::create(k4n_sensor->recorder.path.c_str(), *k4n_sensor->param.device, k4n_sensor->param.configuration);
    recorder.write_header();
    k4n_sensor->recorder.ts_beg = k4n_sensor->player.ts_cur;
  }

  //Recording
  if(k4n_sensor->player.record && recorder.is_valid()){
    recorder.write_capture(capture);
    k4n_sensor->recorder.ts_rec = k4n_sensor->player.ts_cur - k4n_sensor->recorder.ts_beg;
  }

  //Flush to file when finish
  if(!k4n_sensor->player.record && recorder.is_valid()){
    recorder.flush();
    recorder.close();
  }

  //---------------------------
}
void K4A_capture::manage_color_setting(k4n::dev::Sensor* k4n_sensor){
  //---------------------------

  k4n_sensor->param.device->set_color_control(k4n_sensor->color.config.exposure.command, k4n_sensor->color.config.exposure.mode, k4n_sensor->color.config.exposure.value);
  k4n_sensor->param.device->set_color_control(k4n_sensor->color.config.white_balance.command, k4n_sensor->color.config.white_balance.mode, k4n_sensor->color.config.white_balance.value);
  k4n_sensor->param.device->set_color_control(k4n_sensor->color.config.brightness.command, k4n_sensor->color.config.brightness.mode, k4n_sensor->color.config.brightness.value);
  k4n_sensor->param.device->set_color_control(k4n_sensor->color.config.contrast.command, k4n_sensor->color.config.contrast.mode, k4n_sensor->color.config.contrast.value);
  k4n_sensor->param.device->set_color_control(k4n_sensor->color.config.saturation.command, k4n_sensor->color.config.saturation.mode, k4n_sensor->color.config.saturation.value);
  k4n_sensor->param.device->set_color_control(k4n_sensor->color.config.sharpness.command, k4n_sensor->color.config.sharpness.mode, k4n_sensor->color.config.sharpness.value);
  k4n_sensor->param.device->set_color_control(k4n_sensor->color.config.gain.command, k4n_sensor->color.config.gain.mode, k4n_sensor->color.config.gain.value);
  k4n_sensor->param.device->set_color_control(k4n_sensor->color.config.backlight_compensation.command, k4n_sensor->color.config.backlight_compensation.mode, k4n_sensor->color.config.backlight_compensation.value);
  k4n_sensor->param.device->set_color_control(k4n_sensor->color.config.power_frequency.command, k4n_sensor->color.config.power_frequency.mode, k4n_sensor->color.config.power_frequency.value);

  //---------------------------
}
