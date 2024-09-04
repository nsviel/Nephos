#include "Target.h"

#include <Engine/Camera/Namespace.h>


namespace cam::glyph{

//Constructor / destructor
Target::Target(){
  //---------------------------

  this->name = "cam::target";
  this->is_permanent = true;
  this->color = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
  this->scale = 0.025;

  //---------------------------
}
Target::~Target(){}

//Main function
void Target::create(){
  //---------------------------

  data->name = "cam::target::data";
  data->width = 2;
  data->is_visible = true;
  data->topology.type = utl::topology::LINE;
  data->unicolor = glm::vec4(1, 1, 1, 0.2f);

  this->construct();

  //---------------------------
}
void Target::update_pose(std::shared_ptr<dat::base::Entity> entity){
  //---------------------------

  if(std::shared_ptr<cam::Entity> camera = std::dynamic_pointer_cast<cam::Entity>(entity)){
    if(camera->mode != CAMERA_MODE_ARCBALL && data->is_visible) data->is_visible = false;

    glm::mat4 translation(1.0);
    translation[0][3] = camera->cam_COM.x;
    translation[1][3] = camera->cam_COM.y;
    translation[2][3] = camera->cam_COM.z;
    pose->model = translation;
  }

  //---------------------------
}

//Subfunction
void Target::construct(){
  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec4>& rgba = data->rgba;
  //---------------------------

  xyz.clear();
  rgba.clear();

  //X axis
  xyz.push_back(glm::vec3(-1*scale, 0, 0));
  xyz.push_back(glm::vec3(1*scale, 0, 0));
  rgba.push_back(color);
  rgba.push_back(color);

  //Y axis
  xyz.push_back(glm::vec3(0, -1*scale, 0));
  xyz.push_back(glm::vec3(0, 1*scale, 0));
  rgba.push_back(color);
  rgba.push_back(color);

  //---------------------------
}

}
