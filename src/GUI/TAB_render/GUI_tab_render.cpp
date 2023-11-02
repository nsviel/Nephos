#include "GUI_tab_render.h"
#include "Engine/GUI_camera.h"
#include "Menu/GUI_render_menu.h"
#include "GUI_render_panel.h"
#include "Engine/GUI_engine.h"
#include "Data/GUI_object.h"
#include "Data/GUI_scene.h"
#include "Data/GUI_set.h"
#include "Profiler/GUI_profiler.h"
#include "Shader/GUI_shader.h"
#include "Data/GUI_scene.h"
#include "Menu/GUI_render_option.h"
#include "GUI_render_panel.h"

#include <GUI.h>
#include <Engine.h>
#include <Data/Load/Loader.h>
#include <Widget/GUI_indicator.h>
#include <Editor/GUI_editor_node.h>
#include <Data/GUI_database.h>
#include <Capture/GUI_capture.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
GUI_tab_render::GUI_tab_render(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->gui_render_panel = new GUI_render_panel();

  //---------------------------
}
GUI_tab_render::~GUI_tab_render(){}

//Main function
void GUI_tab_render::create_panels(){
  //---------------------------

  this->gui_engine = new GUI_engine(gui);
  this->gui_render_option = new GUI_render_option(gui, &gui_render_panel->show_option, "Option");
  this->gui_object = new GUI_object(gui, &gui_render_panel->show_object, "Object");
  this->gui_set = new GUI_set(gui, &gui_render_panel->show_set, "Set");
  this->gui_profiler = new GUI_profiler(gui, &gui_render_panel->show_profiler, "Profiler");
  this->gui_shader = new GUI_shader(gui, &gui_render_panel->show_shader, "Shader");
  this->gui_scene = new GUI_scene(gui, &gui_render_panel->show_scene, "Scene");
  this->gui_capture = new GUI_capture(gui, &gui_render_panel->show_capture, "Capture");
  this->gui_camera = new GUI_camera(gui, &gui_render_panel->show_camera, "Camera");
  this->gui_database = new GUI_database(gui, &gui_render_panel->show_database, "Database##4323");
  this->gui_render_menu = new GUI_render_menu(gui);

  //---------------------------
}
void GUI_tab_render::draw_panels(){
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
void GUI_tab_render::open_panels(){
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
