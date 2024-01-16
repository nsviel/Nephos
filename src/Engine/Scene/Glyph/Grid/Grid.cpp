#include "Grid.h"


namespace glyph::grid{

//Constructor / destructor
Grid::Grid(Engine* engine) : Glyph(engine){
  //---------------------------

  this->name = "grid";
  this->nb_cell = 10;
  this->is_suppressible = false;
  this->is_movable = false;

  this->mesh = new glyph::grid::Mesh(engine);
  this->axis = new glyph::grid::Axis(engine);
  this->plane = new glyph::grid::Plane(engine);

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
void Grid::insert_object_from_glyph(entity::Glyph* glyph){
  //---------------------------

  vector<utl::base::Data*>& vec_data = glyph->get_vec_data();
  for(int i=0; i<vec_data.size(); i++){
    this->vec_data.push_back(vec_data[i]);
  }

  //---------------------------
}

}
