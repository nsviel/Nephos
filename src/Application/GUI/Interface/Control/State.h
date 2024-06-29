#pragma once

#include <Utility/Base/Type/Path.h>
#include <vector>
#include <string>

namespace gui{class Node;}
namespace utl::base{class Path;}


namespace gui::interface{

class State
{
public:
  //Constructor / Destructor
  State(gui::Node* gui);
  ~State();

public:
  //Main function
  void save_state();
  void load_state(std::string filename = "");

  //Subfunction
  void update_file_list();

  inline std::vector<std::string> get_vec_file(){return vec_file;}
  inline utl::base::Path* get_current_path(){return &path;}

private:
  std::vector<std::string> vec_file;
  utl::base::Path path;
};

}
