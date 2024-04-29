#include "Node.h"

#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Scene/Namespace.h>
#include <Glyph/Namespace.h>
#include <Loader/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace sce{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* sce_panel = add_panel("Graph", ICON_FA_FILE, true);
  utl::gui::Panel* ldr_panel = add_panel("Loader", ICON_FA_FOLDER, false);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();

  //Child
  this->sce_database = new sce::Database(this);
  this->sce_entity = new sce::Entity(this);
  this->sce_format = new sce::Format(this);
  this->sce_loader = new sce::Loader(this);
  this->node_glyph = new gly::Node(this);
  this->sce_exporter = new sce::Exporter(this);
  this->sce_bookmark = new sce::Bookmark(this);
  this->sce_graph = new sce::Graph(this);
  this->gui_loader = new sce::gui::Loader(this, &ldr_panel->is_open);
  this->gui_scene = new sce::gui::Graph(this, &sce_panel->is_open);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete sce_database;
  delete node_glyph;
  delete sce_loader;

  //---------------------------
}

void Node::init(){
  //---------------------------

  sce_bookmark->init();
  sce_database->init();
  sce_graph->init();
  node_glyph->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  sce_database->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  sce_database->clean();

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

  sce_database->reset();

  //---------------------------
}


}
