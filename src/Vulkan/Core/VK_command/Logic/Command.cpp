#include "Command.h"

#include <Vulkan/Namespace.h>


namespace vk::command{

//Constructor / Destructor
Command::Command(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Command::~Command(){}

//Main function
void Command::submit_graphics_command(std::shared_ptr<vk::structure::Command_buffer> command_buffer){
  //---------------------------

  std::unique_ptr<vk::structure::Command> command = std::make_unique<vk::structure::Command>();
  command->command_buffer = command_buffer;
  vk_struct->core.command.graphics->add_command(std::move(command));

  //---------------------------
}
void Command::submit_transfer_command(std::shared_ptr<vk::structure::Command_buffer> command_buffer){
  //---------------------------

  std::unique_ptr<vk::structure::Command> command = std::make_unique<vk::structure::Command>();
  command->command_buffer = command_buffer;
  vk_struct->core.command.transfer->add_command(std::move(command));

  //---------------------------
}

}
