#include "GUI_left_panel.h"

#include "../Node_gui.h"
#include "../Menu/GUI_menubar.h"
#include "../Control/GUI_time.h"
#include "../Engine/GUI_shader.h"
#include "../Engine/GUI_device.h"
#include "../Data/GUI_filemanager.h"

#include "../../Load/Node_load.h"
#include "../../Load/Processing/Loader.h"
#include "../../Engine/Node_engine.h"
#include "../../Engine/Dimension/Dimension.h"
#include "../../Node.h"
#include "../../Engine/Param_engine.h"


//Constructor / Destructor
GUI_left_panel::GUI_left_panel(Node_gui* node_gui){
  //---------------------------

  this->node_engine = node_gui->get_node_engine();
  this->dimManager = node_engine->get_dimManager();
  this->node_gui = node_gui;
  this->gui_filemanager = node_gui->get_gui_filemanager();
  this->gui_time = node_gui->get_gui_time();
  this->gui_menubar = node_gui->get_gui_menubar();
  this->gui_shader = node_gui->get_gui_shader();
  this->gui_device = node_gui->get_gui_device();

  //---------------------------
}
GUI_left_panel::~GUI_left_panel(){}

//Main function
void GUI_left_panel::draw_left_panel(){
  Tab* tab_left = dimManager->get_tab("left_panel");
  //---------------------------

  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_MenuBar;
  ImGui::SetNextWindowPos(ImVec2(tab_left->pos.x, tab_left->pos.y));
  ImGui::SetNextWindowSize(ImVec2(tab_left->dim.x, tab_left->dim.y));
  ImGui::SetNextWindowSizeConstraints(ImVec2(tab_left->dim_min.x, tab_left->dim_min.y), ImVec2(tab_left->dim_max.x, tab_left->dim_max.y));
  ImGui::Begin("LeftPanel##botOuter", NULL, window_flags);

  this->update_dim();
  gui_menubar->design_menubar();
  this->design_top();
  this->design_bot();

  ImGui::PopStyleVar();
  ImGui::End();

  //---------------------------
}
void GUI_left_panel::design_top(){
  Tab* tab_panel_left = dimManager->get_tab("left_panel");
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  vec2* gui_ltp_dim = dimManager->get_gui_ltp_dim();
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
  ImGui::SetNextWindowSize(ImVec2(tab_panel_left->dim.x, 105));
  ImGui::SetNextWindowPos(ImVec2(0, 20));
  ImGui::Begin("LeftPanel##topInner", NULL, window_flags);
  {
    gui_filemanager->tree_view(tab_panel_left->dim.x);
  }
  ImGui::End();
  ImGui::SetCursorPos(ImVec2(8, 125));
  ImGui::PopStyleVar();

  //---------------------------
}
void GUI_left_panel::design_bot(){
  //---------------------------

  gui_shader->design_shader();

  ImVec2 windowSize = ImGui::GetWindowSize();
  float widgetHeight = 150.0f; // Adjust the height of the widget as needed
  float widgetYPosition = windowSize.y - widgetHeight - ImGui::GetStyle().ItemSpacing.y;
  ImGui::SetCursorPos(ImVec2(8, widgetYPosition));

  gui_device->design_device();
  gui_time->design_time();

  //---------------------------
}

//Subfunction
void GUI_left_panel::update_dim(){
  Tab* tab_left = dimManager->get_tab("left_panel");
  //---------------------------

  float dim_x = ImGui::GetWindowSize().x;
  if(dim_x != tab_left->dim.x){
    tab_left->dim.x = ImGui::GetWindowSize().x;
    dimManager->update();
  }

  //---------------------------
}
