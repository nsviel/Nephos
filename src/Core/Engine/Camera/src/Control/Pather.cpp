#include "Pather.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include <glm/glm.hpp>


namespace cam{

//Constructor / Destructor
Pather::Pather(cam::Node* node_camera){
  //---------------------------

  this->cam_struct = node_camera->get_cam_struct();
  this->cam_control = node_camera->get_cam_control();

  //---------------------------
}
Pather::~Pather(){}

//Main function
void Pather::init(){
  cam::Entity* camera = cam_struct->cam_current;
  //---------------------------


  //---------------------------
}
void Pather::loop(){
  //---------------------------

  if(cam_struct->path.enable){
    this->make_sin_wheel();
  }

  //---------------------------
}

//Subfunction
void Pather::make_sin_wheel(){
  cam::Entity* camera = cam_struct->cam_current;
  //---------------------------

  float amplitude = cam_struct->path.amplitude;
  float frequency = cam_struct->path.frequency;
  float lambda = cam_struct->path.lambda;

  static auto startTime = std::chrono::steady_clock::now();
  auto currentTime = std::chrono::steady_clock::now();

  float elapsed = std::chrono::duration<float>(currentTime - startTime).count();
  float value = amplitude * std::sin(2.0f * M_PI * frequency * elapsed);

  cam_control->control_wheel(value / 1000 * lambda);

  //---------------------------
}
float Pather::update_position(const float& start, const float& end, float t){
  //---------------------------

  float interpolation = (1.0f - std::cos(M_PI * t)) / 2.0f;
  float position = start + interpolation * (end - start);

  //---------------------------
  return position;
}

}
