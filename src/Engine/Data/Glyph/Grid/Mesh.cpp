#include "Mesh.h"


namespace glyph::grid{

//Constructor / destructor
Mesh::Mesh(){
  //---------------------------

  this->name = "grid";
  this->color = vec4(0.3f, 0.3f, 0.3f, 1.0f);
  this->nb_cell = 10;

  //---------------------------
}
Mesh::~Mesh(){
  //---------------------------

  delete data;

  //---------------------------
}

//Main function
void Mesh::create(){
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
void Mesh::update(){
  //---------------------------

  this->construct_mesh();
  this->construct_submesh();

  //---------------------------
}

//Subfunction
void Mesh::construct_mesh(){
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
void Mesh::construct_submesh(){
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
