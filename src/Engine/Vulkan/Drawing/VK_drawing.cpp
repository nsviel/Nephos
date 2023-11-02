#include "VK_drawing.h"

#include <Vulkan/Command/VK_cmd.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>
#include <Vulkan/Drawing/DR_scene.h>
#include <Vulkan/Drawing/DR_edl.h>
#include <Vulkan/Drawing/DR_psr.h>
#include <Vulkan/Drawing/DR_ui.h>
#include <Vulkan/Pipeline/VK_pipeline.h>
#include <Vulkan/Command/VK_submit.h>
#include <Vulkan/Command/VK_command.h>
#include <Vulkan/Presentation/VK_canvas.h>
#include <Vulkan/VK_binding/VK_descriptor.h>


//Constructor / Destructor
VK_drawing::VK_drawing(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_struct = vk_engine->get_vk_struct();
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
  vk_submit->acquire_next_image(&vk_struct->swapchain);

  //Drawing operations
  dr_scene->draw_scene(&vk_struct->renderpass_scene);


  dr_edl->draw_edl(&vk_struct->renderpass_edl);
  dr_ui->draw_ui(&vk_struct->renderpass_ui);

  //Submit drawn image
  vk_submit->submit_presentation(&vk_struct->swapchain);
  vk_submit->set_next_frame_ID(&vk_struct->swapchain);

  //---------------------------
  vk_struct->time.draw_frame.push_back(timer.stop_ms(t1));
}
