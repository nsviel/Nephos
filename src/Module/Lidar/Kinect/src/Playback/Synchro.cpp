#include "Synchro.h"

#include <Utility/Namespace.h>
#include <Kinect/Namespace.h>
#include <chrono>


namespace k4n::capture{

//Constructor / Destructor
Synchro::Synchro(k4n::Node* node_k4n){
  //---------------------------

  dat::Node* node_data = node_k4n->get_node_data();

  this->dat_set = node_data->get_data_set();
  this->dat_graph = node_data->get_data_graph();

  //---------------------------
}
Synchro::~Synchro(){
  //---------------------------

  this->stop_thread();
  this->thread.join();

  //---------------------------
}

//Main function
void Synchro::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Synchro::run_thread, this);
  }

  //---------------------------
  this->thread_running = true;
}
void Synchro::run_thread(){
  static int nb_dev_old = 0;
  //---------------------------

  //Refresh connected sensors
  while(thread_running){
    /*
      for(int i=0; i<list_entity.size(); i++){
        dat::base::Entity* entity = *next(list_entity.begin(), i);

        if(k4n::dev::Sensor* sensor = dynamic_cast<k4n::dev::Sensor*>(entity)){
          auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(player->ts_cur));
          sensor->synchro.seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
        }
      }*/

    //Little sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  //---------------------------
}
void Synchro::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//Subfunction

}
