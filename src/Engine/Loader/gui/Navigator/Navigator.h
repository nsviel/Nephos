#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr::io{class Importer;}
namespace ldr::gui{class File;}
namespace ldr::bookmark{class Manager;}


namespace ldr::gui{

class Navigator
{
public:
  //Constructor / Destructor
  Navigator(ldr::Node* node_loader, bool with_bookmark);
  ~Navigator();

public:
  //Main function
  void draw_navigator();

  //Subfunction
  void draw_header();
  void draw_file_content();
  void draw_bookmark(ldr::gui::File& bookmark);

  //Item function
  void item_organisation();
  void item_folder();
  void item_file();
  void item_selection();
  virtual void item_operation(){}

protected:
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;

  std::vector<ldr::gui::File> vec_folder;
  std::vector<ldr::gui::File> vec_file;
  std::string default_dir = "";
  std::string current_dir = "";
  std::string current_path = "";
  ImVector<int> vec_selection;
  bool goto_file_tab = false;
  bool with_bookmark = true;
};

}
