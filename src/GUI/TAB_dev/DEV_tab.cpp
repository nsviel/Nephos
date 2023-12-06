#include "DEV_tab.h"
#include "DEV_config/DEV_panel.h"

#include <GUI.h>
#include <TAB_dev/DEV_editor/DEV_code_editor.h>
#include <TAB_dev/DEV_command/DEV_command.h>
#include <TAB_dev/DEV_database/DEV_database.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
DEV_tab::DEV_tab(GUI* gui){
  //---------------------------

  this->gui = gui;
  this->dev_panel = new DEV_panel();
  this->dev_database = new DEV_database(gui, &dev_panel->show_database, "Database##4323");

  //---------------------------
}
DEV_tab::~DEV_tab(){}

//Main function
void DEV_tab::create_panels(){
  //---------------------------

  static bool truc = true;
  dev_panel->vec_editor.push_back(new DEV_code_editor(gui, &truc, "Editor"));
  this->dev_command = new DEV_command(gui);

  //---------------------------
}
void DEV_tab::draw_panels(){
  //---------------------------

  dev_panel->run_editors();
  dev_command->run_panel();
  dev_database->run_panel();

  //---------------------------
}
void DEV_tab::open_panels(){
  //---------------------------

  ImGui::Checkbox(ICON_FA_KEY " Database##456", &dev_panel->show_database);

  //---------------------------
}
