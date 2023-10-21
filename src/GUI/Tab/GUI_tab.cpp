#include "GUI_tab.h"
#include "Engine/GUI_panel_engine.h"
#include "Engine/Panel_engine.h"

#include <GUI.h>


//Constructor / Destructor
GUI_tab::GUI_tab(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->panel = new Panel_engine();
  this->gui_panel_engine = new GUI_panel_engine(this);
  
  //---------------------------
}
GUI_tab::~GUI_tab(){}

//Main function
