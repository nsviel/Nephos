#pragma once

#include <string>

namespace vk{class Structure;}
namespace vk::commandbuffer{class Command_buffer;}
namespace vk::commandbuffer{class Allocator;}
namespace vk::command{class Command;}


namespace vk::gui{

class Font
{
public:
  //Constructor / Destructor
  Font(vk::Structure* vk_struct);
  ~Font();

public:
  //Main function
  void create_font();

  //Subfunction
  void font_text();
  void font_editor();
  void font_build();

private:
  vk::Structure* vk_struct;
  vk::command::Command* vk_command;
  vk::commandbuffer::Allocator* vk_allocator;
  vk::commandbuffer::Command_buffer* vk_commandbuffer;

  std::string path_text;
  std::string path_icon;
};

}
