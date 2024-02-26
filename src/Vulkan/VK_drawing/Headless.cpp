#include "Headless.h"

#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Headless::Headless(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_render = new vk::draw::Renderer(struct_vulkan);
  this->vk_fence = new vk::synchro::Fence(struct_vulkan);
  this->vk_semaphore = new vk::synchro::Semaphore(struct_vulkan);

  //---------------------------
}
Headless::~Headless(){}

//Main function
void Headless::draw_frame(){
  //---------------------------

  vk::structure::Semaphore* semaphore = vk_semaphore->query_free_semaphore();
  struct_vulkan->queue.presentation->acquire_next_image(semaphore->end);

  //Renderpass
  int nb_renderpass = struct_vulkan->render.vec_renderpass.size();
  for(int i=0; i<nb_renderpass; i++){
    vk::structure::Renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];
    string name = "eng::rp::" + renderpass->name;
    struct_vulkan->profiler->tasker_main->task_begin(name);

    //Create command
    vk::structure::Command* command = new vk::structure::Command();
    command->vec_semaphore_processing.push_back(semaphore->end);

    //Run renderpass
    vk_render->run_renderpass(renderpass);

    //Complete and submit command with semaphore
    semaphore = vk_semaphore->query_free_semaphore();
    command->vec_command_buffer.push_back(renderpass->command_buffer);
    command->vec_semaphore_done.push_back(semaphore->end);
    command->vec_wait_stage.push_back(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);

    struct_vulkan->queue.graphics->submit_command(command);
    struct_vulkan->profiler->tasker_main->task_end(name);
  }

  //---------------------------
}

//Draw command
void Headless::cmd_draw_data(VkCommandBuffer& command_buffer, vk::structure::Object* vk_object){
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
    vkCmdDraw(command_buffer, vk_object->data->point.xyz.size(), 1, 0, 0);
  }

  //---------------------------
}
void Headless::cmd_line_with(VkCommandBuffer& command_buffer, vk::structure::Object* vk_object){
  //---------------------------

  vkCmdSetLineWidth(command_buffer, vk_object->data->line.width);

  //---------------------------
}

}
