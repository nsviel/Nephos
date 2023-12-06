#include "DEV_menu.h"

#include <GUI.h>
#include <GUI_interface/GUI_tab.h>
#include <TAB_dev/TAB_dev.h>


//Constructor / Destructor
DEV_menu::DEV_menu(GUI* gui){
  //---------------------------

  GUI_tab* gui_tab = gui->get_gui_tab();
  this->gui_tab_dev = gui_tab->get_gui_dev();

  //---------------------------
}
DEV_menu::~DEV_menu(){}

//Main function
void DEV_menu::run_tab_menu(){
  //---------------------------

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Panel##111")){
    gui_tab_dev->open_panels();
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();

  //---------------------------
}

//Subfunctions
