#ifndef GUI_RENDER_H
#define GUI_RENDER_H

class GUI;
class GUI_renderpass;
class VK_engine;


class GUI_render
{
public:
  //Constructor / Destructor
  GUI_render(GUI* gui);
  ~GUI_render();

public:
  //Main functions
  void init();
  void loop();
  void exit();

private:
  GUI_renderpass* gui_renderpass;
  VK_engine* vk_engine;
};

#endif
