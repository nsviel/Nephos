#pragma once

#include <Engine/Data/Namespace.h>
#include <Engine/Base/Namespace.h>

#include <Utility/UTL_base/Namespace.h>
#include <Utility/UTL_base/Struct_file.h>
#include <Utility/UTL_file/Directory.h>
#include <Utility/UTL_file/Zenity.h>
#include <Utility/UTL_file/File.h>

#include <string>
#include <vector>

class ENG_format;

using MyFile = data::File;


namespace eng::data{
class Scene;


class ENG_loader
{
public:
  //Constructor / Destructor
  ENG_loader(eng::data::Node* eng_data);
  ~ENG_loader();

public:
  //Main functions
  eng::structure::Object* load_object(std::string path);
  std::vector<eng::structure::Object*> load_objects(std::vector<std::string> path);
  void load_by_zenity();

  //Subfunctions
  void transfert_data(eng::structure::Object* object, MyFile* file_data);

private:
  ENG_format* eng_format;
  eng::data::Scene* eng_scene;

  std::string path_current_dir;
  int ID;
};

}
