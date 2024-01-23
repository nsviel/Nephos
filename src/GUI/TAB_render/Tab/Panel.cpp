#include "Panel.h"

#include <GUI.h>
#include <image/IconsFontAwesome6.h>


namespace gui::rnd::tab{

//Constructor / Destructor
Panel::Panel(GUI* gui){
  //---------------------------

  this->gui = gui;

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::create_panels(){
  //---------------------------

  this->rnd_loader = new gui::rnd::data::Loader(gui, &show_loader, "Loader");
  this->rnd_scene = new gui::rnd::data::Scene(gui, &show_scene, "Scene");
  this->rnd_option = new gui::rnd::tab::Option(gui, &show_option, "Option");
  this->rnd_profiler = new gui::engine::Profiler(gui, &show_profiler, "Profiler");
  this->rnd_shader = new gui::engine::Shader(gui, &show_shader, "Shader");
  this->rnd_camera = new camera::gui::Camera(gui->get_engine(), &show_camera, "Camera");
  //this->rnd_kinect = new gui::kinect::Device(gui->get_engine(), &show_kinect, "Player");
  //this->rnd_stream = new gui::kinect::Stream(gui->get_engine(), &show_kinect, "Stream");
  this->rnd_render = new gui::engine::Renderer(gui);
  this->rnd_menu = new gui::rnd::tab::Menu(this);

  //---------------------------
}
void Panel::draw_panels(){
  //---------------------------

  rnd_menu->run_tab_menu();
  rnd_loader->run_panel();
  rnd_shader->run_panel();
  rnd_camera->run_panel();
  //rnd_kinect->run_panel();
  //rnd_stream->run_panel();
  rnd_scene->run_panel();
  rnd_profiler->run_panel();
  rnd_option->run_panel();
  rnd_render->design_panel();

  //---------------------------
}
void Panel::open_panels(){
  //---------------------------

  ImGui::Checkbox(ICON_FA_FOLDER " Loader##456", &show_loader);
  ImGui::Checkbox(ICON_FA_COG " Option##456", &show_option);
  ImGui::Checkbox(ICON_FA_PLAY " Scene##456", &show_scene);
  ImGui::Checkbox(ICON_FA_ARROW_ROTATE_RIGHT " Profiler##456", &show_profiler);
  ImGui::Checkbox(ICON_FA_CAMERA " Camera##456", &show_camera);
  ImGui::Checkbox(ICON_FA_ROAD " Shader##456", &show_shader);
  ImGui::Checkbox(ICON_FA_FILM " Kinect##456", &show_kinect);

  //---------------------------
}

}
