#include "Node.h"
#include "ENG_scene/ENG_scene.h"
#include "ENG_scene/ENG_database.h"
#include "ENG_glyph/ENG_glyph.h"
#include "ENG_load/ENG_loader.h"


namespace eng::data{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->eng_database = new Nodebase(this);
  this->eng_scene = new ENG_scene(this);
  this->eng_glyph = new ENG_glyph(this);
  this->eng_loader = new ENG_loader(this);

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

  eng_scene->init_set();
  eng_scene->init_scene();
  eng_glyph->create_glyph_scene();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  eng_scene->reset_scene();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  eng_scene->loop();

  //---------------------------
}

}
