#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr::gui::navigator{class Structure;}
namespace ldr::gui::navigator{class Organisation;}
namespace ldr::io{class Importer;}
namespace ldr::gui::navigator{class File;}
namespace ldr::bookmark{class Manager;}
namespace utl::base{class Path;}


namespace ldr::gui{

class Navigator
{
public:
  //Constructor / Destructor
  Navigator(ldr::Node* node_loader, bool with_bookmark);
  ~Navigator();

public:
  //Main function
  void draw_navigator(utl::base::Path& path);

  //Subfunction
  void draw_header(utl::base::Path& path);
  void draw_file_content(utl::base::Path& path);
  void draw_bookmark(ldr::gui::navigator::File& bookmark);

  //Item function
  void item_folder(utl::base::Path& path);
  void item_file(utl::base::Path& path);
  void item_selection(utl::base::Path& path);
  void make_selection(ldr::gui::navigator::File& file, bool& already_selected);

  virtual void item_filtering(std::vector<std::string>& vec_path){}
  virtual void item_operation(){}

protected:
  ldr::gui::navigator::Structure* nav_struct;
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;
  ldr::gui::navigator::Organisation* nav_organisation;
};

}
