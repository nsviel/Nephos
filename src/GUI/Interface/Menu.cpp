#include "Menu.h"

#include <Vulkan/Namespace.h>
#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace gui::interface{

//Constructor / Destructor
Menu::Menu(gui::Node* gui){
  //---------------------------

  this->node_utility = gui->get_node_utility();
  this->gui = gui;
  this->gui_font = gui->get_gui_font();
  this->gui_git = new utl::element::gui::Git();

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
    vk::Node* vulkan = gui_render->get_vulkan();
    vk::main::Info* vk_info = vulkan->get_vk_info();
    prf::Node* node_profiler = node_utility->get_node_profiler();
    prf::Manager* profiler = node_profiler->get_profiler();
    prf::Tasker* tasker_cpu = profiler->get_tasker_cpu();
    ImGui::Text("%.2f", tasker_cpu->get_loop_fps());
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
