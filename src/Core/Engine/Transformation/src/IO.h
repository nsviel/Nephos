#pragma once

#include <vector>
#include <string>

namespace utl::base{class Element;}
namespace dat::base{class Entity;}


namespace eng::trf{

class IO
{
public:
  //Constructor / Destructor
  IO();
  ~IO();

public:
  //Main function
  void load_transformation(dat::base::Entity* entity);
  void load_transformation(utl::base::Element* element, std::string path);
  void save_transformation(utl::base::Element* element, std::string path);

  //Subfunction
  void init_path();
  void update_path(utl::base::Element* element);
  std::vector<std::string> get_supported_format();

private:
  utl::base::Path path;
};

}
