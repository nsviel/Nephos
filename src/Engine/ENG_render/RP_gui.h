#ifndef RP_UI_H
#define RP_UI_H

#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_pipeline.h>
#include <ELE_specific/common.h>

class Engine;
class VK_engine;


class RP_gui
{
public:
  //Constructor / Destructor
  RP_gui(Engine* engine);
  ~RP_gui();

public:
  //Init functions
  Struct_renderpass* init_renderpass();
  void create_subpass(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
};

#endif
