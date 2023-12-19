#include "Axis.h"


namespace glyph::object{

//Constructor / destructor
Axis::Axis(){
  //---------------------------

  this->is_visible = true;
  this->eng_transform = new eng::ope::Transformation();

  //---------------------------
}
Axis::~Axis(){}

void Axis::create(eng::structure::Cloud* cloud){
  //---------------------------

  //Create glyph
  cloud->axis.name = "axis";
  cloud->axis.draw_line_width = 3;
  cloud->axis.is_visible = is_visible;
  cloud->axis.draw_type_name = "line";

  //Axis colors
  vector<vec4>& RGB = cloud->axis.rgb;
  RGB.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));

  vector<vec3>& XYZ = cloud->axis.xyz;
  vec3 root = vec3(0, 0, 0);
  vec3 x = vec3(0.1,0,0);
  vec3 y = vec3(0,0.1,0);
  vec3 z = vec3(0,0,0.1);
  XYZ.push_back(root);
  XYZ.push_back(x);
  XYZ.push_back(root);
  XYZ.push_back(y);
  XYZ.push_back(root);
  XYZ.push_back(z);

  //---------------------------
}
void Axis::update(eng::structure::Cloud* cloud){
  //---------------------------

  eng_transform->make_translation(&cloud->axis, cloud->trans);
  eng_transform->make_rotation(&cloud->axis, cloud->rotat);

  //---------------------------
}

}
