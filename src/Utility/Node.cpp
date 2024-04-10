#include "Node.h"

#include <Application/Node.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>
#include <Application/Configuration.h>


namespace utl{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  Configuration* config = node_app->get_configuration();

  this->node_profiler = node_app->get_node_profiler();
  this->utl_window = new utl::element::Window(config);

  utl_window->create_window();

  //---------------------------
}
Node::~Node(){}


}
