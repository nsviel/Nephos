#include "Entity.h"


namespace cam{

//Constructor / Destructor
Entity::Entity(){
  //---------------------------

  this->reset_entity();
  this->entity_type = "cam::Entity";

  //---------------------------
}
Entity::~Entity(){}

//Main function
void Entity::update_pose(){
  //----------------------------

  for(int i=0; i<list_glyph.size(); i++){
    utl::entity::Glyph* glyph = *next(list_glyph.begin(), i);
    glyph->update_pose(this);
  }

  //----------------------------
}
void Entity::reset_entity(){
  //---------------------------

  this->angle_azimuth = M_PI/4;
  this->angle_elevation = -M_PI/6;
  this->fov = 65;
  this->velocity = 3;
  this->clip_far = 1000.0;
  this->clip_near = 0.01;

  this->player_mouse_sensibility = glm::vec2(0.003, 0.003);
  this->arcball_mouse_sensibility = glm::vec2(0.3, 0.2);

  this->cam_F = glm::vec3(0.0f);
  this->cam_R = glm::normalize(glm::vec3(cos(angle_azimuth - M_PI/2.0f), sin(angle_azimuth - M_PI/2.0f), 0));
  this->cam_U = glm::vec3(0.0f);
  this->cam_P = glm::vec3(-2, -2, 2);
  this->cam_COM = glm::vec3(0.0f, 0.0f, 1.0f);

  this->projection = CAMERA_PROJ_PERSPECTIVE;
  this->mode = CAMERA_MODE_ARCBALL;

  //---------------------------
}

}
