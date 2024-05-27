#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace dat{class Graph;}
namespace ldr::io{class Importer;}
namespace ldr::gui{class Bookmark;}
namespace ldr::bookmark{class Manager;}
namespace dat{class Set;}
namespace ope{class Transformation;}
namespace ope{class Operation;}
namespace dat::base{class Entity;}


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
  dat::Graph* dat_graph;
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;
  dat::Set* dat_set;
  ope::Transformation* ope_transform;
  ope::Operation* ope_operation;

  std::vector<ldr::gui::Bookmark> vec_bookmark_folder;
  std::vector<ldr::gui::Bookmark> vec_bookmark_file;
  std::string default_dir;
  std::string current_dir;
  ImVector<int> vec_selection;
  float param_scaling = 1;
  bool param_remove_old = true;
  bool param_centered = true;
  bool goto_file_tab = false;
};

}
