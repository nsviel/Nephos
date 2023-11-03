#ifndef VK_CMD_H
#define VK_CMD_H

#include "../VK_struct/struct_renderpass.h"
#include "../VK_struct/struct_data.h"
#include <ELE_specific/common.h>

class VK_engine;
class VK_struct;
class VK_viewport;


class VK_cmd
{
public:
  //Constructor / Destructor
  VK_cmd(VK_engine* vk_engine);
  ~VK_cmd();

public:
  //Main function
  void cmd_viewport(Struct_renderpass* renderpass);
  void cmd_bind_pipeline(Struct_renderpass* renderpass, string pipeline_name);
  void cmd_draw_data(Struct_renderpass* renderpass, Struct_data* data);
  void cmd_bind_descriptor(Struct_renderpass* renderpass, string pipeline_name, VkDescriptorSet set);
  void cmd_line_with(Struct_renderpass* renderpass, Struct_data* data);

private:
  VK_engine* vk_engine;
  VK_struct* vk_struct;
  VK_viewport* vk_viewport;
};

#endif
