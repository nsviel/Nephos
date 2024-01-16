#include "Mesh.h"


namespace glyph::grid{

//Constructor / destructor
Mesh::Mesh(Engine* engine) : Glyph(engine){
  //---------------------------

  this->is_permanent = true;
  this->name = "grid";
  this->color_mesh = vec4(0.3f, 0.3f, 0.3f, 1.0f);
  this->color_submesh = vec4(0.24f, 0.24f, 0.24f, 1.0f);
  this->nb_subcell = 10;

  //---------------------------
}
Mesh::~Mesh(){}

//Main function
void Mesh::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  utl::base::Data* data = new utl::base::Data();
  data->draw_line_width = 1;
  data->is_visible = true;
  data->draw_type_name = "line";
  data->unicolor = color_mesh;
  this->vec_data.push_back(data);

  //---------------------------
}
void Mesh::update_glyph(int nb_cell){
  vec_data[0]->xyz.clear();
  vec_data[0]->rgb.clear();
  //---------------------------

  this->construct_mesh(nb_cell);
  this->construct_submesh(nb_cell);

  //---------------------------
}

//Subfunction
void Mesh::construct_mesh(int nb_cell){
  vector<vec3>& XYZ = vec_data[0]->xyz;
  vector<vec4>& RGB = vec_data[0]->rgb;
  float z = -0.002;
  //---------------------------

  int cpt = 0;
  for(int i=-nb_cell; i<=nb_cell; i++){
    XYZ.push_back(vec3((float)i, -(float)nb_cell, z));
    XYZ.push_back(vec3((float)i, (float)nb_cell, z));

    XYZ.push_back(vec3(-(float)nb_cell, (float)i, z));
    XYZ.push_back(vec3((float)nb_cell, (float)i, z));

    cpt++;
  }

  for(int i=0; i<(cpt*4); i++){
    RGB.push_back(color_mesh);
  }

  //---------------------------
}
void Mesh::construct_submesh(int nb_cell){
  vector<vec3>& XYZ = vec_data[0]->xyz;
  vector<vec4>& RGB = vec_data[0]->rgb;
  float z = -0.003;
  //---------------------------

  int cpt = 0;
  for(int i=-nb_cell; i<=nb_cell-1; i++){
    for(int j=1; j<nb_subcell; j++){
      XYZ.push_back(vec3((float)i+(float)j/nb_subcell, (float)-nb_cell, z));
      XYZ.push_back(vec3((float)i+(float)j/nb_subcell, (float)nb_cell, z));

      XYZ.push_back(vec3((float)-nb_cell, (float)i+(float)j/nb_subcell, z));
      XYZ.push_back(vec3((float)nb_cell, (float)i+(float)j/nb_subcell, z));

      cpt++;
    }
  }

  for(int i=0; i<(cpt*4); i++){
    RGB.push_back(color_submesh);
  }

  //---------------------------
}


}
