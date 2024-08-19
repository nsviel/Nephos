#include "AABB.h"

#include <Data/Element/Namespace.h>


namespace dat::glyph::object{

AABB::AABB(){
  //---------------------------

  this->name = "object::AABB";
  this->is_permanent = true;
  this->color = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
  this->type = dat::base::object::AABB;

  //---------------------------
}
AABB::~AABB(){}

//Main function
void AABB::create(){
  //---------------------------

  data.name = "object::AABB::data";
  data.width = 1;
  data.is_visible = false;
  data.topology.type = utl::topology::LINE;
  data.unicolor = color;

  for(int i=0; i<24; i++){
    data.rgba.push_back(color);
  }

  //---------------------------
}
void AABB::update_glyph(utl::base::Pose* pose){
  //---------------------------

  glm::vec3 min = pose->min;
  glm::vec3 max = pose->max;
  data.xyz = build_box(min, max);

  //---------------------------
}

//Subfunction
std::vector<glm::vec3> AABB::build_box(glm::vec3 min, glm::vec3 max){
  std::vector<glm::vec3> XYZ;
  glm::vec3 l1, l2;
  //---------------------------

  for(int i=0; i<3; i++){
    l1=min;
    l2=min;
    l2[i]=max[i];
    XYZ.push_back(l1);
    XYZ.push_back(l2);

    l1=max;
    l2=max;
    l2[i]=min[i];
    XYZ.push_back(l1);
    XYZ.push_back(l2);
  }
  for(int i=0; i<2; i++){
    l1=min;
    l1.z=max.z;
    l2=min;
    l2.z=max.z;
    l2[i]=max[i];
    XYZ.push_back(l1);
    XYZ.push_back(l2);

    l1=max;
    l1.z=min.z;
    l2=max;
    l2.z=min.z;
    l2[i]=min[i];
    XYZ.push_back(l1);
    XYZ.push_back(l2);

    l1=min;
    l1[i]=max[i];
    l2=l1;
    l2.z=max.z;
    XYZ.push_back(l1);
    XYZ.push_back(l2);
  }

  //---------------------------
  return XYZ;
}


}
