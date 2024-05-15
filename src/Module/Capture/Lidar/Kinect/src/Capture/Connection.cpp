#include "Connection.h"

#include <Utility/Namespace.h>
#include <Kinect/Namespace.h>
#include <chrono>


namespace k4n::capture{

//Constructor / Destructor
Connection::Connection(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();

  this->dat_set = node_data->get_data_set();
  this->dat_graph = node_data->get_data_graph();

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
    this->current_nb_dev = k4a_device_get_installed_count();

    //Action on changement
    if(current_nb_dev != nb_dev_old){
      this->manage_connected_device();
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
void Connection::create_sensor(int index){
  //---------------------------
/*
  //Associated master
  this->close_master("Kinect");
  k4n::dev::Master* master = get_or_create_capture_master("Capture");

  //Sensor creation
  k4n::dev::Sensor* sensor = new k4n::dev::Sensor(node_k4n);
  sensor->name = "capture_" + to_string(index);
  sensor->device.idx_dev = index;
  sensor->master = master;

  //Sensor initialization
  sensor->init();
  dat_set->insert_entity(master, sensor);
  dat_graph->assign_UID(sensor);
  utl::transformation::apply_transformation_capture(sensor->get_pose()->model);
  sensor->run_thread();

*/
  //---------------------------
}
void Connection::manage_connected_device(){
  //---------------------------
/*
  //Suppress all devices
  k4n::dev::Master* master = get_or_create_capture_master("capture");
  if(master == nullptr) return;
  dat_set->remove_all_entity(master);

  //Create required number of new devices
  for(int i=0; i<current_nb_dev; i++){
    this->create_sensor(i);
  }

  //---------------------------
*/
}
void Connection::manage_master(){
/*  dat::base::Set* set_scene = dat_graph->get_set_graph();
  //---------------------------

  //Check if already existing
  for(int i=0; i<k4n_struct->list_sensor.size(); i++){
    k4n::dev::Master* master = *std::next(k4n_struct->list_master.begin(), i);
    if(name == master->name){
      return master;
    }
  }

  //Create the master
  k4n::dev::Master* master = new k4n::dev::Master(node_k4n);
  master->name = name;
  master->is_lockable = true;

  k4n_config->make_master_configuration_initial(master);
  dat_set->add_subset(set_scene, master);
  k4n_struct->list_master.push_back(master);*/

  //---------------------------
}

}
