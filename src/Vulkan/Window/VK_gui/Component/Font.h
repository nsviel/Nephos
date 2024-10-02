#pragma once

#include <string>

namespace vk{class Structure;}
namespace vk::commandbuffer{class Command;}
namespace vk::commandbuffer{class Allocator;}


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
  vk::commandbuffer::Allocator* vk_allocator;
  vk::commandbuffer::Command* vk_command;

  std::string path_text;
  std::string path_icon;
};

}
