#include "Menu.h"

#include <Node/GUI.h>
#include <Vulkan/Vulkan.h>
#include <GUI/GUI_main/Style/GUI_font.h>
#include <image/IconsFontAwesome5.h>


namespace gui{

//Constructor / Destructor
Menu::Menu(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->gui_font = gui->get_gui_font();
  this->gui_git = new gui::element::Git(gui);

  this->show_demo = false;

  //---------------------------
}
Menu::~Menu(){}

//Menu function
void Menu::menu(){
  //---------------------------

  this->menu_option();
  this->menu_demo();
  this->menu_git();

  //---------------------------
}
void Menu::menu_option(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(ImGui::BeginMenu(ICON_FA_COG, "menu_option")){
    gui_font->combo_font_gui();
    gui_font->combo_font_editor();

    Render* gui_render = gui->get_rnd_tab();
    Vulkan* vulkan = gui_render->get_vulkan();
    VK_info* vk_info = vulkan->get_vk_info();
    float fps = vk_info->get_fps();
    ImGui::Text("%.2f", fps);
    ImGui::EndMenu();
  }

  //---------------------------
}
void Menu::menu_demo(){
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
void Menu::menu_git(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(ImGui::BeginMenu(ICON_FA_GITHUB_ALT, "menu_git")){
    gui_git->design_panel();

    ImGui::EndMenu();
  }

  //---------------------------
}

}
