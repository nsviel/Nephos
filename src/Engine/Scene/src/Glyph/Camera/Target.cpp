#include "Target.h"

#include <Engine/Camera/Namespace.h>


namespace glyph::camera{

//Constructor / destructor
Target::Target(eng::Node* engine) : Glyph(engine){
  //---------------------------

  this->is_permanent = true;
  this->color = vec4(1.0f, 1.0f, 1.0f, 0.5f);
  this->scale = 0.025;

  //---------------------------
}
Target::~Target(){}

//Main function
void Target::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  utl::type::Data* data = new utl::type::Data();
  data->line.width = 2;
  data->is_visible = true;
  data->draw_type = utl::topology::LINE;
  data->unicolor = vec4(1, 1, 1, 0.2f);
  this->vec_data.push_back(data);
  this->construct(data);

  //---------------------------
}
void Target::update_pose(utl::type::Entity* entity){
  utl::type::Data* data = vec_data[0];
  //---------------------------

  if(utl::entity::Camera* camera = dynamic_cast<utl::entity::Camera*>(entity)){
    camera->mode == CAMERA_MODE_ARCBALL ? is_visible = true : is_visible = false;

    glm::mat4 translation(1.0);
    translation[0][3] = camera->cam_COM.x;
    translation[1][3] = camera->cam_COM.y;
    translation[2][3] = camera->cam_COM.z;
    pose->model = translation;
    data->is_visible = is_visible;

    eng::cam::Control* cam_control = node_camera->get_camera_control();
    cam_control->compute_camera_mvp(pose);
  }

  //---------------------------
}
void Target::construct(utl::type::Data* data){
  vector<vec3>& XYZ = data->line.xyz;
  vector<vec4>& RGB = data->line.rgb;
  //---------------------------

  XYZ.clear();
  RGB.clear();

  //X axis
  XYZ.push_back(vec3(-1*scale, 0, 0));
  XYZ.push_back(vec3(1*scale, 0, 0));
  RGB.push_back(color);
  RGB.push_back(color);

  //Y axis
  XYZ.push_back(vec3(0, -1*scale, 0));
  XYZ.push_back(vec3(0, 1*scale, 0));
  RGB.push_back(color);
  RGB.push_back(color);

  //---------------------------
}

}
