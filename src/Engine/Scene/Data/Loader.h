#pragma once

#include <Engine/Scene/Namespace.h>
#include <Engine/Base/Namespace.h>

#include <Engine/Base/Namespace.h>
#include <Engine/Base/Namespace.h>
#include <Utility/Function/File/Directory.h>
#include <Utility/Function/File/Zenity.h>
#include <Utility/Function/File/File.h>

#include <string>
#include <vector>

namespace eng::scene{
class Scene;
class Format;
class Node;


class Loader
{
public:
  //Constructor / Destructor
  Loader(eng::scene::Node* node_scene);
  ~Loader();

public:
  //Main functions
  eng::data::Object* load_entity(std::string path);

  //Subfunctions
  eng::data::Object* load_object(string path);
  bool is_format_supported(string format);

private:
  eng::scene::Format* eng_format;

  vector<string> supported_format;
  std::string path_current_dir;
};

}
