#include "VK_drawing.h"

#include <VK_command/VK_cmd.h>
#include <VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <VK_drawing/DR_scene.h>
#include <VK_drawing/DR_edl.h>
#include <VK_drawing/DR_psr.h>
#include <VK_drawing/DR_ui.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_command/VK_submit.h>
#include <VK_command/VK_command.h>
#include <VK_presentation/VK_canvas.h>
#include <VK_binding/VK_descriptor.h>


//Constructor / Destructor
VK_drawing::VK_drawing(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_cmd = vk_engine->get_vk_cmd();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_submit = vk_engine->get_vk_submit();
  this->dr_scene = new DR_scene(vk_engine);
  this->dr_edl = new DR_edl(vk_engine);
  this->dr_psr = new DR_psr(vk_engine);
  this->dr_ui = new DR_ui(vk_engine);

  //---------------------------
}
VK_drawing::~VK_drawing(){}

//Main function
void VK_drawing::draw_frame(){
  Struct_submit_commands commands;
  timer_time t1 = timer.start_t();
  //---------------------------

  //Next image to draw
  vk_submit->acquire_next_image(&struct_vulkan->swapchain);

  //Drawing operations
  dr_scene->draw_scene(&struct_vulkan->renderpass_scene);


  dr_edl->draw_edl(&struct_vulkan->renderpass_edl);
  dr_ui->draw_ui(&struct_vulkan->renderpass_ui);

  //Submit drawn image
  vk_submit->submit_presentation(&struct_vulkan->swapchain);
  vk_submit->set_next_frame_ID(&struct_vulkan->swapchain);

  //---------------------------
  struct_vulkan->time.draw_frame.push_back(timer.stop_ms(t1));
}
