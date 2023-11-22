#include "GUI_gpu.h"

#include <GUI.h>
#include <VK_main/Struct_vulkan.h>
#include <Vulkan.h>
#include <VK_main/VK_imgui.h>
#include <UTL_window/UTL_window.h>
#include <GUI_main/GUI_render/GUI_render.h>


//Constructor / Destructor
GUI_gpu::GUI_gpu(GUI* gui){
  //---------------------------

  GUI_render* gui_render = gui->get_gui_render();
  Vulkan* vulkan = gui_render->get_vulkan();
  this->vk_imgui = vulkan->get_vk_imgui();

  //---------------------------
}
GUI_gpu::~GUI_gpu(){}

//Main function
void GUI_gpu::init_vulkan(){
  //---------------------------

  vk_imgui->init();

  //---------------------------
}
void GUI_gpu::clean_vulkan(){
  //---------------------------

  vk_imgui->clean();

  //---------------------------
}

//Render function
void GUI_gpu::render_frame(){
  //---------------------------

  ImGui::Render();

  //---------------------------
}
