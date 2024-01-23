#pragma once

#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Tab/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Data/src/Loader/Item.h>
#include <Utility/Base/GUI/Panel.h>

class Engine;


namespace gui::rnd::data{

class Loader : public utl::base::Panel
{
public:
  //Constructor / Destructor
  Loader(Engine* engine, bool* show_window, string name);
  ~Loader();

public:
  //Main function
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
  eng::scene::Scene* sce_scene;
  eng::scene::Loader* sce_loader;
  eng::scene::Bookmark* sce_bookmark;
  ope::src::Transformation* ope_transform;
  ope::src::Operation* ope_operation;

  vector<Item> vec_item_folder;
  vector<Item> vec_item_file;
  ImVector<int> file_selection;
  string default_dir;
  string current_dir;
  float param_scaling = 1;
  bool param_remove_old = true;
  bool param_centered = true;
  bool goto_file_tab = false;
};

}
