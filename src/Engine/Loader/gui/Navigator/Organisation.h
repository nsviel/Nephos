#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::io{class Importer;}
namespace ldr::gui{class File;}
namespace ldr::bookmark{class Manager;}
namespace utl::base{class Path;}


namespace ldr::gui{

class Organisation
{
public:
  //Constructor / Destructor
  Organisation(ldr::Node* node_loader);
  ~Organisation();

public:
  //Main function
  void item_organisation(std::vector<std::string>& vec_path);

  //Subfunction
  void insert_file(std::string& path, int& ID);
  void insert_folder(std::string& path, int& ID);

protected:
  ldr::Structure* ldr_struct;
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;

  std::vector<ldr::gui::File> vec_folder;
  std::vector<ldr::gui::File> vec_file;
  std::string default_path;
  ImVector<int> vec_selection;
  bool goto_file_tab = false;
  bool with_bookmark = true;
};

}
