#include "VK_drawing.h"
#include "../VK_presentation/VK_swapchain.h"

#include <VK_main/VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <VK_struct/struct_synchro.h>
#include <VK_drawing/DR_scene.h>
#include <VK_drawing/DR_edl.h>
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
  this->struct_synchro = vk_engine->get_struct_synchro();
  this->vk_command = new VK_command(vk_engine);
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_submit = new VK_submit(vk_engine);
  this->vk_swapchain = vk_engine->get_vk_swapchain();
  this->dr_scene = new DR_scene(vk_engine);
  this->dr_edl = new DR_edl(vk_engine);
  this->dr_ui = new DR_ui(vk_engine);

  //---------------------------
}
VK_drawing::~VK_drawing(){}

//Main function
void VK_drawing::draw_frame(){
  Struct_submit_commands commands;
  VkSemaphore semaphore;
  timer_time t1 = timer.start_t();
  //---------------------------

  //Next image to draw
  Frame* frame_inflight = struct_vulkan->swapchain.get_frame_inflight();
  semaphore = frame_inflight->semaphore_image_ready;
  vk_submit->acquire_next_image(&struct_vulkan->swapchain, semaphore, frame_inflight->fence);

  //Drawing operations
  Struct_renderpass* renderpass;
  renderpass = &struct_vulkan->renderpass_scene;
  //renderpass->semaphore_wait = struct_synchro->vec_semaphore_rp_wait[0];
  //renderpass->semaphore_done = struct_synchro->vec_semaphore_rp_done[0];
  renderpass->semaphore_wait = frame_inflight->semaphore_image_ready;
  renderpass->semaphore_done = frame_inflight->semaphore_scene_ready;
  renderpass->fence = VK_NULL_HANDLE;
  dr_scene->draw_scene(renderpass);

  renderpass = &struct_vulkan->renderpass_edl;
  //renderpass->semaphore_wait = struct_synchro->vec_semaphore_rp_done[0];
  //renderpass->semaphore_done = struct_synchro->vec_semaphore_rp_done[1];
  renderpass->semaphore_wait = frame_inflight->semaphore_scene_ready;
  renderpass->semaphore_done = frame_inflight->semaphore_edl_ready;
  renderpass->fence = VK_NULL_HANDLE;
  dr_edl->draw_edl(&struct_vulkan->renderpass_edl);

  renderpass = &struct_vulkan->renderpass_ui;
  //renderpass->semaphore_wait = struct_synchro->vec_semaphore_rp_done[1];
  //renderpass->semaphore_done = struct_synchro->vec_semaphore_rp_done[2];
  //renderpass->fence = struct_synchro->vec_fence[0];
  renderpass->semaphore_wait = frame_inflight->semaphore_edl_ready;
  renderpass->semaphore_done = frame_inflight->semaphore_ui_ready;
  renderpass->fence = frame_inflight->fence;
  dr_ui->draw_ui(&struct_vulkan->renderpass_ui);

  //Submit drawn image
  semaphore = frame_inflight->semaphore_ui_ready;
  vk_submit->submit_presentation(&struct_vulkan->swapchain, semaphore);
  vk_submit->set_next_frame_ID(&struct_vulkan->swapchain);

  //---------------------------
  struct_vulkan->time.draw_frame.push_back(timer.stop_ms(t1));
}
void VK_drawing::cmd_draw_data(Struct_renderpass* renderpass, Struct_data* data){
  //---------------------------

  VkDeviceSize offsets[] = {0};
  if(data->xyz.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(renderpass->command_buffer, 0, 1, &data->xyz.vbo, offsets);
  }
  if(data->rgb.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(renderpass->command_buffer, 1, 1, &data->rgb.vbo, offsets);
  }
  if(data->uv.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(renderpass->command_buffer, 2, 1, &data->uv.vbo, offsets);
  }
  vkCmdDraw(renderpass->command_buffer, data->object->xyz.size(), 1, 0, 0);

  //---------------------------
}
void VK_drawing::cmd_line_with(Struct_renderpass* renderpass, Struct_data* data){
  //---------------------------

  vkCmdSetLineWidth(renderpass->command_buffer, data->object->draw_line_width);

  //---------------------------
}
