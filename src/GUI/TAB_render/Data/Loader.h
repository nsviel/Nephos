#pragma once

#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Tab/Namespace.h>
#include <Engine/Data/Namespace.h>
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

  //Panel
  void draw_header();
  void draw_content();
  void draw_footer();

  //Subfunction
  void operation_load();

private:
  eng::data::Scene* eng_scene;
  eng::data::Loader* eng_loader;
  eng::ope::Transformation* transformManager;

  ImVector<int> file_selection;
  vector<string> bookmark;
  string default_dir;
  string current_dir;
  bool remove_old = true;
  float scale = 1;
};

}
