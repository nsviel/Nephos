#include "Grid.h"

#include <Engine/Scene/Namespace.h>


namespace glyph::grid{

//Constructor / destructor
Grid::Grid(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "grid::main";
  this->nb_cell = 10;
  this->is_suppressible = false;
  this->is_movable = false;

  this->mesh = new glyph::grid::Mesh(node_engine);
  this->axis = new glyph::grid::Axis(node_engine);
  this->plane = new glyph::grid::Plane(node_engine);

  //---------------------------
}
Grid::~Grid(){}

void Grid::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  mesh->create();
  axis->create();
  plane->create();

  this->update_glyph();

  this->insert_object_from_glyph(mesh);
  this->insert_object_from_glyph(axis);
  this->insert_object_from_glyph(plane);

  //---------------------------
}
void Grid::update_glyph(){
  //---------------------------

  mesh->update_glyph(nb_cell);
  axis->update_glyph(nb_cell);
  plane->update_glyph(nb_cell);

  //---------------------------
}
void Grid::insert_object_from_glyph(utl::entity::Glyph* glyph){
  //---------------------------

  for(int i=0; i<glyph->vec_data.size(); i++){
    this->vec_data.push_back(glyph->vec_data[i]);
  }

  //---------------------------
}

}
