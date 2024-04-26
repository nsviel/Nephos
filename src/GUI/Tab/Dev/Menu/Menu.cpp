#include "Menu.h"

#include <image/IconsFontAwesome6.h>


namespace dev::gui{

//Constructor / Destructor
Menu::Menu(dev::gui::Node* tab_dev){
  //---------------------------

  this->tab_dev = tab_dev;

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


  //---------------------------
}

}
