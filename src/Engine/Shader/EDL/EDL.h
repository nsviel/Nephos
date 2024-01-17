#pragma once


#include <Engine/Shader/EDL/EDL_param.h>
#include <Engine/Shader/Base/BASE_shader.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

class Engine;


namespace eng::shader{

class EDL : public BASE_shader
{
public:
  //Contrustor / destructor
  EDL(Engine* engine);
  ~EDL();

  //Main function
  void init_shader();
  void update_shader();

  inline eng::shader::EDL_param* get_edl_param(){return edl_param;}

private:
  eng::camera::Manager* cam_manager;
  entity::Camera* camera;
  util::element::Window* utl_window;
  eng::shader::EDL_param* edl_param;
};

}
