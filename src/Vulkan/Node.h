#pragma once

#include <Utility/Base/Class/Node.h>

namespace utl{class Node;}
namespace vk{class Structure;}
namespace vk{class Interface;}
namespace vk::core{class Node;}
namespace vk::render{class Node;}
namespace vk::window{class Node;}

namespace vk::gui{class Imgui;}
namespace vk::image{class Texture;}
namespace vk::image{class Screenshot;}
namespace vk::data{class Data;}


namespace vk{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(bool* running);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void clean();

  inline vk::Structure* get_vk_struct(){return vk_struct;}
  inline vk::gui::Imgui* get_vk_imgui(){return vk_imgui;}
  inline vk::image::Texture* get_vk_texture(){return vk_texture;}
  inline vk::image::Screenshot* get_vk_screenshot(){return vk_screenshot;}
  inline vk::Interface* get_vk_interface(){return vk_interface;}
  inline vk::data::Data* get_vk_data(){return vk_data;}

private:
  vk::Structure* vk_struct;
  vk::render::Node* vk_render;
  vk::core::Node* vk_core;
  vk::window::Node* vk_window;

  vk::gui::Imgui* vk_imgui;
  vk::image::Texture* vk_texture;
  vk::image::Screenshot* vk_screenshot;
  vk::Interface* vk_interface;
  vk::data::Data* vk_data;
};

}
