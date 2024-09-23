#pragma once

#include <string>

namespace vk{class Structure;}
namespace vk::command{class Command;}
namespace vk::command{class Allocator;}


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
  vk::command::Allocator* vk_allocator;
  vk::command::Command* vk_command;

  std::string path_text;
  std::string path_icon;
};

}
