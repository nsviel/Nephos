#pragma once

#include <Utility/Base/Shader/BASE_shader.h>
#include <Utility/Specific/common.h>

namespace eng::render{class Node;}
namespace eng::shader{class EDL_param;}
namespace eng::cam{class Manager;}
namespace utl::entity{class Camera;}
namespace utl::element{class Window;}


namespace eng::shader{

class EDL : public utl::base::BASE_shader
{
public:
  //Contrustor / destructor
  EDL(eng::render::Node* node_render);
  ~EDL();

  //Main function
  void init_shader();
  void update_shader();

  inline eng::shader::EDL_param* get_edl_param(){return edl_param;}

private:
  eng::cam::Manager* cam_manager;
  eng::shader::EDL_param* edl_param;
  utl::entity::Camera* camera;
  utl::element::Window* utl_window;
};

}
