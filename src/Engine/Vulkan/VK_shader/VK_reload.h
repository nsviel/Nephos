#ifndef VK_RELOAD_H
#define VK_RELOAD_H

#include <Specific/common.h>

class VK_engine;
class VK_pipeline;
class VK_struct;
class VK_renderpass;


class VK_reload
{
public:
  //Constructor / Destructor
  VK_reload(VK_engine* vk_engine);
  ~VK_reload();

public:
  //Main function
  void hot_shader_reload(string shader_1, string shader_2);

private:
  VK_engine* vk_engine;
  VK_pipeline* vk_pipeline;
  VK_struct* vk_struct;
  VK_renderpass* vk_renderpass;
};

#endif
