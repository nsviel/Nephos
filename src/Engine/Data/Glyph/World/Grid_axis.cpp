#include "Grid_axis.h"


namespace glyph::world{

//Constructor / destructor
Grid_axis::Grid_axis(){
  //---------------------------

  this->color = vec4(1, 1, 1, 0.5);
  this->nb_cell = 40;

  //---------------------------
}
Grid_axis::~Grid_axis(){
  //---------------------------

  delete glyph;

  //---------------------------
}

eng::structure::Glyph* Grid_axis::create(){
  //---------------------------

  this->glyph = new eng::structure::Glyph();
  glyph->draw_line_width = 5;
  glyph->is_visible = true;
  glyph->draw_type_name = "line";
  glyph->is_permanent = true;
  glyph->unicolor = color;
  this->update();

  //---------------------------
  return glyph;
}
void Grid_axis::update(){
  vector<vec3>& XYZ = glyph->xyz;
  vector<vec4>& RGB = glyph->rgb;
  //---------------------------

  //Parameters
  XYZ.clear();
  RGB.clear();

  //X axis
  XYZ.push_back(vec3(-nb_cell, 0, 0));
  XYZ.push_back(vec3(nb_cell, 0, 0));
  RGB.push_back(color);
  RGB.push_back(color);

  //Y axis
  XYZ.push_back(vec3(0, -nb_cell, 0.005));
  XYZ.push_back(vec3(0, nb_cell, 0.005));
  RGB.push_back(color);
  RGB.push_back(color);

  //---------------------------
}

}
