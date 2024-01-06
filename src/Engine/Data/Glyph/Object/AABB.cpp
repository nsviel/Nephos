#include "AABB.h"


namespace glyph::object{

AABB::AABB(){
  //---------------------------

  this->color = vec4(1.0f, 1.0f, 1.0f, 0.5f);

  //---------------------------
}

//Main function
void AABB::create(){
  //---------------------------

  data = new eng::data::Object();
  data->name = "aabb";
  data->draw_line_width = 1;
  data->is_visible = false;
  data->draw_type_name = "line";
  data->is_permanent = true;
  data->unicolor = color;

  for(int i=0; i<24; i++){
    data->rgb.push_back(color);
  }

  //---------------------------
}
void AABB::update(eng::data::Object* object){
  //---------------------------

  vec3 min = object->min;
  vec3 max = object->max;
  data->xyz = build_box(min, max);

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
