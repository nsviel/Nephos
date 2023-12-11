#include "VK_drawing.h"

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_drawing/VK_presentation.h>
#include <Vulkan/VK_drawing/VK_render.h>


//Constructor / Destructor
VK_drawing::VK_drawing(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_render = new VK_render(struct_vulkan);
  this->vk_presentation = new VK_presentation(struct_vulkan);

  //---------------------------
}
VK_drawing::~VK_drawing(){}

//Main function
void VK_drawing::draw_frame(){
  timer_time t1 = timer.start_t();
  //---------------------------

  if(struct_vulkan->param.headless){
    this->draw_frame_headless();
  }
  else{
    this->draw_frame_presentation();
  }

  //---------------------------
  struct_vulkan->info.draw_frame.push_back(timer.stop_ms(t1));
}
void VK_drawing::draw_frame_headless(){
  //---------------------------

  VkSemaphore semaphore_wait = struct_vulkan->synchro.semaphore_image_ready;
  VkSemaphore semaphore_done = struct_vulkan->synchro.vec_semaphore_render[0];

  //Renderpass
  int nb_renderpass = struct_vulkan->render.vec_renderpass.size();
  for(int i=0; i<nb_renderpass; i++){
    vk::structure::Renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];

    vk_render->run_renderpass(renderpass);

    vk::structure::Command& command = renderpass->command;
    command.fence = (i == nb_renderpass-1) ? struct_vulkan->synchro.fence : VK_NULL_HANDLE;
    vk_render->submit_command(renderpass);

    semaphore_wait = struct_vulkan->synchro.vec_semaphore_render[i];
    semaphore_done = struct_vulkan->synchro.vec_semaphore_render[i+1];
  }

  VkFence fence = struct_vulkan->synchro.fence;
  vk_render->wait_end_rendering(fence);

  //---------------------------
}
void VK_drawing::draw_frame_presentation(){
  //---------------------------

  vk::structure::Frame* frame = struct_vulkan->swapchain.get_frame_presentation();
  VkSemaphore semaphore_wait = frame->semaphore_image_ready;
  VkSemaphore semaphore_done = frame->vec_semaphore_render[0];
  vk_presentation->acquire_next_image(semaphore_wait);

  //Renderpass
  int nb_renderpass = struct_vulkan->render.vec_renderpass.size();
  for(int i=0; i<nb_renderpass; i++){
    vk::structure::Renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];

    vk_render->run_renderpass(renderpass);

    vk::structure::Command& command = renderpass->command;
    command.vec_semaphore_wait.push_back(semaphore_wait);
    command.vec_semaphore_done.push_back(semaphore_done);
    command.fence = (i == nb_renderpass-1) ? frame->fence : VK_NULL_HANDLE;
    vk_render->submit_command(renderpass);

    semaphore_wait = frame->vec_semaphore_render[i];
    semaphore_done = frame->vec_semaphore_render[i+1];
  }

  VkSemaphore semaphore = frame->vec_semaphore_render[nb_renderpass-1];
  VkFence fence = frame->fence;
  vk_render->wait_end_rendering(fence);
  vk_presentation->image_presentation(semaphore, fence);

  //---------------------------
}

//Draw command
void VK_drawing::cmd_draw_data(VkCommandBuffer& command_buffer, vk::structure::Entity* data){
  //---------------------------

  VkDeviceSize offsets[] = {0};
  if(data->xyz.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(command_buffer, 0, 1, &data->xyz.vbo, offsets);
  }
  if(data->rgb.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(command_buffer, 1, 1, &data->rgb.vbo, offsets);
  }
  if(data->uv.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(command_buffer, 2, 1, &data->uv.vbo, offsets);
  }
  vkCmdDraw(command_buffer, data->object->xyz.size(), 1, 0, 0);

  //---------------------------
}
void VK_drawing::cmd_line_with(VkCommandBuffer& command_buffer, vk::structure::Entity* data){
  //---------------------------

  vkCmdSetLineWidth(command_buffer, data->object->draw_line_width);

  //---------------------------
}
