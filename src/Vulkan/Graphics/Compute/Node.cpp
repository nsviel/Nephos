#include "Node.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::compute{

//Constructor / Destructor
Node::Node(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_dtc = new vk::compute::dtc::Pipeline(vk_struct);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  vk_dtc->create_pipeline();

  //---------------------------
}
void Node::loop(){
  //---------------------------


  //---------------------------
}

}
