#pragma once

#include <functional>

namespace ldr::gui::navigator{class Structure;}
namespace ldr::gui::navigator{class Header;}
namespace ldr::gui::navigator{class Content;}
namespace utl::base{class Path;}


namespace ldr::gui{

class Navigator
{
public:
  //Constructor / Destructor
  Navigator();
  ~Navigator();

public:
  //Main function
  void draw_navigator(utl::base::Path& path);

  //Subfunction
  void add_fct_item_operation(std::function<void()> func);
  void add_fct_item_icon(std::function<void()> func);

protected:
  ldr::gui::navigator::Structure* nav_struct;
  ldr::gui::navigator::Header* nav_header;
  ldr::gui::navigator::Content* nav_content;
};

}
