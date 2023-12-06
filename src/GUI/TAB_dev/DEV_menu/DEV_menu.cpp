#include "DEV_menu.h"
#include "../DEV_nsp.h"
#include "../DEV_config/DEV_panel.h"

#include <GUI.h>
#include <GUI_interface/GUI_tab.h>
#include <TAB_dev/DEV_tab.h>
#include <image/IconsFontAwesome5.h>


namespace dev{

//Constructor / Destructor
DEV_menu::DEV_menu(dev::DEV_panel* dev_panel){
  //---------------------------

  this->dev_panel = dev_panel;

  //---------------------------
}
DEV_menu::~DEV_menu(){}

//Main function
void DEV_menu::run_tab_menu(){
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
void DEV_menu::open_panels(){
  //---------------------------

  ImGui::Checkbox(ICON_FA_KEY " Database##456", &dev_panel->show_database);

  //---------------------------
}

}
