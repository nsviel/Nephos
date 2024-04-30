#include "Node.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Module/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace dat{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* dat_panel = add_panel("Graph", ICON_FA_FILE, true);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();

  //Child
  this->dat_database = new dat::Database(this);
  this->dat_glyph = new dat::Glyph(this);
  this->dat_entity = new dat::Entity(this);

  this->gui_graph = new dat::gui::Graph(this, &dat_panel->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  dat_database->init();
  dat_glyph->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  dat_database->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  dat_database->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_graph->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  dat_database->reset();

  //---------------------------
}


}
