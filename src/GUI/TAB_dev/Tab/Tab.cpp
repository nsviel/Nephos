#include "Tab.h"

#include <GUI.h>


namespace gui::dev::tab{

//Constructor / Destructor
Tab::Tab(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->panel = new gui::dev::tab::Panel();
  this->menu = new gui::dev::tab::Menu(panel);
  this->database = new gui::dev::data::Database(gui, &panel->show_database, "Database##4323");

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::create_panels(){
  //---------------------------

  static bool truc = true;
  panel->vec_editor.push_back(new gui::dev::editor::Editor(gui, &truc, "Editor"));
  this->command = new gui::dev::editor::Command(gui);

  //---------------------------
}
void Tab::draw_panels(){
  //---------------------------

  menu->run_tab_menu();
  panel->run_editors();
  command->run_panel();
  database->run_panel();

  //---------------------------
}

}
