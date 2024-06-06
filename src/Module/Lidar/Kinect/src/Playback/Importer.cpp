#include "Importer.h"

#include <Engine/Namespace.h>
#include <Kinect/Namespace.h>
#include <Data/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Importer::Importer(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();

  this->node_k4n = node_k4n;
  this->node_engine = node_k4n->get_node_engine();
  this->dat_graph = node_data->get_dat_graph();
  this->dat_entity = node_data->get_dat_entity();
  this->dat_set = node_data->get_dat_set();
  this->dat_glyph = node_data->get_dat_glyph();

  this->format = "mkv";
  this->require_discrete_gpu = true;

  //---------------------------
}
Importer::~Importer(){}

//Main function
utl::base::Element* Importer::import(utl::base::Path path){
  if(!utl::file::is_exist(path.data)) return nullptr;
  //---------------------------

  //Create sensor
  k4n::playback::Sensor* sensor = new k4n::playback::Sensor(node_k4n, path);
  sensor->name = utl::path::get_name_from_path(path.data);
  sensor->data.name = utl::path::get_name_from_path(path.data);
  sensor->data.path = path;
  sensor->data.format = format;
  sensor->timestamp.begin = find_mkv_ts_beg(path.data);
  sensor->timestamp.end = find_mkv_ts_end(path.data);
  sensor->vec_recorder.push_back(new k4n::capture::Recorder());

  //Associated set
  sensor->set_parent = manage_set_parent();
  sensor->start_thread();

  //---------------------------
  return sensor;
}

//Subfunction
float Importer::find_mkv_ts_beg(string path){
  //---------------------------

  k4a::playback playback = k4a::playback::open(path.c_str());;
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_BEGIN);

  k4a::capture capture;
  k4a::image color = nullptr;
  while(color == nullptr){
    playback.get_next_capture(&capture);
    color = capture.get_color_image();
  }

  float ts_beg = color.get_device_timestamp().count() / 1000000.0f;

  //---------------------------
  return ts_beg;
}
float Importer::find_mkv_ts_end(string path){
  //---------------------------

  k4a::playback playback = k4a::playback::open(path.c_str());;
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_END);

  k4a::capture capture;
  k4a::image color = nullptr;
  while(color == nullptr){
    playback.get_previous_capture(&capture);
    color = capture.get_color_image();
  }

  float ts_end = color.get_device_timestamp().count() / 1000000.0f;

  //---------------------------
  return ts_end;
}
dat::base::Set* Importer::manage_set_parent(){
  dat::base::Set* set_graph = dat_graph->get_set_graph();
  //---------------------------

  //Check if already existing
  dat::base::Set* set = dat_set->get_subset(set_graph, "kinect");
  if(set != nullptr) return set;

  //Create the set
  set = new dat::base::Set();
  set->name = "kinect";
  set->is_lockable = true;
  set->icon = ICON_FA_USER;
  set->is_locked = true;
  set->is_suppressible = true;
  dat_set->add_subset(set_graph, set);

  //---------------------------
  return set;
}

}
