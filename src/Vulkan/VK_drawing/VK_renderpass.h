#ifndef VK_RENDERPASS_H
#define VK_RENDERPASS_H

#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_pipeline.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_color;
class VK_pipeline;
class VK_subpass;
class VK_command_buffer;

class ENG_scene;
class ENG_edl;
class ENG_gui;


class VK_renderpass
{
public:
  //Constructor / Destructor
  VK_renderpass(VK_engine* vk_engine);
  ~VK_renderpass();

public:
  //Main functions
  void init_renderpass();
  void clean_renderpass();
  void clean_renderpass_object(Struct_renderpass* renderpass);

  //Subfunction
  void create_renderpass(Struct_renderpass* renderpass);
  void create_renderpass_obj(Struct_renderpass* renderpass);

  inline ENG_edl* get_eng_edl(){return eng_edl;}

private:
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_color* vk_color;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_command_buffer* vk_command_buffer;

  ENG_scene* eng_scene;
  ENG_edl* eng_edl;
  ENG_gui* eng_gui;
};

#endif
