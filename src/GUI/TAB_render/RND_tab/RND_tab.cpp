#include "RND_tab.h"

#include <GUI.h>
#include <Engine.h>
#include <ENG_data/ENG_load/ENG_loader.h>
#include <GUI_widget/GUI_indicator.h>
#include <GUI_editor/EDI_node.h>
#include <RND_engine/RND_camera.h>
#include <RND_tab/RND_menu.h>
#include <RND_tab/RND_panel.h>
#include <RND_profiler/RND_profiler.h>
#include <RND_shader/RND_shader.h>
#include <RND_tab/RND_option.h>
#include <TAB_render/Panel_nsp.h>
#include <RND_kinect/RND_kinect.h>
#include <RND_kinect/RND_capture.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
RND_tab::RND_tab(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->gui_render_panel = new RND_panel();

  //---------------------------
}
RND_tab::~RND_tab(){}

//Main function
void RND_tab::create_panels(){
  //---------------------------

  this->rnd_option = new RND_option(gui, &gui_render_panel->show_option, "Option");
  this->rnd_object = new gui::rnd::panel::Object(gui, &gui_render_panel->show_object, "data::Object");
  this->rnd_set = new gui::rnd::panel::Set(gui, &gui_render_panel->show_set, "Set");
  this->rnd_profiler = new RND_profiler(gui, &gui_render_panel->show_profiler, "Profiler");
  this->rnd_shader = new RND_shader(gui, &gui_render_panel->show_shader, "Shader");
  this->rnd_scene = new gui::rnd::panel::Scene(gui, &gui_render_panel->show_scene, "Scene");
  this->rnd_camera = new RND_camera(gui, &gui_render_panel->show_engine_camera, "Camera");
  this->rnd_kinect = new RND_kinect(gui, &gui_render_panel->show_kinect, "Kinect");
  this->rnd_capture = new RND_capture(gui, &gui_render_panel->show_capture, "Capture");
  this->rnd_render = new gui::rnd::panel::Render(gui);
  this->rnd_menu = new RND_menu(gui);

  //---------------------------
}
void RND_tab::draw_panels(){
  //---------------------------

  rnd_menu->run_tab_menu();
  rnd_shader->run_panel();
  rnd_camera->run_panel();
  rnd_object->run_panel();
  rnd_set->run_panel();
  rnd_kinect->run_panel();
  rnd_capture->run_panel();
  rnd_scene->run_panel();
  rnd_profiler->run_panel();
  rnd_option->run_panel();
  rnd_render->design_panel();

  //---------------------------
}
void RND_tab::open_panels(){
  //---------------------------

  ImGui::Checkbox(ICON_FA_COG " Option##456", &gui_render_panel->show_option);
  ImGui::Checkbox(ICON_FA_PLAY " Scene##456", &gui_render_panel->show_scene);
  ImGui::Checkbox(ICON_FA_REFRESH " Profiler##456", &gui_render_panel->show_profiler);
  ImGui::Checkbox(ICON_FA_CAMERA " Camera##456", &gui_render_panel->show_engine_camera);
  ImGui::Checkbox(ICON_FA_ROAD " Shader##456", &gui_render_panel->show_shader);
  ImGui::Checkbox(ICON_FA_FILM " Kinect##456", &gui_render_panel->show_kinect);

  //---------------------------
}
