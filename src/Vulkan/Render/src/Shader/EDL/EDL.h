#pragma once

#include <Utility/Specific/common.h>

namespace vk{class Node;}
namespace vk::render{class EDL_param;}
namespace eng::cam{class Manager;}
namespace utl::entity{class Camera;}
namespace utl::element{class Window;}


namespace vk::render{

class EDL : public utl::shader::Base
{
public:
  //Contrustor / destructor
  EDL(vk::Node* node_vulkan);
  ~EDL();

  //Main function
  void init_shader();
  void update_shader();

  inline vk::render::EDL_param* get_edl_param(){return edl_param;}

private:
  eng::cam::Manager* cam_manager;
  vk::render::EDL_param* edl_param;
  utl::entity::Camera* camera;
  utl::element::Window* utl_window;
};

}
