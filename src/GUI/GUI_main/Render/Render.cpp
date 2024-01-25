#include "Render.h"

#include <GUI.h>
#include <Engine/Node.h>
#include <Utility/Namespace.h>
#include <Vulkan/Namespace.h>


namespace gui{

//Constructor / Destructor
Render::Render(GUI* gui){
  //---------------------------

  utl::Node* utility = gui->get_node_utility();
  eng::Node* engine = gui->get_engine();
  utl::element::Window* utl_window = utility->get_utl_window();

  this->vulkan = engine->get_eng_vulkan();
  //this->vulkan = new Vulkan(utl_window);
  this->vk_engine = vulkan->get_vk_engine();
  this->gui_renderpass = new gui::Renderpass(vulkan);
  this->vk_imgui = vulkan->get_vk_imgui();

  //---------------------------
}
Render::~Render(){}

// Main code
void Render::init(){
  //---------------------------

  vk_imgui->init();

  //---------------------------
}
void Render::loop(){
  //---------------------------

  ImGui::Render();

  //---------------------------
}
void Render::clean(){
  //---------------------------

  vk_imgui->clean();

  //---------------------------
}
void Render::new_frame(){
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  //---------------------------
}

}
