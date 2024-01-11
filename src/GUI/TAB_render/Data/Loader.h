#pragma once

#include "Item.h"

#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Tab/Namespace.h>
#include <Engine/Scene/Namespace.h>
#include <GUI/GUI_utility/Base/Namespace.h>

class GUI;


namespace gui::rnd::data{

class Loader : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Loader(GUI* gui, bool* show_window, string name);
  ~Loader();

public:
  //Main function
  void design_panel();

  //File stuff
  void draw_file();
  void draw_file_header();
  void draw_file_content();

  //Other stuff
  void draw_bookmark();
  void draw_footer();

  //Subfunction
  void operation_selection();
  void operation_selection(string path);

private:
  eng::scene::Scene* sce_scene;
  eng::scene::Loader* sce_loader;
  eng::ope::Transformation* ope_transform;
  eng::ope::Operation* ope_operation;

  vector<Item> vec_item_folder;
  vector<Item> vec_item_file;
  ImVector<int> file_selection;
  vector<string> vec_bookmark;
  string default_dir;
  string current_dir;
  float param_scaling = 1;
  bool param_remove_old = true;
  bool param_centered = true;
};

}
