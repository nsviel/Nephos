#include "Menu.h"

#include <image/IconsFontAwesome6.h>


namespace gui::tab::dev{

//Constructor / Destructor
Menu::Menu(){
  //---------------------------


  //---------------------------
}
Menu::~Menu(){}

//Main function
void Menu::draw(){
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
