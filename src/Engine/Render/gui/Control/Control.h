#pragma once

#include <Utility/Specific/Common.h>

namespace rnd{class Node;}
namespace eng{class Node;}
namespace ope{class Operation;}
namespace rnd::gui{class Wheel;}
namespace sce{class Database;}
namespace sce{class Set;}
namespace cam{class Control;}
namespace cam{class Manager;}


namespace rnd::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(rnd::Node* node_render);
  ~Control();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard_oneAction();
  void control_keyboard_translation();

  //Mouse
  void control_mouse_wheel();

  inline rnd::gui::Wheel* get_gui_wheel(){return gui_wheel;}

private:
  eng::Node* node_engine;
  sce::Database* sce_database;
  sce::Set* sce_set;
  cam::Control* cam_control;
  cam::Manager* cam_manager;
  ope::Operation* ope_operation;
  rnd::gui::Wheel* gui_wheel;
};

}
