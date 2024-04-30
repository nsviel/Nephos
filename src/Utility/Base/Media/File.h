#pragma once

#include <Utility/Base/Media/Path.h>
#include <Utility/Base/Type/Topology.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace utl::file{

enum Type{
  DATA = 0,
  DATASET = 1,
};

}

namespace utl::media{

struct File{
  //---------------------------

  int type = utl::file::DATA;
  std::string name = "";
  utl::media::Path path;

  virtual void hello(){}

  //---------------------------
};

}

namespace utl::file{

struct Data : public utl::media::File{
  //---------------------------

  //Info
  int nb_element = 0;
  int draw_type = utl::topology::POINT;

  //Data
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec4> rgb;
  std::vector<glm::vec2> uv;

  std::vector<float> ts;
  std::vector<float> Is;
  std::vector<float> R;
  std::vector<float> A;

  //---------------------------
};

struct Dataset : public utl::media::File{
  //---------------------------

  //Data
  std::vector<utl::file::Data*> vec_data;

  //---------------------------
};

}
