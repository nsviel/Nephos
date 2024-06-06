#include "Connection.h"

#include <Utility/Namespace.h>
#include <Kinect/Namespace.h>
#include <Loader/Namespace.h>
#include <Data/Namespace.h>
#include <chrono>


namespace k4n::capture{

//Constructor / Destructor
Connection::Connection(k4n::Node* node_k4n){
  //---------------------------

  ldr::Node* node_loader = node_k4n->get_node_loader();
  dat::Node* node_data = node_k4n->get_node_data();

  this->node_k4n = node_k4n;
  this->ldr_operation = node_loader->get_ldr_operation();
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
  //---------------------------

  //Suppress all present entities
  ldr_operation->ope_clean();

  //Create required number of new devices
  for(int i=0; i<current_nb_dev; i++){
    this->create_sensor(i);
  }

  //---------------------------
  this->flag = false;
}
void Connection::create_sensor(int index){
  //---------------------------

  //Sensor creation
  k4n::capture::Sensor* sensor = new k4n::capture::Sensor(node_k4n, index);
  sensor->name = "capture_" + to_string(index);
  sensor->data.name = sensor->name;
  sensor->pose.model[2][3] = 1;

  //Sensor initialization
  dat::base::Set* set = manage_set_parent();
  sensor->set_parent = set;
  sensor->vec_recorder.push_back(new k4n::capture::Recorder());
  ldr_operation->ope_insertion(sensor);
  sensor->start_thread();

  //---------------------------
}
dat::base::Set* Connection::manage_set_parent(){
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
