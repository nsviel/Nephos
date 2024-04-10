#pragma once

#include <Utility/Specific/Common.h>

namespace eng::render{class Node;}
namespace rnd::edl{class Structure;}
namespace eng::cam{class Manager;}
namespace utl::entity{class Camera;}
namespace utl::element{class Window;}


namespace rnd::edl{

class Shader : public utl::shader::Base
{
public:
  //Contrustor / destructor
  Shader(eng::render::Node* node_render);
  ~Shader();

  //Main function
  void init_shader();
  void update_shader();

  inline rnd::edl::Structure* get_edl_param(){return edl_param;}

private:
  eng::cam::Manager* cam_manager;
  rnd::edl::Structure* edl_param;
  utl::entity::Camera* camera;
  utl::element::Window* utl_window;
};

}
