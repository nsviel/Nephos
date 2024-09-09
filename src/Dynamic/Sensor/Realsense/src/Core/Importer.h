#pragma once

#include <IO/Base/Importer.h>
#include <string>
#include <memory>

namespace rlx{class Node;}
namespace rlx{class Factory;}
namespace io::imp{class Node;}
namespace utl::base{class Element;}


namespace rlx{

class Importer : public io::base::Importer
{
public:
  //Constructor / Destructor
  Importer(rlx::Node* node_realsense);
  ~Importer();

public:
  //Main function
  void insert_importer();

  //Subfunction
  std::shared_ptr<utl::base::Element> capture();

private:
  io::imp::Node* node_importer;

  rlx::Node* node_realsense;
  rlx::Factory* rlx_factory;
};

}
