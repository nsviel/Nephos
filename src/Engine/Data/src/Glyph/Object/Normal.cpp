#include "Normal.h"

#include <Scene/Namespace.h>
#include <Data/Namespace.h>
#include <Camera/Namespace.h>


namespace dat::glyph::object{

//Constructor / destructor
Normal::Normal(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "object::normal";
  this->width = 2;
  this->size = 1;
  this->is_visible = false;
  this->color = vec4(0.11f, 0.35f, 0.69f, 1.0f);
  this->need_update = true;
  this->type = dat::object::glyph::NORMAL;

  //---------------------------
}
Normal::~Normal(){}

//Main function
void Normal::create(){
  //---------------------------

  //Create glyph
  data.name = "object::normal::data";
  data.width = width;
  data.is_visible = is_visible;
  data.nb_data_max = 1000000;
  data.topology.type = utl::topology::LINE;
  data.unicolor = vec4(0, 0.7, 0.7, 1);

  this->init();

  //---------------------------
}
void Normal::update_pose(dat::base::Entity* entity){
  //---------------------------

  utl::type::Pose* entity_pose = entity->get_pose();
  pose.model = entity_pose->model;

  cam::Control* cam_control = node_camera->get_control();
  cam_control->compute_camera_mvp(&pose);

  //---------------------------
}
void Normal::update_glyph(dat::base::Entity* entity){
  //---------------------------

  this->construct(entity);

  //---------------------------
}

//Subfunction
void Normal::construct(dat::base::Entity* entity){
  //---------------------------

  //Data glyph
  vector<vec3> xyz_g;
  vector<vec4> rgb_g;

  xyz_g.reserve(data.xyz.size());
  rgb_g.reserve(data.rgb.size());

  //Data entity
  utl::type::Pose* pose_entity = entity->get_pose();
  utl::type::Data* data_entity = entity->get_data();
  vector<vec3>& xyz_e = data_entity->xyz;
  vector<vec3>& Nxyz_e = data_entity->Nxyz;

  //Check vector length
  if(xyz_e.size() == 0 || Nxyz_e.size() == 0 || Nxyz_e.size() != xyz_e.size()) return;

  //Construct glyph
  float lgt = 0.05 * size;
  for(int i=0; i<xyz_e.size(); i++){
    vec3& xyz = xyz_e[i];
    vec3& nxyz = Nxyz_e[i];

    if(nxyz == vec3(0, 0, 0)) continue;

    vec3 xyz_n = vec3(xyz.x + nxyz.x * lgt, xyz.y + nxyz.y * lgt, xyz.z + nxyz.z * lgt);
    vec4 nxyz_h = vec4(nxyz.x,  nxyz.y,  nxyz.z, 1) * pose_entity->rotat;
    vec4 rgb_n = vec4(abs(nxyz_h.x),  abs(nxyz_h.y), abs(nxyz_h.z), 1);

    xyz_g.push_back(xyz);
    xyz_g.push_back(xyz_n);

    rgb_g.push_back(rgb_n);
    rgb_g.push_back(rgb_n);
  }

  data.xyz = xyz_g;
  data.rgb = rgb_g;

  //---------------------------
}
glm::vec4 Normal::generate_random(){
  //---------------------------

  float Red = float(rand()%101)/100;
  float Green = float(rand()%101)/100;
  float Blue = float(rand()%101)/100;
  glm::vec4 color = glm::vec4(Red, Green, Blue, 1.0f);

  //---------------------------
  return color;
}

}
