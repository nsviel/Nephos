#include "Mesh.h"

#include <Scene/Namespace.h>


namespace gly::element::grid{

//Constructor / destructor
Mesh::Mesh(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "grid::mesh";
  this->is_permanent = true;
  this->color_mesh = vec4(0.3f, 0.3f, 0.3f, 1.0f);
  this->color_submesh = vec4(0.24f, 0.24f, 0.24f, 1.0f);
  this->nb_subcell = 10;

  //---------------------------
}
Mesh::~Mesh(){}

//Main function
void Mesh::create(){
  //---------------------------

  data.name = "grid::mesh::data";
  data.width = 1;
  data.is_visible = true;
  data.topology.type = utl::topology::LINE;
  data.unicolor = color_mesh;

  this->init();

  //---------------------------
}

//Subfunction
void Mesh::construct(int nb_cell){
  data.xyz.clear();
  data.rgb.clear();
  //---------------------------

  this->construct_mesh(nb_cell);
  this->construct_submesh(nb_cell);

  //---------------------------
}
void Mesh::construct_mesh(int nb_cell){
  vector<vec3>& xyz = data.xyz;
  vector<vec4>& rgb = data.rgb;
  float z = -0.002;
  //---------------------------

  int cpt = 0;
  for(int i=-nb_cell; i<=nb_cell; i++){
    xyz.push_back(vec3((float)i, -(float)nb_cell, z));
    xyz.push_back(vec3((float)i, (float)nb_cell, z));

    xyz.push_back(vec3(-(float)nb_cell, (float)i, z));
    xyz.push_back(vec3((float)nb_cell, (float)i, z));

    cpt++;
  }

  for(int i=0; i<(cpt*4); i++){
    rgb.push_back(color_mesh);
  }

  //---------------------------
}
void Mesh::construct_submesh(int nb_cell){
  vector<vec3>& xyz = data.xyz;
  vector<vec4>& rgb = data.rgb;
  float z = -0.003;
  //---------------------------

  int cpt = 0;
  for(int i=-nb_cell; i<=nb_cell-1; i++){
    for(int j=1; j<nb_subcell; j++){
      xyz.push_back(vec3((float)i+(float)j/nb_subcell, (float)-nb_cell, z));
      xyz.push_back(vec3((float)i+(float)j/nb_subcell, (float)nb_cell, z));

      xyz.push_back(vec3((float)-nb_cell, (float)i+(float)j/nb_subcell, z));
      xyz.push_back(vec3((float)nb_cell, (float)i+(float)j/nb_subcell, z));

      cpt++;
    }
  }

  for(int i=0; i<(cpt*4); i++){
    rgb.push_back(color_submesh);
  }

  //---------------------------
}


}