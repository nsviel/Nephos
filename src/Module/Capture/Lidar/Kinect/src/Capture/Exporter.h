#pragma once

#include <Loader/src/Base/Exporter.h>
#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace eng{class Node;}
namespace dat{class Graph;}


namespace k4n::capture{

class Exporter : public ldr::base::Exporter
{
public:
  //Constructor / Destructor
  Exporter(k4n::Node* node_k4n);
  ~Exporter();

public:
  //Main function

  //Subfunction

private:

};

}
