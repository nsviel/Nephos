#pragma once

#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Tab/Namespace.h>
#include <Engine/Data/Namespace.h>

class GUI;

namespace gui::rnd::tab{


class Loader
{
public:
  //Constructor / Destructor
  Loader(GUI* gui);
  ~Loader();

public:
  //Main function
  void loader_dialog();
  void loader_panel();

private:
  eng::data::Loader* eng_loader;
};

}
