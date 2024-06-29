#include "Theme.h"

#include <GUI/Namespace.h>


namespace gui::style{

//Constructor / Destructor
Theme::Theme(gui::Node* gui){
  //---------------------------


  //---------------------------
}
Theme::~Theme(){}

//Main function
void Theme::init_theme(){
  //---------------------------

  this->theme_main();
  this->theme_window();
  this->theme_widget();

  //---------------------------
}

//Subfunction
void Theme::theme_main(){
  //---------------------------

  ImGui::StyleColorsDark();

  //---------------------------
}
void Theme::theme_window(){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  style.Colors[ImGuiCol_Header] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
  style.Colors[ImGuiCol_Tab] = ImVec4(0.17, 0.28, 0.39, 0.86);
  style.Colors[ImGuiCol_Border] = ImVec4(0, 0, 0, 1.0f);

  style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0, 0, 0, 1.0f);
  style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.06, 0.06, 0.06, 1.0f);
  style.Colors[ImGuiCol_WindowBg] = ImVec4(0.2, 0.2, 0.2, 1.0f);

  style.Colors[ImGuiCol_PopupBg] = ImVec4(0, 0, 0, 1.0f);
  style.Colors[ImGuiCol_Separator] = ImVec4(0.3, 0.3, 0.3, 1.0f);
  style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0, 0, 0, 1.0f);

  //---------------------------
}
void Theme::theme_widget(){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Widget
  style.Colors[ImGuiCol_Button] = ImVec4(0.31, 0.31, 0.31, 1.0f);
  style.Colors[ImGuiCol_CheckMark] = ImVec4(0, 0, 0, 1.0f);

  //Widget frame
  style.Colors[ImGuiCol_FrameBg] = ImVec4(0.31, 0.31, 0.31, 1.0f);
  style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.31, 0.31, 0.31, 1.0f);
  style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.31, 0.31, 0.31, 1.0f);

  //Slider
  style.Colors[ImGuiCol_SliderGrab] = ImVec4(0, 0, 0, 1.0f);
  style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0, 0, 0, 1.0f);

  //Table
  style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0, 0, 0, 1.0f);
  style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.13, 0.13, 0.13, 1.0f);
  style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.1, 0.1, 0.1, 1.0f);

  //---------------------------
}

}
