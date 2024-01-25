#include "Panel.h"

#include <GUI.h>
#include <image/IconsFontAwesome6.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Operation/Namespace.h>


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

  //this->rnd_loader = new eng::scene::gui::Loader(gui->get_engine(), &show_loader, "Loader");
  //this->rnd_scene = new eng::scene::gui::Scene(gui->get_engine(), &show_scene, "Scene");
  this->rnd_option = new gui::rnd::tab::Option(gui, &show_option, "Option");
  this->rnd_profiler = new eng::ope::gui::Profiler(gui->get_engine(), &show_profiler, "Profiler");
  this->rnd_shader = new eng::render::gui::Shader(gui, &show_shader, "Shader");
  this->rnd_render = new eng::render::gui::Renderer(gui->get_engine());
  this->rnd_menu = new gui::rnd::tab::Menu(this);

  //---------------------------
}
void Panel::draw_panels(){
  //---------------------------

  rnd_menu->run_tab_menu();
  rnd_shader->run_panel();
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
