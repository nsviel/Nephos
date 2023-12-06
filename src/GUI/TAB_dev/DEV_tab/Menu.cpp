#include "Menu.h"
#include "../DEV_nsp.h"

#include <GUI.h>
#include <GUI_interface/GUI_tab.h>
#include <TAB_dev/DEV_tab/DEV_tab.h>
#include <TAB_dev/DEV_tab/Panel.h>
#include <image/IconsFontAwesome5.h>


namespace dev{

//Constructor / Destructor
Menu::Menu(dev::Panel* panel){
  //---------------------------

  this->panel = panel;

  //---------------------------
}
Menu::~Menu(){}

//Main function
void Menu::run_tab_menu(){
  //---------------------------

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Panel##111")){
    this->open_panels();
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();

  //---------------------------
}

//Subfunctions
void Menu::open_panels(){
  //---------------------------

  ImGui::Checkbox(ICON_FA_KEY " Database##456", &panel->show_database);

  //---------------------------
}

}
