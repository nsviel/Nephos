#include "Drawer.h"

#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Drawer::Drawer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_render = new vk::draw::Renderer(struct_vulkan);
  this->vk_presentation = new vk::presentation::VK_presentation(struct_vulkan);

  //---------------------------
}
Drawer::~Drawer(){}

//Main function
void Drawer::draw_frame(){

  //---------------------------

  if(struct_vulkan->param.headless){
    this->draw_frame_headless();
  }
  else{
    this->draw_frame_presentation();
  }

  //---------------------------

}
void Drawer::draw_frame_headless(){
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
void Drawer::draw_frame_presentation(){
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
void Drawer::cmd_draw_data(VkCommandBuffer& command_buffer, vk::structure::Object* vk_object){
  //---------------------------

  VkDeviceSize offsets[] = {0};
  if(vk_object->rgb.vbo != VK_NULL_HANDLE && vk_object->has_rgb){
    vkCmdBindVertexBuffers(command_buffer, 1, 1, &vk_object->rgb.vbo, offsets);
  }
  if(vk_object->uv.vbo != VK_NULL_HANDLE && vk_object->has_uv){
    vkCmdBindVertexBuffers(command_buffer, 2, 1, &vk_object->uv.vbo, offsets);
  }
  if(vk_object->xyz.vbo != VK_NULL_HANDLE && vk_object->has_xyz){
    vkCmdBindVertexBuffers(command_buffer, 0, 1, &vk_object->xyz.vbo, offsets);
    vkCmdDraw(command_buffer, vk_object->data->xyz.size(), 1, 0, 0);
  }

  //---------------------------
}
void Drawer::cmd_line_with(VkCommandBuffer& command_buffer, vk::structure::Object* vk_object){
  //---------------------------

  vkCmdSetLineWidth(command_buffer, vk_object->data->draw_line_width);

  //---------------------------
}

}
