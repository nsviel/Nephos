#include "Node.h"

#include <Engine/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::scene{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* sce_panel = new_panel("Scene", ICON_FA_FILE, true);
  utl::gui::Panel* ldr_panel = new_panel("Loader", ICON_FA_FOLDER, true);
  //---------------------------

  this->node_engine = node_engine;
  this->sce_database = new eng::scene::Database(this);
  this->sce_world = new eng::scene::World(this);
  this->sce_glyph = new eng::scene::Glyph(this);
  this->sce_scene = new eng::scene::Scene(this);
  this->sce_loader = new eng::scene::Loader(this);
  this->sce_bookmark = new eng::scene::Bookmark(this);
  this->gui_loader = new eng::scene::gui::Loader(this, &ldr_panel->is_open);
  this->gui_scene = new eng::scene::gui::Scene(this, &sce_panel->is_open);
  this->cpu_profiler = node_engine->get_cpu_profiler();

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
