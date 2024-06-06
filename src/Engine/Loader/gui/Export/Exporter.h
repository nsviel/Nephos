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


private:
  ldr::Structure* ldr_struct;
  ldr::io::Exporter* ldr_exporter;
  dat::Selection* dat_selection;
};

}
