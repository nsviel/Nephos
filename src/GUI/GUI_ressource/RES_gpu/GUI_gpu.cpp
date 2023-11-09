#include "GUI_gpu.h"

#include <GUI.h>
#include <Engine.h>
#include <VK_struct/Struct_vulkan.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_imgui.h>
#include <ELE_window/ELE_window.h>
#include <GUI_main/GUI_render/GUI_render.h>


//Constructor / Destructor
GUI_gpu::GUI_gpu(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  VK_engine* vk_engine = engine->get_vk_engine();

  GUI_render* gui_render = gui->get_gui_render();
  //VK_engine* vk_engine = gui_render->get_vk_engine();
  this->vk_imgui = vk_engine->get_vk_imgui();

  //---------------------------
}
GUI_gpu::~GUI_gpu(){}

//Main function
void GUI_gpu::init_gui_vulkan(){
  //---------------------------

  vk_imgui->init();

  //---------------------------
}
void GUI_gpu::clean_gui_vulkan(){
  //---------------------------

  vk_imgui->clean();

  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  //---------------------------
}

//Render function
void GUI_gpu::render_frame(){
  //---------------------------

  ImGui::Render();

  //---------------------------
}
