#include "Importer.h"

#include <Engine/Namespace.h>
#include <Kinect/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Importer::Importer(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();

  this->node_k4n = node_k4n;
  this->node_engine = node_k4n->get_node_engine();
  this->dat_graph = node_data->get_data_graph();
  this->dat_entity = node_data->get_data_entity();
  this->dat_set = node_data->get_data_set();

  this->format = "mkv";
  this->require_discrete_gpu = true;

  //---------------------------
}
Importer::~Importer(){}

//Main function
utl::media::File* Importer::import(utl::media::Path path){
  if(!utl::file::is_exist(path.data)) return nullptr;
  //---------------------------

  //Associated master
  k4n::dev::Master* master = manage_master();
  k4n::playback::Sensor* sensor = new k4n::playback::Sensor(node_k4n, path);
  sensor->master = master;
  sensor->ts_beg = find_mkv_ts_beg(path.data);
  sensor->ts_end = find_mkv_ts_end(path.data);

  //Sensor initialization
  sensor->init();
  dat_entity->init_entity(sensor);
  dat_set->insert_entity(master, sensor);
  master->player->player_update();

  //---------------------------
  return nullptr;
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
k4n::dev::Master* Importer::manage_master(){
  dat::base::Set* set_scene = dat_graph->get_set_graph();
  //---------------------------

  //Check if already existing
  for(int i=0; i<set_scene->list_subset.size(); i++){
    dat::base::Set* set = *std::next(set_scene->list_subset.begin(), i);
    if(set->name == "kinect"){
      return dynamic_cast<k4n::dev::Master*>(set);
    }
  }

  //Create the master
  k4n::dev::Master* master = new k4n::dev::Master(node_k4n);
  master->name = "kinect";
  master->is_lockable = true;
  dat_set->add_subset(set_scene, master);

  //---------------------------
  return master;
}

}
