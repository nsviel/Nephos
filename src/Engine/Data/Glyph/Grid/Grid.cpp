#include "Grid.h"

#include <Vulkan/VK_main/VK_engine.h>


namespace glyph::grid{

//Constructor / destructor
Grid::Grid(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->name = "Grid";

  //---------------------------
}
Grid::~Grid(){}

void Grid::create(){
  //---------------------------

  mesh.create();
  axis.create();
  plane.create();

  //vk_engine->insert_object_in_engine(mesh.get_object());
  //vk_engine->insert_object_in_engine(axis.get_object());
  //vk_engine->insert_object_in_engine(plane.get_object());

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
