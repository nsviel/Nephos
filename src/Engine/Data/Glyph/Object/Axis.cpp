#include "Axis.h"


namespace glyph::object{

//Constructor / destructor
Axis::Axis(){
  //---------------------------

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

  //---------------------------
}
void Axis::update(eng::structure::Cloud* cloud){
  vector<vec3>& XYZ = cloud->axis.xyz;
  vec3 subset_root = cloud->axis.root;
  //---------------------------

  cloud->axis.is_visible = true;
  XYZ.clear();

  //Axis rotation
  mat4 R = cloud->rotat;
  vec4 Rx = vec4(0.1,0,0,1) * R;
  vec4 Ry = vec4(0,0.1,0,1) * R;
  vec4 Rz = vec4(0,0,0.1,1) * R;

  //X Axis
  vec3 subsey_x = vec3(subset_root.x + Rx.x, subset_root.y + Rx.y, subset_root.z + Rx.z);
  XYZ.push_back(subset_root);
  XYZ.push_back(subsey_x);

  //Y Axis
  vec3 subsey_y = vec3(subset_root.x + Ry.x, subset_root.y + Ry.y, subset_root.z + Ry.z);
  XYZ.push_back(subset_root);
  XYZ.push_back(subsey_y);

  //Z Axis
  vec3 subsey_z = vec3(subset_root.x + Rz.x, subset_root.y + Rz.y, subset_root.z + Rz.z);
  XYZ.push_back(subset_root);
  XYZ.push_back(subsey_z);

  //---------------------------
}

}
