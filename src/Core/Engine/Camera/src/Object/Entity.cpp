#include "Entity.h"

#include <Engine/Camera/Namespace.h>
#include <Data/Namespace.h>


namespace cam{

//Constructor / Destructor
Entity::Entity(){
  //---------------------------

  this->reset();
  this->list_glyph.push_back(std::make_shared<cam::glyph::Target>());

  //---------------------------
}
Entity::~Entity(){}

//Main function
void Entity::update_pose(){
  //----------------------------
/*
  for(auto& glyph : list_glyph){
    std::shared_ptr<dat::base::Entity> entity = std::static_pointer_cast<dat::base::Entity>(this);
    glyph->update_pose(entity);
  }
*/
  //----------------------------
}
void Entity::reset(){
  //---------------------------

  /*
  this->angle_azimuth = M_PI/4;
  this->angle_elevation = -M_PI/6;
  this->fov = 65;
  this->velocity = 3;
  this->zoom = -4.5;
  this->clip_far = 1000.0;
  this->clip_near = 0.01;

  this->player_mouse_sensibility = glm::vec2(0.003, 0.003);
  this->arcball_mouse_sensibility = glm::vec2(0.3, 0.2);

  this->cam_forward = glm::vec3(0.0f);
  this->cam_right = glm::normalize(glm::vec3(cos(angle_azimuth - M_PI/2.0f), sin(angle_azimuth - M_PI/2.0f), 0));
  this->cam_up = glm::vec3(0.0f);
  this->cam_pose = glm::vec3(-2, -2, 2);
  this->cam_COM = glm::vec3(0.0f, 0.0f, 1.0f);
  */

  this->angle_azimuth = 0;
  this->angle_elevation = 0;
  this->fov = 65;
  this->velocity = 3;
  this->zoom = 0;
  this->clip_far = 1000.0;
  this->clip_near = 0.01;

  this->player_mouse_sensibility = glm::vec2(0.003, 0.003);
  this->arcball_mouse_sensibility = glm::vec2(0.3, 0.2);

  this->cam_forward = glm::vec3(1, 0, 0);
  this->cam_right = glm::vec3(0, -1, 0);
  this->cam_up = glm::vec3(0, 0, 1);
  this->cam_pose = glm::vec3(-2, 0, 0);
  this->cam_COM = glm::vec3(0.0f, 0.0f, 0.0f);

  //---------------------------
}

}
