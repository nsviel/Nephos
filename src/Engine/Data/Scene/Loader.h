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

namespace eng::scene{
class Scene;
class Format;
class Node;

class Loader
{
public:
  //Constructor / Destructor
  Loader(eng::scene::Node* eng_data);
  ~Loader();

public:
  //Main functions
  eng::data::Object* load_object(std::string path);
  std::vector<eng::data::Object*> load_objects(std::vector<std::string> path);

  //Subfunctions
  void transfert_data(eng::data::Object* object, MyFile* file_data);
  bool check_format_viability(string format);

private:
  eng::scene::Format* eng_format;
  eng::scene::Scene* eng_scene;

  vector<string> accepted_format;
  std::string path_current_dir;
};

}
