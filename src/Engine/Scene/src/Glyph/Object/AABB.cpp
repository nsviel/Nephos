#include "AABB.h"


namespace glyph::object{

AABB::AABB(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "object::AABB";
  this->is_permanent = true;
  this->color = vec4(1.0f, 1.0f, 1.0f, 0.5f);
  this->type = utl::entity::object::AABB;

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
    data.rgb.push_back(color);
  }

  this->init();

  //---------------------------
}
void AABB::update_glyph(utl::type::Pose* pose){
  //---------------------------

  vec3 min = pose->min;
  vec3 max = pose->max;
  data.xyz = build_box(min, max);

  //---------------------------
}

//Subfunction
vector<vec3> AABB::build_box(vec3 min, vec3 max){
  vector<vec3> XYZ;
  vec3 l1, l2;
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
