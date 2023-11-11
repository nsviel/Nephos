#include "VK_drawing.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_command/VK_submit.h>
#include <VK_command/VK_command.h>
#include <VK_presentation/VK_swapchain.h>


//Constructor / Destructor
VK_drawing::VK_drawing(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_command = new VK_command(struct_vulkan);
  this->vk_submit = new VK_submit(struct_vulkan);
  this->vk_swapchain = new VK_swapchain(struct_vulkan);

  //---------------------------
}
VK_drawing::~VK_drawing(){}

//Main function
void VK_drawing::draw_frame(){
  timer_time t1 = timer.start_t();
  //---------------------------

  this->run_next_image();

  //Renderpass
  vector<VkCommandBuffer> vec_command_buffer;
  for(int i=0; i<struct_vulkan->render.vec_renderpass.size(); i++){
    Struct_renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];

    this->run_renderpass(renderpass, i);
    this->run_command(renderpass, i);
  }

  this->run_presentation();

  //---------------------------
  struct_vulkan->info.draw_frame.push_back(timer.stop_ms(t1));
}

//Subfunction
void VK_drawing::run_next_image(){
  //---------------------------

  VkSemaphore semaphore = struct_vulkan->synchro.vec_semaphore_render[0];
  VkFence fence = struct_vulkan->synchro.vec_fence[0];
  vk_swapchain->acquire_next_image(semaphore, fence);

  //---------------------------
}
void VK_drawing::run_renderpass(Struct_renderpass* renderpass, int i){
  Struct_command command;
  //---------------------------

  VkFramebuffer fbo;
  if(renderpass->target == "graphics"){
    fbo = renderpass->framebuffer->fbo;
  }
  else if(renderpass->target == "presentation"){
    fbo = struct_vulkan->swapchain.get_frame_presentation()->fbo;
  }
  else{
    cout<<"[error] No renderpass target"<<endl;
  }
  vk_command->start_render_pass(renderpass, fbo, false);

  //Subpass
  for(int j=0; j<renderpass->vec_subpass.size(); j++){
    Struct_subpass* subpass = renderpass->vec_subpass[j];
    subpass->draw_task(subpass);
    command.vec_command_buffer.push_back(subpass->command_buffer);
  }

  vk_command->stop_render_pass(renderpass);

  //---------------------------
  renderpass->command = command;
}
void VK_drawing::run_command(Struct_renderpass* renderpass, int i){
  Struct_command& command = renderpass->command;
  //---------------------------

  command.vec_semaphore_wait.push_back(struct_vulkan->synchro.vec_semaphore_render[i]);
  command.vec_semaphore_done.push_back(struct_vulkan->synchro.vec_semaphore_render[i+1]);
  command.vec_wait_stage.push_back(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
  command.fence = (i != struct_vulkan->render.vec_renderpass.size()-1) ? VK_NULL_HANDLE : struct_vulkan->synchro.vec_fence[0];

  vk_submit->submit_command_render(&command);

  //---------------------------
}
void VK_drawing::run_presentation(){
  //---------------------------

  VkSemaphore semaphore = struct_vulkan->synchro.vec_semaphore_render[struct_vulkan->render.vec_renderpass.size()];
  vk_swapchain->submit_presentation(semaphore);
  vk_swapchain->set_next_frame_ID();

  //---------------------------
}

//Draw command
void VK_drawing::cmd_draw_data(Struct_subpass* subpass, Struct_entity* data){
  //---------------------------

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
void VK_drawing::cmd_line_with(Struct_subpass* subpass, Struct_entity* data){
  //---------------------------

  vkCmdSetLineWidth(subpass->command_buffer, data->object->draw_line_width);

  //---------------------------
}
