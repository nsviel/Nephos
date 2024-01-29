#include "Panel.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Panel::Panel(gui::Node* gui){
  //---------------------------

  this->gui = gui;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::init_tab(){
  //---------------------------

  this->rnd_option = new gui::rnd::tab::Option(gui, &show_option, "Option");


  //---------------------------
}
void Panel::draw_tab(){
  //---------------------------


  rnd_option->run_panel();


  //---------------------------
}


}
