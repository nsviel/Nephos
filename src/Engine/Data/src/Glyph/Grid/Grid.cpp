#include "Grid.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>


namespace dat::glyph::grid{

//Constructor / destructor
Grid::Grid(eng::Node* node_engine){
  //---------------------------

  dat::Node* node_data = node_engine->get_node_data();

  this->node_engine = node_engine;
  this->dat_glyph = node_data->get_dat_glyph();
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
/*
  dat_glyph->create_glyph(this, new dat::glyph::grid::Mesh(node_engine));
  dat_glyph->create_glyph(this, new dat::glyph::grid::Axis(node_engine));
  dat_glyph->create_glyph(this, new dat::glyph::grid::Plane(node_engine));

  this->construct(nb_cell);
*/
  //---------------------------
}
void Grid::construct(int nb_cell){
  //---------------------------

  for(int i=0; i<list_glyph.size(); i++){
    dat::base::Glyph* glyph = *next(list_glyph.begin(), i);
    dat::glyph::grid::Grid* grid = dynamic_cast<dat::glyph::grid::Grid*>(glyph);
    // /grid->construct(nb_cell);
  }

  //---------------------------
}
void Grid::update_data(){
  //----------------------------

  dat_entity->update_data(mesh);
  dat_entity->update_data(axis);
  dat_entity->update_data(plane);

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
