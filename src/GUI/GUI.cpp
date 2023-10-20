#include "GUI.h"
#include "GPU/GUI_gpu.h"
#include "GPU/GUI_image.h"
#include "GPU/GUI_video.h"
#include "Panel/Panel.h"
#include "Panel/GUI_panel.h"
#include "Element/Initialization/GUI_init.h"
#include "Element/Capture/GUI_capture.h"
#include "Window/Window.h"
#include "Window/Menu/GUI_mainmenubar.h"

#include "Control/GUI_control_engine.h"
#include "Style/GUI_style.h"
#include "Engine/GUI_engine.h"
#include "Engine/Camera/GUI_camera.h"
#include "Engine/Data/GUI_object.h"
#include "Engine/Data/GUI_set.h"
#include "Engine/Profiler/GUI_profiler.h"
#include "Engine/Render/GUI_shader.h"
#include "Engine/Data/GUI_scene.h"

#include <Engine.h>
#include <GPU/GPU_render.h>
#include <Vulkan/VK_engine.h>


//Constructor / Destructor
GUI::GUI(Window* window, Engine* engine){
  //---------------------------

  this->engine = engine;
  this->window = window;
  this->data = engine->get_data();

  this->gui_image = new GUI_image(engine);
  this->gui_video = new GUI_video(engine);
  this->gui_init = new GUI_init(this);
  this->gui_control = new GUI_control_engine(this);
  this->gui_style = new GUI_style(this);
  this->gui_panel = new GUI_panel(this);
  this->gui_menubar = new GUI_mainmenubar(this);
  this->gui_gpu = new GUI_gpu(engine);

  //---------------------------
}
GUI::~GUI(){
  //---------------------------

  delete gui_panel;
  delete gui_control;

  //---------------------------
}

//Main function
void GUI::init(){
  //---------------------------

  gui_panel->create_panels();
  gui_gpu->init_gui();
  gui_style->gui_style();

  //---------------------------
}
void GUI::loop(){
  VK_engine* vk_engine = engine->get_vk_engine();
  GPU_render* gpu_render = vk_engine->get_gpu_gui();
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  this->docker_space_main();
  gui_menubar->design_menubar();
  gui_panel->draw_panels();

  gui_gpu->render_frame();

  //---------------------------
}
void GUI::exit(){
  //---------------------------

  gui_gpu->clean_gui();

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
