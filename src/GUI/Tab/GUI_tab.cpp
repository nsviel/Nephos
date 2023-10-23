#include "GUI_tab.h"
#include "Render/GUI_render.h"
#include "Render/GUI_render_panel.h"
#include "Dev/GUI_dev.h"

#include <GUI.h>
#include <Style/GUI_font.h>
#include <image/IconsFontAwesome5.h>
//#include <Python.h>


//Constructor / Destructor
GUI_tab::GUI_tab(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->gui_font = gui->get_gui_font();
  this->gui_render_panel = new GUI_render_panel();
  this->gui_render = new GUI_render(gui);
  this->gui_dev = new GUI_dev(gui);

  this->active_tab = "Render";
  this->tab_to_open = "";
  this->vec_tab.push_back("Render");
  this->vec_tab.push_back("Dev");

  //---------------------------
}
GUI_tab::~GUI_tab(){
  //---------------------------

  delete gui_render;
  delete gui_dev;

  //---------------------------
}

//Main function
void GUI_tab::create_panels(){
  //---------------------------

  gui_render->create_panels();
  gui_dev->create_panels();

  //---------------------------
}
void GUI_tab::run_tab(){
  //---------------------------

  //Draw main menu bar
  ImGui::BeginMainMenuBar();
  this->main_menu();
  ImGui::Separator();
  this->menu_tabs();
  ImGui::Dummy(ImVec2(100.0f, 0.0f)); // empty space
  ImGui::EndMainMenuBar();
  this->draw_panels();

  //---------------------------
}

//Subfunction
void GUI_tab::main_menu(){
  //---------------------------

  this->menu_demo();
  this->menu_font();

  //---------------------------
}
void GUI_tab::menu_demo(){
  //---------------------------

  if(ImGui::BeginMenu(ICON_FA_BOOK, "Demo")){
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
void GUI_tab::menu_font(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(ImGui::BeginMenu(ICON_FA_COG, "Main_font")){

    //Font main gui
    ImFont* font_current = ImGui::GetFont();
    ImFont* font_selected = gui_font->gui_combo_font("GUI##Font", font_current);
    gui_font->set_current_font(font_selected);

    //Font editor
    ImFont* font_editor = gui_font->get_font_editor();
    ImFont* font_editor_selected = gui_font->gui_combo_font("Editor##Font", font_editor);
    gui_font->set_editor_font(font_editor_selected);

    ImGui::EndMenu();
  }

  //---------------------------
}
void GUI_tab::menu_tabs(){
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
    gui_render->draw_panels();
  }
  else if(active_tab == "Dev"){
    gui_dev->draw_panels();
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
