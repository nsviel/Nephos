#include "GUI_engine.h"

#include <Engine.h>
#include <GUI.h>
#include <Element/Control/GUI_control_engine.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>
#include <image/IconsFontAwesome5.h>


//Constructor / Destructor
GUI_engine::GUI_engine(GUI* gui){
  //---------------------------

  Engine* engine = gui->get_engine();
  VK_engine* vk_engine = engine->get_vk_engine();
  this->vk_struct = vk_engine->get_vk_struct();
  this->gui_control = new GUI_control_engine(gui);

  //---------------------------
}
GUI_engine::~GUI_engine(){}

//Main function
void GUI_engine::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  if(ImGui::Begin("Engine", NULL)){ //ImGuiWindowFlags_MenuBar
    //this->engine_menubar();
    this->engine_window();
    ImGui::End();
  }
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void GUI_engine::engine_menubar(){
  //---------------------------

  if(ImGui::BeginMenuBar()){
    if(ImGui::BeginMenu("Load")){
      //loaderManager->load_by_zenity();
      ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Init")){
      //gui_init->design_init();
      ImGui::EndMenu();
    }
    if(ImGui::BeginMenu(ICON_FA_COG, "Option")){
      //gui_render_option->design_option();
      ImGui::EndMenu();
    }
    if(ImGui::MenuItem(ICON_FA_CAMERA, "Camera##111")){
      //gui_render_panel->show_camera = !gui_render_panel->show_camera;
    }
    ImGui::EndMenuBar();
  }



  //---------------------------
}
void GUI_engine::engine_window(){
  //---------------------------

  //Vraiment deguelasse,a changer au plus vite !!
  static ImVec2 previous_size;
  ImVec2 current_size = ImGui::GetWindowSize();
  if (current_size.x != previous_size.x || current_size.y != previous_size.y){
    has_been_initialized = false;
    previous_size = current_size;
  }

  if(has_been_initialized == false){
    for(int i=0; i<vk_struct->nb_frame; i++){
      Frame* frame_edl = vk_struct->renderpass_edl.get_rendering_frame();
      Struct_image* image = &frame_edl->color;
      this->descriptor = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    }
    has_been_initialized = true;
  }

  Frame* frame_edl = vk_struct->renderpass_edl.get_rendering_frame();
  Struct_image* image = &frame_edl->color;
  this->descriptor = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(descriptor, ImVec2{viewportPanelSize.x, viewportPanelSize.y});

  if(ImGui::IsItemHovered()){
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 center = ImVec2(windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f);

    gui_control->run_control(center);
  }

  //---------------------------
}
