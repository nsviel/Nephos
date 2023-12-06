#include "DEV_tab.h"
#include "DEV_nsp.h"

#include <GUI.h>
#include <TAB_dev/DEV_editor/Editor.h>
#include <TAB_dev/DEV_command/DEV_command.h>
#include <TAB_dev/DEV_data/Database.h>
#include <TAB_dev/DEV_utility/Menu.h>
#include <TAB_dev/DEV_utility/Panel.h>



//Constructor / Destructor
DEV_tab::DEV_tab(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->panel = new dev::Panel();
  this->menu = new dev::Menu(panel);
  this->database = new dev::Database(gui, &panel->show_database, "Database##4323");

  //---------------------------
}
DEV_tab::~DEV_tab(){}

//Main function
void DEV_tab::create_panels(){
  //---------------------------

  static bool truc = true;
  panel->vec_editor.push_back(new dev::Editor(gui, &truc, "Editor"));
  this->dev_command = new dev::DEV_command(gui);

  //---------------------------
}
void DEV_tab::draw_panels(){
  //---------------------------

  menu->run_tab_menu();
  panel->run_editors();
  dev_command->run_panel();
  database->run_panel();

  //---------------------------
}
