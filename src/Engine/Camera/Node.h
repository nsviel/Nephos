#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>

class Engine;
namespace eng::cam{class Control;}
namespace eng::cam{class Manager;}
namespace eng::cam::gui{class Control;}


namespace eng::cam{

class Node
{
public:
  Node(Engine* engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void reset();

  inline Engine* get_engine(){return engine;}
  inline utl::element::Window* get_utl_window(){return utl_window;}
  inline eng::cam::Control* get_camera_control(){return cam_control;}
  inline eng::cam::Manager* get_camera_manager(){return cam_manager;}

private:
  Engine* engine;
  utl::element::Window* utl_window;
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;
  eng::cam::gui::Control* gui_control;
};

}
