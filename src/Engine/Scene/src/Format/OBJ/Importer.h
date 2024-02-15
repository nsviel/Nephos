#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/File/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>


namespace format::obj{

struct Vertex{
  //---------------------------

  glm::vec3 location;
  glm::vec2 texcoord;
  glm::vec3 normal;

  //---------------------------
};
struct Vertex_ref{
  //---------------------------

  Vertex_ref( int v, int vt, int vn ) : v(v), vt(vt), vn(vn) { }
  int v, vt, vn;

  //---------------------------
};

class Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main function
  utl::media::File* Loader(std::string filePath);

  //Subfunction
  void init_params();
  std::vector<Vertex> get_data_from_file(std::istream& in);
  void parse_mtl(std::string path_obj);
  void fill_data_file(utl::media::File* data, std::vector<Vertex>& vertex_vec);

private:
  utl::media::File* data_out;
  std::string file_mtl;
  std::string file_texture;
  bool is_face;
};

}