#pragma once

#include <Loader/gui/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::io{class Recorder;}
namespace ldr::gui{class File;}
namespace dyn{class Structure;}
namespace dat{class Selection;}


namespace ldr::gui::exporter{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(ldr::Node* node_loader);
  ~Recorder();

public:
  //Main function
  void design_header();

  //Header function
  void display_action();
  void display_path();
  void display_format();

  //Subfunction
  void item_filtering(std::vector<std::string>& vec_path);
  void item_update();
  void item_operation();

private:
  dyn::Structure* dyn_struct;
  ldr::Structure* ldr_struct;
  ldr::io::Recorder* ldr_recorder;
  dat::Selection* dat_selection;
};

}
