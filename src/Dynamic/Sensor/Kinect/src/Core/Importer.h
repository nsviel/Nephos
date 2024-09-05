#pragma once

#include <IO/Base/Importer.h>
#include <string>
#include <memory>

namespace k4n{class Node;}
namespace k4n{class Factory;}
namespace io::imp{class Node;}
namespace utl::base{class Element;}


namespace k4n{

class Importer : public io::base::Importer
{
public:
  //Constructor / Destructor
  Importer(k4n::Node* node_k4n);
  ~Importer();

public:
  //Main function
  void insert_importer();

  //Subfunction
  std::shared_ptr<utl::base::Element> import(utl::base::Path path);
  std::shared_ptr<utl::base::Element> capture(utl::base::Path path);

private:
  io::imp::Node* node_importer;

  k4n::Node* node_k4n;
  k4n::Factory* k4n_factory;
};

}
