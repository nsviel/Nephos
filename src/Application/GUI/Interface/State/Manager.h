#pragma once

#include <Utility/Base/Type/Path.h>
#include <vector>
#include <string>

namespace gui{class Node;}
namespace utl::base{class Path;}


namespace gui::state{

class Manager
{
public:
  //Constructor / Destructor
  Manager(gui::Node* gui);
  ~Manager();

public:
  //Main function
  void init();
  void loop();
  void gui();

  //Subfunction
  void save_state();
  void load_state(std::string filename);
  void reload_state();
  void update_file_list();
  void make_current_default();
  int get_idx_path_current();

  inline std::vector<std::string> get_vec_file(){return vec_file;}
  inline utl::base::Path* get_path_current(){return &path_current;}
  inline utl::base::Path* get_path_save(){return &path_save;}
  inline bool get_is_default(){return path_current.name == path_default.name;}

private:
  std::vector<std::string> vec_file;
  utl::base::Path path_default;
  utl::base::Path path_current;
  utl::base::Path path_save;
  bool flag_reload = false;
};

}
