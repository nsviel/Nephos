#include "Node.h"

#include <Utility/Namespace.h>
#include <Application/Config.h>


namespace utl{

//Constructor / Destructor
Node::Node(Config* config, utl::element::Profiler* cpu_profiler){
  utl::gui::Panel* prf_panel = new_panel("Profiler", ICON_FA_ARROW_ROTATE_RIGHT, true);
  //---------------------------

  this->utl_window = new utl::element::Window(config);
  this->cpu_profiler = cpu_profiler;

  utl_window->create_window();

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------



  //---------------------------
}
void Node::loop(){
  cpu_profiler->task_begin("utility");
  //---------------------------

  utl_window->manage_input();
  utl_window->window_should_close();
  utl_window->check_for_resizing();

  //---------------------------
  cpu_profiler->task_end("utility");
}
void Node::exit(){
  //---------------------------

  utl_window->destroy_window();

  //---------------------------
}
void Node::gui(){
  //---------------------------


  //---------------------------
}

}
