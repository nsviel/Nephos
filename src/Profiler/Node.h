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

  inline prf::Manager* get_prf_profiler(){return prf_profiler;}
  inline prf::vulkan::Manager* get_prf_vulkan(){return prf_vulkan;}

private:
  prf::gui::Panel* gui_panel;
  prf::vulkan::Manager* prf_vulkan;
  prf::Manager* prf_profiler;
};

}
