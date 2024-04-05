#include "Graphical.h"

#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Graphical::Graphical(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_render = new vk::draw::Renderer(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);

  //---------------------------
}
Graphical::~Graphical(){}

//Main function
void Graphical::draw_frame(){
  //---------------------------

  vk::structure::Semaphore* semaphore = vk_semaphore->query_free_semaphore();
  vk_struct->queue.presentation->acquire_next_image(semaphore->end);

  //Renderpass
  vector<vk::structure::Command*> vec_command;

  int nb_renderpass = vk_struct->render.vec_renderpass.size();
  for(int i=0; i<nb_renderpass; i++){
    vk::structure::Renderpass* renderpass = vk_struct->render.vec_renderpass[i];
    string name = "eng::rp::" + renderpass->name;
    vk_struct->profiler->tasker_main->task_begin(name);

    //Create command
    vk::structure::Command* command = new vk::structure::Command();
    vec_command.push_back(command);
    command->vec_semaphore_processing.push_back(semaphore->end);

    //Run renderpass
    vk_render->run_renderpass(renderpass);

    //Complete and submit command with semaphore
    semaphore = vk_semaphore->query_free_semaphore();
    command->vec_command_buffer.push_back(renderpass->command_buffer);
    command->vec_semaphore_done.push_back(semaphore->end);
    command->vec_wait_stage.push_back(VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);

    vk_struct->profiler->tasker_main->task_end(name);
  }

  for(int i=0; i<vec_command.size(); i++){
    vk::structure::Command* command = vec_command[i];
    vk_struct->queue.graphics->add_command(command);
  }
  //vk_struct->queue.graphics->add_command(vec_command);

  vk_struct->queue.graphics->wait_for_idle();


  vk_struct->queue.presentation->image_presentation(semaphore->end);

  //---------------------------
}

//Draw command
void Graphical::cmd_draw_data(VkCommandBuffer& command_buffer, vk::structure::Object* vk_object){
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
void Graphical::cmd_line_with(VkCommandBuffer& command_buffer, vk::structure::Object* vk_object){
  //---------------------------

  vkCmdSetLineWidth(command_buffer, vk_object->data->width);

  //---------------------------
}

}
