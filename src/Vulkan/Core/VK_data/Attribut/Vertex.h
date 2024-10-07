#pragma once

#include <vulkan/vulkan.h>

namespace vk{class Structure;}
namespace vk::data{class Buffer;}
namespace vk::structure{class Object;}


namespace vk::data{

class Vertex
{
public:
  //Constructor / Destructor
  Vertex(vk::Structure* vk_struct);
  ~Vertex();

public:
  //Main function
  void build_vertex(vk::structure::Object& vk_object);
  void update_vertex(vk::structure::Object& vk_object);
  void clean_vertex(vk::structure::Object& vk_object);

  //Subfunction
  void cmd_draw_vertex(VkCommandBuffer& command_buffer, vk::structure::Object& vk_object);
  void cmd_line_with(VkCommandBuffer& command_buffer, vk::structure::Object& vk_object);

protected:
  vk::Structure* vk_struct;
  vk::data::Buffer* vk_buffer;
};

}
