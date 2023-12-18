#include "AABB.h"


namespace glyph::object{

AABB::AABB(){
  //---------------------------

  this->name = "aabb";
  this->color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
  this->width = 1;

  //---------------------------
}

//Main function
void AABB::create(eng::structure::Cloud* cloud){
  //---------------------------

  cloud->aabb.name = "aabb";
  cloud->aabb.draw_line_width = width;
  cloud->aabb.is_visible = true;
  cloud->aabb.draw_type_name = "line";
  cloud->aabb.is_permanent = true;
  cloud->aabb.unicolor = color;

  for(int i=0; i<24; i++){
    cloud->aabb.rgb.push_back(color);
  }

  //---------------------------
}
void AABB::update(eng::structure::Cloud* cloud){
  //---------------------------

  vec3 min = cloud->min;
  vec3 max = cloud->max;
  cloud->aabb.xyz = build_box(min, max);

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
