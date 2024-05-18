#include "Pather.h"

#include <Camera/Namespace.h>
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

  glm::vec3 startPosition(0.0f, 0.0f, 0.0f);
  glm::vec3 endPosition(10.0f, 0.0f, 0.0f);
  glm::vec3 position;

  auto startTime = std::chrono::steady_clock::now();
  float duration = 5.0f; // Duration for one full cycle back and forth

  //Start loop

  auto currentTime = std::chrono::steady_clock::now();
  float elapsed = std::chrono::duration<float>(currentTime - startTime).count();

  // Calculate normalized time value (t) for a full back and forth cycle
  float cycleTime = fmod(elapsed, duration * 2);
  float t = cycleTime / duration;
  if (cycleTime > duration) {
      t = 2.0f - t; // Reverse the direction
  }

  // Update camera position
  position = update_position(startPosition, endPosition, t);

  //---------------------------
}
void Pather::make_path(){
  cam::Entity* camera = cam_struct->cam_current;
  //---------------------------

  static float amplitude = 1.0f; // Maximum value
  static float frequency = 0.2f; // Number of cycles per second
  static float phase = 0.0f; // Phase shift

  static auto startTime = std::chrono::steady_clock::now();
/*
  //Start loop

  auto currentTime = std::chrono::steady_clock::now();
  float elapsed = std::chrono::duration<float>(currentTime - startTime).count();

  // Calculate normalized time value (t) for a full back and forth cycle
  float cycleTime = fmod(elapsed, duration * 2);
  float t = cycleTime / duration;
  if (cycleTime > duration) {
      t = 2.0f - t; // Reverse the direction
  }

  // Update camera position
  position = update_position(startPosition, endPosition, t);

  control_wheel(float value)
*/
  //---------------------------
}

//Subfunction
glm::vec3 Pather::update_position(const glm::vec3& start, const glm::vec3& end, float t){
  //---------------------------

  float interpolation = (1.0f - std::cos(M_PI * t)) / 2.0f;
  glm::vec3 position = start + interpolation * (end - start);

  //---------------------------
  return position;
}

}
