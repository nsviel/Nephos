#include "Grid.h"


namespace glyph::grid{

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

  delete data;

  //---------------------------
}

void Grid::create(){
  //---------------------------

  this->data = new eng::data::Object();
  data->draw_line_width = 1;
  data->is_visible = true;
  data->draw_type_name = "line";
  data->is_permanent = true;
  data->is_suppressible = false;
  data->unicolor = color;
  this->update();

  //---------------------------
}
void Grid::update(){
  vector<vec3>& XYZ = data->xyz;
  vector<vec4>& RGB = data->rgb;
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
