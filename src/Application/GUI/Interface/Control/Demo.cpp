#include "Demo.h"

#include <GUI/Namespace.h>
#include <Utility/Namespace.h>
#include <imgui/core/imgui.h>
#include <iostream>


namespace gui::interface{

//Constructor / Destructor
Demo::Demo(gui::Node* gui){
  //---------------------------

  //---------------------------
}
Demo::~Demo(){}

//Main function
void Demo::loop(){
  //---------------------------

  if(show_demo){
    ImGui::ShowDemoWindow(&show_demo);
  }

  //---------------------------
}

//Subfunction
void Demo::open_demo_file(){
  //---------------------------

  int ret = system("xed ../extern/imgui/core/imgui_demo.cpp");

  //---------------------------
}

}
