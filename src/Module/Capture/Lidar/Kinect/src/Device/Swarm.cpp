#include "Swarm.h"

#include <Engine/Namespace.h>
#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::dev{

//Constructor / Destructor
Swarm::Swarm(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  dat::Node* node_data = node_engine->get_node_data();
  prf::Node* node_profiler = node_k4n->get_node_profiler();

  this->node_k4n = node_k4n;
  this->k4n_struct = node_k4n->get_k4n_struct();
  this->profiler = node_profiler->get_prf_manager();
  this->dat_graph = node_data->get_data_graph();
  this->dat_set = node_data->get_data_set();
  this->k4n_transfo = new k4n::utils::Transformation();
  this->k4n_config = new k4n::utils::Configuration();

  //---------------------------
}
Swarm::~Swarm(){}

//Sensor function
void Swarm::create_sensor_playback(utl::media::Path path){
  if(!utl::file::is_exist(path.data)) return;
  //---------------------------

  //Associated master
  k4n::dev::Master* master = get_or_create_playback_master("Playback");
  int index = dat_set->compute_number_entity(master);

  //Sensor creation
  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(node_k4n);
  sensor->name = "playback_" + to_string(index);
  sensor->param.format = utl::path::get_format_from_path(path.data);
  sensor->param.file_size = utl::file::size(path.data);
  sensor->param.index = index;
  sensor->param.path = path;
  sensor->master = master;

  //Sensor initialization
  sensor->init();
  dat_set->insert_entity(master, sensor);
  master->player_update();
  dat_graph->assign_UID(sensor);
  k4n_transfo->find_transformation_from_file(sensor, path.transformation);
  k4n_struct->device.list_sensor.push_back(sensor);


  //---------------------------
}
void Swarm::create_sensor_capture(int index){
  //---------------------------

  //Associated master
  this->close_master("Playback");
  k4n::dev::Master* master = get_or_create_capture_master("Capture");

  //Sensor creation
  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(node_k4n);
  sensor->name = "capture_" + to_string(index);
  sensor->param.index = index;
  sensor->master = master;

  //Sensor initialization
  sensor->init();
  dat_set->insert_entity(master, sensor);
  dat_graph->assign_UID(sensor);
  k4n_transfo->apply_transformation_capture(sensor);
  sensor->run_thread_capture();
  k4n_struct->device.list_sensor.push_back(sensor);

  //---------------------------
}

//Master function
void Swarm::close_master(string name){
  //---------------------------

  for(int i=0; i<k4n_struct->device.list_sensor.size(); i++){
    k4n::dev::Master* master = *std::next(k4n_struct->device.list_master.begin(), i);
    if(master->name == name){
      this->close_master(master);
      return;
    }
  }

  //---------------------------
}
void Swarm::close_master(k4n::dev::Master* master){
  //---------------------------

  dat_set->remove_all_entity(master);
  k4n_struct->device.list_master.remove(master);

  //---------------------------
}
void Swarm::close_all_master(){
  //---------------------------

  for(int i=0; i<k4n_struct->device.list_sensor.size(); i++){
    k4n::dev::Master* master = *std::next(k4n_struct->device.list_master.begin(), i);
    dat_set->remove_all_entity(master);
  }

  //---------------------------
}
k4n::dev::Master* Swarm::get_or_create_playback_master(string name){
  dat::base::Set* set_scene = dat_graph->get_set_graph();
  //---------------------------

  //Check if already existing
  for(int i=0; i<k4n_struct->device.list_sensor.size(); i++){
    k4n::dev::Master* master = *std::next(k4n_struct->device.list_master.begin(), i);
    if(name == master->name){
      return master;
    }
  }

  //Create the master
  k4n::dev::Master* master = new k4n::dev::Master(node_k4n);
  master->name = name;
  master->is_lockable = true;
  master->mode = k4n::dev::PLAYBACK;

  dat_set->add_subset(set_scene, master);
  k4n_struct->device.list_master.push_back(master);
  k4n_struct->device.selected_master = master;

  //---------------------------
  return master;
}
k4n::dev::Master* Swarm::get_or_create_capture_master(string name){
  dat::base::Set* set_scene = dat_graph->get_set_graph();
  //---------------------------

  //Check if already existing
  for(int i=0; i<k4n_struct->device.list_sensor.size(); i++){
    k4n::dev::Master* master = *std::next(k4n_struct->device.list_master.begin(), i);
    if(name == master->name){
      return master;
    }
  }

  //Create the master
  k4n::dev::Master* master = new k4n::dev::Master(node_k4n);
  master->name = name;
  master->is_lockable = true;
  master->mode = k4n::dev::CAPTURE;

  k4n_config->make_master_configuration_initial(master);
  dat_set->add_subset(set_scene, master);
  k4n_struct->device.list_master.push_back(master);
  k4n_struct->device.selected_master = master;

  //---------------------------
  return master;
}
k4n::dev::Master* Swarm::get_selected_master(){
  return k4n_struct->device.selected_master;
}

//Subfunction
void Swarm::manage_connected_device(){
  if(!k4n_struct->device.connected_device_change) return;
  //---------------------------

  //Suppress all devices
  k4n::dev::Master* master = get_or_create_capture_master("capture");
  if(master == nullptr) return;
  dat_set->remove_all_entity(master);

  //Create required number of new devices
  for(int i=0; i<k4n_struct->device.nb_connected_sensor; i++){
    this->create_sensor_capture(i);
  }

  //---------------------------
  k4n_struct->device.connected_device_change = false;
}
int Swarm::get_number_running_thread(){
  int nb_thread = 0;
  //---------------------------

  for(int i=0; i<k4n_struct->device.list_sensor.size(); i++){
    k4n::dev::Sensor* sensor = *std::next(k4n_struct->device.list_sensor.begin(), i);

    if(sensor->is_playback_running()){
      nb_thread++;
    }
    if(sensor->is_capture_running()){
      nb_thread++;
    }
  }

  //---------------------------
  return nb_thread;
}

}
