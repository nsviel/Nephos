#ifndef VK_DRAW_PSR_H
#define VK_DRAW_PSR_H

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
class VK_viewport;


class DR_psr
{
public:
  //Constructor / Destructor
  DR_psr(VK_engine* vk_engine);
  ~DR_psr();

public:
  //Main functions
  void draw_psr(Struct_renderpass* renderpass);

  //Subfunction
  void update_descriptor(Struct_renderpass* renderpass);
  void record_command(Struct_renderpass* renderpass);
  void submit_command(Struct_renderpass* renderpass);

  //Command function
  void cmd_draw(Struct_renderpass* renderpass);

private:
  Timer timer;

  VK_engine* vk_engine;
  VK_struct* vk_struct;
  VK_command* vk_command;
  VK_cmd* vk_cmd;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  VK_viewport* vk_viewport;

};

#endif
