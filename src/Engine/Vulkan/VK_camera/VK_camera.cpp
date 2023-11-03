#include "VK_camera.h"

#include "../VK_engine.h"

#include <Camera/Camera.h>
#include <Engine.h>


//Constructor / Destructor
VK_camera::VK_camera(VK_engine* vk_engine){
  //---------------------------

  Engine* engine = vk_engine->get_engine();

  this->cameraManager = engine->get_cameraManager();

  //---------------------------
}
VK_camera::~VK_camera(){}

//Main function
void VK_camera::compute_mvp(Object* object){
  //---------------------------

  mat4 view = cameraManager->compute_cam_view();
  mat4 proj = cameraManager->compute_cam_proj();
  mat4 model = glm::transpose(object->model);

  object->mvp = proj * view * model;

  //---------------------------
}
