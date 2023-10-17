#include "GUI_panel.h"
#include "Panel.h"
#include "../Engine/GUI_engine.h"
#include "../Element/Editor/GUI_editor_node.h"
#include "../Element/Data/GUI_database.h"
#include "../Element/Capture/GUI_capture.h"
#include "../Style/Widget/GUI_indicator.h"
#include "../Window/Menu/GUI_mainmenubar.h"
#include "../Engine/Profiler/GUI_timing.h"
#include "../Engine/Render/GUI_shader.h"
#include "../Engine/Data/GUI_scene.h"
#include "../Engine/Camera/GUI_camera.h"
#include "../Engine/Data/GUI_object.h"
#include "../Engine/Data/GUI_set.h"
#include "../GUI.h"

#include <Panel/Panel.h>
#include <GUI.h>
#include <Engine.h>
#include <Data/Load/Loader.h>


//Constructor / Destructor
GUI_panel::GUI_panel(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->panel = gui->get_panel();

  this->gui_scene = gui->get_gui_scene();
  this->gui_timing = gui->get_gui_profiling();
  this->gui_menubar = gui->get_gui_menubar();
  this->gui_shader = gui->get_gui_shader();
  this->gui_engine = gui->get_gui_engine();
  this->gui_camera = gui->get_gui_camera();
  this->gui_object = gui->get_gui_object();
  this->gui_set = gui->get_gui_set();
  this->gui_capture = gui->get_gui_capture();
  this->gui_database = new GUI_database(gui, &panel->show_database, "Database##4323");

  //---------------------------
}
GUI_panel::~GUI_panel(){}

//Main function
void GUI_panel::draw_panels(){
  //---------------------------


  gui_shader->run_panel();
  gui_timing->design_panel();
  gui_engine->design_panel();
  gui_database->run_panel();
  gui_scene->design_panel();
  gui_camera->run_panel();
  gui_object->run_panel();
  gui_set->run_panel();
  gui_capture->run_panel();

  //---------------------------
}

//Subfunction
void GUI_panel::set_initial_panel_focus(){
  //---------------------------

  ImGui::SetWindowFocus("Object");

  //---------------------------
}
