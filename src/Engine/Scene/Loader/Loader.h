#pragma once

#include <Engine/Scene/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Function/File/Directory.h>
#include <Utility/Function/File/Zenity.h>
#include <Utility/Function/File/File.h>

#include <string>
#include <vector>

class Engine;
class VK_engine;

namespace eng::scene{
class Scene;
class Format;
class Node;
class Glyph;


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
  entity::Object* load_object(string path);
  bool is_format_supported(string format);

private:
  Engine* engine;
  VK_engine* vk_engine;
  eng::scene::Glyph* sce_glyph;
  eng::scene::Format* eng_format;

  vector<string> supported_format;
  std::string path_current_dir;
};

}
