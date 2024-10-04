#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::queue{class Base;}
namespace vk::structure{class Command_buffer;}


namespace vk::command{

class Command
{
public:
  //Constructor / Destructor
  Command(vk::Structure* vk_struct);
  ~Command();

public:
  //Main function
  void submit_graphics_command(std::shared_ptr<vk::structure::Command_buffer> command_buffer);
  void submit_transfer_command(std::shared_ptr<vk::structure::Command_buffer> command_buffer);

private:
  vk::Structure* vk_struct;
};

}
