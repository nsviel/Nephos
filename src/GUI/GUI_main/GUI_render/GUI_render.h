#ifndef GUI_RENDER_H
#define GUI_RENDER_H

class GUI;
class GUI_renderpass;
class VK_engine;
class VK_render;


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
  void clean();
  void wait();

  inline VK_engine* get_vk_engine(){return vk_engine;}

private:
  GUI_renderpass* gui_renderpass;
  VK_engine* vk_engine;
  VK_render* vk_render;
};

#endif
