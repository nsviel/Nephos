#include "DEV_menu.h"

#include <GUI.h>
#include <GUI_interface/GUI_tab.h>
#include <TAB_dev/DEV_tab.h>


//Constructor / Destructor
DEV_menu::DEV_menu(GUI* gui){
  //---------------------------

  GUI_tab* gui_tab = gui->get_gui_tab();
  this->dev_tab = gui_tab->get_dev_tab();

  //---------------------------
}
DEV_menu::~DEV_menu(){}

//Main function
void DEV_menu::run_tab_menu(){
  //---------------------------

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Panel##111")){
    dev_tab->open_panels();
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();

  //---------------------------
}

//Subfunctions
