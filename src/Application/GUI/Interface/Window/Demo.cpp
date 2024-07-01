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
void Demo::gui(){
  //---------------------------

  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Demo");

  //Demo window
  ImGui::Checkbox("Window", &show_demo);

  //Demo file
  if(ImGui::Button("Open file", ImVec2(120, 0))){
    this->open_demo_file();
  }

  //---------------------------
  ImGui::Separator();
}

//Subfunction
void Demo::open_demo_file(){
  //---------------------------

  int ret = system("xed ../extern/imgui/core/imgui_demo.cpp");

  //---------------------------
}

}
