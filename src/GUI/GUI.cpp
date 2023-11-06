#include "GUI.h"
#include "ELE_window/Window.h"

#include <Engine.h>
#include <VK_main/VK_engine.h>
#include <GUI_tab/GUI_tab.h>
#include <RES_gpu/GUI_gpu.h>
#include <GUI_control/GUI_control_gui.h>
#include <GUI_style/GUI_style.h>
#include <GUI_style/GUI_font.h>
#include <TAB_render/RND_engine/RND_engine.h>
#include <TAB_render/RND_engine/PAN_camera.h>
#include <TAB_render/RND_data/PAN_object.h>
#include <TAB_render/RND_data/PAN_set.h>
#include <TAB_render/RND_profiler/GUI_profiler.h>
#include <TAB_render/RND_shader/RND_shader.h>
#include <TAB_render/RND_data/PAN_scene.h>
#include <TAB_render/RND_initialization/RND_init.h>
#include <RES_capture/GUI_capture.h>


//Constructor / Destructor
GUI::GUI(Window* window, Engine* engine){
  //---------------------------

  this->engine = engine;
  this->window = window;
  this->eng_data = engine->get_eng_data();

  this->gui_init = new RND_init(this);
  this->gui_style = new GUI_style(this);
  this->gui_font = new GUI_font(this);
  this->gui_tab = new GUI_tab(this);
  this->gui_gpu = new GUI_gpu(this);
  this->gui_control = new GUI_control_gui(this);

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

  //---------------------------
}
void GUI::exit(){
  //---------------------------

  gui_gpu->clean_gui_vulkan();

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
