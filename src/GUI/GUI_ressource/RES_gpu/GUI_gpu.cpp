#include "GUI_gpu.h"

#include <GUI.h>
#include <VK_main/Struct_vulkan.h>
#include <Vulkan.h>
#include <VK_main/VK_imgui.h>
#include <ELE_window/ELE_window.h>
#include <GUI_main/GUI_render/GUI_render.h>


//Constructor / Destructor
GUI_gpu::GUI_gpu(GUI* gui){
  //---------------------------

  GUI_render* gui_render = gui->get_gui_render();
  Vulkan* gui_vulkan = gui_render->get_gui_vulkan();
  this->vk_imgui = gui_vulkan->get_vk_imgui();

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
