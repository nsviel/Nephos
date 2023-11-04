#include "GUI_gpu.h"

#include <GUI.h>
#include <Engine.h>
#include <VK_struct/struct_vulkan.h>
#include <VK_engine.h>
#include <VK_drawing/VK_drawing.h>
#include <VK_drawing/DR_ui.h>
#include <ELE_window/Window.h>


//Constructor / Destructor
GUI_gpu::GUI_gpu(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  this->vk_engine = engine->get_vk_engine();
  VK_drawing* vk_drawing = vk_engine->get_vk_drawing();
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->ui_drawing = vk_drawing->get_ui_drawing();

  //---------------------------
}
GUI_gpu::~GUI_gpu(){}

//Main function
void GUI_gpu::init_gui_vulkan(){
  //---------------------------

  vk_engine->imgui_init();

  //---------------------------
}
void GUI_gpu::clean_gui_vulkan(){
  //---------------------------

  vk_engine->imgui_clean();

  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  //---------------------------
}

//Render function
void GUI_gpu::render_frame(){
  //---------------------------

  ImGui::Render();
  this->draw_data = ImGui::GetDrawData();
  ui_drawing->set_imgui_drawdata(draw_data);

  //---------------------------
}
