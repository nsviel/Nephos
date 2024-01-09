#include "Grid.h"


namespace glyph::grid{

//Constructor / destructor
Grid::Grid(){
  //---------------------------

  this->name = "Grid";
  this->nb_cell = 10;

  //---------------------------
}
Grid::~Grid(){}

void Grid::create(){
  if(vec_object.size() != 0) return;
  //---------------------------

  mesh.create();
  axis.create();
  plane.create();

  this->update();

  this->insert_object_from_glyph(mesh);
  this->insert_object_from_glyph(axis);
  this->insert_object_from_glyph(plane);

  //---------------------------
}
void Grid::update(){
  //---------------------------

  mesh.update(nb_cell);
  axis.update(nb_cell);
  plane.update(nb_cell);

  //---------------------------
}
void Grid::insert_object_from_glyph(eng::data::Glyph& glyph){
  //---------------------------

  vector<eng::data::Object*> vec_object = glyph.get_vec_object();
  for(int i=0; i<vec_object.size(); i++){
    this->vec_object.push_back(vec_object[i]);
  }

  //---------------------------
}

}
