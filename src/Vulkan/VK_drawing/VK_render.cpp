#include "VK_render.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_command/VK_submit.h>
#include <VK_command/VK_command.h>


//Constructor / Destructor
VK_render::VK_render(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_command = new VK_command(struct_vulkan);
  this->vk_submit = new VK_submit(struct_vulkan);

  //---------------------------
}
VK_render::~VK_render(){}

//Main function
void VK_render::run_renderpass(Struct_renderpass* renderpass, int i){
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
void VK_render::run_command(Struct_renderpass* renderpass, int i){
  Struct_command& command = renderpass->command;
  //---------------------------

  command.vec_semaphore_wait.push_back(struct_vulkan->synchro.vec_semaphore_render[i]);
  command.vec_semaphore_done.push_back(struct_vulkan->synchro.vec_semaphore_render[i+1]);
  command.vec_wait_stage.push_back(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
  command.fence = (i != struct_vulkan->render.vec_renderpass.size()-1) ? VK_NULL_HANDLE : struct_vulkan->synchro.vec_fence[0];

  vk_submit->submit_command_render(&command);

  //---------------------------
}
