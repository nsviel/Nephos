#include "Headless.h"

#include <Vulkan/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Headless::Headless(vk::structure::Vulkan* vk_struct) : vk::draw::Drawer(vk_struct){
  //---------------------------


  //---------------------------
}
Headless::~Headless(){}

//Main function
void Headless::draw_frame(){
  //---------------------------

  vk_struct->queue.graphics->wait_for_idle();
  vk_struct->queue.presentation->wait_for_idle();
  vk::synchro::structure::Semaphore* semaphore = nullptr;

  //Renderpass
  vector<vk::structure::Command*> vec_command;
  for(int i=0; i<vk_struct->render.vec_renderpass.size(); i++){
    vk::structure::Renderpass* renderpass = vk_struct->render.vec_renderpass[i];

    //Run renderpass
    vk_render->run_renderpass(renderpass);

    //Create command
    vk::structure::Command* command = new vk::structure::Command();
    if(semaphore != nullptr) command->semaphore_wait = semaphore->handle;
    command->wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    command->command_buffer = renderpass->command_buffer;
    semaphore = vk_semaphore->query_free_semaphore();
    if(i < vk_struct->render.vec_renderpass.size() - 1) command->semaphore_done = semaphore->handle;
    vec_command.push_back(command);
  }

  //Submission
  vk_struct->queue.graphics->add_graphics(vec_command);

  //---------------------------
}

}
