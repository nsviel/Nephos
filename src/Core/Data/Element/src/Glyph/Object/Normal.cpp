#include "Normal.h"

#include <Data/Base/Namespace.h>


namespace dat::glyph::object{

//Constructor / destructor
Normal::Normal(){
  //---------------------------

  this->name = "object::normal";
  this->width = 2;
  this->size = 1;
  this->color = glm::vec4(0.11f, 0.35f, 0.69f, 1.0f);
  this->need_update = true;
  this->type = dat::base::object::NORMAL;

  //---------------------------
}
Normal::~Normal(){}

//Main function
void Normal::create(){
  //---------------------------

  //Create glyph
  data.name = "object::normal::data";
  data.width = width;
  data.is_visible = false;
  data.nb_data_max = 1000000;
  data.topology.type = utl::topology::LINE;
  data.unicolor = glm::vec4(0, 0.7, 0.7, 1);

  //---------------------------
}
void Normal::update_pose(dat::base::Entity* entity){
  //---------------------------

  utl::base::Pose* entity_pose = &entity->pose;;
  pose.model = entity_pose->model;

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
  std::vector<glm::vec3> xyz_g;
  std::vector<glm::vec4> rgb_g;

  xyz_g.reserve(data.xyz.size());
  rgb_g.reserve(data.rgba.size());

  //Data entity
  std::vector<glm::vec3>& xyz_e = entity->data.xyz;
  std::vector<glm::vec3>& Nxyz_e = entity->data.Nxyz;

  //Check vector length
  if(xyz_e.size() == 0 || Nxyz_e.size() == 0 || Nxyz_e.size() != xyz_e.size()) return;

  //Construct glyph
  float lgt = 0.05 * size;
  for(int i=0; i<xyz_e.size(); i++){
    glm::vec3& xyz = xyz_e[i];
    glm::vec3& nxyz = Nxyz_e[i];

    if(nxyz == glm::vec3(0, 0, 0)) continue;

    glm::vec3 xyz_n = glm::vec3(xyz.x + nxyz.x * lgt, xyz.y + nxyz.y * lgt, xyz.z + nxyz.z * lgt);
    glm::vec4 nxyz_h = glm::vec4(nxyz.x,  nxyz.y,  nxyz.z, 1) * entity->pose.rotat;
    glm::vec4 rgb_n = glm::vec4(abs(nxyz_h.x),  abs(nxyz_h.y), abs(nxyz_h.z), 1);

    xyz_g.push_back(xyz);
    xyz_g.push_back(xyz_n);

    rgb_g.push_back(rgb_n);
    rgb_g.push_back(rgb_n);
  }

  data.xyz = xyz_g;
  data.rgba = rgb_g;

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
