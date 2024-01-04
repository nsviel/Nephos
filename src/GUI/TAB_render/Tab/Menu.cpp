#include "Menu.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <GUI/GUI_main/Interface/Tab.h>
#include <Engine/Data/Namespace.h>
#include <GUI/TAB_render/Tab/Init.h>
#include <imgui/dialog/ImDialog.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Menu::Menu(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::data::Node* eng_data = engine->get_eng_data();
  gui::Tab* gui_tab = gui->get_gui_tab();

  this->gui = gui;
  this->gui_init = new Init(gui);
  this->rnd_tab = gui_tab->get_rnd_tab();
  this->rnd_option = rnd_tab->get_rnd_option();
  this->rnd_panel = rnd_tab->get_rnd_panel();
  this->eng_loader = eng_data->get_eng_loader();

  //---------------------------
}
Menu::~Menu(){}

//Main function
void Menu::run_tab_menu(){
  //---------------------------

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Panel##111")){
    rnd_tab->open_panels();
    ImGui::EndMenu();
  }
  if(ImGui::MenuItem("Load")){
    //eng_loader->load_by_zenity();
    this->loader_dialog();
  }
  if(ImGui::BeginMenu("Init")){
    gui_init->design_init();
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();

  this->loader_panel();

  //---------------------------
}

//Subfunctions
void Menu::loader_dialog(){
  //---------------------------

  ImDialog::Instance()->OpenDialog("selection_dialog", "Selection", ".ply, .pcap, .mkv", "..");

  //---------------------------
}
void Menu::loader_panel(){
  //---------------------------

  // display
  if (ImDialog::Instance()->Display("selection_dialog")){
    // action if OK
    if (ImDialog::Instance()->IsOk()){
      std::string filePathName = ImDialog::Instance()->GetFilePathName();
      std::string filePath = ImDialog::Instance()->GetCurrentPath();
      // action
    }

    // close
    ImDialog::Instance()->Close();
  }

  //---------------------------
}

}
