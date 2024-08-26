#include "Playback.h"

#include <Velodyne/Namespace.h>


namespace vld::main{

//Constructor / Destructor
Playback::Playback(vld::structure::Main* vld_struct){
  //---------------------------

  this->vld_struct = vld_struct;
  this->thread_playback = new vld::thread::Playback(vld_struct);

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
