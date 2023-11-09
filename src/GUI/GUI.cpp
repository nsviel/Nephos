#include "GUI.h"

#include <Engine.h>
#include <ELE_window/ELE_window.h>
#include <RES_gpu/GUI_gpu.h>
#include <GUI_tab/GUI_tab.h>
#include <GUI_control/GUI_control.h>
#include <GUI_render/GUI_render.h>
#include <GUI_style/GUI_style.h>
#include <GUI_style/GUI_font.h>


//Constructor / Destructor
GUI::GUI(ELE_window* ele_window, Engine* engine){
  //---------------------------

  this->engine = engine;
  this->ele_window = ele_window;

  this->gui_style = new GUI_style(this);
  this->gui_font = new GUI_font(this);
  this->gui_tab = new GUI_tab(this);
  this->gui_gpu = new GUI_gpu(this);
  this->gui_control = new GUI_control(this);
  this->gui_render = new GUI_render(this);

  //---------------------------
}
GUI::~GUI(){
  //---------------------------

  delete gui_tab;
  delete gui_control;

  //---------------------------
}

//Main function
void GUI::init(){
  //---------------------------

  gui_tab->create_panels();
  gui_gpu->init_gui_vulkan();
  gui_font->init_gui_font();
  gui_style->gui_style();
  gui_render->init();

  //---------------------------
}
void GUI::loop(){
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  this->docker_space_main();
  gui_tab->run_tab();
  gui_control->run_control();

  gui_gpu->render_frame();
  gui_render->loop();

  //---------------------------
}
void GUI::exit(){
  //---------------------------

  gui_gpu->clean_gui_vulkan();
  gui_render->clean();

  //---------------------------
}

//Subfunction
void GUI::docker_space_main(){
  //---------------------------

  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

  // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
  // because it would be confusing to have two docking targets within each others.
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowViewport(viewport->ID);

  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
  window_flags |= ImGuiWindowFlags_NoBackground;

  // Main dock space
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("dock_space_main", nullptr, window_flags);
  ImGui::PopStyleVar(3);

  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable){
  	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
  	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
  }

  ImGui::End();

  //---------------------------
}
