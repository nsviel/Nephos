#pragma once

#include <Engine/Data/Namespace.h>
#include <Engine/Base/Namespace.h>

#include <Utility/Base/Namespace.h>
#include <Utility/Base/Struct_file.h>
#include <Utility/Function/File/Directory.h>
#include <Utility/Function/File/Zenity.h>
#include <Utility/Function/File/File.h>

#include <string>
#include <vector>

using MyFile = util::base::File;

namespace eng::data{
class Scene;
class Format;
class Node;

class Loader
{
public:
  //Constructor / Destructor
  Loader(eng::data::Node* eng_data);
  ~Loader();

public:
  //Main functions
  eng::structure::Object* load_object(std::string path);
  std::vector<eng::structure::Object*> load_objects(std::vector<std::string> path);
  void load_by_zenity();

  //Subfunctions
  void transfert_data(eng::structure::Object* object, MyFile* file_data);

private:
  eng::data::Format* eng_format;
  eng::data::Scene* eng_scene;

  std::string path_current_dir;
};

}
