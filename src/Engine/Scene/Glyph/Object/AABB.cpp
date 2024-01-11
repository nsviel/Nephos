#include "AABB.h"


namespace glyph::object{

AABB::AABB(){
  //---------------------------

  this->color = vec4(1.0f, 1.0f, 1.0f, 0.5f);

  //---------------------------
}
AABB::~AABB(){}

//Main function
void AABB::create(){
  if(vec_object.size() != 0) return;
  //---------------------------

  eng::data::Object* object = new eng::data::Object();
  object->name = "aabb";
  object->draw_line_width = 1;
  object->is_visible = false;
  object->draw_type_name = "line";
  object->is_permanent = true;
  object->unicolor = color;

  for(int i=0; i<24; i++){
    object->rgb.push_back(color);
  }

  this->vec_object.push_back(object);

  //---------------------------
}
void AABB::update(eng::data::Entity* entity){
  //---------------------------

  if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
    vec3 min = object->min;
    vec3 max = object->max;
    vec_object[0]->xyz = build_box(min, max);
  }

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
