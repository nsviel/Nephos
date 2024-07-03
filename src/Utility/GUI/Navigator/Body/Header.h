#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace utl::gui{class Navigator;}
namespace utl::gui::navigator{class Structure;}
namespace utl::base{class Path;}


namespace utl::gui::navigator{

class Header
{
public:
  //Constructor / Destructor
  Header(utl::gui::Navigator* navigator);
  ~Header();

public:
  //Main function
  void draw_header(utl::base::Path& path);

  //Subfunction
  void draw_directory_trail(utl::base::Path& path);
  void draw_directory_add(utl::base::Path& path);

private:
  utl::gui::navigator::Structure* nav_struct;
};

}
