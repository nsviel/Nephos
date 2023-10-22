#include "GUI_render.h"
#include "GUI_render_menu.h"
#include "GUI_render_panel.h"

#include <GUI.h>
#include <Tab/Render/GUI_render_panel.h>
#include <Data/Load/Loader.h>
#include <Style/Widget/GUI_indicator.h>
#include <Tab/Render/GUI_render_option.h>

#include <Element/Editor/GUI_editor_node.h>
#include <Element/Data/GUI_database.h>
#include <Element/Capture/GUI_capture.h>

#include <Engine.h>
#include <Engine/GUI_engine.h>
#include <Engine/Data/GUI_object.h>
#include <Engine/Data/GUI_scene.h>
#include <Engine/Data/GUI_set.h>
#include <Engine/GUI_engine.h>
#include <Engine/Profiler/GUI_profiler.h>
#include <Engine/Render/GUI_shader.h>
#include <Engine/Data/GUI_scene.h>
#include <Engine/Camera/GUI_camera.h>


//Constructor / Destructor
GUI_render::GUI_render(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->gui_render_panel = new GUI_render_panel();

  //---------------------------
}
GUI_render::~GUI_render(){}

//Main function
void GUI_render::create_panels(){
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
void GUI_render::draw_panels(){
  //---------------------------

  gui_render_menu->design_menubar();
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
void GUI_render::open_panels(){
  //---------------------------

  ImGui::Checkbox("Option##456", &gui_render_panel->show_option);
  ImGui::Checkbox("Scene##456", &gui_render_panel->show_scene);
  ImGui::Checkbox("Database##456", &gui_render_panel->show_database);
  ImGui::Checkbox("Profiler##456", &gui_render_panel->show_profiler);
  ImGui::Checkbox("Camera##456", &gui_render_panel->show_camera);
  ImGui::Checkbox("Shader##456", &gui_render_panel->show_shader);
  ImGui::Checkbox("Capture##456", &gui_render_panel->show_capture);

  //---------------------------
}
