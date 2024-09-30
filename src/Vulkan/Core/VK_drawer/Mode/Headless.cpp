#include "Headless.h"

#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Headless::Headless(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_render = new vk::draw::Renderer(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);

  //---------------------------
}
Headless::~Headless(){}

//Main function
void Headless::draw_frame(){
  //---------------------------

  //vk_struct->core.queue.graphics->wait_for_idle();
  //vk_struct->core.queue.presentation->wait_for_idle();
  vk::synchro::structure::Semaphore* semaphore = nullptr;

  //Renderpass
  std::vector< std::unique_ptr<vk::structure::Command> > vec_command;

  int i=0;
  for(auto& renderpass : vk_struct->graphics.render.renderpass.vec_renderpass){
    //Run renderpass
    vk_render->run_renderpass(renderpass);

    //Create command
    std::unique_ptr<vk::structure::Command> command = std::make_unique<vk::structure::Command>();
    if(semaphore != nullptr) command->semaphore_wait = semaphore->handle;
    command->wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    command->command_buffer = renderpass->command_buffer;
    semaphore = vk_semaphore->query_free_semaphore();
    if(i < vk_struct->graphics.render.renderpass.vec_renderpass.size() - 1) command->semaphore_done = semaphore->handle;
    vec_command.push_back(std::move(command));

    i++;
  }

  //Submission
  vk_struct->core.queue.graphics->add_command(std::move(vec_command));

  //---------------------------
}

}
