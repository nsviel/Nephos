#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr::gui::navigator{class Structure;}
namespace utl::base{class Path;}


namespace ldr::gui::navigator{

class Header
{
public:
  //Constructor / Destructor
  Header(ldr::gui::navigator::Structure* nav_struct);
  ~Header();

public:
  //Main function
  void draw_header(utl::base::Path& path);

protected:
  ldr::gui::navigator::Structure* nav_struct;
};

}
