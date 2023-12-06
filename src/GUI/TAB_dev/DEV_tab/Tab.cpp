#include "Tab.h"

#include <GUI.h>
#include <TAB_dev/DEV_nsp.h>



namespace dev{

//Constructor / Destructor
Tab::Tab(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->panel = new dev::Panel();
  this->menu = new dev::Menu(panel);
  this->database = new dev::Database(gui, &panel->show_database, "Database##4323");

  //---------------------------
}
Tab::~Tab(){}

//Main function
void Tab::create_panels(){
  //---------------------------

  static bool truc = true;
  panel->vec_editor.push_back(new dev::Editor(gui, &truc, "Editor"));
  this->command = new dev::Command(gui);

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
