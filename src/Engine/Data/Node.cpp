#include "Node.h"

#include <Engine/Data/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->sce_database = new eng::scene::Database(this);
  this->sce_glyph = new eng::scene::Glyph(this);
  this->sce_scene = new eng::scene::Scene(this);
  this->sce_loader = new eng::scene::Loader(this);
  this->sce_operation = new eng::scene::Operation(this);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete sce_scene;
  delete sce_database;
  delete sce_glyph;
  delete sce_loader;

  //---------------------------
}

void Node::init(){
  //---------------------------

  sce_database->init_set();
  sce_scene->init();
  sce_glyph->create_glyph_world();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  sce_scene->reset();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  sce_scene->loop();

  //---------------------------
}

}
