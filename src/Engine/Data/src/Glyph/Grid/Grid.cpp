#include "Grid.h"

#include <Scene/Namespace.h>
#include <Data/Namespace.h>


namespace dat::glyph::grid{

//Constructor / destructor
Grid::Grid(eng::Node* node_engine) : Glyph(node_engine){
  //---------------------------

  this->name = "grid::main";
  this->nb_cell = 10;
  this->is_suppressible = false;
  this->is_movable = false;

  this->mesh = new dat::glyph::grid::Mesh(node_engine);
  this->axis = new dat::glyph::grid::Axis(node_engine);
  this->plane = new dat::glyph::grid::Plane(node_engine);

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

  mesh->update_data();
  axis->update_data();
  plane->update_data();

  //----------------------------
}
void Grid::update_pose(){
  //----------------------------

  mesh->update_pose();
  axis->update_pose();
  plane->update_pose();

  //----------------------------
}
void Grid::set_visibility(bool value){
  //---------------------------

  mesh->set_visibility(value);
  axis->set_visibility(value);
  plane->set_visibility(value);

  //---------------------------
}


}
