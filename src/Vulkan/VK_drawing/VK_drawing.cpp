#include "VK_drawing.h"
#include "VK_renderpass.h"
#include "../VK_presentation/VK_swapchain.h"

#include <VK_main/VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <VK_struct/struct_synchro.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_command/VK_submit.h>
#include <VK_command/VK_command.h>
#include <VK_presentation/VK_canvas.h>
#include <VK_binding/VK_descriptor.h>

#include <ENG_vulkan/ENG_scene.h>
#include <ENG_vulkan/ENG_edl.h>


//Constructor / Destructor
VK_drawing::VK_drawing(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->struct_synchro = vk_engine->get_struct_synchro();
  
  this->vk_engine = vk_engine;
  this->vk_command = new VK_command(vk_engine);
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_submit = new VK_submit(vk_engine);
  this->vk_swapchain = vk_engine->get_vk_swapchain();
  this->rp_scene = new ENG_scene(vk_engine);
  this->rp_edl = new ENG_edl(vk_engine);

  //---------------------------
}
VK_drawing::~VK_drawing(){}

//Main function
void VK_drawing::draw_frame(){
  Struct_submit_commands commands;
  VkSemaphore semaphore;
  VkFence fence;
  timer_time t1 = timer.start_t();
  //---------------------------

  //Next image to draw
  semaphore = struct_synchro->vec_semaphore_image[0];
  fence = struct_synchro->vec_fence[0];
  vk_submit->acquire_next_image(&struct_vulkan->swapchain, semaphore, fence);

  //SCENE
  Struct_renderpass* renderpass;
  renderpass = &struct_vulkan->renderpass_scene;
  renderpass->semaphore_wait = struct_synchro->vec_semaphore_image[0];
  renderpass->semaphore_done = struct_synchro->vec_semaphore_render[0];
  renderpass->fence = VK_NULL_HANDLE;
  rp_scene->draw_scene(renderpass);
  vk_submit->submit_graphics_command(renderpass);

  //EDL
  renderpass = &struct_vulkan->renderpass_edl;
  renderpass->semaphore_wait = struct_synchro->vec_semaphore_render[0];
  renderpass->semaphore_done = struct_synchro->vec_semaphore_render[1];
  renderpass->fence = VK_NULL_HANDLE;
  rp_edl->draw_edl(&struct_vulkan->renderpass_edl);
  vk_submit->submit_graphics_command(renderpass);

  //GUI
  renderpass = &struct_vulkan->renderpass_ui;
  renderpass->semaphore_wait = struct_synchro->vec_semaphore_render[1];
  renderpass->semaphore_done = struct_synchro->vec_semaphore_render[2];
  renderpass->fence = struct_synchro->vec_fence[0];

  Frame* frame_current = struct_vulkan->swapchain.get_frame_current();
  vk_command->start_render_pass(renderpass, frame_current, false);
  ImDrawData* draw_data = ImGui::GetDrawData();
  ImGui_ImplVulkan_RenderDrawData(draw_data, renderpass->command_buffer);
  vk_command->stop_render_pass(renderpass);
  vk_submit->submit_graphics_command(renderpass);

  //Submit drawn image
  semaphore = struct_synchro->vec_semaphore_render[2];
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
