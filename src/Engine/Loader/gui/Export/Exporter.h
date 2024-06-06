#pragma once

#include <Loader/gui/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::io{class Exporter;}
namespace ldr::gui{class File;}
namespace dat{class Selection;}


namespace ldr::gui::exporter{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(ldr::Node* node_loader);
  ~Exporter();

public:
  //Main function
  void design_header();

  //Header function
  void display_action();
  void display_path();
  void display_format();
  void display_encording();

  //Subfunction
  void item_filtering(std::vector<std::string>& vec_path);
  void item_update();
  void item_operation();

private:
  ldr::Structure* ldr_struct;
  ldr::io::Exporter* ldr_exporter;
  dat::Selection* dat_selection;
};

}
