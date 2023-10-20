#include "GUI_panel.h"
#include "Panel.h"

#include <GUI.h>
#include <Tab/Engine/Panel.h>
#include <Data/Load/Loader.h>
#include <Style/Widget/GUI_indicator.h>

#include <Window/Menu/GUI_mainmenubar.h>
#include <Window/Menu/GUI_option.h>

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
GUI_panel::GUI_panel(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->panel = new Panel();

  //---------------------------
}
GUI_panel::~GUI_panel(){}

//Main function
void GUI_panel::create_panels(){
  //---------------------------

  this->gui_engine = new GUI_engine(gui);
  this->gui_option = new GUI_option(gui, &panel->show_option, "Option");
  this->gui_object = new GUI_object(gui, &panel->show_object, "Object");
  this->gui_set = new GUI_set(gui, &panel->show_set, "Set");
  this->gui_profiler = new GUI_profiler(gui, &panel->show_profiler, "Profiler");
  this->gui_shader = new GUI_shader(gui, &panel->show_shader, "Shader");
  this->gui_scene = new GUI_scene(gui, &panel->show_scene, "Scene");
  this->gui_capture = new GUI_capture(gui, &panel->show_capture, "Capture");
  this->gui_camera = new GUI_camera(gui, &panel->show_camera, "Camera");
  this->gui_database = new GUI_database(gui, &panel->show_database, "Database##4323");

  //---------------------------
}
void GUI_panel::draw_panels(){
  //---------------------------

  gui_shader->run_panel();
  gui_database->run_panel();
  gui_camera->run_panel();
  gui_object->run_panel();
  gui_set->run_panel();
  gui_capture->run_panel();
  gui_scene->run_panel();
  gui_profiler->run_panel();
  gui_option->run_panel();

  gui_engine->design_panel();

  //---------------------------
}
void GUI_panel::open_panels(){
  //---------------------------

  ImGui::Checkbox("Option##456", &panel->show_option);
  ImGui::Checkbox("Scene##456", &panel->show_scene);
  ImGui::Checkbox("Database##456", &panel->show_database);
  ImGui::Checkbox("Profiler##456", &panel->show_profiler);
  ImGui::Checkbox("Camera##456", &panel->show_camera);
  ImGui::Checkbox("Shader##456", &panel->show_shader);
  ImGui::Checkbox("Capture##456", &panel->show_capture);

  //---------------------------
}
