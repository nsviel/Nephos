#pragma once

#include <imgui/implot/implot.h>
#include <string>

namespace vk::command{class Command_buffer;}
namespace vk::command{class Allocator;}
namespace vk::structure{class Vulkan;}


namespace vk::gui{

class Font
{
public:
  //Constructor / Destructor
  Font(vk::structure::Vulkan* vk_struct);
  ~Font();

public:
  //Main function
  void create_font();

  //Subfunction
  void font_text();
  void font_editor();
  void font_build();

private:
  vk::structure::Vulkan* vk_struct;
  vk::command::Allocator* vk_allocator;
  vk::command::Command_buffer* vk_command_buffer;

  std::string path_text;
  std::string path_icon;
};

}
