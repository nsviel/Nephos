#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::base{class Path;}
namespace ldr::io{class Importer;}
namespace ldr::gui{class File;}
namespace ldr::bookmark{class Manager;}


namespace ldr::gui{

class Navigator
{
public:
  //Constructor / Destructor
  Navigator(ldr::Node* node_loader);
  ~Navigator();

public:
  //Main function
  void draw_navigator(ldr::base::Path& path);

  //Subfunction
  void draw_header(ldr::base::Path& path);
  void draw_file_content(ldr::base::Path& path);
  void draw_bookmark(ldr::gui::File& bookmark);

  //Item function
  virtual void item_filtering(std::vector<std::string>& vec_path){}
  void item_organisation(std::vector<std::string>& vec_path);
  void item_folder(ldr::base::Path& path);
  void item_file(ldr::base::Path& path);
  void item_selection(ldr::base::Path& path);
  virtual void item_operation(){}

protected:
  ldr::Structure* ldr_struct;
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;

  std::vector<ldr::gui::File> vec_folder;
  std::vector<ldr::gui::File> vec_file;
  ImVector<int> vec_selection;
  bool goto_file_tab = false;
  bool with_bookmark = true;
};

}
