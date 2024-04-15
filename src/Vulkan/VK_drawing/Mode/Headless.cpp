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

  vk::structure::Semaphore* semaphore;

  //Renderpass
  vector<vk::structure::Command*> vec_command;
  for(int i=0; i<vk_struct->render.vec_renderpass.size(); i++){
    vk::structure::Renderpass* renderpass = vk_struct->render.vec_renderpass[i];

    //Create command
    vk::structure::Command* command = new vk::structure::Command();
    if(i>0) command->semaphore_wait = semaphore->end;

    //Run renderpass
    vk_render->run_renderpass(renderpass);

    //Complete and submit command with semaphore
    semaphore = vk_semaphore->query_free_semaphore();
    command->command_buffer = renderpass->command_buffer;
    command->semaphore_done = semaphore->end;
    command->wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    vec_command.push_back(command);
  }

  //Submission
  vk_struct->queue.graphics->add_graphics(vec_command);

  vk::image::Screenshot vk_screenshot = vk::image::Screenshot(vk_struct);
  vk_screenshot.make_screenshot();

  //---------------------------
}

}
