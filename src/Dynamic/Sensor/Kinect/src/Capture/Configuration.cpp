#include "Configuration.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Configuration::Configuration(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();
  dat::graph::Node* node_graph = node_data->get_node_graph();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->dat_graph = node_graph->get_dat_graph();
  this->dat_set = node_element->get_dat_set();

  //---------------------------
  this->make_default_configuration();
}
Configuration::~Configuration(){}

//Main function
void Configuration::manage_configuration(){
  dat::base::Set* set_graph = dat_graph->get_set_graph();
  dat::base::Set* set = dat_set->get_subset(set_graph, "kinect");
  if(set != nullptr) return;
  //---------------------------



  //---------------------------
}
void Configuration::make_default_configuration(){
  //---------------------------

  k4n_struct->config.depth.mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
  k4n_struct->config.color.format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  k4n_struct->config.color.resolution = K4A_COLOR_RESOLUTION_1080P;

  k4n_struct->fps.mode = K4A_FRAMES_PER_SECOND_30;
  k4n_struct->config.synchro.depth_delay_off_color_us = 0;
  k4n_struct->config.synchro.wired_mode = K4A_WIRED_SYNC_MODE_STANDALONE;
  k4n_struct->config.synchro.subordinate_delay_off_master_us = 0;
  k4n_struct->config.synchro.disable_streaming_indicator = true;
  k4n_struct->config.synchro.synchronized_images_only = true;

  k4n_struct->config.color.exposure.value = 15625;
  k4n_struct->config.color.white_balance.value = 4500;
  k4n_struct->config.color.brightness.value = 128;
  k4n_struct->config.color.contrast.value = 5;
  k4n_struct->config.color.saturation.value = 32;
  k4n_struct->config.color.sharpness.value = 2;
  k4n_struct->config.color.gain.value = 0;
  k4n_struct->config.color.backlight_compensation.value = 0;
  k4n_struct->config.color.power_frequency.value = 2;

  //---------------------------
}
void Configuration::find_calibration(k4n::base::Sensor* sensor){
  k4a::device& device = sensor->device.handle;
  //---------------------------

  sensor->device.calibration = device.get_calibration(k4n_struct->config.depth.mode, k4n_struct->config.color.resolution);
  sensor->device.transformation = k4a::transformation(sensor->device.calibration);

  //---------------------------
}
void Configuration::find_versioning(k4n::base::Sensor* sensor){
  //---------------------------

  k4a_hardware_version_t version = sensor->device.version;
  sensor->firmware.color = std::to_string(version.rgb.major) + "." + std::to_string(version.rgb.minor) + "." + std::to_string(version.rgb.iteration);
  sensor->firmware.depth = std::to_string(version.depth.major) + "." + std::to_string(version.depth.minor) + "." + std::to_string(version.depth.iteration);
  sensor->firmware.audio = std::to_string(version.audio.major) + "." + std::to_string(version.audio.minor) + "." + std::to_string(version.audio.iteration);
  sensor->firmware.build = version.firmware_build == K4A_FIRMWARE_BUILD_RELEASE ? "Release" : "Debug";
  sensor->firmware.constructor = version.firmware_signature == K4A_FIRMWARE_SIGNATURE_MSFT ? "Microsoft" : version.firmware_signature == K4A_FIRMWARE_SIGNATURE_TEST ? "Test" : "Unsigned";

  //---------------------------
}
void Configuration::make_sensor_configuration(k4n::base::Sensor* sensor){
  //---------------------------

  k4a_device_configuration_t configuration = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;

  //Field stuff
  configuration.color_format = k4n_struct->config.color.format;
  configuration.color_resolution = k4n_struct->config.color.resolution;
  configuration.depth_mode = k4n_struct->config.depth.mode;

  //Synchro stuff
  configuration.camera_fps = k4n_struct->fps.mode;
  configuration.depth_delay_off_color_usec = k4n_struct->config.synchro.depth_delay_off_color_us;
  configuration.wired_sync_mode = k4n_struct->config.synchro.wired_mode;
  configuration.subordinate_delay_off_master_usec = k4n_struct->config.synchro.subordinate_delay_off_master_us;
  configuration.disable_streaming_indicator = k4n_struct->config.synchro.disable_streaming_indicator;
  configuration.synchronized_images_only = k4n_struct->config.synchro.synchronized_images_only;

  //---------------------------
  sensor->device.configuration = configuration;
}
void Configuration::make_sensor_color_configuration(k4n::base::Sensor* sensor){
  k4a::device& device = sensor->device.handle;
  //---------------------------

  device.set_color_control(k4n_struct->config.color.exposure.command, k4n_struct->config.color.exposure.mode, k4n_struct->config.color.exposure.value);
  device.set_color_control(k4n_struct->config.color.white_balance.command, k4n_struct->config.color.white_balance.mode, k4n_struct->config.color.white_balance.value);
  device.set_color_control(k4n_struct->config.color.brightness.command, k4n_struct->config.color.brightness.mode, k4n_struct->config.color.brightness.value);
  device.set_color_control(k4n_struct->config.color.contrast.command, k4n_struct->config.color.contrast.mode, k4n_struct->config.color.contrast.value);
  device.set_color_control(k4n_struct->config.color.saturation.command, k4n_struct->config.color.saturation.mode, k4n_struct->config.color.saturation.value);
  device.set_color_control(k4n_struct->config.color.sharpness.command, k4n_struct->config.color.sharpness.mode, k4n_struct->config.color.sharpness.value);
  device.set_color_control(k4n_struct->config.color.gain.command, k4n_struct->config.color.gain.mode, k4n_struct->config.color.gain.value);
  device.set_color_control(k4n_struct->config.color.backlight_compensation.command, k4n_struct->config.color.backlight_compensation.mode, k4n_struct->config.color.backlight_compensation.value);
  device.set_color_control(k4n_struct->config.color.power_frequency.command, k4n_struct->config.color.power_frequency.mode, k4n_struct->config.color.power_frequency.value);

  sensor->color.config = k4n_struct->config.color;
  sensor->depth.config = k4n_struct->config.depth;
  sensor->ir.config = k4n_struct->config.ir;

  //---------------------------
}

}
