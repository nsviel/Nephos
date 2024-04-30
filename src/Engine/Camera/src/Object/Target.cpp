#include "Target.h"

#include <Camera/Namespace.h>


namespace cam::glyph{

//Constructor / destructor
Target::Target(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "cam::target";
  this->is_permanent = true;
  this->color = vec4(1.0f, 1.0f, 1.0f, 0.5f);
  this->scale = 0.025;

  //---------------------------
}
Target::~Target(){}

//Main function
void Target::create(){
  //---------------------------

  data.name = "cam::target::data";
  data.width = 2;
  data.is_visible = true;
  data.topology.type = utl::topology::LINE;
  data.unicolor = vec4(1, 1, 1, 0.2f);

  this->construct();
  this->init();

  //---------------------------
}
void Target::update_pose(dat::base::Entity* entity){
  //---------------------------

  if(cam::Entity* camera = dynamic_cast<cam::Entity*>(entity)){
    camera->mode == CAMERA_MODE_ARCBALL ? is_visible = true : is_visible = false;

    glm::mat4 translation(1.0);
    translation[0][3] = camera->cam_COM.x;
    translation[1][3] = camera->cam_COM.y;
    translation[2][3] = camera->cam_COM.z;
    pose.model = translation;
    data.is_visible = is_visible;

    cam::Control* cam_control = node_camera->get_control();
    cam_control->compute_camera_mvp(&pose);
  }

  //---------------------------
}

//Subfunction
void Target::construct(){
  vector<vec3>& xyz = data.xyz;
  vector<vec4>& rgb = data.rgb;
  //---------------------------

  xyz.clear();
  rgb.clear();

  //X axis
  xyz.push_back(vec3(-1*scale, 0, 0));
  xyz.push_back(vec3(1*scale, 0, 0));
  rgb.push_back(color);
  rgb.push_back(color);

  //Y axis
  xyz.push_back(vec3(0, -1*scale, 0));
  xyz.push_back(vec3(0, 1*scale, 0));
  rgb.push_back(color);
  rgb.push_back(color);

  //---------------------------
}

}
