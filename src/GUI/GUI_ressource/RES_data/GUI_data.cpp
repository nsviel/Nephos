#include "GUI_data.h"

#include <Engine.h>
#include <VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <GUI.h>


//Constructor / Destructor
GUI_data::GUI_data(GUI* gui){
  //---------------------------

  this->gui = gui;
  Engine* engine = gui->get_engine();
  this->vk_engine = engine->get_vk_engine();
  this->vk_struct = vk_engine->get_vk_struct();

  this->width = 150;

  //---------------------------
}
GUI_data::~GUI_data(){}

//Main function
void GUI_data::design_data(){
  //---------------------------



  //---------------------------
}

//Subfunctions
