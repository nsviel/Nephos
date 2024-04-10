#pragma once

namespace vk::gui{class Imgui;}
namespace gui{class Node;}


namespace gui{

class Render
{
public:
  //Constructor / Destructor
  Render(gui::Node* gui);
  ~Render();

public:
  //Main functions
  void init();
  void render();
  void clean();
  void new_frame();

private:
  vk::gui::Imgui* vk_imgui;
};

}
