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
  this->k4n_usb = new k4n::config::USB();

  //---------------------------
}
Capture::~Capture(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Capture::start_thread(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Capture::run_thread, this, sensor);
  }

  //---------------------------
}
void Capture::run_thread(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_tasker("capture");
  k4n::dev::Master* master = sensor->master;
  //---------------------------

  //Init elements
  sensor->param.index = 0;
  sensor->param.device = k4a::device::open(sensor->param.index);
  sensor->param.serial_number = sensor->param.device.get_serialnum();
  sensor->param.version = sensor->param.device.get_version();

  //Configuration
  configuration->make_device_configuration_initial(sensor);
  k4n_calibration->make_capture_calibration(sensor, sensor->param.device);
  k4n_calibration->make_device_transformation(sensor);

  //Start camera
//  this->manage_color_setting(sensor, device);
  k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
  config.camera_fps = K4A_FRAMES_PER_SECOND_30;
  config.depth_mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;
  // NE MARCHE QU'EN YUY2 !!!!!!!!!!!!!!
  //En faite ne marche que dans certaine configurations
  //du coup vérifier quelles config marchent pas et les empécher
  
  config.color_format = K4A_IMAGE_FORMAT_COLOR_YUY2;
  config.color_resolution = K4A_COLOR_RESOLUTION_1080P;
  sensor->param.device.start_cameras(&config);

  //Start capture thread
  this->thread_running = true;
  while(thread_running){
    //Next capture
    tasker->loop_begin();
    k4a::capture* capture = manage_capture(sensor);
    if(!capture->is_valid()){
      delete capture;
      continue;
    }

    //Find data from capture
    k4a_data->run_thread(sensor, capture);

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

//Subfunction
k4a::capture* Capture::manage_capture(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_tasker("capture");
  //---------------------------

  tasker->task_begin("capture");

  k4a::capture* capture = new k4a::capture();
  bool ok = sensor->param.device.get_capture(capture, std::chrono::milliseconds(2000));

  tasker->task_end("capture");

  //---------------------------
  return capture;
}
void Capture::manage_pause(k4n::dev::Sensor* sensor){
  //---------------------------

  //If pause, wait until end pause or end thread
  bool& is_paused = sensor->master->player.pause;
  if(is_paused || !sensor->master->player.play){
    sensor->profiler->clear();
    while(is_paused && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
void Capture::manage_recording(k4n::dev::Sensor* sensor, k4a::capture* capture){
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
void Capture::manage_color_setting(k4n::dev::Sensor* sensor, k4a::device& device){
  //---------------------------

  device.set_color_control(sensor->color.config.exposure.command, sensor->color.config.exposure.mode, sensor->color.config.exposure.value);
  device.set_color_control(sensor->color.config.white_balance.command, sensor->color.config.white_balance.mode, sensor->color.config.white_balance.value);
  device.set_color_control(sensor->color.config.brightness.command, sensor->color.config.brightness.mode, sensor->color.config.brightness.value);
  device.set_color_control(sensor->color.config.contrast.command, sensor->color.config.contrast.mode, sensor->color.config.contrast.value);
  device.set_color_control(sensor->color.config.saturation.command, sensor->color.config.saturation.mode, sensor->color.config.saturation.value);
  device.set_color_control(sensor->color.config.sharpness.command, sensor->color.config.sharpness.mode, sensor->color.config.sharpness.value);
  device.set_color_control(sensor->color.config.gain.command, sensor->color.config.gain.mode, sensor->color.config.gain.value);
  device.set_color_control(sensor->color.config.backlight_compensation.command, sensor->color.config.backlight_compensation.mode, sensor->color.config.backlight_compensation.value);
  device.set_color_control(sensor->color.config.power_frequency.command, sensor->color.config.power_frequency.mode, sensor->color.config.power_frequency.value);

  //---------------------------
}


}
