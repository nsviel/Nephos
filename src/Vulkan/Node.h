#pragma once

#include <Utility/Base/Class/Node.h>

namespace utl{class Node;}
namespace vk{class Structure;}
namespace vk::core{class Node;}
namespace vk::render{class Node;}
namespace vk::compute{class Node;}
namespace vk::window{class Node;}
namespace vk::interface{class Data;}
namespace vk::interface{class Texture;}
namespace vk::interface{class Window;}
namespace vk::interface{class Render;}


namespace vk{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node();
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void clean();

  inline vk::Structure* get_vk_struct(){return vk_struct;}
  inline vk::interface::Data* get_vk_data(){return vk_interface_data;}
  inline vk::interface::Texture* get_vk_texture(){return vk_interface_texture;}
  inline vk::interface::Window* get_vk_window(){return vk_interface_window;}
  inline vk::interface::Render* get_vk_render(){return vk_interface_render;}

private:
  //Core
  vk::Structure* vk_struct;
  vk::render::Node* vk_render;
  vk::compute::Node* vk_compute;
  vk::core::Node* vk_core;
  vk::window::Node* vk_window;

  //Interface
  vk::interface::Data* vk_interface_data;
  vk::interface::Texture* vk_interface_texture;
  vk::interface::Window* vk_interface_window;
  vk::interface::Render* vk_interface_render;
};

}
