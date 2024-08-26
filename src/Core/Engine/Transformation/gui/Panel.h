#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <memory>
#include <string>
#include <vector>

namespace eng::trf{class Node;}
namespace eng::trf{class IO;}
namespace utl::base{class Element;}
namespace dat::gph{class Selection;}


namespace eng::trf::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(eng::trf::Node* node_transfo, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel(std::shared_ptr<utl::base::Element> element);

  //Subfunction
  void display_loader(std::shared_ptr<utl::base::Element> element);
  void display_path(std::shared_ptr<utl::base::Element> element);
  void display_format(std::shared_ptr<utl::base::Element> element);
  void display_matrix(std::shared_ptr<utl::base::Element> element);
  void item_filtering(std::vector<std::string>& vec_path);
  void item_operation();

private:
  eng::trf::IO* trf_io;
  utl::gui::Navigator* gui_navigator;
  dat::gph::Selection* gph_selection;

  std::string name;
  bool* show_window;
};

}
