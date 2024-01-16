#include "Mesh.h"


namespace glyph::grid{

//Constructor / destructor
Mesh::Mesh(Engine* engine) : Glyph(engine){
  //---------------------------

  this->name = "grid";
  this->color_mesh = vec4(0.3f, 0.3f, 0.3f, 1.0f);
  this->color_submesh = vec4(0.24f, 0.24f, 0.24f, 1.0f);
  this->nb_subcell = 10;

  //---------------------------
}
Mesh::~Mesh(){}

//Main function
void Mesh::create(){
  if(vec_object.size() != 0) return;
  //---------------------------

  entity::Object* object = new entity::Object(engine);
  object->name = "grid_mesh";
  object->data->draw_line_width = 1;
  object->is_visible = true;
  object->draw_type_name = "line";
  object->is_permanent = true;
  object->unicolor = color_mesh;
  this->vec_object.push_back(object);

  //---------------------------
}
void Mesh::update_glyph(int nb_cell){
  vec_object[0]->xyz.clear();
  vec_object[0]->rgb.clear();
  //---------------------------

  this->construct_mesh(nb_cell);
  this->construct_submesh(nb_cell);

  //---------------------------
}

//Subfunction
void Mesh::construct_mesh(int nb_cell){
  vector<vec3>& XYZ = vec_object[0]->xyz;
  vector<vec4>& RGB = vec_object[0]->rgb;
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
  vector<vec3>& XYZ = vec_object[0]->xyz;
  vector<vec4>& RGB = vec_object[0]->rgb;
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
