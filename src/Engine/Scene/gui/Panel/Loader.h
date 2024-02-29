#pragma once

#include <Utility/Specific/common.h>

class Item;
namespace eng::scene{class Node;}
namespace eng::scene{class Database;}
namespace eng::scene{class Loader;}
namespace eng::scene{class Bookmark;}
namespace eng::scene{class Format;}
namespace eng::scene{class Set;}
namespace ope{class Transformation;}
namespace ope{class Operation;}


namespace eng::scene::gui{

class Loader
{
public:
  //Constructor / Destructor
  Loader(eng::scene::Node* node_scene, bool* show_window);
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
  void draw_bookmark_button(Item& item);
  void draw_bookmark_tab();
  void draw_footer();

  //Subfunction
  void operation_selection();
  void operation_selection(string path);
  void operation_entity(utl::type::Entity* entity);

private:
  eng::scene::Database* sce_database;
  eng::scene::Loader* sce_loader;
  eng::scene::Bookmark* sce_bookmark;
  eng::scene::Format* sce_format;
  eng::scene::Set* sce_set;
  ope::Transformation* ope_transform;
  ope::Operation* ope_operation;

  vector<Item> vec_item_folder;
  vector<Item> vec_item_file;
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
