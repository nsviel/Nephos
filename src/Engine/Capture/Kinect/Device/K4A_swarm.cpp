#include "K4A_swarm.h"

#include <Engine/Engine.h>


//Constructor / Destructor
K4A_swarm::K4A_swarm(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->str_swarm = new eng::kinect::structure::Swarm();

  //---------------------------
}
K4A_swarm::~K4A_swarm(){}

//Main function
K4A_device* K4A_swarm::create_playback(string path){
  //---------------------------

  K4A_device* k4a_device = new K4A_device(engine);
  k4a_device->device.index = ID_virtual++;
  k4a_device->device.is_virtual = true;
  k4a_device->player.is_playback = true;
  str_swarm->list_device.push_back(k4a_device);
  str_swarm->nb_playback++;
  k4a_device->init();
  eng::kinect::configuration::find_file_information(k4a_device, path);

  //---------------------------
  return k4a_device;
}
K4A_device* K4A_swarm::create_device(int index){
  //---------------------------

  k4a::device device = k4a::device::open(index);
  K4A_device* k4a_device = new K4A_device(engine);
  k4a_device->device.index = index;
  k4a_device->device.is_virtual = false;
  k4a_device->player.is_playback = false;
  k4a_device->device.serial_number = device.get_serialnum();
  k4a_device->init();
  str_swarm->list_device.push_back(k4a_device);
  str_swarm->nb_device++;

  //---------------------------
  return k4a_device;
}
void K4A_swarm::delete_device(K4A_device* device){
  list<K4A_device*>& list_device = str_swarm->list_device;
  //---------------------------

  device->stop_threads();

  for(int i=0; i<list_device.size(); i++){
    K4A_device* device_current = *std::next(list_device.begin(), i);
    if(device_current->device.serial_number == device->device.serial_number){
      list_device.remove(device);
    }
  }

  device->device.is_virtual ? str_swarm->nb_playback-- : str_swarm->nb_device--;
  delete(device);

  //---------------------------
}
void K4A_swarm::refresh_connected_device_list(){
  list<K4A_device*>& list_device = str_swarm->list_device;
  //---------------------------

//REFAIRE CETTE FUNCTION POUR regarder si
//si changement -> si 0 real device, creer un virtual device
//si changement -> si virtual device, supprimer celui-ci et créer un réle device
//si changement -> si n-1 device supprimer real device
//si changement -> si 0 device supprimer real device et créer un nouveau virtual device

  const uint32_t nb_device = k4a_device_get_installed_count();

  if(nb_device != nb_connected_device){
    //If no real device create virtual one
    if(nb_device == 0){
      string path = "/home/aether/Desktop/output.mkv";
      K4A_device* device = create_playback(path);
      str_swarm->selected_device = device;
      device->run_replay(path);
    }
    //Else keep trace of them and run
    else{
      //Fill connected device list
      str_swarm->list_device.clear();
      for(int i=0; i<nb_device; i++){
        try{
          this->create_device(i);
        }
        catch(const int error){
          cout<<"[error] refresh device vector"<<endl;
          continue;
        }
      }

      //Default selection
      str_swarm->selected_device = *std::next(list_device.begin(), 0);

      //Run all thread
      for(int i=0; i<list_device.size(); i++){
        K4A_device* device = *std::next(list_device.begin(), i);

        if(!device->device.is_virtual){
          device->run_capture();
        }
      }
    }

    this->nb_connected_device = nb_device;
  }

  //---------------------------
}
void K4A_swarm::draw_all_clouds(){
  list<K4A_device*>& list_device = str_swarm->list_device;
  //---------------------------

  //Run all thread
  for(int i=0; i<list_device.size(); i++){
    K4A_device* device = *std::next(list_device.begin(), i);
    device->draw_cloud();
  }

  //---------------------------
}
