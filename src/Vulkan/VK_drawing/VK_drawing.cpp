#include "VK_drawing.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_drawing/VK_presentation.h>
#include <VK_drawing/VK_render.h>


//Constructor / Destructor
VK_drawing::VK_drawing(Struct_vulkan* struct_vulkan){
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
/////// FAIRE MARCHER EN HEADLESS !!!

  Struct_frame* frame = struct_vulkan->swapchain.get_frame_presentation();
  VkSemaphore semaphore_wait = frame->semaphore_image_ready;
  VkSemaphore semaphore_done = frame->vec_semaphore_render[0];
  vk_presentation->acquire_next_image(semaphore_wait);

  //Renderpass
  int nb_renderpass = render.vec_renderpass.size();
  for(int i=0; i<struct_vulkan->nb_renderpass; i++){
    Struct_renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];

    vk_render->run_renderpass(renderpass, i);

    Struct_command& command = renderpass->command;
    command.vec_semaphore_wait.push_back(semaphore_wait);
    command.vec_semaphore_done.push_back(semaphore_done);
    command.fence = (i != struct_vulkan->render.vec_renderpass.size()-1) ? VK_NULL_HANDLE : frame->fence;
    vk_render->run_command(renderpass, i);

    semaphore_wait = frame->vec_semaphore_render[i];
    semaphore_done = frame->vec_semaphore_render[i+1];
  }

  VkSemaphore semaphore = frame->vec_semaphore_render[nb_renderpass-1];
  VkFence fence = frame->fence;
  vk_presentation->run_presentation(semaphore, fence);

  //---------------------------
  struct_vulkan->info.draw_frame.push_back(timer.stop_ms(t1));
}

//Draw command
void VK_drawing::cmd_draw_data(VkCommandBuffer& command_buffer, Struct_entity* data){
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
void VK_drawing::cmd_line_with(VkCommandBuffer& command_buffer, Struct_entity* data){
  //---------------------------

  vkCmdSetLineWidth(command_buffer, data->object->draw_line_width);

  //---------------------------
}
