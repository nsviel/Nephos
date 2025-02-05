#include "Node.h"

#include <Core/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Module/Namespace.h>
#include <Utility/Namespace.h>
#include <Application/Namespace.h>


namespace app{

//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->root = this;
  this->node_vulkan = new vk::Node();
  this->node_profiler = new prf::Node(this);
  this->node_core = new core::Node(this);
  this->node_module = new mod::Node(this);
  this->node_dynamic = new dyn::Node(this);

  this->node_scene = new sce::Node(this);
  this->node_gui = new gui::Node(this);
  this->tasker = node_profiler->get_tasker_cpu();
  this->vk_window = node_vulkan->get_vk_window();

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_vulkan->init();
  node_profiler->init();
  node_core->init();
  node_dynamic->init();
  node_module->init();
  node_gui->init();
  node_scene->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  //Main loop
  while(vk_window->is_running()){
    node_profiler->loop();

    tasker->task_begin("gui");
    node_gui->loop();
    tasker->task_end("gui");

    tasker->task_begin("core");
    node_core->loop();
    tasker->task_end("core");

    tasker->task_begin("vulkan");
    node_vulkan->loop();
    tasker->task_end("vulkan");

    tasker->task_begin("dynamic");
    node_dynamic->loop();
    tasker->task_end("dynamic");

    tasker->task_begin("module");
    node_module->loop();
    tasker->task_end("module");
  }

  //Clean engine stuff
  node_vulkan->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_core->gui();
  node_module->gui();
  node_dynamic->gui();
  node_profiler->gui();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_core->reset();

  //---------------------------
}
void Node::close(){
  //---------------------------

  vk_window->close_window();

  //---------------------------
}

}
