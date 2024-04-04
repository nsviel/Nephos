#include "Playback.h"

#include <Velodyne/Namespace.h>


namespace vld::thread{

//Constructor / Destructor
Playback::Playback(vld::structure::Main* vld_struct){
  //---------------------------

  this->vld_struct = vld_struct;
  this->vld_player = new vld::Player(vld_struct);

  //---------------------------
}
Playback::~Playback(){}

//Main function
void Playback::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Playback::run_thread, this);
  }

  //---------------------------
  this->thread_idle = false;
}
void Playback::run_thread(){
  //---------------------------

  //Playback thread
  while(thread_running){
    vld_player->forward_index(vld_struct->player.idx_cur + 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(33));
  }

  //---------------------------
  this->thread_idle = true;
}
void Playback::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}


}
