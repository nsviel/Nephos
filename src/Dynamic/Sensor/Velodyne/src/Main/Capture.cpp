#include "Capture.h"

#include <Velodyne/Namespace.h>


namespace vld::main{

//Constructor / Destructor
Capture::Capture(vld::Node* node_velodyne){
  //---------------------------

  this->vld_struct = node_velodyne->get_vld_struct();
  this->thread_server = new vld::thread::Server(node_velodyne);

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::init(){
  //---------------------------

  thread_server->start_thread();

  //---------------------------
}
void Capture::clean(){
  //---------------------------

  thread_server->stop_thread();

  //---------------------------
}

}
