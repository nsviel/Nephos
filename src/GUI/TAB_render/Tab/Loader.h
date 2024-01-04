#pragma once

#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Tab/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <GUI/GUI_utility/Base/Namespace.h>

class GUI;


namespace gui::rnd::tab{

class Loader : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Loader(GUI* gui, bool* show_window, string name);
  ~Loader();

public:
  //Main function
  void design_panel();

  //Subfunction
  void draw_header();
  void draw_content();
  void draw_footer();

private:
  eng::data::Loader* eng_loader;

  string current_dir;
  bool remove_old = true;
  float scale = 1;
};

}
