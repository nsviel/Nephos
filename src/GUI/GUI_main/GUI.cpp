#include "GUI.h"

#include <Engine.h>
#include <Utility.h>
#include <UTL_window/UTL_window.h>
#include <GUI_image/GUI_gpu.h>
#include <GUI_interface/GUI_tab.h>
#include <GUI_interface/GUI_docking.h>
#include <GUI_control/GUI_control.h>
#include <GUI_render/GUI_render.h>
#include <GUI_style/GUI_style.h>
#include <GUI_style/GUI_font.h>
#include <GUI_main/GUI_render/GUI_render.h>


//Constructor / Destructor
GUI::GUI(Utility* utility, Engine* engine){
  //---------------------------

  this->engine = engine;
  this->utility = utility;
  this->utl_window = utility->get_utl_window();

  this->gui_render = new GUI_render(this);
  this->gui_style = new GUI_style(this);
  this->gui_font = new GUI_font(this);
  this->gui_tab = new GUI_tab(this);
  this->gui_gpu = new GUI_gpu(this);
  this->gui_control = new GUI_control(this);
  this->gui_docking = new GUI_docking(this);

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

  gui_render->init();
  gui_tab->create_panels();
  gui_gpu->init_vulkan();
  gui_font->init_gui_font();
  gui_style->gui_style();

  //---------------------------
}
void GUI::loop(){
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  gui_docking->docker_space_main();
  gui_tab->run_tab();
  gui_control->run_control();

  gui_gpu->render_frame();
  gui_render->loop();

  //---------------------------
}
void GUI::exit(){
  //---------------------------

  gui_gpu->clean_vulkan();
  gui_render->clean();

  //---------------------------
}
void GUI::wait(){
  //---------------------------

  gui_render->wait();

  //---------------------------
}
