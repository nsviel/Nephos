#pragma once

#include <Engine/Scene/Namespace.h>
#include <Utility/Specific/common.h>

namespace eng::scene{


class Bookmark
{
public:
  //Constructor / Destructor
  Bookmark(eng::scene::Node* node_scene);
  ~Bookmark();

public:
  void init();

  inline vector<string> get_vec_bookmark(){return vec_bookmark;}
private:
  vector<string> vec_bookmark;
  string path_file;
};

}
