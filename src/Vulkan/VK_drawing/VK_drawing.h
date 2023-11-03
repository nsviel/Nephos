#ifndef VK_DRAWING_H
#define VK_DRAWING_H

#include <VK_struct/struct_frame.h>
#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_command.h>
#include <ELE_specific/common.h>

class VK_engine;
class VK_struct;
class VK_command;
class VK_cmd;
class VK_descriptor;
class VK_submit;
class DR_scene;
class DR_edl;
class DR_psr;
class DR_ui;


class VK_drawing
{
public:
  //Constructor / Destructor
  VK_drawing(VK_engine* vk_engine);
  ~VK_drawing();

public:
  //Main functions
  void draw_frame();

  inline DR_ui* get_ui_drawing(){return dr_ui;}

private:
  Timer timer;

  VK_engine* vk_engine;
  VK_struct* vk_struct;
  VK_command* vk_command;
  VK_cmd* vk_cmd;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  DR_psr* dr_psr;
  DR_ui* dr_ui;
  DR_scene* dr_scene;
  DR_edl* dr_edl;

};

#endif
