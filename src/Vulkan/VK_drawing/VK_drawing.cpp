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
//TODO CHANGER CETTE CLASS POUR HEADLESS MODE !!!!
// OU FAIRE UNE AUTRA CLASS RENDER QUI GERE LE RENDERING OFFSCREEEN ET CETTE CLASS POUR LE DRAWING ON SCREEN ???!!
  VkSemaphore semaphore = struct_vulkan->synchro.vec_semaphore_render[0];
  VkFence fence = struct_vulkan->synchro.vec_fence[0];
  vk_presentation->acquire_next_image(semaphore, fence);

  //Renderpass
  vector<VkCommandBuffer> vec_command_buffer;
  for(int i=0; i<struct_vulkan->render.vec_renderpass.size(); i++){
    Struct_renderpass* renderpass = struct_vulkan->render.vec_renderpass[i];

    vk_render->run_renderpass(renderpass, i);
    vk_render->run_command(renderpass, i);
  }

  vk_presentation->run_presentation();

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
