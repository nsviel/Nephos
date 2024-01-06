#include "Grid.h"


namespace glyph::world{

//Constructor / destructor
Grid::Grid(){
  //---------------------------

  this->name = "grid";
  this->color = vec4(1, 1, 1, 0.3);
  this->nb_cell = 40;

  //---------------------------
}
Grid::~Grid(){
  //---------------------------

  delete object;

  //---------------------------
}

eng::data::Object* Grid::create(){
  //---------------------------

  this->object = new eng::data::Object();
  object->draw_line_width = 1;
  object->is_visible = true;
  object->draw_type_name = "line";
  object->is_permanent = true;
  object->unicolor = color;
  this->update();

  //---------------------------
  return object;
}
void Grid::update(){
  vector<vec3>& XYZ = object->xyz;
  vector<vec4>& RGB = object->rgb;
  //---------------------------

  //Parameters
  XYZ.clear();
  RGB.clear();

  //Construct glyph
  for(int i=-nb_cell; i<=nb_cell; i++){
    XYZ.push_back(vec3((float)i, -(float)nb_cell, 0));
    XYZ.push_back(vec3((float)i, (float)nb_cell, 0));

    XYZ.push_back(vec3(-(float)nb_cell, (float)i, 0));
    XYZ.push_back(vec3((float)nb_cell, (float)i, 0));

    for(int j=0; j<4; j++){
      RGB.push_back(color);
    }
  }

  //---------------------------
}

}
