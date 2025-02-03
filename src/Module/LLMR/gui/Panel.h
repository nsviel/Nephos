#pragma once

#include <memory>
#include <string>

namespace llmr{class Node;}
namespace dat::gph{class Selection;}
namespace dat::base{class Entity;}
namespace llmr::gui{class Terminal;}


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
  llmr::gui::Terminal* utl_terminal;
  dat::gph::Selection* gph_selection;

  std::string name;
  bool* show_window;
};

}
