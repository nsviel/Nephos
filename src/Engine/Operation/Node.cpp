#include "Node.h"

#include <Engine/Operation/Namespace.h>


namespace eng::ope{

//Constructor / Destructor
Node::Node(eng::Engine* engine){
  //---------------------------

  this->gui_profiler = new eng::ope::gui::Profiler(engine, &show_profiler);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------



  //---------------------------
}
void Node::loop(){
  //---------------------------


  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_profiler->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------



  //---------------------------
}


}
