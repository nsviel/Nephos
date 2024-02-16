#include "Node.h"

#include <Engine/Namespace.h>
#include <Capture/Namespace.h>
#include <Scene/Namespace.h>
#include <Velodyne/Namespace.h>



namespace velodyne{

//Constructor / Destructor
Node::Node(eng::capture::Node* node_capture){
  //---------------------------

  this->node_engine = node_capture->get_node_engine();
  //this->velo_capture = new velodyne::Capture();

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  eng::scene::Node* node_scene = node_engine->get_node_scene();
  eng::scene::Format* sce_format = node_scene->get_scene_format();
  //---------------------------

  sce_format->insert_importer(new velodyne::Importer());

  //---------------------------
}

}
