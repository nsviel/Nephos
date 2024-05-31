#include "Grid.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>


namespace dat::glyph::grid{

//Constructor / destructor
Grid::Grid(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  dat::Node* node_data = node_engine->get_node_data();

  this->dat_entity = node_data->get_dat_entity();
  this->mesh = new dat::glyph::grid::Mesh(node_engine);
  this->axis = new dat::glyph::grid::Axis(node_engine);
  this->plane = new dat::glyph::grid::Plane(node_engine);

  this->name = "grid::main";
  this->nb_cell = 10;
  this->is_suppressible = false;
  this->is_movable = false;

  //---------------------------
}
Grid::~Grid(){}

//Main function
void Grid::create(){
  //---------------------------

  this->construct();
  mesh->create();
  axis->create();
  plane->create();

  //---------------------------
}
void Grid::construct(){
  //---------------------------

  mesh->construct(nb_cell);
  axis->construct(nb_cell);
  plane->construct(nb_cell);

  //---------------------------
}
void Grid::update_data(){
  //----------------------------

  dat_entity->update_data(mesh);
  dat_entity->update_data(axis);
  dat_entity->update_data(plane);

  //----------------------------
}
void Grid::update_pose(){
  //----------------------------

  mesh->update_pose();
  axis->update_pose();
  plane->update_pose();

  //----------------------------
}
void Grid::visibility(bool value){
  //---------------------------

  mesh->visibility(value);
  axis->visibility(value);
  plane->visibility(value);

  //---------------------------
}


}
