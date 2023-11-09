#include "GUI_tab.h"

#include <GUI.h>
#include <GUI_style/GUI_font.h>
#include <RES_git/GUI_git.h>
#include <image/IconsFontAwesome5.h>
#include <TAB_render/TAB_render.h>
#include <TAB_render/RND_config/RND_panel.h>
#include <TAB_dev/TAB_dev.h>


//Constructor / Destructor
GUI_tab::GUI_tab(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->gui_font = gui->get_gui_font();
  this->gui_tab_render = new TAB_render(gui);
  this->gui_tab_dev = new TAB_dev(gui);
  this->gui_git = new GUI_git(gui);

  this->active_tab = "Render";
  this->tab_to_open = "";
  this->vec_tab.push_back("Render");
  this->vec_tab.push_back("Dev");

  //---------------------------
}
GUI_tab::~GUI_tab(){
  //---------------------------

  delete gui_tab_render;
  delete gui_tab_dev;

  //---------------------------
}

//Main function
void GUI_tab::create_panels(){
  //---------------------------

  gui_tab_render->create_panels();
  gui_tab_dev->create_panels();

  //---------------------------
}
void GUI_tab::run_tab(){
  //---------------------------

  //Draw main menu bar
  ImGui::BeginMainMenuBar();
  this->menu();
  ImGui::Separator();
  this->tabs();
  ImGui::Dummy(ImVec2(100.0f, 0.0f)); // empty space
  ImGui::EndMainMenuBar();
  this->draw_panels();

  //---------------------------
}

//Menu function
void GUI_tab::menu(){
  //---------------------------

  this->menu_option();
  this->menu_demo();
  this->menu_git();

  //---------------------------
}
void GUI_tab::menu_option(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(ImGui::BeginMenu(ICON_FA_COG, "menu_option")){
    gui_font->combo_font_gui();
    gui_font->combo_font_editor();

    GUI_render* gui_render = gui->get_gui_render();
    VK_info* vk_info = gui_render->get_vk_info();
    float fps = vk_info->get_fps();
    ImGui::Text("%.2f", fps);
    ImGui::EndMenu();
  }

  //---------------------------
}
void GUI_tab::menu_demo(){
  //---------------------------

  if(ImGui::BeginMenu(ICON_FA_BOOK, "menu_demo")){
    //Demo file
    if(ImGui::Button("Demo file")){
      int ret = system("xed ../extern/imgui/core/imgui_demo.cpp");
    }

    //Demo window
    ImGui::Checkbox("Demo window", &show_demo);
    ImGui::EndMenu();
  }

  if(show_demo){
    ImGui::ShowDemoWindow(&show_demo);
  }

  //---------------------------
}
void GUI_tab::menu_git(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(ImGui::BeginMenu(ICON_FA_GITHUB_ALT, "menu_git")){
    gui_git->design_panel();

    ImGui::EndMenu();
  }

  //---------------------------
}

//Tab function
void GUI_tab::tabs(){
  ImGuiTabItemFlags flag;
  //---------------------------

  if (ImGui::BeginTabBar("main_tab")){
    for(int i=0; i<vec_tab.size(); i++){
      if(tab_to_open == vec_tab[i]){
        flag = ImGuiTabItemFlags_SetSelected;
        this->tab_to_open = "";
      }else{
        flag = 0;
      }
      ImGui::SetNextItemWidth(100);
      if (ImGui::BeginTabItem(vec_tab[i].c_str(), NULL, flag)){
        this->active_tab = vec_tab[i];
        ImGui::EndTabItem();
      }
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}
void GUI_tab::draw_panels(){
  //---------------------------

  //Draw selected tab panels
  if(active_tab == "Render"){
    gui_tab_render->draw_panels();
  }
  else if(active_tab == "Dev"){
    gui_tab_dev->draw_panels();
  }

  //---------------------------
}
void GUI_tab::next_tab(){
  //---------------------------

  for(int i=0; i<vec_tab.size(); i++){
    if(vec_tab[i] == active_tab){
      if(i == vec_tab.size()-1){
        this->tab_to_open = vec_tab[0];
      }else{
        this->tab_to_open = vec_tab[i+1];
      }
    }
  }


  //---------------------------
}
