#pragma once

#include <Utility/Specific/Common.h>

namespace ldr{class Node;}
namespace dat{class Database;}
namespace ldr{class Loader;}
namespace ldr{class Item;}
namespace ldr{class Bookmark;}
namespace ldr{class Format;}
namespace dat{class Set;}
namespace eng::loader{class Item;}
namespace ope{class Transformation;}
namespace ope{class Operation;}
namespace utl::type{class Entity;}


namespace ldr::gui{

class Loader
{
public:
  //Constructor / Destructor
  Loader(ldr::Node* node_loader, bool* show_window);
  ~Loader();

public:
  //Main function
  void run_panel();
  void design_panel();

  //File stuff
  void draw_file();
  void draw_file_header();
  void draw_file_content();

  //Other stuff
  void draw_header();
  void draw_bookmark_button(ldr::Item& item);
  void draw_bookmark_tab();

  //Subfunction
  void operation_selection();
  void operation_selection(string path);
  void operation_entity(utl::type::Entity* entity);

private:
  dat::Database* dat_database;
  ldr::Loader* ldr_loader;
  ldr::Bookmark* ldr_bookmark;
  ldr::Format* ldr_format;
  dat::Set* dat_set;
  ope::Transformation* ope_transform;
  ope::Operation* ope_operation;

  vector<ldr::Item> vec_item_folder;
  vector<ldr::Item> vec_item_file;
  ImVector<int> file_selection;
  string default_dir;
  string current_dir;
  float param_scaling = 1;
  bool param_remove_old = true;
  bool param_centered = true;
  bool goto_file_tab = false;

  string name;
  bool* show_window;
};

}
