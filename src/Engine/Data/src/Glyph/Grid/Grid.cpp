#include "Grid.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>


namespace dat::glyph::grid{

//Constructor / destructor
Grid::Grid(){
  //---------------------------

  this->name = "grid::main";
  this->nb_cell = 10;
  this->is_suppressible = false;
  this->is_movable = false;

  this->list_glyph.push_back(new dat::glyph::grid::Mesh());
  this->list_glyph.push_back(new dat::glyph::grid::Axis());
  this->list_glyph.push_back(new dat::glyph::grid::Plane());

  //---------------------------
}
Grid::~Grid(){}

//Main function
void Grid::create(){
  //---------------------------

  this->construct(nb_cell);

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



}
