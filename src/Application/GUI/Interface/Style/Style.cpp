#include "Style.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>


namespace gui::style{

//Constructor / Destructor
Style::Style(gui::Node* node_gui){
  //---------------------------



  //---------------------------
}
Style::~Style(){}

//Main function
void Style::init(){
  //---------------------------

  this->style_window();

  //---------------------------
}

//Subfunction
void Style::style_window(){
  ImGuiStyle& style = ImGui::GetStyle();
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  //Formatting -> rounding
  style.WindowRounding = 0.0f;
  style.TabRounding = 0.0f;
  style.GrabRounding = 0.0f;
  style.ScrollbarRounding = 0.0f;
  style.ChildRounding = 0.0f;
  style.FrameRounding = 0.0f;
  style.PopupRounding = 0.0f;
  style.WindowMenuButtonPosition = ImGuiDir_None; // Docking Tab Menu

  //Formatting -> size
  style.FrameBorderSize = 0.0f;
  style.FrameBorderSize = 1.0f;
  style.WindowBorderSize = 0.0f;

  //IO parameters
  //io.IniFilename = "../media/config/gui/imgui.ini";
  io.IniFilename = NULL; //Prevent auto save
  io.ConfigWindowsResizeFromEdges = true;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  //---------------------------
}

}
