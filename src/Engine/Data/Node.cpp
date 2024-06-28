#include "Node.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* dat_panel = add_panel("Graph", ICON_FA_FILE, true);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_camera = node_engine->get_node_camera();

  //Child
  this->dat_struct = new dat::Structure();
  this->dat_uid = new dat::graph::UID(this);
  this->dat_set = new dat::element::Set(this);
  this->dat_graph = new dat::Graph(this);
  this->dat_entity = new dat::element::Entity(this);
  this->dat_glyph = new dat::Glyph(this);
  this->dat_image = new dat::element::Image(this);
  this->dat_selection = new dat::graph::Selection(this);
  this->gui_graph = new dat::gui::Graph(this, &dat_panel->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  dat_graph->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  dat_graph->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  dat_graph->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_graph->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  dat_graph->reset();

  //---------------------------
}


}
