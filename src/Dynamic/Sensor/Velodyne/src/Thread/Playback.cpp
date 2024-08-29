#include "Playback.h"

#include <Velodyne/Namespace.h>


namespace vld::thread{

//Constructor / Destructor
Playback::Playback(vld::Structure* vld_struct){
  //---------------------------

  this->vld_struct = vld_struct;
  this->vld_player = new vld::processing::Player(vld_struct);

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
  this->thread_running = true;
  //---------------------------

  //Playback thread
  while(thread_running){
    vld_player->forward_index(vld_struct->player.idx_cur + 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(60));

    this->manage_pause();
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

//Subfunction
void Playback::manage_pause(){
  //---------------------------

  //If pause, wait until end pause or end thread
  bool& is_paused = vld_struct->player.pause;
  if(is_paused || !vld_struct->player.play){
    //Pause loop
    this->thread_paused = true;
    while(is_paused && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    this->thread_paused = false;
  }

  //---------------------------
}

}
