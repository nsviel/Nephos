#pragma once

#include <Utility/Specific/Common.h>

namespace sce{class Node;}
namespace sce{class Database;}
namespace sce{class Loader;}
namespace sce{class Bookmark;}
namespace sce{class Format;}
namespace sce{class Set;}
namespace eng::loader{class Item;}
namespace ope{class Transformation;}
namespace ope{class Operation;}


namespace sce::gui{

class Loader
{
public:
  //Constructor / Destructor
  Loader(sce::Node* node_scene, bool* show_window);
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
  void draw_bookmark_button(eng::loader::Item& item);
  void draw_bookmark_tab();

  //Subfunction
  void operation_selection();
  void operation_selection(string path);
  void operation_entity(utl::type::Entity* entity);

private:
  sce::Database* sce_database;
  sce::Loader* sce_loader;
  sce::Bookmark* sce_bookmark;
  sce::Format* sce_format;
  sce::Set* sce_set;
  ope::Transformation* ope_transform;
  ope::Operation* ope_operation;

  vector<eng::loader::Item> vec_item_folder;
  vector<eng::loader::Item> vec_item_file;
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
