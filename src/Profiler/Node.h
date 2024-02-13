#pragma once

#include <Utility/Specific/common.h>

namespace prf::gui{class Panel;}
namespace prf::vulkan{class Manager;}
namespace prf{class Manager;}


namespace prf{

class Node : public utl::type::Node
{
public:
  Node();
  ~Node();

public:
  //Main function
  void init();
  void gui();

  inline prf::Manager* get_profiler_manager(){return profiler_manager;}
  inline prf::vulkan::Manager* get_vulkan_manager(){return vulkan_manager;}

private:
  prf::gui::Panel* gui_panel;
  prf::vulkan::Manager* vulkan_manager;
  prf::Manager* profiler_manager;
};

}
