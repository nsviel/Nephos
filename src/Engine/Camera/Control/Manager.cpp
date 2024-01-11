#include "Manager.h"

#include <Engine/Engine.h>


namespace eng::camera{

//Constructor / Destructor
Manager::Manager(Engine* engine){
  //---------------------------


  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::create_camera(){
  //---------------------------

  eng::data::Camera* camera = new eng::data::Camera();
  this->vec_camera.push_back(camera);
  this->current_camera = camera;

  //---------------------------
}
void Manager::reset(){
  //---------------------------

  for(int i=0; i<vec_camera.size(); i++){
    eng::data::Camera* camera = vec_camera[i];
    camera->reset();
  }

  //---------------------------
}


}
