#pragma once

namespace vk{class Structure;}
namespace vk::window{class Window;}


namespace vk::presentation{

class Surface
{
public:
  //Constructor / Destructor
  Surface(vk::Structure* vk_struct);
  ~Surface();

public:
  //Main function
  void init();
  void clean();

private:
  vk::Structure* vk_struct;
  vk::window::Window* vk_window;
};

}
