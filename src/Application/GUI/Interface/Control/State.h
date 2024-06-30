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
  void init();

  //Subfunction
  void save_state();
  void load_state(std::string filename);
  void reload_state();
  void update_file_list();
  int get_idx_current_path();

  inline std::vector<std::string> get_vec_file(){return vec_file;}
  inline utl::base::Path* get_save_path(){return &save_path;}

private:
  std::vector<std::string> vec_file;
  utl::base::Path current_path;
  utl::base::Path save_path;
  bool flag_reload = false;
};

}
