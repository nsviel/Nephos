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
namespace dat::base{class Entity;}


namespace ldr::gui::exporter{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(ldr::Node* node_loader);
  ~Exporter();

public:
  //Main function
  void draw_header(dat::base::Entity* entity);

  //Header function
  void display_action();
  void display_path();
  void display_format();
  void display_encording();
  void display_option();

  //Subfunction
  void item_filtering(std::vector<std::string>& vec_path);
  void item_update(dat::base::Entity* entity);
  void item_operation();

private:
  ldr::Structure* ldr_struct;
  ldr::io::Exporter* ldr_exporter;
  dat::Selection* dat_selection;
};

}
