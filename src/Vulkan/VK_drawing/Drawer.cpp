#include "Drawer.h"

#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Drawer::Drawer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_render = new vk::draw::Renderer(struct_vulkan);
  this->vk_presentation = new vk::presentation::Presentation(struct_vulkan);
  this->vk_fence = new vk::synchro::Fence(struct_vulkan);
  this->vk_semaphore = new vk::synchro::Semaphore(struct_vulkan);
  this->vk_command = new vk::command::Command(struct_vulkan);

  //---------------------------
}
Drawer::~Drawer(){}

//Main function
void Drawer::draw_frame(){
  //---------------------------

  vk::structure::Semaphore* semaphore = vk_semaphore->query_free_semaphore();
  vk_presentation->acquire_next_image(semaphore->end);

  //Renderpass
  int nb_renderpass = struct_vulkan->render.vec_renderpass.size();
  for(int i=0; i<nb_renderpass; i++){
    vk::structure::Renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];
    vk::structure::Command command;

    command.vec_semaphore_processing.push_back(semaphore->end);

    string name = "eng::rp::" + renderpass->name;
    struct_vulkan->tasker_cpu->task_begin(name);
    vk_render->run_renderpass(renderpass);

    semaphore = vk_semaphore->query_free_semaphore();
    command.vec_command_buffer.push_back(renderpass->command_buffer);
    command.vec_semaphore_done.push_back(semaphore->end);
    command.vec_wait_stage.push_back(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
    renderpass->command = command;

    struct_vulkan->tasker_cpu->task_end(name);
  }



  vk::structure::Fence* fence = vk_fence->query_free_fence();
  //vk_command->submit_command(&command_all, fence);

  for(int i=0; i<nb_renderpass; i++){
    vk::structure::Renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];

    if(i != nb_renderpass-1){
      vk_command->submit_command(&renderpass->command, nullptr);
    }else{
      vk_command->submit_command(&renderpass->command, fence);
    }
  }



  vkWaitForFences(struct_vulkan->device.device, 1, &fence->fence, VK_TRUE, UINT64_MAX);
  vk_presentation->image_presentation(semaphore->end);
  vk_fence->reset_fence(fence);

  //---------------------------
}

//Draw command
void Drawer::cmd_draw_data(VkCommandBuffer& command_buffer, vk::structure::Object* vk_object){
  //---------------------------

  VkDeviceSize offsets[] = {0};
  if(vk_object->buffer.rgb.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(command_buffer, 1, 1, &vk_object->buffer.rgb.vbo, offsets);
  }
  if(vk_object->buffer.uv.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(command_buffer, 2, 1, &vk_object->buffer.uv.vbo, offsets);
  }
  if(vk_object->buffer.xyz.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(command_buffer, 0, 1, &vk_object->buffer.xyz.vbo, offsets);
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
