#ifndef VK_RENDERPASS_H
#define VK_RENDERPASS_H

#include <Vulkan/VK_struct/struct_renderpass.h>
#include <Vulkan/VK_struct/struct_pipeline.h>
#include <ELE_specific/common.h>

class VK_engine;
class VK_struct;
class VK_color;
class VK_pipeline;
class VK_subpass;

class RP_scene;
class RP_edl;
class RP_psr;
class RP_ui;


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

  inline RP_edl* get_rp_edl(){return rp_edl;}

private:
  VK_engine* vk_engine;
  VK_struct* vk_struct;
  VK_color* vk_color;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;

  RP_scene* rp_scene;
  RP_edl* rp_edl;
  RP_psr* rp_psr;
  RP_ui* rp_ui;
};

#endif
