#include "Importer.h"


namespace format::obj{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->format = "obj";

  //---------------------------
}
Importer::~Importer(){}

//Main function
utl::file::Entity* Importer::import(utl::file::Path path){
  //---------------------------

  utl::file::Entity* entity = new utl::file::Entity();
  entity->name = utl::fct::info::get_name_from_path(path.data);
  entity->path = path;

  //Init
  this->init_params();

  // Open file and fill path info
  std::ifstream file(path.data);

  // Retrieve file data
  std::vector<Vertex> vertex_vec = get_data_from_file(file);

  //Parse MTL file
  this->parse_mtl(path.data);

  // Fill output format with file data
  this->fill_data_file(entity, vertex_vec);

  //---------------------------
  return entity;
}

//Subfunction
void Importer::init_params(){
  //---------------------------

  this->file_mtl = "";
  this->file_texture = "";

  //---------------------------
}
std::vector<Vertex> Importer::get_data_from_file(std::istream& file){
  //---------------------------

  //Initiate std::vectors
  std::vector<Vertex> vertex_vec;
  std::vector<glm::vec4> xyz(1, glm::vec4( 0, 0, 0, 0 ));
  std::vector<glm::vec3> uv(1, glm::vec3( 0, 0, 0 ));
  std::vector<glm::vec3> Nxyz(1, glm::vec3( 0, 0, 0 ));

  //Read file line by line
  std::string line;
  this->is_face = false;
  while(std::getline(file, line)){
    std::istringstream line_str(line);
    std::string line_type;
    line_str >> line_type;

    // location
    if(line_type == "v"){
      float x = 0, y = 0, z = 0, w = 1;
      line_str >> x >> y >> z >> w;
      xyz.push_back( glm::vec4( x, y, z, w ) );
    }
    // texture
    else if(line_type == "vt"){
      float u = 0, v = 0, w = 0;
      line_str >> u >> v >> w;
      uv.push_back( glm::vec3( u, v, w ) );
    }
    // normal
    else if(line_type == "vn"){
      float i = 0, j = 0, k = 0;
      line_str >> i >> j >> k;
      Nxyz.push_back( glm::normalize( glm::vec3( i, j, k ) ) );
    }
    // polygon
    else if(line_type == "f"){
      this->is_face = true;
      std::vector<Vertex_ref> refs;
      std::string refStr;
      while( line_str >> refStr){
        std::istringstream ref( refStr );
        std::string vStr, vtStr, vnStr;
        std::getline( ref, vStr, '/' );
        std::getline( ref, vtStr, '/' );
        std::getline( ref, vnStr, '/' );
        int v = atoi( vStr.c_str() );
        int vt = atoi( vtStr.c_str() );
        int vn = atoi( vnStr.c_str() );
        v  = (  v >= 0 ?  v : xyz.size() +  v );
        vt = ( vt >= 0 ? vt : uv.size() + vt );
        vn = ( vn >= 0 ? vn : Nxyz.size()   + vn );
        refs.push_back( Vertex_ref( v, vt, vn ) );
      }

      // triangulate, assuming n>3-gons are convex and coplanar
      for( size_t i = 1; i+1 < refs.size(); ++i){
        const Vertex_ref* p[3] = { &refs[0], &refs[i], &refs[i+1] };

        // http://www.opengl.org/wiki/Calculating_a_Surface_Normal
        glm::vec3 U( xyz[ p[1]->v ] - xyz[ p[0]->v ] );
        glm::vec3 V( xyz[ p[2]->v ] - xyz[ p[0]->v ] );
        glm::vec3 faceNormal = glm::normalize( glm::cross( U, V ) );

        for( size_t j = 0; j < 3; ++j){
          Vertex vertex;
          vertex.location = glm::vec3( xyz[ p[j]->v ] );
          vertex.texcoord = glm::vec2( uv[ p[j]->vt ] );
          vertex.normal = ( p[j]->vn != 0 ? Nxyz[ p[j]->vn ] : faceNormal );
          vertex_vec.push_back( vertex );
        }
      }
    }
    //header
    else if(line_type == "mtllib"){
      std::string mtl;
      line_str >> mtl;
      this->file_mtl = mtl;
    }
  }

  if(is_face == false){
    for(int i=0; i<xyz.size(); i++){
      Vertex vertex;
      vertex.location = glm::vec3(xyz[i].x, xyz[i].y, xyz[i].z);
      vertex_vec.push_back( vertex );
    }
  }

  //---------------------------
  return vertex_vec;
}
void Importer::parse_mtl(std::string path_obj){
  if(file_mtl == ""){return;}
  //---------------------------

  // Retrieve mtl file path
  std::string path = utl::fct::info::get_path_from_filepath(path_obj);
  std::string path_mtl = path + file_mtl;

  //Open mtl file
  std::ifstream file(path_mtl);

  //Read mtl data
  std::string line;
  while(std::getline(file, line)){
    std::istringstream line_str(line);
    std::string line_type;
    line_str >> line_type;

    // texture
    if(line_type == "map_Kd" || line_type == "map_Bump"){
      std::string filename_texture;
      line_str >> filename_texture;
      std::string path = path + filename_texture;

      this->file_texture = path;
    }
  }

  //---------------------------
}
void Importer::fill_data_file(utl::file::Entity* data, std::vector<Vertex>& vertex_vec){
  //---------------------------

  if(is_face){
    for(int i=0; i<vertex_vec.size(); i++){
      data->xyz.push_back(vertex_vec[i].location);
      data->Nxyz.push_back(vertex_vec[i].normal);
      data->uv.push_back(vertex_vec[i].texcoord);
    }
    data->draw_type = utl::topology::TRIANGLE;
    data->path_texture = file_texture;
  }else{
    for(int i=0; i<vertex_vec.size(); i++){
      data->xyz.push_back(vertex_vec[i].location);
    }
    data->draw_type = utl::topology::POINT;
  }


  //---------------------------
}

}
