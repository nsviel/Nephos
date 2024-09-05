#pragma once

#include <Utility/Base/Class/Node.h>

namespace dat{class Node;}
namespace io{class Node;}
namespace eng{class Node;}

namespace io::imp{class Structure;}
namespace io::imp{class Importer;}
namespace io::imp{class Operation;}
namespace io::imp{class Bookmark;}
namespace io::imp{class Loader;}
namespace io::imp{class Capture;}
namespace io::imp::gui{class Panel;}


namespace io::imp{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(io::Node* node_io);
  ~Node();

public:
  //Main function
  void init();
  void gui();

  inline dat::Node* get_node_data(){return node_data;}
  inline eng::Node* get_node_engine(){return node_engine;}

  inline io::imp::Structure* get_io_struct(){return io_struct;}
  inline io::imp::Importer* get_io_importer(){return io_importer;}
  inline io::imp::Operation* get_io_operation(){return io_operation;}
  inline io::imp::Bookmark* get_io_bookmark(){return io_bookmark;}
  inline io::imp::Loader* get_io_loader(){return io_loader;}
  inline io::imp::Capture* get_io_capture(){return io_capture;}

private:
  //Dependancy
  dat::Node* node_data;
  eng::Node* node_engine;

  //Child
  io::imp::Structure* io_struct;
  io::imp::Importer* io_importer;
  io::imp::Operation* io_operation;
  io::imp::Bookmark* io_bookmark;
  io::imp::Loader* io_loader;
  io::imp::Capture* io_capture;
  io::imp::gui::Panel* gui_import;
};

}
