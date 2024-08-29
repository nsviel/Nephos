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

  this->node_k4n = node_k4n;
  this->k4n_utils = new k4n::Utils(node_k4n);
  this->io_operation = node_importer->get_io_operation();

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

  //Create sensor
  std::shared_ptr<k4n::capture::Sensor> sensor = std::make_shared<k4n::capture::Sensor>(node_k4n, index);

  //Insert sensor into data tree
  k4n_utils->insert_in_kinect_set(*sensor);

  //Apply imported stuff 
  io_operation->ope_insertion(sensor);

  //Start sensor
  sensor->start();

  //---------------------------
}

}
