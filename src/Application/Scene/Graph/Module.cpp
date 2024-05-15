#include "Module.h"

#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Kinect/Namespace.h>
#include <Radiometry/Namespace.h>


namespace sce{

//Constructor / Destructor
Module::Module(sce::Node* node_scene){
  //---------------------------

  eng::Node* node_engine = node_scene->get_node_engine();

  this->node_kinect = new k4n::Node(node_engine);
  this->node_radio = new rad::Node(node_engine);

  this->add_node_panel(node_kinect);
  this->add_node_panel(node_radio);

  //---------------------------
}
Module::~Module(){}

//Main function
void Module::init(){
  //---------------------------

  node_kinect->init();

  //---------------------------
}
void Module::loop(){
  //---------------------------

  node_kinect->loop();

  //---------------------------
}
void Module::clean(){
  //---------------------------

  node_kinect->clean();

  //---------------------------
}
void Module::gui(){
  //---------------------------

  node_kinect->gui();
  node_radio->gui();

  //---------------------------
}

}
