#include "Node.h"

#include <Engine/Data/Namespace.h>


namespace eng::data{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->eng_database = new eng::data::Database(this);
  this->eng_scene = new eng::data::Scene(this);
  this->eng_glyph = new eng::data::Glyph(this);
  this->eng_loader = new eng::data::Loader(this);

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
