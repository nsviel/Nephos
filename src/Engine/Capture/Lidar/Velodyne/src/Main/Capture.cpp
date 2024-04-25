#include "Capture.h"

#include <Velodyne/Namespace.h>
#include <Scene/Namespace.h>


namespace vld::main{

//Constructor / Destructor
Capture::Capture(vld::Node* node_vld){
  //---------------------------

  this->vld_struct = node_vld->get_vld_struct();
  this->thread_server = new vld::thread::Server(node_vld);
  this->thread_screenshot = new vld::thread::Screenshot(node_vld);

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
