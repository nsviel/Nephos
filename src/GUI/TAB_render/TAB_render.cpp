#include "TAB_render.h"
#include "RND_engine/PAN_camera.h"
#include "RND_menu/RND_menu.h"
#include "RND_config/RND_panel.h"
#include "RND_engine/RND_engine.h"
#include "RND_data/PAN_object.h"
#include "RND_data/PAN_scene.h"
#include "RND_data/PAN_set.h"
#include "RND_profiler/GUI_profiler.h"
#include "RND_shader/RND_shader.h"
#include "RND_data/PAN_scene.h"
#include "RND_menu/RND_option.h"

#include <GUI.h>
#include <Engine.h>
#include <ENG_data/ENG_load/Loader.h>
#include <RES_widget/GUI_indicator.h>
#include <RES_editor/EDI_node.h>
#include <RES_data/GUI_database.h>
#include <RES_capture/GUI_capture.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
TAB_render::TAB_render(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->gui_render_panel = new RND_panel();

  //---------------------------
}
TAB_render::~TAB_render(){}

//Main function
void TAB_render::create_panels(){
  //---------------------------

  this->gui_engine = new RND_engine(gui);
  this->gui_render_option = new RND_option(gui, &gui_render_panel->show_option, "Option");
  this->gui_object = new PAN_object(gui, &gui_render_panel->show_object, "Object");
  this->gui_set = new PAN_set(gui, &gui_render_panel->show_set, "Set");
  this->gui_profiler = new GUI_profiler(gui, &gui_render_panel->show_profiler, "Profiler");
  this->gui_shader = new RND_shader(gui, &gui_render_panel->show_shader, "Shader");
  this->gui_scene = new PAN_scene(gui, &gui_render_panel->show_scene, "Scene");
  this->gui_capture = new GUI_capture(gui, &gui_render_panel->show_capture, "Capture");
  this->gui_camera = new PAN_camera(gui, &gui_render_panel->show_camera, "Camera");
  this->gui_database = new GUI_database(gui, &gui_render_panel->show_database, "Database##4323");
  this->gui_render_menu = new RND_menu(gui);

  //---------------------------
}
void TAB_render::draw_panels(){
  //---------------------------

  gui_render_menu->run_tab_menu();
  gui_shader->run_panel();
  gui_database->run_panel();
  gui_camera->run_panel();
  gui_object->run_panel();
  gui_set->run_panel();
  gui_capture->run_panel();
  gui_scene->run_panel();
  gui_profiler->run_panel();
  gui_render_option->run_panel();
  gui_engine->design_panel();

  //---------------------------
}
void TAB_render::open_panels(){
  //---------------------------

  ImGui::Checkbox(ICON_FA_COG " Option##456", &gui_render_panel->show_option);
  ImGui::Checkbox(ICON_FA_PLAY " Scene##456", &gui_render_panel->show_scene);
  ImGui::Checkbox(ICON_FA_KEY " Database##456", &gui_render_panel->show_database);
  ImGui::Checkbox(ICON_FA_REFRESH " Profiler##456", &gui_render_panel->show_profiler);
  ImGui::Checkbox(ICON_FA_CAMERA " Camera##456", &gui_render_panel->show_camera);
  ImGui::Checkbox(ICON_FA_ROAD " Shader##456", &gui_render_panel->show_shader);
  ImGui::Checkbox(ICON_FA_FILM " Capture##456", &gui_render_panel->show_capture);

  //---------------------------
}
