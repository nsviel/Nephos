#include "Tab.h"

#include <GUI.h>
#include <Engine.h>
#include <ENG_data/ENG_load/ENG_loader.h>
#include <GUI_utility/Widget/GUI_indicator.h>
#include <TAB_render/Data/Namespace.h>
#include <image/IconsFontAwesome5.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Tab::Tab(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->gui_render_panel = new Panel();

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::create_panels(){
  //---------------------------

  this->rnd_option = new gui::rnd::tab::Option(gui, &gui_render_panel->show_option, "Option");
  this->rnd_object = new gui::rnd::panel::Object(gui, &gui_render_panel->show_object, "data::Object");
  this->rnd_set = new gui::rnd::panel::Set(gui, &gui_render_panel->show_set, "Set");
  this->rnd_profiler = new gui::engine::Profiler(gui, &gui_render_panel->show_profiler, "Profiler");
  this->rnd_shader = new gui::engine::Shader(gui, &gui_render_panel->show_shader, "Shader");
  this->rnd_scene = new gui::rnd::panel::Scene(gui, &gui_render_panel->show_scene, "Scene");
  this->rnd_camera = new gui::engine::Camera(gui, &gui_render_panel->show_engine_camera, "Camera");
  this->rnd_kinect = new gui::kinect::Kinect_panel(gui, &gui_render_panel->show_kinect, "Kinect");
  this->rnd_capture = new gui::kinect::Capture(gui, &gui_render_panel->show_capture, "Capture");
  this->rnd_render = new gui::engine::Render(gui);
  this->rnd_menu = new gui::rnd::tab::Menu(gui);

  //---------------------------
}
void Tab::draw_panels(){
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
void Tab::open_panels(){
  //---------------------------

  ImGui::Checkbox(ICON_FA_COG " Option##456", &gui_render_panel->show_option);
  ImGui::Checkbox(ICON_FA_PLAY " Scene##456", &gui_render_panel->show_scene);
  ImGui::Checkbox(ICON_FA_REFRESH " Profiler##456", &gui_render_panel->show_profiler);
  ImGui::Checkbox(ICON_FA_CAMERA " Camera##456", &gui_render_panel->show_engine_camera);
  ImGui::Checkbox(ICON_FA_ROAD " Shader##456", &gui_render_panel->show_shader);
  ImGui::Checkbox(ICON_FA_FILM " Kinect_panel##456", &gui_render_panel->show_kinect);

  //---------------------------
}

}
