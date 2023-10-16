#include "GUI.h"
#include "GPU/GUI_gpu.h"
#include "GPU/GUI_image.h"
#include "Panel/Panel.h"
#include "Panel/GUI_panel.h"
#include "Element/Editor/GUI_editor_node.h"
#include "Element/Initialization/GUI_init.h"
#include "Element/Capture/GUI_capture.h"
#include "Window/Window.h"
#include "Window/Menu/GUI_mainmenubar.h"
#include "Window/Menu/GUI_option.h"
#include "Window/Control/GUI_control.h"
#include "Style/GUI_style.h"
#include "Engine/GUI_engine.h"
#include "Engine/Camera/GUI_camera.h"
#include "Engine/Data/GUI_object.h"
#include "Engine/Data/GUI_set.h"
#include "Engine/Profiler/GUI_timing.h"
#include "Engine/Render/GUI_shader.h"
#include "Engine/Data/GUI_scene.h"

#include <Engine.h>
#include <GPU/GPU_render.h>
#include <Vulkan/VK_engine.h>


//Constructor / Destructor
GUI::GUI(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->window = window;
  this->data_node = engine->get_data();
  this->panel = new Panel();

  this->gui_image = new GUI_image(engine);
  this->gui_timing = new GUI_timing(this);
  this->gui_shader = new GUI_shader(this, &panel->show_shader, "Shader");
  this->gui_option = new GUI_option(this);
  this->gui_object = new GUI_object(this, &panel->show_object, "Object");
  this->gui_set = new GUI_set(this, &panel->show_set, "Set");
  this->gui_scene = new GUI_scene(this);
  this->gui_init = new GUI_init(this);
  this->gui_menubar = new GUI_mainmenubar(this);
  this->gui_control = new GUI_control(this);
  this->gui_engine = new GUI_engine(this);
  this->gui_style = new GUI_style(this);
  this->gui_capture = new GUI_capture(this, &panel->show_capture, "Capture");
  this->gui_camera = new GUI_camera(this, &panel->show_camera, "Camera");
  this->gui_panel = new GUI_panel(this);
  this->gui_gpu = new GUI_gpu(engine);

  //---------------------------
}
GUI::~GUI(){
  //---------------------------

  delete panel;
  delete gui_panel;
  delete gui_control;
  delete gui_option;
  delete gui_scene;
  delete gui_timing;

  //---------------------------
}

//Main function
void GUI::init(){
  //---------------------------

  gui_gpu->init_gui();
  gui_style->gui_style();
  gui_panel->set_initial_panel_focus();

  //---------------------------
}
void GUI::loop(){
  VK_engine* vk_engine = engine->get_vk_engine();
  GPU_render* gpu_render = vk_engine->get_gpu_gui();
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  gui_panel->draw_panels();

  gui_gpu->render_frame();

  //---------------------------
}
void GUI::exit(){
  //---------------------------

  gui_gpu->clean_gui();

  //---------------------------
}
