#include "Grid.h"


namespace glyph::grid{

//Constructor / destructor
Grid::Grid(){
  //---------------------------

  this->name = "Grid";

  //---------------------------
}
Grid::~Grid(){}

void Grid::create(){
  if(vec_object.size() != 0) return;
  //---------------------------

  mesh.create();
  axis.create();
  plane.create();

  this->vec_object.push_back(mesh.get_vec_object());
  this->vec_object.push_back(axis.get_vec_object());
  this->vec_object.push_back(plane.get_vec_object());

  //---------------------------
}
void Grid::update(){
  //---------------------------

  mesh.update();
  axis.update();
  plane.update();

  //---------------------------
}

}
