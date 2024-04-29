#include "Node.h"

#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Scene/Namespace.h>
#include <Glyph/Namespace.h>
#include <Loader/Namespace.h>
#include <Module/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace dat{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* sce_panel = add_panel("Graph", ICON_FA_FILE, true);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();

  //Child
  this->dat_database = new dat::Database(this);
  this->dat_entity = new dat::Entity(this);
  this->node_glyph = new gly::Node(this);
  this->sce_graph = new sce::Graph(this);
  this->gui_scene = new sce::gui::Graph(this, &sce_panel->is_open);
  this->node_module = new eng::module::Node(node_engine);


  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete dat_database;
  delete node_glyph;
  delete ldr_loader;

  //---------------------------
}

void Node::init(){
  //---------------------------

  node_module->config();
  ldr_bookmark->init();
  dat_database->init();
  sce_graph->init();
  node_glyph->init();
  node_module->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  dat_database->loop();
  node_module->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  dat_database->clean();
  node_module->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_loader->run_panel();
  gui_scene->run_panel();
  node_module->gui();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  dat_database->reset();

  //---------------------------
}


}
