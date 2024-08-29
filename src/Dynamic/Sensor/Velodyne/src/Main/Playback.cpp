#include "Playback.h"

#include <Velodyne/Namespace.h>


namespace vld::main{

//Constructor / Destructor
Playback::Playback(vld::Node* node_velodyne){
  //---------------------------

  this->vld_struct = node_velodyne->get_vld_struct();
  this->thread_playback = new vld::thread::Playback(node_velodyne);

  //---------------------------
}
Playback::~Playback(){}

//Main function
void Playback::start_playback(){
  if(vld_struct->data.current_set == nullptr) return;
  std::shared_ptr<dat::base::Set> set = vld_struct->data.current_set;
  //---------------------------

  thread_playback->start_thread();

  //---------------------------
}
void Playback::stop_playback(){
  //---------------------------

  thread_playback->stop_thread();

  //---------------------------
}

}
