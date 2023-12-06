#include "RND_tab.h"

#include <GUI.h>
#include <Engine.h>
#include <ENG_data/ENG_load/ENG_loader.h>
#include <GUI_widget/GUI_indicator.h>
#include <GUI_editor/EDI_node.h>
#include <RND_engine/RND_camera.h>
#include <RND_menu/RND_menu.h>
#include <RND_config/RND_panel.h>
#include <RND_engine/RND_engine.h>
#include <RND_profiler/GUI_profiler.h>
#include <RND_shader/RND_shader.h>
#include <RND_menu/RND_option.h>
#include <RND_data/RND_object.h>
#include <RND_data/RND_scene.h>
#include <RND_data/RND_set.h>
#include <RND_kinect/GUI_kinect.h>
#include <RND_kinect/KIN_capture.h>
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
  this->rnd_object = new RND_object(gui, &gui_render_panel->show_object, "Object");
  this->rnd_set = new RND_set(gui, &gui_render_panel->show_set, "Set");
  this->gui_profiler = new GUI_profiler(gui, &gui_render_panel->show_profiler, "Profiler");
  this->rnd_shader = new RND_shader(gui, &gui_render_panel->show_shader, "Shader");
  this->rnd_scene = new RND_scene(gui, &gui_render_panel->show_scene, "Scene");
  this->rnd_camera = new RND_camera(gui, &gui_render_panel->show_engine_camera, "Camera");
  this->gui_kinect = new GUI_kinect(gui, &gui_render_panel->show_kinect, "Kinect");
  this->gui_capture = new KIN_capture(gui, &gui_render_panel->show_capture, "Capture");
  this->rnd_engine = new RND_engine(gui);
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
  gui_kinect->run_panel();
  gui_capture->run_panel();
  rnd_scene->run_panel();
  gui_profiler->run_panel();
  rnd_option->run_panel();
  rnd_engine->design_panel();

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
