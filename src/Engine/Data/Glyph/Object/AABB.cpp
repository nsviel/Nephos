#include "AABB.h"


namespace glyph::object{

AABB::AABB(){
  //---------------------------

  this->color = vec4(1.0f, 1.0f, 1.0f, 0.5f);

  //---------------------------
}

//Main function
void AABB::create(eng::structure::Object* object){
  //---------------------------

  object->aabb = new eng::structure::Object();
  eng::structure::Object* aabb = object->aabb;

  aabb->name = "aabb";
  aabb->draw_line_width = 1;
  aabb->is_visible = false;
  aabb->draw_type_name = "line";
  aabb->is_permanent = true;
  aabb->unicolor = color;

  for(int i=0; i<24; i++){
    aabb->rgb.push_back(color);
  }

  //---------------------------
}
void AABB::update(eng::structure::Object* object){
  eng::structure::Object* aabb = object->aabb;
  //---------------------------

  vec3 min = object->min;
  vec3 max = object->max;
  aabb->xyz = build_box(min, max);

  //---------------------------
}
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
