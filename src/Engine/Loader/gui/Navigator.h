#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr::io{class Importer;}
namespace ldr::gui{class Bookmark;}
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
  void draw_navigator();

  //Subfunction
  void draw_header();
  void draw_file_content();
  void draw_bookmark(ldr::gui::Bookmark& bookmark);
  virtual void operation_selection(){}

  //Item function
  void item_organisation();
  void item_folder();
  void item_file();

private:
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;

  std::vector<ldr::gui::Bookmark> vec_bookmark_folder;
  std::vector<ldr::gui::Bookmark> vec_bookmark_file;
  std::string default_dir;
  std::string current_dir;
  ImVector<int> vec_selection;
  bool goto_file_tab = false;
};

}
