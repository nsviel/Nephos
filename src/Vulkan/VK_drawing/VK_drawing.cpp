#include "VK_drawing.h"

#include <VK_main/VK_engine.h>
#include <VK_struct/Struct_vulkan.h>
#include <VK_struct/Struct_synchro.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_command/VK_submit.h>
#include <VK_command/VK_command.h>
#include <VK_data/VK_canvas.h>
#include <VK_binding/VK_descriptor.h>
#include <VK_drawing/VK_viewport.h>
#include <VK_renderpass/VK_renderpass.h>
#include <VK_presentation/VK_swapchain.h>


//Constructor / Destructor
VK_drawing::VK_drawing(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->struct_synchro = vk_engine->get_struct_synchro();

  this->vk_command = new VK_command(vk_engine);
  this->vk_descriptor = new VK_descriptor(vk_engine);
  this->vk_submit = new VK_submit(vk_engine);
  this->vk_swapchain = new VK_swapchain(vk_engine);
  this->vk_viewport = new VK_viewport(vk_engine);

  //---------------------------
}
VK_drawing::~VK_drawing(){}

//Main function
void VK_drawing::draw_frame(){
  Struct_command commands;
  VkSemaphore semaphore;
  VkFence fence;
  timer_time t1 = timer.start_t();
  //---------------------------

  //Next image to draw
  semaphore = struct_synchro->vec_semaphore_render[0];
  fence = struct_synchro->vec_fence[0];
  vk_submit->acquire_next_image(&struct_vulkan->swapchain, semaphore, fence);

  //Renderpass
  for(int i=0; i<struct_vulkan->vec_renderpass.size(); i++){
    Struct_command command;
    Struct_renderpass* renderpass = struct_vulkan->vec_renderpass[i];

    //Subpass
    for(int j=0; j<renderpass->vec_subpass.size(); j++){
      Struct_subpass* subpass = renderpass->vec_subpass[j];
      renderpass->draw_task(renderpass);
      command.vec_command_buffer.push_back(subpass->command_buffer);
    }

    //Command
    command.vec_semaphore_wait.push_back(struct_synchro->vec_semaphore_render[i]);
    command.vec_semaphore_done.push_back(struct_synchro->vec_semaphore_render[i+1]);
    command.vec_wait_stage.push_back(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
    command.fence = (i != struct_vulkan->vec_renderpass.size()-1) ? VK_NULL_HANDLE : struct_synchro->vec_fence[0];
    vk_submit->submit_graphics_command(&command);
  }

  //Submit drawn image
  semaphore = struct_synchro->vec_semaphore_render[3];
  vk_submit->submit_presentation(&struct_vulkan->swapchain, semaphore);
  vk_submit->set_next_frame_ID(&struct_vulkan->swapchain);

  //---------------------------
  struct_vulkan->info.draw_frame.push_back(timer.stop_ms(t1));
}
void VK_drawing::cmd_draw_data(Struct_renderpass* renderpass, Struct_data* data){
  //---------------------------

  Struct_subpass* subpass = renderpass->vec_subpass[0];

  VkDeviceSize offsets[] = {0};
  if(data->xyz.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(subpass->command_buffer, 0, 1, &data->xyz.vbo, offsets);
  }
  if(data->rgb.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(subpass->command_buffer, 1, 1, &data->rgb.vbo, offsets);
  }
  if(data->uv.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(subpass->command_buffer, 2, 1, &data->uv.vbo, offsets);
  }
  vkCmdDraw(subpass->command_buffer, data->object->xyz.size(), 1, 0, 0);

  //---------------------------
}
void VK_drawing::cmd_line_with(Struct_renderpass* renderpass, Struct_data* data){
  //---------------------------

  Struct_subpass* subpass = renderpass->vec_subpass[0];

  vkCmdSetLineWidth(subpass->command_buffer, data->object->draw_line_width);

  //---------------------------
}
