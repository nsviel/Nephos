#include "VK_render.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_command/VK_submit.h>
#include <VK_command/VK_command.h>
#include <VK_struct/Frame.h>


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
void VK_render::run_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  this->start_renderpass(renderpass);
  this->draw_subpass(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------

}
void VK_render::submit_command(vk::structure::Renderpass* renderpass){
  vk::structure::Command& command = renderpass->command;
  //---------------------------

  command.vec_wait_stage.push_back(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
  vk_submit->submit_command_render(&command);

  //---------------------------
}

//Subfunction
void VK_render::start_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  VkFramebuffer fbo;
  if(renderpass->target == "graphics" || renderpass->target == "transfert"){
    fbo = renderpass->framebuffer->fbo;
  }
  else if(renderpass->target == "presentation"){
    fbo = struct_vulkan->swapchain.get_frame_presentation()->fbo;
  }
  else{
    cout<<"[error] Renderpass target not recognized ["<<renderpass->target<<"]"<<endl;
  }
  vk_command->start_render_pass(renderpass, fbo, false);

  //---------------------------
}
void VK_render::draw_subpass(vk::structure::Renderpass* renderpass){
  vk::structure::Command command;
  //---------------------------

  for(int j=0; j<renderpass->vec_subpass.size(); j++){
    vk::structure::Subpass* subpass = renderpass->vec_subpass[j];
    subpass->command_buffer = renderpass->command_buffer;
    subpass->draw_task(subpass);
  }

  command.vec_command_buffer.push_back(renderpass->command_buffer);

  //---------------------------
  renderpass->command = command;
}
void VK_render::wait_end_rendering(VkFence& fence){
  //---------------------------

  vkWaitForFences(struct_vulkan->device.device, 1, &fence, VK_TRUE, UINT64_MAX);
  vkResetFences(struct_vulkan->device.device, 1, &fence);

  //---------------------------
}
