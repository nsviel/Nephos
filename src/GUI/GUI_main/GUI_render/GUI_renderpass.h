#ifndef GUI_RENDERPASS_H
#define GUI_RENDERPASS_H

#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_pipeline.h>
#include <ELE_specific/common.h>

class GUI;
class VK_pipeline;


class GUI_renderpass
{
public:
  //Constructor / Destructor
  GUI_renderpass(GUI* gui);
  ~GUI_renderpass();

public:
  //Init functions
  void init_renderpass();
  void create_subpass(Struct_renderpass* renderpass);

  //Draw function
  void draw_gui(Struct_subpass* subpass);

private:
  //ENG_shader* eng_shader;
  VK_pipeline* vk_pipeline;
};

#endif
