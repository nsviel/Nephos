#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
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
  void draw_navigator();

  //Subfunction
  void draw_header();
  void draw_file_content();
  void draw_bookmark(ldr::gui::File& bookmark);

  //Item function
  virtual void item_filtering(std::vector<std::string>& vec_path){}
  void item_organisation(std::vector<std::string>& vec_path);
  void item_folder();
  void item_file();
  void item_selection();
  virtual void item_operation(){}

protected:
  ldr::Structure* ldr_struct;
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;

  std::vector<ldr::gui::File> vec_folder;
  std::vector<ldr::gui::File> vec_file;
  std::string default_dir = "";
  ImVector<int> vec_selection;
  bool goto_file_tab = false;
  bool with_bookmark = true;
};

}
