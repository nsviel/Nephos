#pragma once

#include <vector>
#include <string>

namespace ldr{class Node;}
namespace ldr{class Structure;}


namespace ldr::io{

class Transformation
{
public:
  //Constructor / Destructor
  Transformation(ldr::Node* node_loader);
  ~Transformation();

public:
  //Main function
  void load_transformation(utl::base::Element* element, std::string path);
  void save_transformation(utl::base::Element* element, std::string path);

  //Subfunction
  std::vector<std::string> get_supported_format();

private:
  ldr::Structure* ldr_struct;
};

}
