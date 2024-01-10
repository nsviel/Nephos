#include "Panel.h"

#include <GUI.h>


namespace gui::dev::tab{

//Constructor / Destructor
Panel::Panel(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->menu = new gui::dev::tab::Menu(this);
  this->database = new gui::dev::data::Database(gui, &show_database, "Database##4323");

  //---------------------------
}
Panel::~Panel(){}

//Main function
void Panel::create_panels(){
  //---------------------------

  static bool truc = true;
  this->vec_editor.push_back(new gui::dev::editor::Editor(gui, &truc, "Editor"));
  this->command = new gui::dev::editor::Command(gui);

  //---------------------------
}
void Panel::draw_panels(){
  //---------------------------

  menu->run_tab_menu();
  this->run_editors();
  command->run_panel();
  database->run_panel();

  //---------------------------
}

//Subfunction
void Panel::run_editors(){
  //---------------------------

  for(int i=0; i<vec_editor.size(); i++){
    gui::dev::editor::Editor* editor = vec_editor[i];
    editor->run_panel();
  }

  //---------------------------
}

}
