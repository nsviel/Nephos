#include "Mesh.h"


namespace glyph::grid{

//Constructor / destructor
Mesh::Mesh(){
  //---------------------------

  this->name = "grid";
  this->color_mesh = vec4(0.3f, 0.3f, 0.3f, 1.0f);
  this->color_submesh = vec4(0.2f, 0.2f, 0.2f, 1.0f);
  this->nb_cell = 10;
  this->nb_subcell = 10;

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
  data->unicolor = color_mesh;
  this->update();

  //---------------------------
}
void Mesh::update(){
  data->xyz.clear();
  data->rgb.clear();
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

  int cpt = 0;
  for(int i=-nb_cell; i<=nb_cell; i++){
    XYZ.push_back(vec3((float)i, -(float)nb_cell, 0));
    XYZ.push_back(vec3((float)i, (float)nb_cell, 0));

    XYZ.push_back(vec3(-(float)nb_cell, (float)i, 0));
    XYZ.push_back(vec3((float)nb_cell, (float)i, 0));

    cpt++;
  }

  for(int i=0; i<(cpt*4); i++){
    RGB.push_back(color_mesh);
  }

  //---------------------------
}
void Mesh::construct_submesh(){
  vector<vec3>& XYZ = data->xyz;
  vector<vec4>& RGB = data->rgb;
  //---------------------------

  int cpt = 0;
  for(int i=-nb_cell; i<=nb_cell-1; i++){
    for(int j=1; j<nb_subcell; j++){
      XYZ.push_back(vec3((float)i+(float)j/nb_subcell, (float)-nb_cell, 0));
      XYZ.push_back(vec3((float)i+(float)j/nb_subcell, (float)nb_cell, 0));

      XYZ.push_back(vec3((float)-nb_cell, (float)i+(float)j/nb_subcell, 0));
      XYZ.push_back(vec3((float)nb_cell, (float)i+(float)j/nb_subcell, 0));

      cpt++;
    }
  }

  for(int i=0; i<(cpt*4); i++){
    RGB.push_back(color_submesh);
  }

  //---------------------------
}


}
