#include "Grid.h"

#include <Data/Namespace.h>


namespace dat::glyph::grid{

//Constructor / destructor
Grid::Grid(){
  //---------------------------

  this->name = "grid::main";
  this->nb_cell = 10;
  this->is_suppressible = false;
  this->pose.movable = false;

  this->list_glyph.push_back(new dat::glyph::grid::Mesh());
  this->list_glyph.push_back(new dat::glyph::grid::Axis());
  this->list_glyph.push_back(new dat::glyph::grid::Plane());

  //---------------------------
}
Grid::~Grid(){}

//Main function
void Grid::create(){
  //---------------------------

  //Create
  for(int i=0; i<list_glyph.size(); i++){
    dat::base::Glyph* glyph = *next(list_glyph.begin(), i);
    glyph->create();
  }

  //Contruct
  this->construct(nb_cell);

  //---------------------------
}
void Grid::construct(int nb_cell){
  //---------------------------

  for(int i=0; i<list_glyph.size(); i++){
    dat::base::Glyph* glyph = *next(list_glyph.begin(), i);
    dat::glyph::grid::Structure* grid = dynamic_cast<dat::glyph::grid::Structure*>(glyph);
    grid->construct(nb_cell);
  }

  //---------------------------
}



}
