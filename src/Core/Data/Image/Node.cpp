#include "Node.h"

#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::img{

//Constructor / Destructor
Node::Node(dat::Node* node_data){
  utl::gui::Panel* panel_stream = add_panel("Stream", ICON_FA_FILM, false);
  //---------------------------

  this->node_graph = node_data->get_node_graph();
  this->node_element = node_data->get_node_element();
  this->node_vulkan = node_data->get_node_vulkan();

  this->dat_image = new dat::img::Image(this);
  this->dat_storage = new dat::img::Storage(this);
  this->dat_depth = new dat::img::Depth(this);
  this->gui_stream = new dat::img::gui::Panel(this, &panel_stream->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::gui(){
  //---------------------------

  gui_stream->run_panel();

  //---------------------------
}

}
