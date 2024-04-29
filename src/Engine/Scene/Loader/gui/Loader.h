#pragma once

#include <Utility/Specific/Common.h>

namespace scene{class Node;}
namespace scene{class Database;}
namespace scene{class Loader;}
namespace scene{class Bookmark;}
namespace scene{class Format;}
namespace scene{class Set;}
namespace eng::loader{class Item;}
namespace ope{class Transformation;}
namespace ope{class Operation;}


namespace scene::gui{

class Loader
{
public:
  //Constructor / Destructor
  Loader(scene::Node* node_scene, bool* show_window);
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
  scene::Database* sce_database;
  scene::Loader* sce_loader;
  scene::Bookmark* sce_bookmark;
  scene::Format* sce_format;
  scene::Set* sce_set;
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