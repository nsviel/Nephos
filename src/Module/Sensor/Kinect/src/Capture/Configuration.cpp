#include "Configuration.h"

#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Configuration::Configuration(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();

  this->k4n_struct = node_k4n->get_k4n_structure();
  this->dat_graph = node_data->get_dat_graph();
  this->dat_set = node_data->get_dat_set();

  //---------------------------
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

}
