#pragma once

#include <Utility/Base/Class/Node.h>

namespace prf{class Node;}
namespace app{class Node;}
namespace io{class Node;}
namespace vk{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace prf::monitor{class Tasker;}
namespace thr::task{class Pool;}


namespace sys{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(app::Node* node_app);
  ~Node();

public:
  //Main function
  void init();

private:

};

}
