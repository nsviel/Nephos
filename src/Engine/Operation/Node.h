#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::ope::gui{class Profiler;}


namespace eng::ope{

class Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* engine);
  ~Node();

public:
  void init();
  void loop();
  void gui();
  void reset();

private:
  eng::ope::gui::Profiler* gui_profiler;

  bool show_profiler;
};

}
