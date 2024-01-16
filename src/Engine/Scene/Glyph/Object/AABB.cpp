#include "AABB.h"


namespace glyph::object{

AABB::AABB(Engine* engine) : Glyph(engine){
  //---------------------------

  this->is_permanent = true;
  this->color = vec4(1.0f, 1.0f, 1.0f, 0.5f);

  //---------------------------
}
AABB::~AABB(){}

//Main function
void AABB::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  entity::Object* object = new entity::Object(engine);
  object->data->draw_line_width = 1;
  object->data->is_visible = false;
  object->data->draw_type_name = "line";
  object->data->unicolor = color;

  for(int i=0; i<24; i++){
    object->data->rgb.push_back(color);
  }

  this->vec_data.push_back(object);

  //---------------------------
}
void AABB::update_glyph(entity::Entity* entity){
  //---------------------------

  if(entity::Object* object = dynamic_cast<entity::Object*>(entity)){
    vec3 min = object->data->min;
    vec3 max = object->data->max;
    vec_data[0]->data->xyz = build_box(min, max);
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
