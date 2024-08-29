#include "Connection.h"

#include <Utility/Namespace.h>
#include <Kinect/Namespace.h>
#include <IO/Namespace.h>
#include <Importer/Namespace.h>
#include <Data/Namespace.h>
#include <chrono>


namespace k4n::capture{

//Constructor / Destructor
Connection::Connection(k4n::Node* node_k4n){
  //---------------------------

  io::Node* node_io = node_k4n->get_node_io();
  io::imp::Node* node_importer = node_io->get_node_importer();
  dat::Node* node_data = node_k4n->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->node_k4n = node_k4n;
  this->io_operation = node_importer->get_io_operation();
  this->dat_set = node_element->get_dat_set();
  this->dat_graph = node_graph->get_gph_graph();

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

  //Suppress all present entities if enable
  io_operation->ope_clean();

  //Create required number of new devices
  for(int i=0; i<current_nb_dev; i++){
    this->create_sensor(i);
  }

  //---------------------------
  this->flag = false;
}
void Connection::create_sensor(int index){
  //---------------------------

  auto sensor = std::make_shared<k4n::capture::Sensor>(node_k4n, index);
  this->manage_set_parent(*sensor);
  io_operation->ope_insertion(sensor);
  sensor->start();

  //---------------------------
}
void Connection::manage_set_parent(k4n::capture::Sensor& sensor){
  //---------------------------

  //Get kinect set
  std::shared_ptr<dat::base::Set> set_graph = dat_graph->get_set_graph();
  std::shared_ptr<dat::base::Set> set = dat_set->get_subset(set_graph, "kinect");

  //If it doesn't exists, create it
  if(!set){
    set = std::make_shared<dat::base::Set>();
    set->name = "kinect";
    set->icon = ICON_FA_USER;
    set->is_locked = false;
    set->is_suppressible = true;
    dat_set->add_subset(set_graph, set);
  }

  //Assign to sensor
  sensor.set_parent = set;

  //---------------------------
}

}
