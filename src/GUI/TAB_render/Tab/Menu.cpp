#include "Menu.h"

#include <Node/GUI.h>
#include <Engine/Engine.h>
#include <GUI/GUI_main/Interface/Tab.h>
#include <image/IconsFontAwesome6.h>
#include <imgui/dialog/ImDialog.h>

namespace gui::rnd::tab{

//Constructor / Destructor
Menu::Menu(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::data::Node* eng_data = engine->get_eng_data();
  gui::Tab* gui_tab = gui->get_gui_tab();
  gui::rnd::tab::Tab* rnd_tab = gui_tab->get_rnd_tab();

  this->gui = gui;
  this->rnd_init = new gui::rnd::tab::Init(gui);
  this->rnd_option = rnd_tab->get_rnd_option();
  this->rnd_panel = rnd_tab->get_rnd_panel();

  //---------------------------
}
Menu::~Menu(){}

//Main function
void Menu::run_tab_menu(){
  //---------------------------

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Panel##111")){
    ImGui::Checkbox(ICON_FA_COG " Option##456", &rnd_panel->show_option);
    ImGui::Checkbox(ICON_FA_PLAY " Scene##456", &rnd_panel->show_scene);
    ImGui::Checkbox(ICON_FA_ARROW_ROTATE_RIGHT " Profiler##456", &rnd_panel->show_profiler);
    ImGui::Checkbox(ICON_FA_CAMERA " Camera##456", &rnd_panel->show_camera);
    ImGui::Checkbox(ICON_FA_ROAD " Shader##456", &rnd_panel->show_shader);
    ImGui::Checkbox(ICON_FA_FILM " Kinect##456", &rnd_panel->show_kinect);
    ImGui::EndMenu();
  }
  if(ImGui::MenuItem("Load")){
    string title = "Selection";
    string filter = ", .ply, .pcap, .mkv";
    ImDialog::Instance()->OpenDialog("selection_dialog", title.c_str(), filter.c_str(), "..");
    ImDialog::Instance()->SetFileStyle(IGFD_FileStyleByTypeDir, "", ImVec4(0.5f, 0.63f, 0.75f, 0.9f), ICON_FA_FOLDER);
    ImDialog::Instance()->SetFileStyle(IGFD_FileStyleByTypeFile, "", ImVec4(1.0f, 1.0f, 1.0f, 0.9f), ICON_FA_FILE);
    //ImDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtention, ".mkv", IM_COL32(45, 133, 133, 255));

  }
  if(ImGui::BeginMenu("Init")){
    rnd_init->design_init();
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();



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
