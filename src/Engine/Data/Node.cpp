#include "Node.h"

#include <Engine/Data/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->eng_database = new eng::scene::Database(this);
  this->eng_glyph = new eng::scene::Glyph(this);
  this->eng_scene = new eng::scene::Scene(this);
  this->eng_loader = new eng::scene::Loader(this);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete eng_scene;
  delete eng_database;
  delete eng_glyph;
  delete eng_loader;

  //---------------------------
}

void Node::init(){
  //---------------------------

  eng_database->init_set();
  eng_scene->init();
  eng_glyph->create_glyph_world();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  eng_scene->reset();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  eng_scene->loop();

  //---------------------------
}

}
