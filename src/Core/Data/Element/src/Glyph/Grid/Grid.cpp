#include "Grid.h"

#include <Data/Element/Namespace.h>


namespace dat::glyph::grid{

//Constructor / destructor
Grid::Grid(){
  //---------------------------

  this->name = "grid::main";
  this->nb_cell = 10;
  this->is_suppressible = false;
  this->pose->is_movable = false;

  this->list_glyph.push_back(std::make_shared<dat::glyph::grid::Mesh>());
  this->list_glyph.push_back(std::make_shared<dat::glyph::grid::Axis>());
  this->list_glyph.push_back(std::make_shared<dat::glyph::grid::Plane>());

  //---------------------------
}
Grid::~Grid(){}

//Main function
void Grid::create(){
  //---------------------------

  //Create
  for(auto& glyph : list_glyph){
    glyph->create();
  }

  //Contruct
  this->construct(nb_cell);

  //---------------------------
}
void Grid::construct(int nb_cell){
  //---------------------------

  for(auto& glyph : list_glyph){
    auto grid = dynamic_cast<dat::glyph::grid::Structure*>(glyph.get());
    grid->construct(nb_cell);
  }

  //---------------------------
}



}
