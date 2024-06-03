#include "Connection.h"

#include <Utility/Namespace.h>
#include <Kinect/Namespace.h>
#include <chrono>


namespace k4n::capture{

//Constructor / Destructor
Connection::Connection(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();

  this->dat_set = node_data->get_dat_set();
  this->dat_graph = node_data->get_dat_graph();

  this->current_nb_dev = 0;

  //---------------------------
}
Connection::~Connection(){
  //---------------------------

  this->stop_thread();
  this->thread.join();

  //---------------------------
}

//Main function
void Connection::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Connection::run_thread, this);
  }

  //---------------------------
  this->thread_running = true;
}
void Connection::run_thread(){
  static int nb_dev_old = 0;
  //---------------------------

  //Refresh connected sensors
  while(thread_running){
    //Get number of connected devices
    //Slow operation so in a dedicated thread
    this->current_nb_dev = k4a_device_get_installed_count();

    //Action on changement
    if(current_nb_dev != nb_dev_old){
      this->flag = true;
      nb_dev_old = current_nb_dev;
    }

    //Little sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  //---------------------------
}
void Connection::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//Subfunction
void Connection::manage_connected_device(){
  //Have to be called from main thread, connection change when flag up
  if(flag == false) return;
  dat::base::Set* set_graph = dat_graph->get_set_graph();
  //---------------------------

  //Suppress all present entities
  dat_set->remove_all_entity(set_graph);

  //Create required number of new devices
  for(int i=0; i<current_nb_dev; i++){
    this->create_sensor(i);
  }

  //---------------------------
  this->flag = false;
}
void Connection::create_sensor(int index){
  //---------------------------
/*
  //Associated set
  dat::base::Set* set = get_or_create_capture_master("Kinect");

  //Sensor creation
  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(node_k4n);
  sensor->name = "capture_" + to_string(index);
  sensor->device.idx_dev = index;
  sensor->set_parent = set;

  //Sensor initialization
  sensor->init();
  dat_set->insert_entity(set, sensor);
  dat_graph->assign_UID(sensor);
  utl::transformation::apply_transformation_capture(sensor->get_pose()->model);
  sensor->run_thread();

*/
  //---------------------------
}
void Connection::manage_master(){
/*  dat::base::Set* set_scene = dat_graph->get_set_graph();
  //---------------------------

  //Check if already existing
  for(int i=0; i<k4n_struct->list_sensor.size(); i++){
    dat::base::Set* set = *std::next(k4n_struct->list_master.begin(), i);
    if(name == set->name){
      return set;
    }
  }

  //Create the set
  dat::base::Set* set = new dat::base::Set(node_k4n);
  set->name = name;
  set->is_lockable = true;

  k4n_config->make_master_configuration_initial(set);
  dat_set->add_subset(set_scene, set);
  k4n_struct->list_master.push_back(set);*/

  //---------------------------
}

}
