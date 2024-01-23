#pragma once

#include <Engine/Data/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Function/File/Directory.h>
#include <Utility/Function/File/Zenity.h>
#include <Utility/Function/File/File.h>

class Engine;

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
  utl::type::Entity* load_entity(std::string path);

  //Subfunctions
  utl::entity::Object* load_object(string path);
  bool is_format_supported(string format);

private:
  Engine* engine;
  eng::scene::Format* sce_format;
  eng::scene::Scene* sce_scene;

  vector<string> supported_format;
  std::string path_current_dir;
};

}
