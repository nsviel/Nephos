#include "Tab.h"

#include <Dev/gui/Namespace.h>


namespace dev::gui{

//Constructor / Destructor
Tab::Tab(){
  //---------------------------

  this->menu = new dev::gui::Menu(this);

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::draw_tab(){
  //---------------------------

  menu->run_tab_menu();
  this->run_editors();

  //---------------------------
}

//Subfunction
void Tab::run_editors(){
  //---------------------------



  //---------------------------
}

}
