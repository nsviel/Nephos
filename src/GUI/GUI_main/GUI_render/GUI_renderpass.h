#ifndef GUI_RENDERPASS_H
#define GUI_RENDERPASS_H

#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_pipeline.h>
#include <ELE_specific/common.h>

class VK_render;
class VK_engine;


class GUI_renderpass
{
public:
  //Constructor / Destructor
  GUI_renderpass(VK_engine* vk_engine);
  ~GUI_renderpass();

public:
  //Main functions
  void init_renderpass();
  void create_subpass(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  VK_render* vk_render;
};

#endif
