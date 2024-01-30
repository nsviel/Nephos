#include "Node.h"

#include <Engine/Scene/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Node::Node(eng::Node* engine){
  Panel* sce_panel = new Panel("Scene", true);
  Panel* ldr_panel = new Panel("Loader", true);
  //---------------------------

  this->engine = engine;
  this->sce_database = new eng::scene::Database(this);
  this->sce_world = new eng::scene::World(this);
  this->sce_glyph = new eng::scene::Glyph(this);
  this->sce_loader = new eng::scene::Loader(this);
  this->sce_scene = new eng::scene::Scene(this);
  this->sce_bookmark = new eng::scene::Bookmark(this);
  this->gui_loader = new eng::scene::gui::Loader(this, &sce_panel->second);
  this->gui_scene = new eng::scene::gui::Scene(this, &ldr_panel->second);

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

  sce_bookmark->init();
  sce_database->init_set();
  sce_scene->init();
  sce_world->init();
  sce_glyph->create_glyph_world();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  sce_scene->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_loader->run_panel();
  gui_scene->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  sce_scene->reset();

  //---------------------------
}


}
