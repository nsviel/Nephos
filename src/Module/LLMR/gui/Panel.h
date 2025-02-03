#pragma once

#include <memory>
#include <string>

namespace llmr{class Node;}
namespace llmr{class Interface;}
namespace dat::gph{class Selection;}
namespace dat::base{class Entity;}
namespace utl::gui::widget{class Terminal;}


namespace llmr::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(llmr::Node* node_llmr, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel(dat::base::Entity& entity);

  //Subfunction
  void prompt_input(dat::base::Entity& entity);

private:
  utl::gui::widget::Terminal* utl_terminal;
  dat::gph::Selection* gph_selection;
  llmr::Interface* llmr_interface;

  std::string name;
  bool* show_window;
};

}
