#include "Capture.h"

#include <K4N/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::thread{

//Constructor / Destructor
Capture::Capture(){
  //---------------------------

  this->k4a_data = new k4n::data::Data();
  this->k4a_cloud = new k4n::data::Cloud();
  this->configuration = new k4n::config::Configuration();
  this->k4n_calibration = new k4n::config::Calibration();

  //---------------------------
}
Capture::~Capture(){
  //---------------------------

  this->stop_thread();
  this->thread.join();

  //---------------------------
}

//Main function
void Capture::start_thread(k4n::dev::Sensor* device){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Capture::run_thread, this, device);
  }

  //---------------------------
}

//Subfunction
void Capture::run_thread(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  k4n::dev::Master* master = sensor->master;
  //---------------------------

  //Init elements
  sensor->param.index =0;
  prf::Tasker* tasker = sensor->profiler->get_tasker("capture");
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
    tasker->loop_begin(master->operation.fps);

    auto timeout = std::chrono::milliseconds(2000);
    device.get_capture(&capture, timeout);
    if(!capture) continue;

    //Capture data
    k4a_data->find_data_from_capture(sensor, capture);
    k4a_cloud->convert_into_cloud(sensor);

    //Manage event
    this->manage_pause(sensor);
    this->manage_recording(sensor, capture);
    tasker->loop_end();
  }

  //---------------------------
}
void Capture::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Capture::manage_pause(k4n::dev::Sensor* sensor){
  //---------------------------

  //If pause, wait until end pause or end thread
  if(sensor->master->player.pause){
    while(sensor->master->player.pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
void Capture::manage_recording(k4n::dev::Sensor* sensor, k4a::capture capture){
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
void Capture::manage_color_setting(k4n::dev::Sensor* sensor){
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


}
