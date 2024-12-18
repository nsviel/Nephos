#include "Localmap.h"

#include "Normal.h"


namespace slam::glyph{

//Constructor / destructor
Localmap::Localmap(){
  //---------------------------

  this->name = "localmap";
  this->color = glm::vec4(66.0f/255.0f, 135.0f/255.0f, 245.0f/255.0f, 1.0f);

  //---------------------------
  this->create_localmap();
  this->create_localcloud();
}
Localmap::~Localmap(){
  //---------------------------

  delete localmap;
  delete localcloud;

  //---------------------------
}

void Localmap::clear(){
  //---------------------------

  localmap->xyz.clear();
  localmap->rgb.clear();

  localcloud->xyz.clear();
  localcloud->rgb.clear();

  //---------------------------
}
void Localmap::create_localmap(){
  this->localmap = new Glyph();
  //---------------------------

  //Create glyph
  localmap->name = "localmap";
  localmap->draw_point_size = 1;
  localmap->draw_type = utl::topology::POINT;
  localmap->unicolor = color;
  localmap->is_visible = false;
  localmap->is_permanent = true;

  //---------------------------
}
void Localmap::create_localcloud(){
  this->localcloud = new Glyph();
  //---------------------------

  //Create glyph
  localcloud->name = "localcloud";
  localcloud->draw_point_size = 1;
  localcloud->draw_type = utl::topology::POINT;
  localcloud->unicolor = color;
  localcloud->is_visible = false;
  localcloud->is_permanent = true;

  //---------------------------
}
void Localmap::update_localmap(slamap* map){
  if(localmap->is_visible){
    //---------------------------

    std::vector<glm::vec3>& gly_xyz = localmap->xyz;
    std::vector<glm::vec4>& gly_rgb = localmap->rgb;

    gly_xyz.clear();
    gly_rgb.clear();

    for(voxelMap_it it = map->map.begin(); it != map->map.end(); it++){
      std::vector<Eigen::Vector3d>& voxel_xyz = it.value();
      for(int i=0; i<voxel_xyz.size(); i++){
        Eigen::Vector3d& point = voxel_xyz[i];

        glm::vec3 xyz = glm::vec3(point(0), point(1), point(2));
        glm::vec4 rgb = localmap->unicolor;

        gly_xyz.push_back(xyz);
        gly_rgb.push_back(rgb);
      }
    }

    //---------------------------
  }
}
void Localmap::update_localcloud(slamap* map){
  if(localcloud->is_visible){
    //---------------------------

    std::vector<glm::vec3>& gly_xyz = localcloud->xyz;
    std::vector<glm::vec4>& gly_rgb = localcloud->rgb;

    gly_xyz.clear();
    gly_rgb.clear();

    for(cloudMap_it it = map->cloud.begin(); it != map->cloud.end(); it++){
      std::vector<Eigen::Vector4d>& voxel_xyz = it.value();
      for(int i=0; i<voxel_xyz.size(); i++){
        Eigen::Vector4d& point = voxel_xyz[i];

        glm::vec3 xyz = glm::vec3(point(0), point(1), point(2));
        glm::vec4 rgb = localcloud->unicolor;

        gly_xyz.push_back(xyz);
        gly_rgb.push_back(rgb);
      }
    }

    //---------------------------
  }
}

}
